#define  _CRT_SECURE_NO_WARNINGS 1
#include "sort.h"

// ============================================================
//  工具函数
// ============================================================

// 打印数组内容，用 "->" 连接
void sortPrint(const std::vector<int>& a)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        std::cout << a[i];
        if (i + 1 < a.size())
            std::cout << "->";
    }
    std::cout << "\n";
}

// ============================================================
//  三数取中：在 left / mid / right 三个位置中
//  选出值处于中间大小的那个下标，作为快排的基准
//  目的：避免在近乎有序的数组上退化为 O(n²)
// ============================================================
static int medianOfThree(std::vector<int>& a, int left, int right)
{
    int mid = left + (right - left) / 2;  // 防溢出写法
    // 把三个数排出大小关系，返回中间值的下标
    if (a[left] < a[mid])
    {
        if (a[mid] < a[right])   return mid;    // left < mid < right
        else if (a[right] < a[left]) return left;  // right < left < mid
        else return right;                          // left < right < mid
    }
    else  // a[left] >= a[mid]
    {
        if (a[left] < a[right])  return left;   // mid < left < right
        else if (a[right] < a[mid]) return mid; // right < mid < left
        else return right;                       // mid < right < left
    }
}

// ============================================================
//  1. 直接插入排序
//  -------------------------------------------------------
//  思想：把数组看成「已排序区 | 未排序区」
//  每次从未排序区取出第一个元素，插入已排序区的正确位置
//
//  时间复杂度：最好 O(n)（已有序）  最坏 O(n²)  平均 O(n²)
//  空间复杂度：O(1)
//  稳定性：稳定
// ============================================================
void insertSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());
    // i 指向「已排序区的最后一个元素」
    // 待插入元素是 a[i+1]
    for (int i = 0; i < n - 1; i++)
    {
        int end = i;            // 已排序区右边界
        int tmp = a[end + 1];   // 取出待插入元素

        // 从右往左扫描已排序区，把比 tmp 大的元素依次右移
        while (end >= 0 && tmp < a[end])
        {
            a[end + 1] = a[end]; // 大元素右移一位
            end--;
        }
        // 找到了 tmp 的位置（end+1），放入
        a[end + 1] = tmp;
    }
}

// ============================================================
//  2. 希尔排序（Shell Sort / 缩小增量排序）
//  -------------------------------------------------------
//  思想：先按较大的间隔 gap 进行「分组插入排序」，
//        让数组宏观上趋近有序；然后逐步缩小 gap，
//        最后 gap=1 时就是普通插入排序，但此时数据
//        已经接近有序，所以非常快。
//
//  gap 序列常用：gap = gap/3 + 1（Knuth 增量）
//  时间复杂度：约 O(n^1.25) ~ O(n^1.5)
//  空间复杂度：O(1)
//  稳定性：不稳定
// ============================================================
void shellSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());
    int gap = n;

    while (gap > 1)
    {
        gap = gap / 3 + 1;  // 缩小增量，保证最后 gap=1

        // 对间隔为 gap 的所有组做插入排序
        // 这里没有「一组一组」地排，而是交替推进，效果一样
        for (int i = 0; i < n - gap; i++)
        {
            int end = i;
            int tmp = a[end + gap];

            while (end >= 0 && tmp < a[end])
            {
                a[end + gap] = a[end]; // 大元素后移 gap 位
                end -= gap;
            }
            a[end + gap] = tmp;
        }
    }
}

// ============================================================
//  3. 选择排序
//  -------------------------------------------------------
//  思想：每一趟从未排序区中选出最小值（同时也选最大值，
//        双向优化），放到正确的位置。
//
//  时间复杂度：O(n²)（任何情况）
//  空间复杂度：O(1)
//  稳定性：不稳定
// ============================================================
void selectSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());
    int left = 0, right = n - 1;

    while (left < right)
    {
        int minIdx = left, maxIdx = left;

        // 在 [left, right] 中同时找最小和最大
        for (int i = left + 1; i <= right; i++)
        {
            if (a[i] < a[minIdx]) minIdx = i;
            if (a[i] > a[maxIdx]) maxIdx = i;
        }

        std::swap(a[left], a[minIdx]); // 最小值放到最左

        // 注意：如果最大值恰好在 left 位置，经过上面的 swap
        // 最大值被换到了 minIdx 的位置，需要修正
        if (maxIdx == left)
            maxIdx = minIdx;

        std::swap(a[right], a[maxIdx]); // 最大值放到最右

        left++;
        right--;
    }
}

// ============================================================
//  4. 堆排序
//  -------------------------------------------------------
//  思想：
//    ① 建大根堆 —— 从最后一个非叶子节点开始向下调整
//    ② 排序 —— 每次把堆顶（最大值）和末尾交换，
//       堆大小减 1，再对堆顶做向下调整
//
//  时间复杂度：O(n log n)（任何情况）
//  空间复杂度：O(1)
//  稳定性：不稳定
// ============================================================

