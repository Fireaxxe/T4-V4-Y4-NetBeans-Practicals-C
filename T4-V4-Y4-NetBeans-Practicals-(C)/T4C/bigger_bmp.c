#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[]) {
    // ensure proper usage
    if (argc != 4) {
        printf("Usage: ./bigger_bmp n infile outfile\n");
        return 1;
    }

    // remember arguments
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (n <= 0 || n > 100) {
        printf("Give a valid multiplier\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof (BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof (BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    //Save old header data
    int previousWidth = bi.biWidth;
    int previousHeight = bi.biHeight;

    //Update header data with multiplier
    bi.biWidth = n * bi.biWidth;
    bi.biHeight = n * bi.biHeight;
    int newPadding = (4 - (bi.biWidth * sizeof (RGBTRIPLE)) % 4) % 4;
    int previousPadding = (4 - (previousWidth * sizeof (RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof (RGBTRIPLE) + newPadding);
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof (BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof (BITMAPINFOHEADER), 1, outptr);

    // establish temporary array to hold row information
    RGBTRIPLE buffer[bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(previousWidth); i < biHeight; i++) {
        int placer = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < previousWidth; j++) {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof (RGBTRIPLE), 1, inptr);

            // store in buffer

            for (int a = 0; a < n; a++) {
                buffer[placer] = triple;
                placer++;
            }
        }

        // write pixel to buffer n times
        for (int i = 0; i < n; i++) {
            // write the new scanline
            for (placer = 0; placer < bi.biWidth; placer++) {
                fwrite(&buffer[placer], sizeof (RGBTRIPLE), 1, outptr);
            }

            // write padding to outfile
            for (int m = 0; m < newPadding; m++) {
                fputc(0x00, outptr);
            }
        }
        // skip over padding, if any
        fseek(inptr, previousPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}