#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define SIZE 10000000 // Max Size of array

int findMax(int *arr, int size)
{
    int Max = arr[0];
    //chunksize 1000
    #pragma omp parallel for reduction(max:Max) schedule(static,1000)
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

    omp_set_num_threads(8);
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

// critical is not used bcz it allows only 1 thread at a time to update Max variable
// whixh leads to serial which reduces efficiency as threds to have wait 

//atomic only works for single operaion but in our case we have conditonal statements

//in reduction each thread gets its own copy of Max variable causes no waiting or locking
//at the end it automaticaly merges all values of Max in final result


// dynamic is not used as it assigns part of array when any of thread is free but it adds overhead
// for threads coordination it is best to when irregular work loads
// in our case finding max each iteration takes aproximately same time so no need to use dynamic