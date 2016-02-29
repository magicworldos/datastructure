#include <stdio.h>

#define SIZE	(10)

//找到最小值
int min_ind(int *array, int size, int start)
{
	int index = -1;
	int t = -1;
	for (int i = start; i < size; i++)
	{
		if (i == start)
		{
			t = array[i];
			index = i;
		}
		//找到最小值并记录其位置
		if (array[i] < t)
		{
			t = array[i];
			index = i;
		}
	}
	return index;
}

//选择排序
void select_sort(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int ind = min_ind(array, size, i);
		//如果当前关键字小于最小值
		if (array[ind] < array[i])
		{
			//互换位置
			int t = array[i];
			array[i] = array[ind];
			array[ind] = t;
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
	{ 5, 3, 7, 2, 9, 8, 1, 0, 6, 4 };
	display(array, SIZE);
	select_sort(array, SIZE);
	display(array, SIZE);

	return 0;
}

