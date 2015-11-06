#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char **args)
{
	//list1 x^10
	s_list *list1 = (s_list *) malloc(sizeof(s_list));
	list_init(list1);
	list_insert_value(list1, 0, 10, 1);

	//list2 2x^6
	s_list *list2 = (s_list *) malloc(sizeof(s_list));
	list_init(list2);
	list_insert_value(list2, 0, 6, 2);

	//list1 (x^10 + 2x^6)
	list_append(list1, list2);

	//list3 (x^10 + 2x^6)y^3
	s_list *list3 = (s_list *) malloc(sizeof(s_list));
	list_init(list3);
	list_insert_value(list3, 1, 3, (int) list1);

	//list4 3x^5
	s_list *list4 = (s_list *) malloc(sizeof(s_list));
	list_init(list4);
	list_insert_value(list4, 0, 5, 3);

	//list5 (3x^5)y^2
	s_list *list5 = (s_list *) malloc(sizeof(s_list));
	list_init(list5);
	list_insert_value(list5, 1, 2, (int) list4);

	//list3 ((x^10 + 2x^6)y^3 + (3x^5)y^2)
	list_append(list3, list5);

	//list6 ((x^10 + 2x^6)y^3 + (3x^5)y^2)z^2
	s_list *list6 = (s_list *) malloc(sizeof(s_list));
	list_init(list6);
	list_insert_value(list6, 1, 2, (int) list3);

	//list7 x^4
	s_list *list7 = (s_list *) malloc(sizeof(s_list));
	list_init(list7);
	list_insert_value(list7, 0, 4, 1);

	//list8 6x^3
	s_list *list8 = (s_list *) malloc(sizeof(s_list));
	list_init(list8);
	list_insert_value(list8, 0, 3, 6);

	//list8 (x^4 + 6x^3)
	list_append(list7, list8);

	//list9 (x^4 + 6x^3)y^4
	s_list *list9 = (s_list *) malloc(sizeof(s_list));
	list_init(list9);
	list_insert_value(list9, 1, 4, (int) list7);

	//list10 2y
	s_list *list10 = (s_list *) malloc(sizeof(s_list));
	list_init(list10);
	list_insert_value(list10, 0, 1, 2);

	//list9 ((x^4 + 6x^3)y^4 + 2y)
	list_append(list9, list10);

	//list11 ((x^4 + 6x^3)y^4 + 2y)z
	s_list *list11 = (s_list *) malloc(sizeof(s_list));
	list_init(list11);
	list_insert_value(list11, 1, 1, (int) list9);

	//list6 ((x^10 + 2x^6)y^3 + (3x^5)y^2)z^2 + ((x^4 + 6x^3)y^4 + 2y)z
	list_append(list6, list11);

	//list12 15
	s_list *list12 = (s_list *) malloc(sizeof(s_list));
	list_init(list12);
	list_insert_value(list12, 0, 0, 15);

	//list6 ((x^10 + 2x^6)y^3 + (3x^5)y^2)z^2 + ((x^4 + 6x^3)y^4 + 2y)z + 15
	list_append(list6, list12);

	list_display(list6, 'z');

	return 0;
}
