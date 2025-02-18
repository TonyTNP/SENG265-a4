/** @file q_array_rotate.c
 *  @brief Submission program for Lab 04.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Ashton M.
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */


#define MAX_SIZE 10

void rotate(int num, int arr[], int size);

int main()
{
    int i = 0;
    char *sep = "";

    // Declare and initialize an int array arr_1 of size MAX_SIZE with random values
    int arr_1[MAX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Print the content of arr_1 to the console
    printf("Original array:\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");

    // Call rotate() with num = 1
    rotate(1, arr_1, MAX_SIZE);
    sep = ""; // Reset separator
    printf("After rotating by 1:\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");

    // Call rotate() with num = 2
    rotate(2, arr_1, MAX_SIZE);
    sep = ""; // Reset separator
    printf("After rotating by 2:\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");

    // Call rotate() with num = 3 ---> This is my own test
    rotate(3, arr_1, MAX_SIZE);
    sep = ""; // Reset separator
    printf("After rotating by 3:\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");
    //Expected output: 7, 8, 9, 10, 1, 2, 3, 4, 5, 6

    // Call rotate() with num = 9 ---> This is my own test
    rotate(3, arr_1, MAX_SIZE);
    sep = ""; // Reset separator
    printf("After rotating by 9:\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");
    //Expected output: 10, 1, 2, 3, 4, 5, 6, 7, 8, 9,

    return 0;
}

/*
 * Function to rotate the array by num positions
 */
void rotate(int num, int arr[], int size)
{
    int temp[size];
    int i;

    // Compute new positions for each element
    for (i = 0; i < size; i++)
    {
        int new_index = (i - num + size) % size; // Calculate new index with wrap-around
        temp[new_index] = arr[i];
    }

    // Copy the rotated array back to the original array
    for (i = 0; i < size; i++)
    {
        arr[i] = temp[i];
    }
}

/*
 * Design a function rotate(int num, .........) that take a number as a parameter (int num) and any other parameters as required
 * When called, the function will modify arr_1 by moving each of its values to an index lowered by num. If the new index becomes negative, then MAX_SIZE is added to get the correct index
 * For example, if num = 2, then a number at index 4 is moved to index 2 (4 - num) and a number at index 1 is moved to index 9(1 - num + MAX_SIZE)
 * Another example, if at the start, arr_1 is {2,4,6,8,1,5},
 * calling arr_1 with num = 2 should change arr_1 to {6,8,1,5,2,4}
 */
