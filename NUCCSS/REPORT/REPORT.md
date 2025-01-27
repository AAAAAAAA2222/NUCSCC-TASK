# ***C***ounter ***S***trike      ~~实验报告~~  
撰写人：HLW  
Q：834295215
*** 
### 一、实验项目名称 

​        c语言排序算法优化

### 二、实验目的

​        在虚拟机中安装 Ubuntu 22.04 LTS 操作系统， 在该系统中实现c语言排序算法，并对比不同优化等级下的排序算法性能表现。

### 三、实验任务

##### 1.安装虚拟机

- 在虚拟机中安装 Ubuntu 22.04 LTS 操作系统。
- 配置虚拟机的网络连接，确保可以正常联网。

#####    2.**安装 C 语言编译器：**

- 安装最新版本的 gcc（可通过 PPA 安装最新稳定版）。
- 验证编译器安装成功，并确保其正常工作。

#####    3.**实现排序算法：**

- 使用 C 语言手动实现以下排序算法：冒泡排序、基础堆排序以及斐波那契堆排序，不调用任何库函数。
- 运行测试代码，确认各排序算法的正确性。

#####    4.**生成测试数据：**

- 编写代码或脚本自动生成测试数据（随机生成浮点数或整数）。
- 测试数据应覆盖不同规模的数据集，其中必须包含至少 100 000 条数据的排序任务。

#####    5.**编译与性能测试：**

- 使用不同等级的 gcc 编译优化选项（如 -O0, -O1, -O2, -O3, -Ofast 等）对冒泡排序和堆排序代码进行编译。
- 记录各优化等级下的排序算法性能表现（如执行时间和资源占用）。

#####    6.**数据记录与可视化：**

- 收集每个编译等级的运行结果和性能数据。
- 分析算法的时间复杂度，并将其与实验数据进行对比。
- 将数据记录在 CSV 或其他格式文件中。
- 使用 Python、MATLAB 等工具绘制矢量图，展示实验结论。

### 四、主要仪器设备及耗材

* PC，Windows11，VMware，Ubuntu22.04，vscode
   
