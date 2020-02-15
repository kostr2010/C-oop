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

	void *key;	 // data
	void *value; // data
};
typedef struct _Node Node;

struct _Tree{
    struct _Map obj;
    Node *root;	//private data

	int (*compare_keys)(void *key1, void *key2);//private func
	int (*compare_vals)(void *val1, void *val2);//private func
};
typedef struct _Tree Tree;

/*======================*/
/* ADDITIONAL FUNCTIONS */

/** Recursivly finds node in subtree n where we can insert new node with key
*
*@return Returns a pointer to found node or NULL if key is already in the tree
*/
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

/** Creates new node and fills in <key> and <value>
*
*@return Returns a pointer to created node or NULL in case of error
*/
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

/** Non-recursively destroys <node>
*/
void destroy_node(Node *node){
	assert(node);

	free(node);
}

/** Recursively destroys subtree <node>
*/
void destroy_subtree(Node *node){
	assert(node);

	if(node->right)
		destroy_subtree(node->right);
	
	if(node->left)
		destroy_subtree(node->left);
		
	destroy_node(node);
}

/**Recursively finds node in subtree <node> with given <key>
*
*@return Returns a pointer to the node with given key or NULL if nothing was found
*/
Node *tree_find_key(Map *obj, Node *node, void *key){
	assert(key);
	assert(obj);

	if(node == NULL)
		return NULL; //no such key in subtree
	
	int cmp_res = ((Tree*)obj)->compare_keys(key, node->key);
	
	if(cmp_res == 0)
		return node;

	if(cmp_res > 0)
		return tree_find_key(obj, node->right, key);
	else
		return tree_find_key(obj, node->left, key);
}

/** Recursively counts the number of pairs (key, <value>) in subtree <node> with given <value>
*
*@return Returns number of pairs
*/
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

/**Recursively calculates number of nodes (number of pairs(key,val)) in subtree <node>
*
*@return Returns number of nodes
*/
int tree_size_subtree(Node *node){
	
	if(node == NULL)
		return 0;
	
	return 1 + tree_size_subtree(node->right) +
			tree_size_subtree(node->left);
}

/*========================*/
/* METHODS IMPLEMENTATION */

/** Changes (<key>, ...) to (<key>, <new_value>)
*
*@return Returns 0 in if changed successfully or 1 if no <key> was found
*/
int tree_change(Map *obj, void *key, void *new_value){
	assert(obj);
	assert(key);
	assert(new_value);

	Node *change_node = tree_find_key(obj, ((Tree*)obj)->root, key);

	if(change_node == NULL){
		return 1; //no such key in dictionary
	}
	else{
		change_node->value = new_value;
		return 0;
	}
}

/** Gets mapped value by its <key>
*
*@return Returns a pointer to found value or NULL if no <key> found
*/
void *tree_get(Map *obj, void *key){
	assert(obj);
	assert(key);

	Node *found_node = tree_find_key(obj, ((Tree*)obj)->root, key);

	return (found_node)? found_node->value : NULL;
}
/** Destroys tree in <obj>
*
*@return No return value
*/
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

/** Inserts (<key>, <value>) in tree in order that
* all keys in right subtree are greater than <key> and
* all keys in left subtree are less than <key>.
* Don't insert repeated keys.
*
*@return Returns 0 if insertion is done and 1 in other ways	
*/
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

/** Deletes pair (<key>, value) from tree
*
*@return Returns 0
*/
int tree_delete(Map *obj, void *key){
	assert(obj);
	assert(key);

	Node *node_to_del = tree_find_key(obj, ((Tree*)obj)->root, key);

	if(node_to_del == NULL){
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

/** Counts number of values <value> in tree
*
*@return Returns number of values found
*/
int tree_count_value(Map *obj, void *value){
	assert(obj);
	assert(value);

	return count_value_in_subtree(obj, ((Tree*)obj)->root, value);
}

/** Calculates size of the tree
*
*@return Returns size of the tree
*/
int tree_size(Map *obj){
	assert(obj);

	return tree_size_subtree(((Tree*)obj)->root); 
}

/** Creates tree and fills in appropriate functions
*
*@return Returns a pointer to created tree or NULL if nothing is created
*/
Map *tree_create(cmp_k cmp_k_func, cmp_v cmp_v_func){
					
    Tree *tree = calloc(1, sizeof(Tree));
	if(tree == NULL)
		return NULL;

    tree->obj.destroy = tree_destroy;
	tree->obj.insert = tree_insert;
	tree->obj.delete = tree_delete;
	tree->obj.change = tree_change;
	tree->obj.get = tree_get;
	tree->obj.count_value = tree_count_value;
	tree->obj.size = tree_size;

	if(!cmp_k_func || !cmp_v_func){
		free(tree);
		return NULL;
	}

	tree->compare_vals = cmp_v_func;
	tree->compare_keys = cmp_k_func

	printf("Tree has been created\n");

    return (Map*)tree;
}

