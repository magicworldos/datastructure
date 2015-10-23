/*
 * string.h
 *
 *  Created on: Oct 21, 2015
 *      Author: lidq
 */

#ifndef STRING_H_
#define STRING_H_

#include "typedef.h"

//计算字符串长度
int str_length(char *str);

//拷贝字符串
bool str_copy(char *str_target, char *str_source);

//比较两个字符串，如果str0 < str1 返回-1, 如果相等返回 0 否则返回 1
int str_compare(char *str0, char *str1);

//将str0和str1连接，结果用str_new返回
bool str_concat(char *str_new, char *str0, char *str1);

//将str从pos位置切割出len个字符到sub中
bool str_sub(char *sub, char *str, int pos, int len);

//返回str_ind在str中第pos个字符后出现的位置
int str_index(char *str, char *str_ind, int pos);

//在str在第pos个位置上插入字符串str_ins
bool str_insert(char *str, char *str_ins, int pos);

//删除str中第pos位置后len个字符
bool str_delete(char *str, int pos, int len);

//KMP算法计算next数组中的值
bool get_next(char *str, int next[]);

#endif /* STRING_H_ */
