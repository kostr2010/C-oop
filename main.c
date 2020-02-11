// main file. here the methods will be tested

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"
#include "hmap.h"
#include "list.h"

int compare_keys(void *key1, void *key2){
	assert(key1);
	assert(key2);

	return *((int*)key1) - *((int*)key2);
}

int compare_vals(void *val1, void *val2){
	assert(val1);
	assert(val2);

	return *(int*)val1 - *(int*)val2;
}

void print_key(void *key){
	assert(key);

	printf("%d", *(int*)key);
}

void print_value(void *val){
	assert(val);

	printf("%d", *(int*)val);
}


int tree_test(){
	Map *tree = tree_create(compare_keys, compare_vals, print_key, print_value, NULL, NULL);

	if(tree == NULL){
		printf("tree = NULL!\n");
		return 0;
	}
	int key1 = 8;
	int key2 = 2;
	int key3 = 5;
	int key4 = 4;

	int val1 = key1 * 5;
	int val2 = key2 * 5;
	int val3 = key3 * 5;
	int val4 = key4 * 5;

	int new_val = 37;

	if(tree->insert(tree, &key1, &val1))
		printf("err1\n");

	if(tree->insert(tree, &key2, &val2))
		printf("err2\n");

	if(tree->insert(tree, &key3, &val3))
		printf("err3\n");

	if(tree->insert(tree, &key4, &val4))
		printf("err4\n");


	printf("inserted successfully!\n");
	printf("tree[2] =(exp.%d) ", val2);
	

	tree->print_value(tree->get(tree, &key2));
	printf("\n");

	tree->change(tree, &key2, &new_val);
	printf("new: tree[2] =(exp.%d) ", new_val);
	tree->print_value(tree->get(tree, &key2));
	printf("\n");
	
	tree->delete(tree, &key1);

	printf("number of %d = (exp.0)%d \n", val1, tree->count_value(tree, &val1));

	tree->insert(tree, &key1, &val1);
	tree->insert(tree, &key1, &val1);
	tree->insert(tree, &key1, &val1);

	printf("number of %d = (exp.1)%d \n", val1, tree->count_value(tree, &val1));


	tree->change(tree, &key2, &val1);
	tree->change(tree, &key3, &val1);
	tree->change(tree, &key4, &val1);

	printf("number of %d = (exp.4)%d \n", val1, tree->count_value(tree, &val1));
	
	printf("size = (exp.4)%d\n", tree->size(tree));

	tree->delete(tree, &key2);
	tree->delete(tree, &key2);
	tree->delete(tree, &key3);
	tree->delete(tree, &key4);
	printf("size = (exp.1)%d\n", tree->size(tree));

	tree->destroy(tree);

	return 0;
}
//====================
// MAIN

int main()
{
    //====================
    // HMAP TEST
    Map *c = hmap_create(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    int val1 = 1;
    int val2 = 2;
    int val3 = 3;

    int key1 = 11;
    int key2 = 21;
    int key3 = 31;

    c->insert(c, &key1, &val1);
    c->insert(c, &key2, &val2);
    c->insert(c, &key3, &val3);
    c->insert(c, &key1, &val1);
    c->insert(c, &key3, &val3);
    c->insert(c, &key2, &val2);
    c->insert(c, &key2, &val2);

    //Print(c);

    c->delete(c, &key3);
    c->change(c, &key2, &val3);

    Print(c);

    printf("entries of %d: %d\n", val3, c->count_value(c, &val3));

    c->destroy(c);

	printf("========TREE TEST=======\n\n");
	tree_test();

    return 0;
}
