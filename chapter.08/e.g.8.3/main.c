#include <stdio.h>

#define SIZE	(10)

//冒泡排序
void bubble_sort(int array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			//将较大的值向右交换
			if (array[j] > array[j + 1])
			{
				int t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}
}

//冒泡排序
void bubble_sort2(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int ind = -1;
		int t = -1;
		for (int j = 0; j < size - i; j++)
		{
			//找到本趟的最大值
			if (array[j] > t)
			{
				t = array[j];
				//记录最大值的位置
				ind = j;
			}
		}
		//交换最大值的位置
		t = array[size - i - 1];
		array[size - i - 1] = array[ind];
		array[ind] = t;
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
	{ 9, 3, 1, 2, 5, 8, 7, 0, 6, 4 };
	display(array, SIZE);
	bubble_sort2(array, SIZE);
	display(array, SIZE);

	int array2[SIZE] =
	{ 9, 3, 1, 2, 5, 8, 7, 0, 6, 4 };
	display(array2, SIZE);
	bubble_sort2(array2, SIZE);
	display(array2, SIZE);

	return 0;
}

