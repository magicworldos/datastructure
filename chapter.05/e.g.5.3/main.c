#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

typedef struct
{
	int no;
	char *name;
} student;

//删除整数函数
void free_student(student *stu)
{
	if (stu != null)
	{
		free(stu->name);
		free(stu);
	}
}

//访问整数函数
void visit_student(student *stu)
{
	if (stu != null)
	{
		printf("%d\t%s\n", stu->no, stu->name);
	}
}

int main(int argc, char **args)
{
	//初始化树
	s_tree tree;
	tree_init(&tree, &visit_student, &free_student);

	student *stu0 = (student *) malloc(sizeof(student));
	stu0->no = 0;
	stu0->name = (char *) malloc(20);
	memcpy(stu0->name, "AAA", 20);

	student *stu1 = (student *) malloc(sizeof(student));
	stu1->no = 1;
	stu1->name = (char *) malloc(20);
	memcpy(stu1->name, "BBB", 20);

	student *stu2 = (student *) malloc(sizeof(student));
	stu2->no = 3;
	stu2->name = (char *) malloc(20);
	memcpy(stu2->name, "CCC", 20);

	student *stu3 = (student *) malloc(sizeof(student));
	stu3->no = 4;
	stu3->name = (char *) malloc(20);
	memcpy(stu3->name, "DDD", 20);

	student *stu4 = (student *) malloc(sizeof(student));
	stu4->no = 2;
	stu4->name = (char *) malloc(20);
	memcpy(stu4->name, "EEE", 20);

	student *stu5 = (student *) malloc(sizeof(student));
	stu5->no = 5;
	stu5->name = (char *) malloc(20);
	memcpy(stu5->name, "FFF", 20);

	student *stu6 = (student *) malloc(sizeof(student));
	stu6->no = 7;
	stu6->name = (char *) malloc(20);
	memcpy(stu6->name, "GGG", 20);

	student *stu7 = (student *) malloc(sizeof(student));
	stu7->no = 8;
	stu7->name = (char *) malloc(20);
	memcpy(stu7->name, "HHH", 20);

	student *stu8 = (student *) malloc(sizeof(student));
	stu8->no = 6;
	stu8->name = (char *) malloc(20);
	memcpy(stu8->name, "III", 20);

	student **pdata = (student **) malloc(sizeof(student *) * 20);

	pdata[0] = stu0;
	pdata[1] = stu1;
	pdata[2] = stu2;
	pdata[3] = null;
	pdata[4] = null;
	pdata[5] = stu3;
	pdata[6] = null;
	pdata[7] = null;
	pdata[8] = stu4;
	pdata[9] = stu5;
	pdata[10] = stu6;
	pdata[11] = null;
	pdata[12] = null;
	pdata[13] = stu7;
	pdata[14] = null;
	pdata[15] = null;
	pdata[16] = stu8;
	pdata[17] = null;
	pdata[18] = null;

	//前序构建二叉树
	tree_create(&tree, 0, (void **) pdata);

	//前序遍历
	tree_preamble_visit(&tree, tree.root);
	printf("\n");
	//中序遍历
	tree_inorder_visit(&tree, tree.root);
	printf("\n");
	//后序遍历
	tree_postorder_visit(&tree, tree.root);
	printf("\n");

	free(pdata);

	//销毁树
	tree_destroy(&tree);

	return 0;
}

