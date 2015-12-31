#include <stdio.h>

#define SIZE (10)

//返回在有序表中key值所在的索引，如没找到结果返回-1
int search(int *array, int size, int key)
{
	//低位索引
	int low = 0;
	//高位索引
	int high = size - 1;

	//两边夹
	while (low <= high)
	{
		//计算折半位置
		int mid = (high + low) / 2;
		//如果key与折半位置数据元素值相等
		if (key == array[mid])
		{
			//返回索引
			return mid;
		}
		//如果如果key小于折半位置数据元素值
		else if (key < array[mid])
		{
			//继续在前半区查找
			high = mid - 1;
		}
		else
		{
			//继续在后半区查找
			low = mid + 1;
		}
	}
	//如果没找到则返回-1
	return -1;
}

int main(int argc, char **args)
{
	int array[SIZE] =
	{ 12, 17, 19, 34, 39, 48, 55, 67, 81, 99 };

	printf("%d %d %d\n", search(array, SIZE, 7), search(array, SIZE, 19), search(array, SIZE, 81));

	return 0;
}

