// this file contains tree methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//====================
// STRUCTURES

struct _Tree{
    struct _Map obj;
    Node *root;
};
typedef struct _Tree Tree;

struct _Node{
	struct _Node *left;
	struct _Node *right;
	void *key;
	void *value;
};
typedef struct _Node Node;

//====================
// METHODS IMPLEMENTATION


Node *tree_create_node(void *key, void *value){
	assert(key);
	assert(value);

	Node *new_node = calloc(1, sizeof(Node));

	if(new_node == NULL)
		return NULL;

	new_node->key = key;
	new_node->value = value;

	return new_node;
}

//if new_key is greater than the key in the current node
//we put it in right subtree
//if -//- less -//-, -//- in left subtree

int tree_insert(Map *obj, void *key, void *value){
	assert(obj);
	assert(key);
	assert(value);

	Tree *tree = (Tree*)obj;

	//if insert in empty tree
	if(tree->root == NULL){
		tree->root = tree_create_node(key, value);
		//check for NULL
		return 0;
	}

	Node *cur_node = tree->root;

	while(1){
		int cmp_res = obj->compare_keys(key, cur_node->key);

		if(cmp_res == 0)
			return 0; //skip repeated keys

		if(cmp_res > 0){
			if(cur_node->right == NULL){
				cur_node->right = tree_create_node(key, value);
				//check for NULL
				return 0;
			}
			else
				cur_node = cur_node->right;
		}

		if(cmp_res < 0){
			if(cur_node->left == NULL){
				cur_node->left = tree_create_node(key, value);
				//check for NULL
				return 0;
			}
			else
				cur_node = cur_node->left;
		}
	}
	return 0;
}

//returns a pointer to the node with a key
Node *tree_find_key(Map *obj, Node *node, void *key){
	assert(key);
	assert(obj);

	if(node == NULL){
		return NULL;
	}
	int cmp_res = obj->compare_keys(key, node->key);

	if(cmp == 0)
		return node;

	if(cmp > 0)
		return tree_find_key(obj, node->right, key);
	else
		return tree_find_key(obj, node->left, key);
}

int tree_change(Map *obj, void *key, void *new_value){
	assert(obj);
	assert(key);
	assert(new_value);

	Node *change_node = tree_find_key(Map, ((Tree*)obj)->root, key);

	if(change_node == NULL){
		return 1; //no such key in dictionary
	}
	else{
		change_node->value = new_value;
		return 0;
		//free value???
	}
}

void* tree_get_value(Map *obj, void *key){
	assert(obj);
	assert(key);

	Node *node = tree_find_key(Map, ((Tree*)obj)->root, key);

	return (node == NULL) ? NULL : node->value;
}

void *tree_destroy(Map *obj){
    free((Tree *)(obj));

    printf("tree dead \n");
}

Map *tree_create(int (*tree_compare_keys)(void *key1, void *key2), void (*print_pair)(void *key, void *value)){
    Tree *tree = calloc(1, sizeof(Tree));
	//if

    tree->obj.destroy = tree_destroy;
	tree->obj.insert = tree_insert;
	tree->obj.delete = tree_delete;
	tree->obj.change = tree_change;
	tree->obj.get = tree_get;

	if(compare_keys == NULL){
		//
		return NULL;
	}
	tree->obj.compare_keys = tree_compare_keys;

	if(print_pair == NULL){
		//
		return NULL;
	}
	tree->obj.print_pair = tree_print_pair;

    return (Map*)tree;
}

