#ifndef _STACK_H_
#define _STACK_H_

#include "typedef.h"

typedef struct
{
	//栈大小，以元素个数为单位
	int stack_size;
	//元素个数
	int ele_count;
	//栈地址
	void *stack_addr;
	//栈顶地址
	void *p;
	//回调函数，在销毁栈时释放未出栈元素的内存
	void (*destructor)();
} s_stack;

//构建一个栈
bool stack_init(s_stack* stack, void (*destructor)());

//销毁栈
bool stack_destroy(s_stack *stack);

//压栈
bool stack_push(s_stack *stack, void *p_ele);

//出栈
bool stack_pop(s_stack *stack, void *p_ele);

#endif
