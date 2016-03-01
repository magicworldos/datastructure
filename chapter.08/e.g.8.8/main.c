#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//数组大小
#define SIZE	(10)
//关键字级数
#define MAX_M	(3)
//空指针
#define null	((void *)(0))

//关键字结构
typedef struct s_rkey
{
	int key;
	struct s_rkey *next;
} s_rkey;

//计算个位、十位、百位……的关键字值
int get_m_key(int key, int m)
{
	m = pow(10, m);
	if (m == 10)
	{
		return key % m;
	}
	return (key % m) / (m / 10);
}

//链式基数排序
s_rkey* radix_link(s_rkey *header, s_rkey **p_rkey_s, s_rkey **p_rkey_e, int size, int m)
{
	//头指针
	s_rkey *p = header;
	s_rkey *p_temp = header;
	//按各个位上的关键字分别加入不同的链表中
	while (p != null)
	{
		p_temp = p->next;
		p->next = null;
		//计算关键字
		int k = get_m_key(p->key, m);
		if (p_rkey_e[k] == null)
		{
			p_rkey_s[k] = p;
			p_rkey_e[k] = p;
		}
		else
		{
			p_rkey_e[k]->next = p;
			p_rkey_e[k] = p_rkey_e[k]->next;
		}
		p = p_temp;
	}
	//将不同内容的关键字链表连接成一个链表
	s_rkey *p_start = null;
	s_rkey *p_end = null;
	for (int i = 0; i < size; i++)
	{
		if (p_start == null && p_rkey_s[i] != null)
		{
			p_start = p_rkey_s[i];
			p_end = p_rkey_e[i];
		}
		else if (p_end != null && p_rkey_s[i] != null)
		{
			p_end->next = p_rkey_s[i];
			p_end = p_rkey_e[i];
		}
	}
	//置空
	for (int i = 0; i < size; i++)
	{
		p_rkey_s[i] = null;
		p_rkey_e[i] = null;
	}
	//返回头节点
	return p_start;
}

//基数排序
void radix_sort(int *array, int size)
{
	//用于存放各个关键字的头尾指针
	s_rkey **p_rkey_s = (s_rkey **) malloc(sizeof(s_rkey *) * size);
	s_rkey **p_rkey_e = (s_rkey **) malloc(sizeof(s_rkey *) * size);
	//初始化
	for (int i = 0; i < size; i++)
	{
		p_rkey_s[i] = null;
		p_rkey_e[i] = null;
	}
	//头尾指针
	s_rkey *p_start = null;
	s_rkey *p_end = null;
	for (int i = 0; i < size; i++)
	{
		//创建链表
		s_rkey *p_rkey = (s_rkey *) malloc(sizeof(s_rkey));
		p_rkey->key = array[i];
		p_rkey->next = null;
		//记录头指针
		if (p_start == null)
		{
			p_start = p_rkey;
			p_end = p_rkey;
		}
		//加入链表
		else
		{
			p_end->next = p_rkey;
			p_end = p_end->next;
		}
	}
	//执行3次循环
	for (int i = 0; i < MAX_M; i++)
	{
		//链式基数排序
		p_start = radix_link(p_start, p_rkey_s, p_rkey_e, size, i + 1);
		//取得头节点
		s_rkey *p = p_start;
		//显示结果
		while (p != null)
		{
			printf("%d ", p->key);
			p = p->next;
		}
		printf("\n");
	}

	//释放内存
	s_rkey *p = p_start;
	while (p != null)
	{
		s_rkey *p_del = p;
		p = p->next;
		free(p_del);
	}
	//释放内存
	free(p_rkey_s);
	free(p_rkey_e);
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
	{ 305, 403, 417, 922, 429, 78, 7, 20, 446, 23 };
	display(array, SIZE);
	radix_sort(array, SIZE);

	return 0;
}