### 五、**实验步骤**  
##  正式开始
#### 实验环境搭建  
1.下载VMware和ubuntu 系统镜像  
![](https://www.helloimg.com/i/2024/10/25/671b0615c7f55.png)  
![](https://www.helloimg.com/i/2024/10/25/671b06163f853.png)  

2.配置ubuntu  
![](https://www.helloimg.com/i/2024/10/25/671b061db8d70.png)  
![](https://www.helloimg.com/i/2024/10/25/671b06165abc4.png)

3.配置gcc  
![](https://www.helloimg.com/i/2024/10/25/671b0615f2cee.png)  

4.在Firefox中官网下载vscode  
![](https://www.helloimg.com/i/2024/10/25/671b061701a95.png)

5.在vscode中搭建编译c语言环境  
  1)配置task.json
![](https://www.helloimg.com/i/2024/10/25/671b061e21306.png)  
![](https://www.helloimg.com/i/2024/10/25/671b061e2f3a1.png)  

  2）配置launch.json
![](https://www.helloimg.com/i/2024/10/25/671b061e5c4cb.png)
![](https://www.helloimg.com/i/2024/10/25/671b061e67a25.png)
  
#### 实现排序算法  
1.**冒泡排序**    
```c
#include <stdio.h>
#include <stdlib.h>
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

```

2.**基础堆排序**  

```c
#include <stdio.h>
#include <stdlib.h>

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
	

```
3.**Fibonacci堆排序**  

 ***注：若用gcc等编译器由于链接器找不到相应的库，必须手动加上*** ```gcc -o program program.c -lm```  
```c
#include <stdlib.h>
#include <limits.h>
#include<stdio.h>
#include <math.h>
#include<time.h>


typedef struct FibHeapNode {
    int key;
    int degree;
    struct FibHeapNode* parent;
    struct FibHeapNode* child;
    struct FibHeapNode* left;
    struct FibHeapNode* right;
    int mark;  // 标记节点是否失去子节点
} FibHeapNode;

// 斐波那契堆的结构
typedef struct FibHeap {
    FibHeapNode* min;  // 指向最小节点
    int n;             // 堆中节点的总数
} FibHeap;

FibHeap* createFibHeap();

FibHeapNode* createFibHeapNode(int key);

void fibHeapLink(FibHeap* heap, FibHeapNode* y, FibHeapNode* x);

void fibHeapInsert(FibHeap* heap, FibHeapNode* node);

FibHeapNode* fibHeapExtractMin(FibHeap* heap);

void fibHeapConsolidate(FibHeap* heap);

void fibonacciHeapSort(int* arr, int n);

void bubble_swap(int* arr, int index_1, int index_2);

void heap_swap(int* arr, int index_1, int index_2);

void heapify(int* arr, int len, int root);
FibHeap* createFibHeap()
{
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

// 创建新的斐波那契堆节点
FibHeapNode* createFibHeapNode(int key)
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

// 合并两个斐波那契堆的根链表
void fibHeapLink(FibHeap* heap, FibHeapNode* y, FibHeapNode* x)
{
    // 将y链接为x的子节点
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

// 将一个节点插入到斐波那契堆
void fibHeapInsert(FibHeap* heap, FibHeapNode* node)
{
    if (heap->min == NULL)
    {
        heap->min = node;
    }
    else
    {
        // 插入到最小节点旁边
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;

        // 更新最小节点 这里的比较涉及switch
        

        
            if (node->key < heap->min->key)
            {
                heap->min = node;
            }
           
        
    }
    heap->n++;
}

// 提取最小值操作
FibHeapNode* fibHeapExtractMin(FibHeap* heap)
{
    FibHeapNode* z = heap->min;
    if (z != NULL)
    {
        // 将最小节点的每个子节点添加到根链表中
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

        // 移除最小节点
        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right)
        {
            heap->min = NULL;
        }
        else
        {
            heap->min = z->right;
            // 调整堆
            fibHeapConsolidate(heap); // 需要实现合并堆
        }
        heap->n--;
    }
    return z;
}

// 合并堆的根链表，确保每个度数唯一
void fibHeapConsolidate(FibHeap* heap)
{
    int D = (int)(log(heap->n) / log(2)) + 1;
    //FibHeapNode *A[D];
   
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

   
        while (numRoots > 0)
        {
            int d = x->degree;
            FibHeapNode* next = x->right;

            while (A[d] != NULL)
            {
                FibHeapNode* y = A[d]; // y与x度数相同
                if (x->key > y->key)
                { // 交换x与y
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
                    if (A[i]->key < heap->min->key)
                    {
                        heap->min = A[i];
                    }
                }
            }
        }
       
    
    //a small bug i forgot
    free(A);
}

// 斐波那契堆排序函数
void fibonacciHeapSort(int arr[], int n)
{
    FibHeap* heap = createFibHeap();

    // 将所有元素插入斐波那契堆
    for (int i = 0; i < n; i++)
    {
        FibHeapNode* node = createFibHeapNode(arr[i]);
        fibHeapInsert(heap, node);
    }

    // 提取最小值，进行排序
    for (int i = 0; i < n; i++)
    {
        FibHeapNode* minNode = fibHeapExtractMin(heap);
        arr[i] = minNode->key; // 这里是直接进行指针访问赋值 因此排序无需返回值
        free(minNode);         // 释放节点
    }
}


// 打印数组
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
    int* arr = malloc(10000 * sizeof(int));
    int n = 10000;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    printf("Original array: \n");
    printArray(arr, n);

    // 使用斐波那契堆进行排序
    fibonacciHeapSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}

```
#### **生成测试数据**  
```c


    #include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef union type
{
	int i;
	float f;
}Type;
 Type* ge_random_arr(int min, int max, int size, char type)
{
     
    ((unsigned int)time(NULL)); 
    
     Type* arr = (union data*)malloc(size * sizeof(union type));//动态数组创建

    switch (type)
    {
    case 'i':
    { // int类型
        int num_i;

        for (int i = 0; i < size; i++)
        {

            num_i = rand() % (max - min + 1) + min;
            arr[i].i = num_i;
        }
        break;
    }
    case 'f':
    {// float类型
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

```

#### ***编译与性能测试***  
1.编写测试脚本(遍历所有gcc优化可选项目)
![](https://www.helloimg.com/i/2024/10/25/671b061e65a63.png)  
![](https://www.helloimg.com/i/2024/10/25/671b061e57e67.png)  

2.记录各优化等级下的排序算法性能表现（执行时间）
1)bubble **(注 bubble排序性能过差，懒得等测试运行结束了（也可能是卡死了）我只测试了10000组数据)**  
![](https://www.helloimg.com/i/2024/10/25/671b0803f33a7.png)
2)heap **(1000000组数据)**  
![](https://www.helloimg.com/i/2024/10/25/671b061e57e67.png)  
3)fib_heap **(1000000组数据)**    
![](https://www.helloimg.com/i/2024/10/25/671b0803e4d0e.png)  
  
#### ***数据记录与可视化***  
1.性能数据csv格式  
![](https://www.helloimg.com/i/2024/10/25/671b080331f26.png)  
  
2.不同算法时间复杂度分析  
1) ***冒泡排序***  
冒泡排序的基本思想是重复地遍历待排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来。 
遍历数列的工作是重复进行直到没有再需要交换，也就是说该数列已经排序完成。  

时间复杂度：  
最好情况：O(n)，当输入的数列已经是有序的，冒泡排序只需进行一轮比较即可完成排序。  
平均情况与最坏情况：O(n^2)，当输入的数列是逆序或随机的，冒泡排序需要进行多轮比较和交换。  
2) ***堆排序***  
堆排序利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：  
即子结点的键值或索引总是小于（或者大于）它的父节点。  

时间复杂度:  
堆排序的时间复杂度总是O(n log n)，无论是最好、平均还是最坏情况。这是因为构建最大堆需要O(n)时间，  
而从堆中提取最大元素并重建堆需要O(log n)时间，这个过程需要重复n次。  
3) ***斐波那契堆排序***  
斐波那契堆是一种特殊的堆结构，它具有非常高效的合并操作和最小元素提取操作。  
斐波那契堆排序通常不是直接用于排序，而是用于优先队列操作。  

时间复杂度:  
斐波那契堆的插入操作的时间复杂度是O(1)，合并（union）操作的时间复杂度是O(1)，  
最小元素提取操作的时间复杂度是O(log n)，因此，如果使用斐波那契堆进行排序，总体的时间复杂度是O(n log n)。  
#### ***绘制矢量图***  
```python
import matplotlib.pyplot as plt
import pandas as pd

# 设置字体，确保支持中文
plt.rcParams['font.sans-serif'] = ['Microsoft Yahei']

# 读取Excel文件
df = pd.read_excel('python_data.xlsx')
print(df.head())

# 获取DataFrame的数值数据
data = df.values
print(data)

# 提取三列数据
y1 = data[:, 0:1]
y2 = data[:, 1:2]
y3 = data[:, 2:3]
print("y1\n", y1)
print("y2\n", y2)
print("y3\n", y3)

# 绘制折线图
plt.figure()
plt.plot(y1.flatten(), color='r', marker='+', label='bubble')
plt.plot(y2.flatten(), color='b', marker='o', label='heap')
plt.plot(y3.flatten(), color='g', marker='v', label='fibheap')

# 添加图例、标签和标题
plt.legend()
plt.xlabel('opt')
plt.ylabel('time/s')
plt.title('可视化数据')

# 保存图形为PNG文件
plt.savefig('visualization.png', dpi=300)  # 可以指定dpi以提高图像质量

# 显示图形
plt.show()
```
**如图**  
![](https://www.helloimg.com/i/2024/10/25/671b0803de198.png)  

### **遇到的问题与解决方案**
1.斐波那契堆排序有点复杂，短时间内无法彻底里掌握，故借鉴HowXu的源码+AI  后续打算加深理解并掌握，  
毕竟斐波那契堆排序还是特别快的！  
2.使用python绘制矢量图展示和对比数据 没接触过python 借助AI之力绘制了折线图  
3.我的bubble_sort算法优化很差，导致只能流畅跑1w左右数据， 后续通过AI解决  

### 引用/借鉴（十分感谢）  
>HowXu  
>wwb-cloud  
>向日葵  
>kimi  
>ChatGPT  


## 写在后面的话  
>有点小拖延，加上最近在学其他的内容，而且我看错时间以为27号是deadline 所以23号才开始实验（麻了）  
>时间虽然紧张但是我确实是认真学习并完成实验 **[是对编程的兴趣和对加入NCUSCC的渴望一直激励着我（bushi]**  
>虽然但是，我确实在deadline之前完成了实验，我的编程之路也还在脚下！  




