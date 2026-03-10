#define  _CRT_SECURE_NO_WARNINGS 1
#include "sort.h"

int main()
{
    std::vector<int> a1 = { 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1 };

    // 每种排序都用同一份数据的拷贝来测试
    auto a2 = a1, a3 = a1, a4 = a1, a5 = a1;
    auto a6 = a1, a7 = a1, a8 = a1, a9 = a1, a10 = a1;

    std::cout << "=== 1. 插入排序 ===" << std::endl;
    insertSort(a1);
    sortPrint(a1);

    std::cout << "=== 2. 希尔排序 ===" << std::endl;
    shellSort(a2);
    sortPrint(a2);

    std::cout << "=== 3. 选择排序 ===" << std::endl;
    selectSort(a3);
    sortPrint(a3);

    std::cout << "=== 4. 堆排序 ===" << std::endl;
    heapSort(a4);
    sortPrint(a4);

    std::cout << "=== 5. 冒泡排序 ===" << std::endl;
    bubbleSort(a5);
    sortPrint(a5);

    std::cout << "=== 6. 快速排序(递归) ===" << std::endl;
    quickSort(a6, 0, static_cast<int>(a6.size()) - 1);
    sortPrint(a6);

    std::cout << "=== 7. 快速排序(非递归) ===" << std::endl;
    quickSortNonR(a7, 0, static_cast<int>(a7.size()) - 1);
    sortPrint(a7);

    std::cout << "=== 8. 归并排序(递归) ===" << std::endl;
    mergeSort(a8);
    sortPrint(a8);

    std::cout << "=== 9. 归并排序(非递归) ===" << std::endl;
    mergeSortNonR(a9);
    sortPrint(a9);

    std::cout << "=== 10. 计数排序 ===" << std::endl;
    countSort(a10);
    sortPrint(a10);

    return 0;
}