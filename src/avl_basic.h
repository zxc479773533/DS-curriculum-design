/*
 * AVL Tree basic library 
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The kind of AVL tree */
#define FRIENDS 0
#define FOLLOWERS 1
#define FOLLOWING 2

/* The AVL node strcut */
typedef struct AVL_node {
  int user_id;     /* node's id */
  int height;      /* the node height */
  AVL_node *left_child;
  AVL_node *right_child;
} AVL_node;

/* The tree struct */
typedef struct AVL_tree {
  int kind;        /* tree kind */
  int user_id;     /* thee's id */
  int num;         /* node nume */
  AVL_node *root;  /* root node */
} AVL_tree;


/* APIs */
int Init_AVL(AVL_tree *AVL);
int Destroy_AVL(AVL_tree *AVL);
int Search_AVL(AVL_tree *AVL, int user_id);
int Insert_AVL(AVL_tree *AVL, int user_id);
int Delete_AVL(AVL_tree *AVL, int user_id);
int Traverse_AVL(AVL_tree *AVL);

/* Assist functions */
AVL_node* search_avl(AVL_node *tree, int user_id);
AVL_node* insert_avl(AVL_node *tree, int user_id);
AVL_node* delete_avl(AVL_node *tree, AVL_node *node);
AVL_node* find_min(AVL_node *tree);
AVL_node* find_max(AVL_node *tree);
AVL_node* leftleft_rotate(AVL_node *tree);
AVL_node* leftright_rotate(AVL_node *tree);
AVL_node* rightleft_rotate(AVL_node *tree);
AVL_node* rightright_rotate(AVL_node *tree);