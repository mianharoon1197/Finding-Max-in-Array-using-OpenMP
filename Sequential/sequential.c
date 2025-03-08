#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define SIZE 100000 // Max Size of array

int findMax(int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max; // returning max value
}

int main()
{
    int Array[SIZE];

    int maxNum;
    double start, end, totalTime = 0;

    // initializing array with raandom numbers
    for (int i = 0; i < SIZE; i++)
    {
        Array[i] = rand() % 1000;
    }

    // running 10 times
    for (int i = 1; i <= 10; i++)
    {
        start = omp_get_wtime();
        maxNum = findMax(Array, SIZE);
        end = omp_get_wtime();
        double timeTaken = (end - start);//time for each iteration
        printf("Run %d: Max Value = %d, Time Taken = %f seconds\n", i, maxNum, timeTaken);
        totalTime += timeTaken;//total time of all iterations
    }

    printf("Max Number: %d\n", maxNum);
    printf("Average Time: %f\n", totalTime / 10);

    return 0;
}
