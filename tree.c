// this file contains tree methods implementation

/*===========*/
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
	void *key;
	void *value;
};
typedef struct _Node Node;

struct _Tree{
    struct _Map obj;
    Node *root;

	void (*free_key)(void* key);
	void (*free_value)(void* value);
};
typedef struct _Tree Tree;


/*======================*/
/* ADDITIONAL FUNCTIONS */

//returns node, where we can insert key
Node *find_place_to_insert(Map *obj, Node *node, void *key){
	assert(obj);
	assert(node);
	assert(key);

	int cmp_res = obj->compare_keys(node->key, key);

	if(cmp_res > 0){
		if(node->right == NULL)
			return node;
		else
			find_place_to_insert(obj, node->right, key);
	}
	else if(cmp_res < 0){
		if(node->left == NULL)
			return node;
		else 
			find_place_to_insert(obj, node->left, key);
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

	((Tree*)obj)->free_key(node->key);		// EDITED BY KOSTYA
	((Tree*)obj)->free_value(node->value);	// EDITED BY KOSTYA
	free(node);
}

void destroy_subtree(Map *obj, Node *node){
	assert(obj);
	assert(node);

	if(node->right)
		destroy_node(obj, node->right);
	
	if(node->left)
		destroy_node(obj, node->left);
		
	destroy_node(obj, node);
}

//returns a pointer to the node with the key
Node *tree_find_key(Map *obj, Node *node, void *key){
	assert(key);
	assert(obj);

	if(node == NULL){
		return NULL;
	}
	int cmp_res = obj->compare_keys(key, node->key);

	if(cmp_res == 0)
		return node;

	if(cmp_res > 0)
		return tree_find_key(obj, node->right, key);
	else
		return tree_find_key(obj, node->left, key);
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
		((Tree*)obj)->free_value(change_node->value);	// EDITED BY KOSTYA
		change_node->value = new_value;
		return 0;
	}
}

//returns NULL if no key found, or a pointer to key
void *tree_get(Map *obj, void *key){
	assert(obj);
	assert(key);

	Node *node = tree_find_key(obj, ((Tree*)obj)->root, key);

	return (node == NULL) ? NULL : node->value;
}

void tree_destroy(Map *obj){
	assert(obj);

	Tree *tree = (Tree*)obj;
	if(tree->root)
		destroy_node(obj, tree->root);

	free((Tree *)obj);
    printf("tree dead \n");
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
		return 1; //no inserting have been done

	else if(obj->compare_keys(key, node_to_insert_in->key) > 0){
		node_to_insert_in->right = tree_create_node(key, value);
		return node_to_insert_in->right ? 0 : 1;
	}
	else{
		node_to_insert_in->left = tree_create_node(key, value);
		return node_to_insert_in->left ? 0 : 1;	
	}
}

int tree_delete(Map *obj, void *key){
	return 0;
}

Map *tree_create(int (*tree_compare_keys)(void *key1, void *key2), 
void (*tree_print_pair)(void *key, void *value), void (*free_key)(void *key), 
void (*free_value)(void *value)){
					
    Tree *tree = calloc(1, sizeof(Tree));
	if(tree == NULL)
		return NULL;

    tree->obj.destroy = tree_destroy;
	tree->obj.insert = tree_insert;
	tree->obj.delete = tree_delete;
	tree->obj.change = tree_change;
	tree->obj.get = tree_get;

	if(tree_compare_keys == NULL || tree_print_pair == NULL){
		free(tree);
		return NULL;
	}
	tree->obj.compare_keys = tree_compare_keys;
	tree->obj.print_pair = tree_print_pair;

	if(free_key == NULL)
		tree->free_key = free_key_default;		// EDITED BY KOSTYA
	else
		tree->free_key = free_key;				// EDITED BY KOSTYA

	if(free_value == NULL)
		tree->free_value = free_value_default;	// EDITED BY KOSTYA
	else
		tree->free_value = free_value;			// EDITED BY KOSTYA

    return (Map*)tree;
}

/*
//returns a pointer to node which is a parent to node with key
//start searching from node
Node *find_parent(Map *obj, Node* node, void *key){
	assert(obj);
	assert(key);
	assert(node);
	
	if(node->right && obj->compare_keys(key, node->right->key) == 0)
		return node;

	if(node->left && obj->compare_keys(key, node->left->key) == 0)
		return node;

	int cmp_res = obj->compare_keys(key, node->key);

	if(cmp_res > 0)
		return node->right ? find_parent(obj, node->right, key) : NULL;
	
	if(cmp_res < 0)
		return node->left ? find_parent(obj, node->left, key) : NULL;

	return NULL;
}

void delete_node(Map *obj, char side, Node *parent){
	assert(parent);
	assert(obj);
	
	//separate deleting node
	Node *node = (side == 'r')? parent->right : parent->left; 
	Node *n_left = node->left;
	Node *n_right = node->right;

	//free node
	obj->free_key(node->key);
	obj->free_value(node->value);
	free(node);

	if(side == 'r')
		parent->right = n_left;
	else
		parent->left = n_left;

	//insert n_right in n_left subtree
	Node *tmp = n_left
	while(tmp->right != NULL)
		tmp = tmp->right;
		
	tmp->right = n_right;
}

int tree_delete(Map *obj, void *key){
	assert(obj);
	assert(key);

	Tree *tree = (Tree*)obj;
	if(tree_root == NULL)
		return 1; //empty tree

	if(obj->compare_keys(key, tree->root->key) == 0){
		Node *n_left = tree->root->left;
		Node *n_right = tree->root->right;
		
		obj->free_key(tree->root->key);
		obj->free_value(tree->root->value);
		free(tree->root);

		tree->root = n_left;
		Node *tmp = n_left;

		while(tmp->right != NULL)
			tmp = tmp->right;
		
		tmp->right = n_right;
	}
	else{
		Node *parent = find_parent(obj, tree->root, key);
		if(
	}
	
}
*/

