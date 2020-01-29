#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmp.h"

int resizeLarger(FILE* inptr, FILE* outptr, double factor);
int resizeSmaller(FILE* inptr, FILE* outptr, float factor);

int main(int argc, char* argv[]) {

    // ensure proper usage
    if (argc != 4) {
        printf("Usage: ./refactor_bmp n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // if either the infile or the outfile does not end with .bmp, abort
    if (strstr(infile, ".bmp") == 0) {
        printf("Infile needs to be a .bmp extension.\n");
        return 1;
    } else if (strstr(outfile, ".bmp") == 0) {
        printf("Outfile needs to be a .bmp extension.\n");
        return 1;
    }

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // check if input is valid
    if (!atof(argv[1])) {
        printf("The n must be a float or integer.\n");
        return 4;
    } else if (atof(argv[1]) <= 0 || atof(argv[1]) >= 100) {
        printf("The n must be of type float or integer and larger than zero and smaller or equal to 100. Aborting.\n");
        return 5;
    }

    // input n to multiply image dimensions with
    float n = atof(argv[1]);

    // resizing the picture in partitioned function alloted for each type of resizing
    if (n >= 1.0) {
        if (resizeLarger(inptr, outptr, n) != 0) {
            printf("An error occurred during the resize process.\n");
            return 6;
        }
    } else if (n < 1.0) {
        if (resizeSmaller(inptr, outptr, n) != 0) {
            printf("An error occurred during the resize process.\n");
            return 6;
        }
    }

    // display rounded n
    printf("Image resized with n: %.4f (rounded).\n", n);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's not all
    return 0;
}

int resizeLarger(FILE* inptr, FILE* outptr, double n) {
    // double check the input n
    if (n < 1.00 || n > 100.00) {
        printf("This function can handle only values larger than 0 and smaller than 1.\n");
        return 9;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof (BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof (BITMAPINFOHEADER), 1, inptr);

    int previousHeight = bi.biHeight;
    int previousWidth = bi.biWidth;

    // overwrite the BITMAPINFOHEADER values for biWidth & biHeight 
    //Update header data with multiplier	
    bi.biWidth = ceil(previousWidth * n);
    bi.biHeight = (previousHeight >= 0) ? ceil(previousHeight * n) : floor(previousHeight * n);
    int previousPadding = (4 - (previousWidth * sizeof (RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth * sizeof (RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + newPadding);
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 7;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof (BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER 
    fwrite(&bi, sizeof (BITMAPINFOHEADER), 1, outptr);

    // float that store each vertical step
    float linesHeightf = n;

    // float that store each horizontal step
    float linesWidthf = n;

    // float that stores a vertical location
    float verticalPositionf = 0.00;

    // int that holds a number of skipped lines(vertical)
    int skippedLines = 0;

    // int that holds a size for each vertical step
    int verticalStep = 0;

    for (int i = 0, newBiHeight = ceil(abs(previousHeight) * n); i < newBiHeight; i++) {
        verticalStep = (ceil(verticalPositionf + linesHeightf) - ceil(verticalPositionf));
        // float that stores a horizontal location and reset to zero after next line
        float horizontalPositionf = 0.00;

        for (int j = 0; j < previousWidth; j++) {
            int horizontalStep = (ceil(horizontalPositionf + linesWidthf) - ceil(horizontalPositionf));
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof (RGBTRIPLE), 1, inptr);
            // for each RGBTRIPLE in the original file, write horizontalStep times as much RGBTRIPLEs
            for (int k = 0; k < horizontalStep; k++)
                // write RGB triples to outfile
                fwrite(&triple, sizeof (RGBTRIPLE), 1, outptr);
            horizontalPositionf += linesWidthf;
        }

        // skip over newPadding in the original image, if any
        fseek(inptr, previousPadding, SEEK_CUR);

        // add the newPadding back
        for (int k = 0; k < newPadding; k++)
            fputc(0x00, outptr);

        // size of each line in bytes
        int previousLineInBytes = ((previousWidth * sizeof (RGBTRIPLE)) + previousPadding);

        if (skippedLines <= verticalStep) {
            // skip one line back
            fseek(inptr, -previousLineInBytes, SEEK_CUR);
            skippedLines++;
        }

        if (skippedLines == verticalStep) {
            skippedLines = 0;
            fseek(inptr, previousLineInBytes, SEEK_CUR);
        }

        if (skippedLines == 0)
            verticalPositionf += linesHeightf;
    }
    return 0;
}

/*
 * Resizes the input image smaller with a given n larger than 0 and smaller than 1 and stores it in another file.
 */
int resizeSmaller(FILE* inptr, FILE* outptr, float n) {
    // recheck
    if (n <= 0.00 || n >= 1.00) {
        printf("This function can handle only values larger than 0 and smaller than 1.\n");
        return 10;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof (BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof (BITMAPINFOHEADER), 1, inptr);

    int previousHeight = bi.biHeight;
    int previousWidth = bi.biWidth;

    // overwrite the BITMAPINFOHEADER values for biWidth & biHeight   
    //Update header data with multiplier
    bi.biWidth = ceil(previousWidth * n);
    bi.biHeight = (previousHeight >= 0) ? ceil(previousHeight * n) : floor(previousHeight * n);
    int previousPadding = (4 - (previousWidth * sizeof (RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth * sizeof (RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + newPadding);
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 7;
    }

    // write outfile's BITMAPFILEHEADER using the new values we assigned earlier
    fwrite(&bf, sizeof (BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER using the new values we assigned earlier
    fwrite(&bi, sizeof (BITMAPINFOHEADER), 1, outptr);

    for (int j = 0, originalBiHeightWithAbs = abs(previousHeight); j < originalBiHeightWithAbs; j++) {
        if (ceil(j * n) != ceil((j + 1) * n)) {
            for (int i = 0; i < previousWidth; i++) {
                if (ceil(i * n) != ceil((i + 1) * n)) {
                    // temporary storage for triple
                    RGBTRIPLE triple;
                    // read one pixel (aka 1 RGBTRIPLE) from the infile
                    fread(&triple, sizeof (RGBTRIPLE), 1, inptr);
                    // write one pixel to the outfile
                    fwrite(&triple, sizeof (RGBTRIPLE), 1, outptr);
                } else if (ceil(i * n) == ceil((i + 1) * n)) {
                    // skip over 1 pixel
                    fseek(inptr, sizeof (RGBTRIPLE), SEEK_CUR);
                }
            }

            // skip over the newPadding in the infile
            fseek(inptr, previousPadding, SEEK_CUR);

            // add it back to the outfile
            for (int k = 0; k < newPadding; k++)
                fputc(0x00, outptr);
        } else if (ceil(j * n) == ceil((j + 1) * n)) {
            fseek(inptr, (sizeof (RGBTRIPLE) * abs(previousWidth) + previousPadding), SEEK_CUR);
        }
    }
    // no errors occurred during the resize process
    return 0;
}