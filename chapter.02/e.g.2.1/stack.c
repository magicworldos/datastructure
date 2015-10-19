#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

//构建一个栈
bool stack_init(s_stack *stack, void (*destructor)())
{
	if (stack == null)
	{
		return false;
	}

	//初始大小为2
	stack->stack_size = 2;
	//当前元素个数为0
	stack->ele_count = 0;
	//申请栈空间
	stack->stack_addr = malloc(4 * stack->stack_size);
	//将指针p设置为栈顶元素
	stack->p = stack->stack_addr + stack->stack_size * 4;
	//设置回调函数，在栈销毁时用于释放未出栈元素的内存
	stack->destructor = destructor;

	return true;
}

//销毁栈
bool stack_destroy(s_stack *stack)
{
	if (stack == null)
	{
		return false;
	}

	//循环释放未出栈元素所占用的内存
	for (int i = 0; i < stack->ele_count; i++)
	{
		//回调函数，释放内存
		stack->destructor((void*) (*(unsigned int *) stack->p));
		//p向下移动
		stack->p += 4;
	}
	//释放栈内存
	free(stack->stack_addr);

	return true;
}

//压栈
bool stack_push(s_stack *stack, void *p_ele)
{
	if (stack == null || p_ele == null)
	{
		return false;
	}

	//p向上移动4byte
	stack->p -= 4;
	//将元素入栈，入栈的是一个地址
	*(unsigned int *) stack->p = (unsigned int) p_ele;
	//元素个数加1
	stack->ele_count++;
	//如果栈满
	if (stack->stack_size == stack->ele_count)
	{
		//申请2倍大小的内存空间
		stack->stack_addr = realloc(stack->stack_addr, stack->stack_size * 2 * 4);
		//设定指针p的新值
		stack->p = stack->stack_addr + stack->stack_size * 2 * 4 - stack->ele_count * 4;
		//复制原数据到新的栈底
		memcpy(stack->stack_addr + stack->stack_size * 4, stack->stack_addr, stack->stack_size * 4);
		//栈大小变为2倍
		stack->stack_size *= 2;
	}

	return true;
}

//出栈
bool stack_pop(s_stack *stack, void *p_ele)
{
	if (stack == null || p_ele == null)
	{
		return false;
	}

	//如果栈空，出栈失败
	if (stack->ele_count == 0)
	{
		return false;
	}
	//出栈
	*(unsigned int *) p_ele = *(unsigned int *) stack->p;
	//p向下移动4byte
	stack->p += 4;
	//元素个数减1
	stack->ele_count--;

	return true;
}
