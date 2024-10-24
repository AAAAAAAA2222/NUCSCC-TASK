#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 堆调整函数，调整以i为根的子树，n为子树中节点的数量
void heapify(int arr[], int n, int i) {
    int largest = i; // 初始化最大值为根
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根大，则更新最大值
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 反之
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大值不是根，交换它们，并继续调整
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(int arr[], int n) {
    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 一个个从堆顶取出元素
    for (int i = n - 1; i >= 0; i--) {
        // 将堆顶元素与末尾元素交换
        swap(&arr[0], &arr[i]);

        // 调整剩余元素构成的堆
        heapify(arr, i, 0);
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

    heapSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
