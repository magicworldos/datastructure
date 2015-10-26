/*
 * string.c
 *
 *  Created on: Oct 21, 2015
 *      Author: lidq
 */

#include "string.h"

//计算字符串长度
int str_length(char *str)
{
	if (str == null)
	{
		return 0;
	}

	//计算字符串长度
	int length = 0;
	while (*str != '\0')
	{
		length++;
		str++;
	}

	return length;
}

//拷贝字符串
bool str_copy(char *str_target, char *str_source)
{
	if (str_target == null || str_source == null)
	{
		return false;
	}

	//复制字符串
	while (*str_source != '\0')
	{
		*str_target++ = *str_source++;
	}
	*str_target = '\0';

	return true;
}

//比较两个字符串，如果str0 < str1 返回-1, 如果相等返回 0 否则返回 1
int str_compare(char *str0, char *str1)
{
	if (str0 == null || str1 == null)
	{
		return 0;
	}

	//比较
	while (*str0 != '\0' && *str1 != '\0')
	{
		//小于
		if (*str0 < *str1)
		{
			return -1;
		}
		//大于
		else if (*str0 > *str1)
		{
			return 1;
		}
		str0++;
		str1++;
	}
	//如果都结束，表示相等
	if (*str0 == '\0' && *str1 == '\0')
	{
		return 0;
	}
	//如果str0结束str1没结束，表示小于
	else if (*str0 == '\0')
	{
		return -1;
	}
	//str1结束str0没结束，表示大于
	else
	{
		return 1;
	}
}

//将str0和str1连接，结果用str_new返回
bool str_concat(char *str_new, char *str0, char *str1)
{
	if (str_new == null || str0 == null || str1 == null)
	{
		return false;
	}

	//复制str0
	while (*str0 != '\0')
	{
		*str_new++ = *str0++;
	}
	//复制str1
	while (*str1 != '\0')
	{
		*str_new++ = *str1++;
	}
	//结尾符
	*str_new = '\0';

	return true;
}

//将str从pos位置切割出len个字符到sub中
bool str_sub(char *sub, char *str, int pos, int len)
{
	if (sub == null || str == null || pos < 0 || len == 0)
	{
		return false;
	}

	//从pos位置开始
	str += pos;
	int i = 0;
	//截取len长度的子串
	while (*str != '\0')
	{
		if (i++ >= len)
		{
			break;
		}
		*sub++ = *str++;
	}
	//结束符
	*sub = '\0';

	return true;
}

//使用new串替换str中所有的old
bool str_replace(char *str, char *old, char *new)
{
	if (str == null || old == null || new == null)
	{
		return false;
	}

	int ind = -1;
	int old_len = str_length(old);
	int new_len = str_length(new);
	do
	{
		ind = str_index(str, old, 0);
		if (ind < 0)
		{
			break;
		}

		str_delete(str, ind, old_len);
		str_insert(str, new, ind);
	}
	while (1);

	return true;
}

/*
 * 返回str_ind在str中第pos个字符后出现的位置
 * 采用KMP算法
 */
int str_index(char *str, char *str_ind, int pos)
{
	if (str_ind == null || str == null || pos < 0)
	{
		return -1;
	}
	//计算长度
	int length = str_length(str);
	int len = str_length(str_ind);
	if (pos >= length)
	{
		return -1;
	}

	//计算next值
	int next[len];
	get_next(str_ind, next);

	//设定起始位置
	int i = pos;
	int j = 0;
	//开始匹配
	while (i < length && j < len)
	{
		//从模式串向匹配串开始匹配
		if (j == 0 && str[i] != str_ind[j])
		{
			i++;
		}
		//如果相等则各加1
		else if (str[i] == str_ind[j])
		{
			i++;
			j++;
		}
		//如果不相等则从next值中取得下一个j的下标
		else
		{
			j -= next[j];
		}
	}

	//如果匹配成功
	if (j == len)
	{
		//计算位置
		return i - j;
	}

	return -1;
}

//在str在第pos个位置上插入字符串str_ins
bool str_insert(char *str, char *str_ins, int pos)
{
	if (str == null || str_ins == null || pos < 0)
	{
		return false;
	}

	//计算长度
	int len = str_length(str);
	if (pos >= len)
	{
		return false;
	}
	//计算长度
	int len_ins = str_length(str_ins);
	// 处理\0所以len - pos + 1
	for (int i = len + len_ins, j = 0; j < len - pos + 1; i--, j++)
	{
		//向后复制
		str[i] = str[i - len_ins];
	}
	for (int i = 0; i < len_ins; i++)
	{
		//插入子串
		str[pos + i] = str_ins[i];
	}

	return true;
}

//删除str中第pos位置后len个字符
bool str_delete(char *str, int pos, int len)
{
	if (str == null || pos < 0 || len < 0)
	{
		return false;
	}

	//计算长度
	int length = str_length(str);

	//向前复制len长度
	for (int i = 0; i < length - pos; ++i)
	{
		str[pos + i] = str[pos + i + len];
	}
	//结束符
	str[length - len] = '\0';

	return true;
}

//KMP算法计算next数组中的值
bool get_next(char *str, int *next)
{
	if (str == null || next == null)
	{
		return false;
	}

	int len = str_length(str);

	//第0个字符值为0
	next[0] = 0;
	for (int j = 0; j < len; ++j)
	{
		//第1个字符值为1
		if (j == 0)
		{
			next[j + 1] = 1;
		}
		else
		{
			int k = j;
			do
			{
				k = next[k] - 1;
				//找到相同的字符
				if (str[j] == str[k])
				{
					//下一个值为k+1
					next[j + 1] = k + 1 + 1;
					break;
				}
				//没找到则为1
				else if (k == 0)
				{
					next[j + 1] = 1;
					break;
				}
			}
			while (k > 0);
		}
	}

	return true;
}
