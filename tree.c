// this file contains tree methods implementation

/*==========*/
/* INCLUDES */

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include <assert.h>

/*============*/
/* STRUCTURES */
struct _Node{
	struct _Node *left;
	struct _Node *right;
	struct _Node *parent;

	void *key;
	void *value;
};
typedef struct _Node Node;

struct _Tree{
    struct _Map obj;
    Node *root;

	void (*free_key)(void *key);
	void (*free_value)(void *value);
	int (*compare_keys)(void *key1, void *key2);
	int (*compare_vals)(void *val1, void *val2);
};
typedef struct _Tree Tree;


/*======================*/
/* ADDITIONAL FUNCTIONS */

//returns node, where we can insert key
Node *find_place_to_insert(Map *obj, Node *n, void *key){
	assert(obj);
	assert(n);
	assert(key);

	int cmp_res = ((Tree*)obj)->compare_keys(key, n->key);

	if(cmp_res > 0){
		return (n->right)? find_place_to_insert(obj, n->right, key) : n;
	}

	if(cmp_res < 0){
		return (n->left)? find_place_to_insert(obj, n->left, key) : n;
	}

	return NULL; //already have such key
}

// Creates node and initialises it with key and value
// returns a pointer to created node or NULL
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

void destroy_node(Map *obj, Node *node){
	assert(obj);
	assert(node);

	((Tree*)obj)->free_key(node->key);
	((Tree*)obj)->free_value(node->value);
	free(node);
}

void destroy_subtree(Map *obj, Node *node){
	assert(obj);
	assert(node);

	if(node->right)
		destroy_subtree(obj, node->right);
	
	if(node->left)
		destroy_subtree(obj, node->left);
		
	destroy_node(obj, node);
}

//returns a pointer to the node with the key
Node *tree_find_key(Map *obj, Node *node, void *key){
	assert(key);
	assert(obj);

	if(node == NULL){
//		printf("find_key: didn't find the key!\n");
		return NULL; //no such key in subtree
	}
	int cmp_res = ((Tree*)obj)->compare_keys(key, node->key);
//	printf("find_key: cmp_res = %d\n", cmp_res);
	
	if(cmp_res == 0)
		return node;

	if(cmp_res > 0)
		return tree_find_key(obj, node->right, key);
	else
		return tree_find_key(obj, node->left, key);
}

int count_value_in_subtree(Map *obj, Node *node, void *value){
	assert(obj);
	assert(value);
	
	if(node == NULL)
		return 0;
	
	int count_left = count_value_in_subtree(obj, node->left, value);
	int count_right = count_value_in_subtree(obj, node->right, value);

	if(((Tree*)obj)->compare_vals(value, node->value) == 0)
		return count_left + count_right + 1;
	else 
		return count_left + count_right;
}

void free_key_default(void *key){
	return;
}

void free_value_default(void *value){
	return;
}

/*========================*/
/* METHODS IMPLEMENTATION */

//returns 0 if changed successfully, 1 if no key found
int tree_change(Map *obj, void *key, void *new_value){
	assert(obj);
	assert(key);
	assert(new_value);

	Node *change_node = tree_find_key(obj, ((Tree*)obj)->root, key);

	if(change_node == NULL){
		return 1; //no such key in dictionary
	}
	else{
		((Tree*)obj)->free_value(change_node->value);
		change_node->value = new_value;
		return 0;
	}
}

//returns NULL if no key found, or a pointer to key
void *tree_get(Map *obj, void *key){
	assert(obj);
	assert(key);

	Node *found_node = tree_find_key(obj, ((Tree*)obj)->root, key);

	assert(found_node);
	return (found_node)? found_node->value : NULL;
}

void tree_destroy(Map *obj){
	assert(obj);

	Tree *tree = (Tree*)obj;

	if(tree->root)
		destroy_subtree(obj, tree->root);

	free((Tree *)obj);
	printf("Tree has been destroyed\n");
}

//if new_key is greater than the key in the current node
//we put it in right subtree
//if -//- less -//-, -//- in left subtree

//inserts a node with (key, value) in the tree.
//returns 0 in success, 1 in other cases
int tree_insert(Map *obj, void *key, void *value){
	assert(obj);
	assert(key);
	assert(value);

	Tree *tree = (Tree*)obj;

	//if insert in empty tree
	if(tree->root == NULL){
		tree->root = tree_create_node(key, value);		
		return tree->root ? 0 : 1;
	}
	
	Node *node_to_insert_in = find_place_to_insert(obj, tree->root, key);

	if(node_to_insert_in == NULL)
		return 1; //already have this key

	int cmp_res = ((Tree*)obj)->compare_keys(key, node_to_insert_in->key);
	Node *new_node = tree_create_node(key, value);

	if(new_node == NULL){
		return 1;
	}
	new_node->parent = node_to_insert_in;

	if(cmp_res > 0){
		node_to_insert_in->right = new_node;
	}
	else{
		node_to_insert_in->left = new_node;
	}

	return 0;
}

int tree_delete(Map *obj, void *key){
	assert(obj);
	assert(key);

	Node *node_to_del = tree_find_key(obj, ((Tree*)obj)->root, key);

	if(node_to_del == NULL){
		printf("no node to del\n"); //////
		return 0; //no such key
	}

	Node *parent = node_to_del->parent;
	Node *left = node_to_del->left;
	Node *right = node_to_del->right;

	
	if(left == NULL && right == NULL){
		;
	}
	else if(left != NULL){
		left->parent = parent;

		if(right != NULL){
			//looking for the rightest node in subtree left
			Node *rightest = left;
	
			while(rightest->right){
				rightest = rightest->right;
			}
			//insert subtree right in subtree left:
			rightest->right = right;
			right->parent = rightest; 
		}
		//if delete root(in hasn't got parent):
		if(node_to_del == ((Tree*)obj)->root)
			((Tree*)obj)->root = left;
		else if(parent->right == node_to_del)
			parent->right = left;
		else
			parent->left = left;
	}
	else{ //right != NULL, left == NULL
		right->parent = parent;

		//if delete root(in hasn't got parent):
		if(node_to_del == ((Tree*)obj)->root)
			((Tree*)obj)->root = right;
		else if(parent->right == node_to_del)
			parent->right = right;
		else
			parent->left = right;
	}

	destroy_node(obj, node_to_del);

	return 0;
}

int tree_count_value(Map *obj, void *value){
	assert(obj);
	assert(value);

	return count_value_in_subtree(obj, ((Tree*)obj)->root, value);
}

Map *tree_create(int (*compare_keys)(void *key1, void *key2),
int (*compare_vals)(void *val1, void *val2),
void (*print_key)(void *key), void (*print_value)(void *value), 
void (*free_key)(void *key), void (*free_value)(void *value)){
					
    Tree *tree = calloc(1, sizeof(Tree));
	if(tree == NULL)
		return NULL;

    tree->obj.destroy = tree_destroy;
	tree->obj.insert = tree_insert;
	tree->obj.delete = tree_delete;
	tree->obj.change = tree_change;
	tree->obj.get = tree_get;
	tree->obj.count_value = tree_count_value;

	if(!compare_keys || !compare_vals || !print_value || !print_key){
		free(tree);
		return NULL;
	}

	tree->compare_vals = compare_vals;
	tree->compare_keys = compare_keys;
	tree->obj.print_value = print_value;
	tree->obj.print_key = print_key;

	tree->free_key = (free_key)? free_key : free_key_default;
	tree->free_value = (free_value)? free_value : free_value_default;

	printf("Tree created\n");
    return (Map*)tree;
}

