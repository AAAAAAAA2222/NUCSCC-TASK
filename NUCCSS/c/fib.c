#define _CRT_SECURE_NO_WARNINGS  1
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include<time.h>
#include<stdio.h>

typedef union data
{
    int i;
    float f;
}Data;
Data* ge_random_arr(int min, int max, int size, char type)
{

    ((unsigned int)time(NULL));

    Data* arr = (union data*)malloc(size * sizeof(union data));//��̬���鴴��

    switch (type)
    {
    case 'i':
    { // int����
        int num_i;

        for (int i = 0; i < size; i++)
        {

            num_i = rand() % (max - min + 1) + min;
            arr[i].i = num_i;
        }
        break;
    }
    case 'f':
    {// float����
        float num_f;

        for (int i = 0; i < size; i++)
        {

            num_f = (float)min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * ((float)max - (float)min);
            arr[i].f = num_f;
        }
        break;
    }
    }
    return arr;
}
//����������� ����һ������
union data* get_random_array(int min, int max, int size, int type);

union data* get_random_array_with_seed(int min, int max, int size, int type, unsigned int seed);
//ð������
int bubble_sort(union data* arr, int len, int type);
//����������
int heap_sort(union data* arr, int len, int type);
//쳲�����������
// �ر���л: ChatGPT
// 쳲������ѵĽڵ�
typedef struct FibHeapNode {
    union data key;
    int degree;
    struct FibHeapNode* parent;
    struct FibHeapNode* child;
    struct FibHeapNode* left;
    struct FibHeapNode* right;
    int mark;  // ��ǽڵ��Ƿ�ʧȥ�ӽڵ�
} FibHeapNode;

// 쳲������ѵĽṹ
typedef struct FibHeap {
    FibHeapNode* min;  // ָ����С�ڵ�
    int n;             // ���нڵ������
} FibHeap;

// �����µ�쳲�������
FibHeap* createFibHeap();

// �����µ�쳲������ѽڵ�
FibHeapNode* createFibHeapNode(union data key);

// �ϲ�����쳲������ѵĸ�����
void fibHeapLink(FibHeap* heap, FibHeapNode* y, FibHeapNode* x);

// ��һ���ڵ���뵽쳲�������
void fibHeapInsert(FibHeap* heap, FibHeapNode* node, int type);

// ��ȡ��Сֵ����
FibHeapNode* fibHeapExtractMin(FibHeap* heap, int type);

// �ϲ��ѵĸ�����ȷ��ÿ������Ψһ
void fibHeapConsolidate(FibHeap* heap, int type);

// 쳲�������������
void fibonacciHeapSort(union data* arr, int n, int type);

//�������û���˹�
// ����ֵ Ϊ�˲��Ը�׼һ������������
void bubble_swap(union data* arr, int index_1, int index_2);

void heap_swap(union data* arr, int index_1, int index_2);

// ��������
void heapify(union data* arr, int len, int root, int type);

