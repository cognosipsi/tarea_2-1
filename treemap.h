#ifndef TREEMAP_H
#define TREEMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct TreeNode TreeNode;

typedef struct TreeMap TreeMap;

//int is_equal(TreeMap* tree, void* key1, void* key2);

TreeNode * minimum(TreeNode * x);

TreeNode * createTreeNode(void* key, void * value);

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2));

void insertTreeMap(TreeMap * tree, void* key, void * value);

void removeNode(TreeMap * tree, TreeNode* node);

void eraseTreeMap(TreeMap * tree, void* key);

void * searchTreeMap(TreeMap * tree, void* key);

void * upperBound(TreeMap * tree, void* key);

void * firstTreeMap(TreeMap * tree);

void * nextTreeMap(TreeMap * tree);



#endif