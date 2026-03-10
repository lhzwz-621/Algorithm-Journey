#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>  // std::copy
#include <cstdlib>    // rand

// ==================== 工具函数 ====================
// 打印数组
void sortPrint(const std::vector<int>& a);

// ==================== 排序算法 ====================
// 1. 直接插入排序
void insertSort(std::vector<int>& a);

// 2. 希尔排序
void shellSort(std::vector<int>& a);

// 3. 选择排序
void selectSort(std::vector<int>& a);

// 4. 堆排序
void heapSort(std::vector<int>& a);

// 5. 冒泡排序
void bubbleSort(std::vector<int>& a);

// 6. 快速排序（递归）
void quickSort(std::vector<int>& a, int left, int right);

// 7. 快速排序（非递归）
void quickSortNonR(std::vector<int>& a, int left, int right);

// 8. 归并排序（递归）
void mergeSort(std::vector<int>& a);

// 9. 归并排序（非递归）
void mergeSortNonR(std::vector<int>& a);

// 10. 计数排序
void countSort(std::vector<int>& a);