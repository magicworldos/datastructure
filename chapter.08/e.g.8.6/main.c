#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE	(10)
#define MAX		(99)

typedef struct
{
	int key;
	int index;
} s_tree;

//创建一棵满二叉树
s_tree** create_tree(int *array, int size, int *ms)
{
	//计算阶数
	int m = (int) log2(size) + 1;
	if (pow(2, m - 1) < size)
	{
		m++;
	}
	//计算叶子节点数
	int c = pow(2, m - 1);

	//申请内存
	s_tree **tree = malloc(sizeof(s_tree *) * m);
	for (int i = 0; i < m; i++)
	{
		//申请内存
		tree[i] = malloc(sizeof(s_tree) * (int) pow(2, i));
	}

	//初始化二叉树的叶子节点数据，不足的补MAX
	for (int j = 0; j < c; j++)
	{
		if (j < size)
		{
			tree[m - 1][j].key = array[j];
		}
		else
		{
			tree[m - 1][j].key = MAX;
		}
		tree[m - 1][j].index = j;
	}
	//返回阶数
	*ms = m;
	//返回满二叉树
	return tree;
}

//销毁满二叉树
void destory_tree(s_tree **tree, int m)
{
	for (int i = 0; i < m; i++)
	{
		free(tree[i]);
	}
	free(tree);
}

//找到最小值
int min_ind_tree(s_tree **tree, int m)
{
	//从最大阶开始
	for (int i = m - 1; i > 0; i--)
	{
		//每两个兄弟节点比较大小
		for (int j = 0; j + 1 < (int) pow(2, i); j += 2)
		{
			//将值大的兄弟节点的值向上赋值给其父节点
			if (tree[i][j].key < tree[i][j + 1].key)
			{
				tree[i - 1][j / 2].key = tree[i][j].key;
				tree[i - 1][j / 2].index = tree[i][j].index;
			}
			else
			{
				tree[i - 1][j / 2].key = tree[i][j + 1].key;
				tree[i - 1][j / 2].index = tree[i][j + 1].index;
			}
		}
	}
	//显示二叉树
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < (int) pow(2, i); j++)
		{
			printf("%02d ", tree[i][j].key);
		}
		printf("\n");
	}
	//最后这个满二叉树的根节点即为最小的关键字
	tree[m - 1][tree[0][0].index].key = MAX;
	//返回根节点关键字
	return tree[0][0].key;
}

//选择排序
void select_sort(int*array, int size)
{
	int m = 0;
	//创建满二叉树
	s_tree **tree = create_tree(array, size, &m);
	//循环数组
	for (int i = 0; i < size; i++)
	{
		//找到最小的关键字
		array[i] = min_ind_tree(tree, m);
		printf("%d times the selection result %d.\n\n", i + 1, array[i]);
	}
	//销毁满二叉树
	destory_tree(tree, m);
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

