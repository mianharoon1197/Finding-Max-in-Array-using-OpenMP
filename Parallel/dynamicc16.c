#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define SIZE 10000000 // Max Size of array

int findMax(int *arr, int size)
{
    int Max = arr[0];
    #pragma omp parallel for reduction(max:Max) schedule(dynamic,10000)
    for (int i = 1; i < size; i++)
    {
       
      //  printf("Thread %d processing index %d, value: %d\n", thread_ID, i, arr[i]);
        if (arr[i] > Max)
        {
            Max = arr[i];
        }
    }
    return Max; // returning max value
}

int main()
{
    //dynamic memory allocation
    int *Array = (int *)malloc(SIZE * sizeof(int));

    int maxNum;
    double start, end, totalTime = 0;

    omp_set_num_threads(16);
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

    
    printf("Average Time: %f\n", totalTime / 10);//finding avg execution time
    free(Array);
    return 0;
}

