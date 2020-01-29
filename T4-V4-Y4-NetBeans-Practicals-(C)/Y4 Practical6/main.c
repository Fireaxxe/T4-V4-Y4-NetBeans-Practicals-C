/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Cotsios
 *
 * Created on February 28, 2018, 12:27 PM
 */

#include <stdio.h>
#include <stdlib.h>

void copy_array(double array_arr[], double copyArray1[], int size) {
    int i;
    //Part 1
    //read data from array_arr
    for (i = 0; i < size; i++) {
        &array_arr[i];
    }
    //print array_arr
    for (i = 0; i < size; i++) {
        printf("Original array elements are: %f\n", array_arr[i]);
    }
    //copy data from array_arr to copyArray2
    for (i = 0; i < size; i++) {
        copyArray1[i] = array_arr[i];
        printf("Copy array elements are:  %f\n", copyArray1[i]);
    }
}

void copy_ptr(double *array_arr, double *copyArray2, int size) {
    double *array_ptr = array_arr; //pointer to array
    double *copyArray2_ptr = copyArray2; //pointer to copyArray2
    double *end_ptr;
    //Part2
    int i;
    for (i = 0; i < size; i++) {
        (array_ptr + i);
    }

    //pointer to last element of array_arr
    end_ptr = &array_arr[size - 1];

    //run loop till array_ptr exists in array memory range
    while (array_ptr <= end_ptr) {
        *copyArray2_ptr = *array_ptr;

        //increment array_ptr and copyArray2_ptr
        array_ptr++;
        copyArray2_ptr++;
    }

    //print array_arr and copyArray2 array after copying
    printf("\nElements of 'array': \n");
    for (i = 0; i < size; i++) {
        printf("%f\n", array_arr[i]);
    }

    printf("\nElements of copyArray2: \n");
    for (i = 0; i < size; i++) {
        printf("%f\n", copyArray2[i]);
    }

}
double getDif(const double *arr, int size);

//Part4
//sum of 2 one-dimensional arrays into a 3rd array
void add(double *arr, double *arr2, int size)
{
    printf("\n");
    double array_arr3[4];
    int i;
    for(i = 0; i < size; i++)
    {
        array_arr3[i] = arr[i] + arr2[i];
        printf("Sum of 2 one-dimensional arrays into Array3: %f",arr[i]);
        printf(" + %f", arr2[i]);
        printf(" = %f\n", array_arr3[i]);
    }
}

int main() {

    double array_arr[4] = {1, 2.3, 4.5, 6.7};
    int size = sizeof (array_arr) / sizeof (double);
    double copyArray1[4];
    double copyArray2[4];
    double dif;

    copy_array(array_arr, copyArray1, size);
    copy_ptr(&array_arr, &copyArray2, size);
    //pass pointer to the array as an argument
    dif = getDif(array_arr, size);
    add(&array_arr, &array_arr, size);
    

    //output the returned value
    printf("\nDifference between highest and lowest value from the array is: %f\n", dif);
    return 0;
}

//Part3

double getDif(const double* array, int size) {
    double min = array[0];
    int i;
    double dif;
    double max = array[0];

    for (i = 0; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }

    for (i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    dif = max - min;
    return dif;
}






