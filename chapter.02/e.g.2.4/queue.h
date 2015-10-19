#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "typedef.h"

//节点
typedef struct s_node
{
	void *data;
	struct s_node *next;
} s_node;

//队列数据结构
typedef struct
{
	//元素大小
	int ele_size;
	//头节点
	s_node *header;
	//脚节点
	s_node *footer;
	//用于释放节点数据的回调函数
	void (*free_data)();
	//用于访问节点数据内容的回调函数
	void (*visit_data)(void *data);
} s_queue;

//构建一个队列
bool init_queue(s_queue *queue, int ele_size, void (*free_data)(), void (*visit_data)());

//销毁队列
bool destroy_queue(s_queue *queue);

//清空队列中所有元素
bool clear_queue(s_queue *queue);

//在队列尾追加一个元素
bool queue_insert(s_queue *queue, void *e);

//在队列头删除一个元素
bool queue_delete(s_queue *queue);

//对每个元素执行visit操作
bool queue_visit(s_queue *queue);

#endif
