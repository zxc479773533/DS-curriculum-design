/*
 * AVL Tree library 
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#ifndef PY_AVL_LIB
#define PY_AVL_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Status */
#define ERROR 0
#define OK 1

/* The kind of AVL tree */
#define FRIENDS 0
#define FOLLOWERS 1
#define FOLLOWING 2

/* The kind of traverse */
#define PREORDER 0
#define INORDER 1
#define POSTORDER 2 

/* Assisr micro */
#define Max(a, b) ((a > b) ? a : b)

/* The AVL node strcut */
typedef struct AVL_node {
  int key;         /* node key */
  int height;      /* node height */
  struct AVL_node *left_child;
  struct AVL_node *right_child;
} AVL_node;

/* The tree struct */
typedef struct AVL_tree {
  int kind;        /* tree kind */
  int id;          /* tree id */
  int num;         /* node nume */
  AVL_node *root;  /* root node */
} AVL_tree;

/* APIs */
extern AVL_tree* Init_AVL(int kind, int id);
extern void Destroy_AVL(AVL_tree *AVL);
extern void Clear_AVL(AVL_tree *AVL);
extern int Search_AVL(AVL_tree *AVL, int key);
extern void Insert_AVL(AVL_tree *AVL, int key);
extern void Delete_AVL(AVL_tree *AVL, int key);
extern void Traverse_AVL(AVL_tree *AVL, int option, void (*visit)(int));
extern int Save_AVL(AVL_tree *AVL, const char *path);
extern int Load_AVL(AVL_tree *AVL, const char *path);

/* Functions */
int avl_height(AVL_node *tree);
AVL_node* search_avl(AVL_node *tree, int key);
AVL_node* find_min(AVL_node *tree);
AVL_node* find_max(AVL_node *tree);
AVL_node* leftleft_rotate(AVL_node *tree);
AVL_node* rightright_rotate(AVL_node *tree);
AVL_node* leftright_rotate(AVL_node *tree);
AVL_node* rightleft_rotate(AVL_node *tree);
AVL_node* insert_avl(AVL_node *tree, int key, int *safe_tag);
AVL_node* delete_avl(AVL_node *tree, AVL_node *node);
AVL_node* clear_avl(AVL_node *tree);
void traverse_avl(AVL_node *tree, int option, void (*visit)(int));
void save_avl(AVL_node *tree, FILE *fp);
void load_avl(AVL_node *tree, FILE *fp);

#endif // !PY_AVL_LIB
