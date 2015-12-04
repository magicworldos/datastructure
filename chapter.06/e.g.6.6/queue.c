#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

//构建一个队列
bool init_queue(s_queue *queue, int ele_size, void (*free_data)(), void (*visit_data)())
{
	if (queue == null)
	{
		return false;
	}
	queue->ele_size = ele_size;
	queue->free_data = free_data;
	queue->visit_data = visit_data;
	queue->header = null;
	queue->footer = null;
	return true;
}

//销毁队列
bool destroy_queue(s_queue *queue)
{
	if (queue == null)
	{
		return false;
	}

	if (queue->header == null)
	{
		return true;
	}

	clear_queue(queue);

	return true;
}

//清空队列中所有元素
bool clear_queue(s_queue *queue)
{
	if (queue == null)
	{
		return false;
	}

	//从头节点开始释放
	s_node *p = queue->header;
	while (p != null)
	{
		//释放内存
		if (queue->free_data != null)
		{
			queue->free_data(p->data);
		}
		s_node *t = p;
		p = p->next;
		free(t);
	}
	queue->header = null;
	queue->footer = null;

	return true;
}

//在队列尾追加一个元素
bool queue_in(s_queue *queue, void *e)
{
	if (queue == null || e == null)
	{
		return false;
	}

	//申请新节点内存
	s_node *p_new = (s_node *) malloc(sizeof(s_node));
	p_new->data = e;
	p_new->next = null;

	if (queue->footer == null)
	{
		queue->header = p_new;
		queue->footer = p_new;

		return true;
	}

	queue->footer->next = p_new;
	queue->footer = p_new;

	return true;
}

//在队列头删除一个元素
bool queue_out(s_queue *queue, void **e)
{
	if (queue == null || queue->header == null)
	{
		return false;
	}

	s_node *p_del = queue->header;
	queue->header = queue->header->next;
	if (queue->footer == p_del)
	{
		queue->footer = queue->header->next;
	}

	*e = p_del->data;

	if (queue->free_data != null)
	{
		queue->free_data(p_del);
	}

	return true;
}

//对每个元素执行visit操作
bool queue_visit(s_queue *queue)
{
	if (queue == null || queue->header == null)
	{
		return false;
	}

	if (queue->visit_data == null)
	{
		return false;
	}

	//顺序访问每一个元素
	s_node *p = queue->header;
	while (p != null)
	{
		queue->visit_data(p->data);
		p = p->next;
	}
	return true;
}
