#include <stdio.h>
#include <stdlib.h>
#include<time.h>
void bubble_sort(int arr[] , int sz)
{
    int i = 0;
    for(;i<sz-1;i++)
    {
        int flag = 1; //假设这一趟已经有序
        int j =0;
        for(;j<sz-1-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                flag = 0;//若发生置换，则代表已经有序
                int spa = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = spa;
            }
        }
        if(flag == 1)
        break;
    }
}
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    int* arr = malloc(1000000 * sizeof(int));
    int n = 1000000;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    printf("Original array: \n");
    printArray(arr, n);

    bubble_sort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
