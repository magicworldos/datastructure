#include "hashtable.h"

int main(int argc, char **args)
{
	s_hashtable ht;
	hashtable_init(&ht, null);

	int t1 = 1111;
	int t2 = 2222;
	int t3 = 3333;
	int t4 = 4444;
	int t5 = 5555;

	hashtable_push(&ht, 1, &t1);
	hashtable_push(&ht, 2, &t2);
	hashtable_push(&ht, 3, &t3);
	hashtable_push(&ht, 4, &t4);
	hashtable_push(&ht, 256, &t5);

	printf("%d\n", *(int *) hashtable_get(&ht, 1));
	printf("%d\n", *(int *) hashtable_get(&ht, 2));
	printf("%d\n", *(int *) hashtable_get(&ht, 3));
	printf("%d\n", *(int *) hashtable_get(&ht, 4));
	printf("%d\n", *(int *) hashtable_get(&ht, 256));

	hashtable_destory(&ht);

	return 0;
}

