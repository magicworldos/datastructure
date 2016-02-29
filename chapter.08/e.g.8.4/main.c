#include <stdio.h>

#define SIZE	(10)

//快速排序
void quick_sort(int *array, int size)
{
	//低指针从头开始
	int low = 0;
	//高指针从尾开始
	int high = size - 1;
	//本趟比较枢纽
	int t = array[0];
	//本趟结束条件
	while (low < high)
	{
		//先从高指针向前找到小于枢纽的元素位置
		while (low < high && array[high] >= t)
		{
			high--;
		}
		//与枢纽位置交换
		array[low] = array[high];
		//再从低指针向后找到大于枢纽的元素位置
		while (low < high && array[low] <= t)
		{
			low++;
		}
		//与枢纽位置交换
		array[high] = array[low];
	}
	//当low和high相等时记录枢纽元素
	array[low] = t;
	//计算前半段数组大小
	int size_low = low;
	//计算后半段数组大小
	int size_high = size - low - 1;
	if (size_low > 1)
	{
		//前半段递归快速排序
		quick_sort(array, size_low);
	}
	if (size_high > 1)
	{
		//后半段递归快速排序
		quick_sort(&array[low + 1], size_high);
	}
}

//显示数组
void display(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(int argc, char **args)
{
	int array[SIZE] =
	{ 5, 3, 7, 2, 9, 8, 1, 0, 6, 4 };
	display(array, SIZE);
	quick_sort(array, SIZE);
	display(array, SIZE);

	return 0;
}