// 向下调整（大根堆）：把 parent 位置的元素"沉"到合适位置
static void siftDown(std::vector<int>& a, int parent, int heapSize)
{
    int child = parent * 2 + 1; // 左孩子

    while (child < heapSize)
    {
        // 选出较大的孩子
        if (child + 1 < heapSize && a[child + 1] > a[child])
            child++;

        // 如果孩子比父亲大，交换并继续下沉
        if (a[child] > a[parent])
        {
            std::swap(a[child], a[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break; // 已满足堆性质
        }
    }
}

void heapSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());

    // ① 建大根堆：从最后一个非叶子节点 (n-1-1)/2 开始
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        siftDown(a, i, n);
    }

    // ② 排序：依次把堆顶换到末尾
    for (int end = n - 1; end > 0; end--)
    {
        std::swap(a[0], a[end]);
        siftDown(a, 0, end); // 堆大小缩小
    }
}

// ============================================================
//  5. 冒泡排序
//  -------------------------------------------------------
//  思想：相邻元素两两比较，大的往后"冒泡"，
//        每一趟把当前未排序区的最大值推到末尾。
//
//  时间复杂度：最好 O(n)（已有序+优化）  最坏 O(n²)
//  空间复杂度：O(1)
//  稳定性：稳定
// ============================================================
void bubbleSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false; // 优化：本趟没有交换说明已有序

        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break; // 提前结束
    }
}

// ============================================================
//  6. 快速排序（递归版）
//  -------------------------------------------------------
//  思想（分治）：
//    ① 选基准 key
//    ② 分区（Partition）：把 < key 的放左边，> key 的放右边
//    ③ 递归处理左右两个子区间
//
//  下面提供三种经典 Partition 方法，最终使用 Lomuto 方案
//
//  时间复杂度：平均 O(n log n)  最坏 O(n²)（三数取中可缓解）
//  空间复杂度：O(log n)（递归栈）
//  稳定性：不稳定
// ============================================================

// --------------- Partition 方法 1：Hoare 法 ---------------
// 原始快排思路：左右指针相向而行
//   right 从右往左找比 key 小的
//   left  从左往右找比 key 大的
//   交换后继续，直到 left == right，把 key 放到相遇点
static int hoarePartition(std::vector<int>& a, int left, int right)
{
    int mid = medianOfThree(a, left, right);
    std::swap(a[left], a[mid]);   // 把基准换到最左边

    int keyi = left;              // 基准的下标

    while (left < right)
    {
        // right 先走，找比基准小的
        while (left < right && a[right] >= a[keyi])
            right--;
        // left 再走，找比基准大的
        while (left < right && a[left] <= a[keyi])
            left++;

        std::swap(a[left], a[right]);
    }
    // 相遇后，把基准放到正确位置
    std::swap(a[keyi], a[left]);
    return left; // 返回基准最终位置
}

// --------------- Partition 方法 2：挖坑法 ---------------
// 先把基准值取出来留一个"坑"
//   right 找到小的 → 填到左边坑里，right 变新坑
//   left  找到大的 → 填到右边坑里，left  变新坑
//   最后把基准值填入最后的坑
static int pitDigPartition(std::vector<int>& a, int left, int right)
{
    int mid = medianOfThree(a, left, right);
    std::swap(a[left], a[mid]);

    int key = a[left]; // 保存基准值
    int hole = left;   // 初始坑在最左边

    while (left < right)
    {
        // 右边找比基准小的，填到左坑
        while (left < right && a[right] >= key)
            right--;
        a[hole] = a[right];
        hole = right;

        // 左边找比基准大的，填到右坑
        while (left < right && a[left] <= key)
            left++;
        a[hole] = a[left];
        hole = left;
    }
    a[hole] = key; // 基准值归位
    return hole;
}

// --------------- Partition 方法 3：Lomuto 前后指针法 ---------------
// 用 prev 和 cur 两个指针（都从左往右走）
//   cur 遇到比 key 小的元素 → prev 前进一步，交换 prev 和 cur
//   最终 prev 左边（含 prev）都 ≤ key
static int lomutoPartition(std::vector<int>& a, int left, int right)
{
    int mid = medianOfThree(a, left, right);
    std::swap(a[left], a[mid]);

    int keyi = left;
    int prev = left;
    int cur = left + 1;

    while (cur <= right)
    {
        // cur 找到比 key 小的，prev 前进并交换
        if (a[cur] < a[keyi] && ++prev != cur)
        {
            std::swap(a[cur], a[prev]);
        }
        cur++;
    }
    std::swap(a[keyi], a[prev]); // 基准归位
    return prev;
}

