#include <stdio.h>

//数组大小
#define A_SIZE (12)
//索引表大小
#define I_SIZE (3)
//索引块大小
#define I_SUB_SIZE (4)

//索引表
typedef struct
{
	//索引快中最大值
	int val;
	//在有序表中的索引
	int ind;
} s_index;

//返回在有序索引表中key值所在的索引，如没找到结果返回-1
int search(int *array, s_index *index, int i_size, int key)
{
	//索引表的索引
	int i_ind = -1;
	//首先在索引表中查找
	for (int i = 0; i < i_size; ++i)
	{
		//找到索引块
		if (key <= index[i].val)
		{
			//记录索引表的索引
			i_ind = i;
			break;
		}
	}

	//如果在索引表中没找到
	if (i_ind == -1)
	{
		//返回-1
		return -1;
	}

	//在索引块中顺序查找
	for (int i = 0; i < I_SUB_SIZE; ++i)
	{
		//如果找到key值相等
		if (key == array[index[i_ind].ind + i])
		{
			//返回所在索引
			return index[i_ind].ind + i;
		}
	}

	//如果没找到则返回-1
	return -1;
}

int main(int argc, char **args)
{
	int array[A_SIZE] =
	{ 12, 17, 19, 8, 34, 39, 57, 48, 59, 81, 67, 99 };

	s_index index[3] =
	{
	{ 19, 0 },
	{ 57, 4 },
	{ 99, 8 } };

	printf("%d %d %d\n", search(array, index, I_SIZE, 5), search(array, index, I_SIZE, 48), search(array, index, I_SIZE, 67));

	return 0;
}

