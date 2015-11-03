#include <stdio.h>
#include <stdlib.h>

//三元组
typedef struct
{
	//行号
	int i;
	//列号
	int j;
	//值
	int val;
} m_data;

//二维矩阵
typedef struct
{
	//总行数
	int m;
	//总列数
	int n;
	//非0元素个数
	int k;
	//线性三元组
	m_data *data;
} matrix;

//设定值
void set_data(m_data *data, int i, int j, int val)
{
	data->i = i;
	data->j = j;
	data->val = val;
}

int main(int argc, char **args)
{
	//原始矩阵
	int original_matrix[5][6] =
	{
	{ 0, 3, 0, 0, 12, 0 },
	{ 0, 0, 0, 0, 0, 0 },
	{ -7, 0, 0, 0, 0, 0 },
	{ 0, 0, 8, 0, 0, 13 },
	{ 11, -5, 0, 0, 9, 0 } };

	//压缩矩阵
	matrix mat;
	mat.m = 5;
	mat.n = 6;
	mat.k = 0;
	//8个非空元素
	mat.data = (m_data *) malloc(sizeof(m_data) * 8);

	//将原始矩阵压缩
	for (int i = 0; i < mat.m; ++i)
	{
		for (int j = 0; j < mat.n; ++j)
		{
			if (original_matrix[i][j] != 0)
			{
				/*
				 * 注意 mat.data + k的真正含义：
				 * 在指针data值（地址）上每加1,表示对这个地址加上一个单位的m_data（因为此指针是指向m_data类型）大小
				 * 因为 sizeof(m_data) == 12 == 0xc
				 * 假设：	mat.data 	 == 0x90cb008
				 * 			mat.data + 1 == 0x90cb014
				 * 			mat.data + 2 == 0x90cb020
				 * 			mat.data + 3 == 0x90cb02c
				 * 			mat.data + 4 == 0x90cb038
				 */
				set_data(mat.data + mat.k, i, j, original_matrix[i][j]);
				mat.k++;
			}
		}
	}

	//显示矩阵内容
	//(0, 1, 3), (0, 4, 12), (2, 0, -7), (3, 2, 8), (3, 5, 13), (4, 0, 11), (4, 1, -5), (4, 4, 9)
	for (int p = 0; p < mat.k; ++p)
	{
		printf("(%d, %d, %d), ", mat.data[p].i, mat.data[p].j, mat.data[p].val);
	}
	printf("\n");

	//压缩矩阵
	matrix r_mat;
	r_mat.data = (m_data *) malloc(sizeof(m_data) * 8);
	r_mat.m = mat.n;
	r_mat.n = mat.m;
	r_mat.k = mat.k;

	int q = 0;
	//从原始矩阵的每一列开始遍历，也就是转置矩阵中的行号
	for (int col = 0; col < mat.n; ++col)
	{
		//在mat中的所有3元组中查找
		for (int p = 0; p < mat.k; ++p)
		{
			//原矩阵中“列号”等于转置矩阵中行号
			if (mat.data[p].j == col)
			{
				//行列转置
				r_mat.data[q].i = mat.data[p].j;
				r_mat.data[q].j = mat.data[p].i;
				r_mat.data[q].val = mat.data[p].val;
				q++;
			}
		}
	}

	printf("\n");
	for (int p = 0; p < r_mat.k; ++p)
	{
		printf("(%d, %d, %d), ", r_mat.data[p].i, r_mat.data[p].j, r_mat.data[p].val);
	}

	//压缩矩阵
	matrix e_mat;
	e_mat.data = (m_data *) malloc(sizeof(m_data) * 8);
	e_mat.m = mat.n;
	e_mat.n = mat.m;
	e_mat.k = mat.k;

	//用于记录矩阵每一列中有多少个非0元素
	int *num = (int *) malloc(sizeof(int) * mat.n);
	//用于记录矩阵每一列第一个非0元素的开始位置（行号）
	int *cpot = (int *) malloc(sizeof(int) * mat.n);

	//初始化num，全部设为0
	for (int j = 0; j < mat.n; ++j)
	{
		num[j] = 0;
	}
	//计算矩阵每一列中有多少个非0元素
	for (int q = 0; q < mat.k; ++q)
	{
		++num[mat.data[q].j];
	}
	//初始号为0
	cpot[0] = 0;
	//计算每一列第一个非0元素的开始位置
	for (int col = 1; col < mat.n; ++col)
	{
		cpot[col] = cpot[col - 1] + num[col - 1];
	}
	//转置矩阵
	int col;
	for (int p = 0; p < mat.k; ++p)
	{
		//取得列号
		col = mat.data[p].j;
		//从cpot中得到开始的位置
		q = cpot[col];
		//转置矩阵元素
		e_mat.data[q].i = mat.data[p].j;
		e_mat.data[q].j = mat.data[p].i;
		e_mat.data[q].val = mat.data[p].val;
		//此列的开始位置加一（转置矩阵的行号）
		++cpot[col];
	}

	printf("\n\n");
	for (int p = 0; p < r_mat.k; ++p)
	{
		printf("(%d, %d, %d), ", e_mat.data[p].i, e_mat.data[p].j, e_mat.data[p].val);
	}

	free(num);
	free(cpot);

	free(mat.data);
	free(r_mat.data);
	free(e_mat.data);

	return 0;
}