// �����µ�쳲�������
FibHeap* createFibHeap()
{
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

// �����µ�쳲������ѽڵ�
FibHeapNode* createFibHeapNode(union data key)
{
    FibHeapNode* node = (FibHeapNode*)malloc(sizeof(FibHeapNode));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    return node;
}

// �ϲ�����쳲������ѵĸ�����
void fibHeapLink(FibHeap* heap, FibHeapNode* y, FibHeapNode* x)
{
    // ��y����Ϊx���ӽڵ�
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;

    if (x->child == NULL)
    {
        x->child = y;
        y->left = y->right = y;
    }
    else
    {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
    y->mark = 0;
}

// ��һ���ڵ���뵽쳲�������
void fibHeapInsert(FibHeap* heap, FibHeapNode* node, int type)
{
    if (heap->min == NULL)
    {
        heap->min = node;
    }
    else
    {
        // ���뵽��С�ڵ��Ա�
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;

        // ������С�ڵ� ����ıȽ��漰switch
        switch (type)
        {
        case 0:
            if (node->key.i < heap->min->key.i)
            {
                heap->min = node;
            }
            break;

        case 1:
            if (node->key.f < heap->min->key.f)
            {
                heap->min = node;
            }
            break;
        }
    }
    heap->n++;
}

// ��ȡ��Сֵ����
FibHeapNode* fibHeapExtractMin(FibHeap* heap, int type)
{
    FibHeapNode* z = heap->min;
    if (z != NULL)
    {
        // ����С�ڵ��ÿ���ӽڵ���ӵ���������
        if (z->child != NULL)
        {
            FibHeapNode* child = z->child;
            do
            {
                FibHeapNode* next = child->right;
                child->left = heap->min;
                child->right = heap->min->right;
                heap->min->right->left = child;
                heap->min->right = child;
                child = next;
            } while (child != z->child);
        }

        // �Ƴ���С�ڵ�
        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right)
        {
            heap->min = NULL;
        }
        else
        {
            heap->min = z->right;
            // ������
            fibHeapConsolidate(heap, type); // ��Ҫʵ�ֺϲ���
        }
        heap->n--;
    }
    return z;
}

// �ϲ��ѵĸ�����ȷ��ÿ������Ψһ
void fibHeapConsolidate(FibHeap* heap, int type)
{
    int D = (int)(log(heap->n) / log(2)) + 1;
    //FibHeapNode *A[D];
    // ��̬���� A ���� Windows��Mingw��֧��c99
    FibHeapNode** A = (FibHeapNode**)malloc(D * sizeof(FibHeapNode*));
    //FibHeapNode *A = (FibHeapNode *) malloc(sizeof(FibHeapNode *[D]));

    for (int i = 0; i < D; i++)
    {
        A[i] = NULL;
    }

    FibHeapNode* x = heap->min;
    int numRoots = 0;
    if (x != NULL)
    {
        numRoots++;
        x = x->right;
        while (x != heap->min)
        {
            numRoots++;
            x = x->right;
        }
    }

    switch (type)
    {
    case 1:
        while (numRoots > 0)
        {
            int d = x->degree;
            FibHeapNode* next = x->right;

            while (A[d] != NULL)
            {
                FibHeapNode* y = A[d]; // y��x������ͬ
                if (x->key.i > y->key.i)
                { // ����x��y
                    FibHeapNode* temp = x;
                    x = y;
                    y = temp;
                }
                fibHeapLink(heap, y, x);
                A[d] = NULL;
                d++;
            }

            A[d] = x;
            x = next;
            numRoots--;
        }

        heap->min = NULL;

        for (int i = 0; i < D; i++)
        {
            if (A[i] != NULL)
            {
                if (heap->min == NULL)
                {
                    heap->min = A[i];
                    heap->min->left = heap->min;
                    heap->min->right = heap->min;
                }
                else
                {
                    A[i]->left = heap->min;
                    A[i]->right = heap->min->right;
                    heap->min->right->left = A[i];
                    heap->min->right = A[i];
                    if (A[i]->key.i < heap->min->key.i)
                    {
                        heap->min = A[i];
                    }
                }
            }
        }
        break;

    case 0:
        while (numRoots > 0) {
            int d = x->degree;
            FibHeapNode* next = x->right;

            while (A[d] != NULL) {
                FibHeapNode* y = A[d];  // y��x������ͬ
                if (x->key.f > y->key.f) {  // ����x��y
                    FibHeapNode* temp = x;
                    x = y;
                    y = temp;
                }
                fibHeapLink(heap, y, x);
                A[d] = NULL;
                d++;
            }

            A[d] = x;
            x = next;
            numRoots--;
        }

        heap->min = NULL;

        for (int i = 0; i < D; i++) {
            if (A[i] != NULL) {
                if (heap->min == NULL) {
                    heap->min = A[i];
                    heap->min->left = heap->min;
                    heap->min->right = heap->min;
                }
                else {
                    A[i]->left = heap->min;
                    A[i]->right = heap->min->right;
                    heap->min->right->left = A[i];
                    heap->min->right = A[i];
                    if (A[i]->key.f < heap->min->key.f) {
                        heap->min = A[i];
                    }
                }
            }
        }
        break;
    }
    //a small bug i forgot
    free(A);
}

// 쳲�������������
void fibonacciHeapSort(union data arr[], int n, int type)
{
    FibHeap* heap = createFibHeap();

    // ������Ԫ�ز���쳲�������
    for (int i = 0; i < n; i++)
    {
        FibHeapNode* node = createFibHeapNode(arr[i]);
        fibHeapInsert(heap, node, type);
    }

    // ��ȡ��Сֵ����������
    for (int i = 0; i < n; i++)
    {
        FibHeapNode* minNode = fibHeapExtractMin(heap, type);
        arr[i] = minNode->key; // ������ֱ�ӽ���ָ����ʸ�ֵ ����������践��ֵ
        free(minNode);         // �ͷŽڵ�
    }
}

//��ӡ����
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
    union data* arr = ge_random_arr(0, 100, 1000, 'i');
    int n = 1000;

    printf("Original array: \n");
    printArray((int*)arr, n);

    //ʹ��쳲������ѽ�������
    fibonacciHeapSort(arr, n, 1);

    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}