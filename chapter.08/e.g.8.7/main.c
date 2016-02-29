#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE	(10)

//显示数组
void display(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

//两个相邻的有序序列归并成一个有序序列
//in[x]~in[y]和in[y+1]~in[z]合并
void merge(int *in, int *out, int x, int y, int z)
{
	int t, i, j;
	//依次从两个有序子表中取得较小的关键字加入out数组中
	for (t = x, i = x, j = y + 1; i <= y && j <= z; t++)
	{
		//取得较小的关键字加入out数组中
		if (in[i] < in[j])
		{
			out[t] = in[i++];
		}
		else
		{
			out[t] = in[j++];
		}
	}
	//将第1个子表中未完成的元素追加到out
	while (i <= y)
	{
		out[t++] = in[i++];
	}
	//将第2个子表中未完成的元素追加到out
	while (j <= z)
	{
		out[t++] = in[j++];
	}
}

//归并排序
void merging_sort(int *array, int size)
{
	//临时数组
	int temp[size];
	//步长
	int step = 1;
	//归并趟数
	int t = 0;
	//多趟归并
	for (t = 0; step < size; t++)
	{
		//每趟归并将数组分为n/2（向上取整）个组
		for (int i = 0; i < size; i += step * 2)
		{
			//计算第1个有序子表的结束位置
			int e = i + step;
			if (e >= size)
			{
				e = size - 1;
			}
			//计算第2个有序子表的结束位置
			int end = e + step - 1;
			if (end >= size)
			{
				end = size - 1;
			}
			//由array向temp中归并
			if (t % 2 == 0)
			{
				merge(array, temp, i, e - 1, end);
			}
			//由temp向array中归并
			else
			{
				merge(temp, array, i, e - 1, end);
			}
		}
		//步长乘2
		step *= 2;

		if (t % 2 == 0)
		{
			display(temp, size);
		}
		else
		{
			display(array, size);
		}
	}
	//如果经过了奇数次并归，说明结果放在了temp中
	if (t % 2 != 0)
	{
		//将temp元素复制到array中
		for (int i = 0; i < size; i++)
		{
			array[i] = temp[i];
		}
	}
}

int main(int argc, char **args)
{
	int array[SIZE] =
	{ 5, 3, 7, 2, 9, 8, 1, 0, 6, 4 };
	display(array, SIZE);
	merging_sort(array, SIZE);

	return 0;
}

