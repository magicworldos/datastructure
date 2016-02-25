#include <stdio.h>

#define SIZE	(10)

//插入排序
void insert_sort(int *array, int size)
{
	//从第2个元素开始
	for (int i = 1; i < size; i++)
	{
		//取得当前元素值到t
		int t = array[i];
		//如果小于有序子表的最大值
		if (t < array[i - 1])
		{
			//插入有序子表
			for (int j = i; j > 0; j--)
			{
				//依次后移一个元素
				array[j] = array[j - 1];
				//如果找到插入位置
				if (t >= array[j - 1])
				{
					//插入t到有序子表
					array[j] = t;
					break;
				}
				//如果t大于有序子表的第1个元素
				if (j == 1 && t < array[0])
				{
					//插入t到有序子表的第1个位置上
					array[0] = t;
					break;
				}
			}
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
	insert_sort(array, SIZE);
	//显示数组
	display(array, SIZE);

	return 0;
}