void quickSort(std::vector<int>& a, int left, int right)
{
    if (left >= right)
        return;

    // 小区间优化：元素少时用插入排序，减少递归开销
    if (right - left + 1 < 10)
    {
        // 对子区间 [left, right] 做插入排序
        for (int i = left + 1; i <= right; i++)
        {
            int tmp = a[i];
            int j = i - 1;
            while (j >= left && a[j] > tmp)
            {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = tmp;
        }
        return;
    }

    // 可切换三种 Partition 方法：
    // int pivot = hoarePartition(a, left, right);
    // int pivot = pitDigPartition(a, left, right);
    int pivot = lomutoPartition(a, left, right);

    quickSort(a, left, pivot - 1);  // 递归排左半部分
    quickSort(a, pivot + 1, right); // 递归排右半部分
}

// ============================================================
//  7. 快速排序（非递归版）
//  -------------------------------------------------------
//  用栈模拟递归：每次从栈中取出一个待处理区间 [left, right]，
//  做一次 Partition，再把左右子区间压栈
// ============================================================
void quickSortNonR(std::vector<int>& a, int left, int right)
{
    std::stack<int> st;

    st.push(left);
    st.push(right);

    while (!st.empty())
    {
        // 注意出栈顺序和入栈顺序相反
        int end = st.top();   st.pop();
        int begin = st.top(); st.pop();

        int pivot = lomutoPartition(a, begin, end);

        // 左子区间有效则入栈
        if (begin < pivot - 1)
        {
            st.push(begin);
            st.push(pivot - 1);
        }
        // 右子区间有效则入栈
        if (pivot + 1 < end)
        {
            st.push(pivot + 1);
            st.push(end);
        }
    }
}

// ============================================================
//  8. 归并排序（递归版）
//  -------------------------------------------------------
//  思想（分治）：
//    ① 将数组从中间一分为二
//    ② 递归排序左半部分、右半部分
//    ③ 合并两个有序子数组（用临时数组辅助）
//
//  时间复杂度：O(n log n)（任何情况）
//  空间复杂度：O(n)（临时数组）
//  稳定性：稳定
// ============================================================

// 递归子函数：对 a[left..right] 归并排序
static void _mergeSort(std::vector<int>& a, std::vector<int>& tmp, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    _mergeSort(a, tmp, left, mid);       // 排左半
    _mergeSort(a, tmp, mid + 1, right);  // 排右半

    // --- 合并两个有序区间 [left, mid] 和 [mid+1, right] ---
    int i = left;           // tmp 的写入位置
    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;

    while (begin1 <= end1 && begin2 <= end2)
    {
        if (a[begin1] <= a[begin2])
            tmp[i++] = a[begin1++];
        else
            tmp[i++] = a[begin2++];
    }
    // 把剩余部分拷贝进 tmp
    while (begin1 <= end1) tmp[i++] = a[begin1++];
    while (begin2 <= end2) tmp[i++] = a[begin2++];

    // 把合并结果拷回原数组
    std::copy(tmp.begin() + left, tmp.begin() + right + 1, a.begin() + left);
}

void mergeSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());
    std::vector<int> tmp(n);
    _mergeSort(a, tmp, 0, n - 1);
}

// ============================================================
//  9. 归并排序（非递归版 / 自底向上）
//  -------------------------------------------------------
//  思想：从 gap=1 开始，每次把相邻的两个长度为 gap 的
//        有序段合并成长度 2*gap 的有序段，gap 不断翻倍
//
//  注意边界：最后一组可能不完整，需要修正 end2
// ============================================================
void mergeSortNonR(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());
    std::vector<int> tmp(n);

    for (int gap = 1; gap < n; gap *= 2)
    {
        for (int i = 0; i < n; i += 2 * gap)
        {
            int begin1 = i, end1 = i + gap - 1;
            int begin2 = i + gap, end2 = i + 2 * gap - 1;

            // 第二组不存在，无需合并
            if (begin2 >= n) break;

            // 第二组不完整，修正右边界
            if (end2 >= n)   end2 = n - 1;

            int j = i;
            while (begin1 <= end1 && begin2 <= end2)
            {
                if (a[begin1] <= a[begin2])
                    tmp[j++] = a[begin1++];
                else
                    tmp[j++] = a[begin2++];
            }
            while (begin1 <= end1) tmp[j++] = a[begin1++];
            while (begin2 <= end2) tmp[j++] = a[begin2++];

            // 拷回原数组
            std::copy(tmp.begin() + i, tmp.begin() + end2 + 1, a.begin() + i);
        }
    }
}

// ============================================================
//  10. 计数排序
//  -------------------------------------------------------
//  思想（非比较排序）：
//    ① 找到数组的最大值和最小值，确定值域范围 range
//    ② 开一个大小为 range 的计数数组 count[]
//    ③ 遍历原数组，统计每个值出现的次数
//    ④ 按照 count[] 依次回写原数组
//
//  时间复杂度：O(n + range)
//  空间复杂度：O(range)
//  适用场景：数据范围集中（range 不大）时非常高效
// ============================================================
void countSort(std::vector<int>& a)
{
    if (a.empty()) return;

    int minVal = *std::min_element(a.begin(), a.end());
    int maxVal = *std::max_element(a.begin(), a.end());
    int range = maxVal - minVal + 1;

    std::vector<int> count(range, 0);

    // 统计每个值的出现次数（减去 minVal 做偏移映射）
    for (int val : a)
    {
        count[val - minVal]++;
    }

    // 按计数回写原数组
    int idx = 0;
    for (int i = 0; i < range; i++)
    {
        while (count[i] > 0)
        {
            a[idx++] = i + minVal;
            count[i]--;
        }
    }
}