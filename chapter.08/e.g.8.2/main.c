#include <stdio.h>

#define SIZE	(10)

//子表插入排序
void shell_insert(int array[], int size, int i, int m)
{
	//子表循环
	for (int j = i + m; j < size; j += m)
	{
		//找到插入位置
		if (array[j] < array[j - m])
		{
			//互换
			int t = array[j];
			int k = j - m;
			//后移
			for (; k >= 0 && array[k] > t; k -= m)
			{
				array[k + m] = array[k];
			}
			array[k + m] = t;
		}
	}
}

//希尔排序
void shell_sort(int *array, int size)
{
	//半步长递增
	for (int i = size / 2; i > 0; i /= 2)
	{
		//执行size / 2趟子表插入排序
		for (int j = 0; j < i; j++)
		{
			shell_insert(array, size, j, i);
		}
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
	//显示数组
	display(array, SIZE);
	//插入排序
	shell_sort(array, SIZE);
	//显示数组
	display(array, SIZE);

	return 0;
}

