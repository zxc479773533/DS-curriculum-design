/*
 * AVL Tree implemention
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include "avltree.h"

/*
 * avl_height -> get height of an avl tree
 * 
 * return <- the height
 */
int avl_height(AVL_node *tree) {
  if (tree == NULL)
    return 0;
  else
    return 1 + Max(avl_height(tree->left_child), avl_height(tree->right_child));
}

/*
 * search_avl -> find a node in an avl tree
 * 
 * return <- the ptr to the node
 */
AVL_node* search_avl(AVL_node *tree, int key) {
  /* Find it */
  if (tree == NULL)
    return NULL;
  /* Find in child tree */
  if (tree->key == key)
    return tree;
  else if (tree->key > key)
    return search_avl(tree->left_child, key);
  else
    return search_avl(tree->right_child, key);
}

/*
 * find_min -> find the min node in an avl tree
 * 
 * return <- the ptr to the node
 */
AVL_node* find_min(AVL_node *tree) {
  /* Find it */
  if (tree->left_child == NULL)
    return tree;
  /* Find in left child tree */
  return find_min(tree->left_child);
}

/*
 * find_min -> find the max node in an avl tree
 * 
 * return <- the ptr to the node
 */
AVL_node* find_max(AVL_node *tree) {
  /* Find it */
  if (tree->right_child == NULL)
    return tree;
  /* Find in right child tree */
  return find_max(tree->right_child);
}

/*
 * leftleft_rotate -> do a left-left rorate
 * 
 *       k1                 k2
 *      /  \               /  \
 *     k2  ##   ------>   ##  k1
 *    /  \                   /  \
 *   ##  @@                 @@  ##
 * 
 * return <- k2, the root after rotated
 */
AVL_node* leftleft_rotate(AVL_node *k1) {
  AVL_node *k2 = k1->left_child;
  k1->left_child = k2->right_child;
  k2->right_child = k1;
  k1->height = 1 + Max(avl_height(k1->left_child), avl_height(k1->right_child));
  k2->height = 1 + Max(avl_height(k2->left_child), avl_height(k2->right_child));
  return k2;
}

/*
 * rightright_rotate -> do a right-right rorate
 * 
 *       k1                 k2
 *      /  \               /  \
 *     ##  k2   ------>   k1  ##
 *        /  \           /  \
 *       @@  ##         ##  @@
 * 
 * return <- k2, the root after rotated
 */
AVL_node* rightright_rotate(AVL_node *k1) {
  AVL_node *k2 = k1->right_child;
  k1->right_child = k2->left_child;
  k2->left_child = k1;
  k1->height = 1 + Max(avl_height(k1->left_child), avl_height(k1->right_child));
  k2->height = 1 + Max(avl_height(k2->left_child), avl_height(k2->right_child));
  return k2;
}

/*
 * leftright_rotate -> do a left-right rorate
 * 
 *       k1                  k1
 *      /  \                /  \                 k3
 *     k2  ##              k3  ##               /  \
 *    /  \      ------>   /  \      ------>   k2    k1
 *   ##  k3              k2  %%              / \    / \
 *      /  \            /  \                ## @@  %% ##
 *     @@  %%          ##  @@
 * 
 * return <- k3, the root after rotated
 */
AVL_node* leftright_rotate(AVL_node *k1) {
  k1->left_child = rightright_rotate(k1->right_child);
  return leftleft_rotate(k1);
}

/*
 * rightleft_rotate -> do a right-left rorate
 * 
 *       k1                 k1
 *      /  \               /  \                  k3
 *     ##  k2             ##  k3                /  \
 *        /  \  ------>      /  \   ------>   k1    k2
 *       k3  ##             @@  k2           / \    / \
 *      /  \                   /  \         ## @@  %% ##
 *     @@  %%                 %%  ##
 * 
 * return <- k3, the root after rotated
 */
AVL_node* rightleft_rotate(AVL_node *k1) {
  k1->right_child = leftleft_rotate(k1->right_child);
  return rightright_rotate(k1);
}

/*
 * insert_avl -> insert a node in avl tree
 * 
 * using recursive function, settle height and balance
 * every return
 * 
 * return <- the root node after balanced
 */
AVL_node* insert_avl(AVL_node *tree, int key) {
  /* Create new node */
  if (tree == NULL) {
    tree = (AVL_node*)malloc(sizeof(AVL_node));
    tree->key = key;
    tree->height = 0;
    tree->left_child = NULL;
    tree->right_child = NULL;
  }
  /* Insert in left child tree */
  else if (key < tree->key) {
    tree->left_child = insert_avl(tree->left_child, key);
    /* Balance it */
    if (avl_height(tree->left_child) - avl_height(tree->right_child) == 2) {
      /* Insert left-left */
      if (key < tree->left_child->key)
        tree = leftleft_rotate(tree);
      /* Insert left right */
      else
        tree = leftright_rotate(tree);
    }
  }
  /* Insert in right child tree */
  else if (key > tree->key) {
    tree->right_child = insert_avl(tree->right_child, key);
    /* Balance it */
    if (avl_height(tree->right_child) - avl_height(tree->left_child) == 2) {
      /* Insert right-left */
      if (key < tree->right_child->key)
        tree = rightleft_rotate(tree);
      /* Insert right-right */
      else
        tree = rightright_rotate(tree);
    }
  }

  /* If the key exists, do nothing */

  /* Count height */
  tree->height = 1 + Max(avl_height(tree->left_child), avl_height(tree->right_child));

  return tree;
}

/*
 * delete_avl -> delete a node in avl tree
 * 
 * Three conditions
 * 1. The node is leaf, just delete it
 * 2. The node has two node, replaced it by the max/min node in child tree
 * 3. The node has ome node, replaced it by its child
 * 
 * return <- the root node after balanced
 */
AVL_node* delete_avl(AVL_node *tree, AVL_node *node) {
  /* Nothing to delete */
  if (tree == NULL || node == NULL)
    return NULL;
  /* Delete in left child tree */
  if (node->key < tree->key) {
    tree->left_child = delete_avl(tree->left_child, node);
    /* Balanced it */
    if (avl_height(tree->right_child) - avl_height(tree->left_child) == 2) {
      /* The same as insert right-left */
      if (avl_height(tree->right_child->left_child) > avl_height(tree->right_child->right_child))
        tree = rightleft_rotate(tree);
      /* The same as insert right-right */
      else
        tree = rightright_rotate(tree);
    }
  }
  /* Delete in right child tree */
  else if (node->key > node->key) {
    tree->right_child = delete_avl(tree->right_child, node);
    /* Balanced it */
    if (avl_height(tree->left_child) - avl_height(tree->right_child) == 2) {
      /* The same as left-left insert */
      if (avl_height(tree->left_child->left_child) > avl_height(tree->left_child->right_child))
        tree = leftleft_rotate(tree);
      /* The same as left-right insert */
      else
        tree = leftright_rotate(tree);
    }
  }
  /* Found the node and delete it */
  else {
    /* If the node is leaf */
    if (!(tree->left_child || tree->right_child)) {
      AVL_node* tmp = tree;
      tree = NULL;
      free(tmp);
    }
    /* If the node has two children */
    else if (tree->left_child && tree->right_child) {
      /* Left child tree higher */
      if (avl_height(tree->left_child) > avl_height(tree->right_child)) {
        AVL_node *max_node = find_max(tree->left_child);
        tree->key = max_node->key;
        tree->left_child = delete_avl(tree->left_child, max_node);
      }
      /* Right child tree higher */
      else {
        AVL_node *min_node = find_min(tree->right_child);
        tree->key = min_node->key;
        tree->right_child = delete_avl(tree->right_child, min_node);
      }
    }
    /* If the node has one child */
    else {
      AVL_node *tmp = tree;
      tree = (tree->left_child != NULL) ? tree->left_child : tree->right_child;
      free(tmp);
    }
  }

  return tree;
}

/*
 * clear_avl -> clear all nodes in AVL tree
 * 
 * return <- NULL
 */
AVL_node* clear_avl(AVL_node *tree) {
  if (tree == NULL)
    return NULL;
  /* Free children */
  if (tree->left_child != NULL)
    tree->left_child = clear_avl(tree->left_child);
  if (tree->right_child != NULL)
    tree->right_child = clear_avl(tree->right_child);
  /* Free itself */
  AVL_node *tmp = tree;
  tree = NULL;
  free(tmp);
  return tree;
}

/*
 * traverse_avl -> traverse the AVL tree
 * 
 * return <- NULL
 */
void traverse_avl(AVL_node *tree, int option, void (*visit)(int)) {
  if (option == PREORDER) {
    (*visit)(tree->key);
    traverse_avl(tree->left_child, option, visit);
    traverse_avl(tree->right_child, option, visit);
  }
  else if (option == INORDER) {
    traverse_avl(tree->left_child, option, visit);
    (*visit)(tree->key);
    traverse_avl(tree->right_child, option, visit);
  }
  else if (option == POSTORDER) {
    traverse_avl(tree->left_child, option, visit);
    traverse_avl(tree->right_child, option, visit);
    (*visit)(tree->key);
  }
}

/*
 * APIs implementions
 */

/*
 * API name: Init_AVL
 * Usage: Initial a new AVL tree
 * Arguements:
 *   -> int kind: The kind of an AVL tree
 *   -> int id: The id of an AVL tree
 * Return:
 *   -> AVL_tree* new_avl: The new AVL tree created
 */
AVL_tree* Init_AVL(int kind, int id) {
  AVL_tree *new_avl = (AVL_tree*)malloc(sizeof(AVL_tree));
  /* Malloc error */
  if (new_avl == NULL)
    return NULL;
  /* Initial set */
  new_avl->kind = kind;
  new_avl->id = id;
  new_avl->root = NULL;
  return new_avl;
}

/*
 * API name: Destroy_AVL
 * Usage: Clear and destroy an AVL tree
 * Arguements:
 *   -> AVL_tree *AVL: The AVL tree to be deleted
 * Return: NULL
 */
void Destroy_AVL(AVL_tree *AVL) {
  AVL->root = clear_avl(AVL->root);
  free(AVL);
}

/*
 * API name: Search_AVL
 * Usage: Find a node in an AVL tree
 * Arguements:
 *   -> AVL_tree *AVL: The AVL tree to be searched
 *   -> int key: The key of the node to be found
 * Return:
 *   -> 0 - Nothing found or int node->key - the result
 */
int Search_AVL(AVL_tree *AVL, int key) {
  AVL_node *node = search_avl(AVL->root, key);
  /* If not found, return 0 */
  if (node == NULL)
    return 0;
  else
    return node->key;
}

/*
 * API name: Insert_AVL
 * Usage: Insert a node in an AVL tree
 * Arguements:
 *   -> AVL_tree *AVL: The AVL tree to be inserted
 *   -> int key: The key of the node to be inserted
 * Return: NULL
 */
void Insert_AVL(AVL_tree *AVL, int key) {
  AVL->root = insert_avl(AVL->root, key);
}

/*
 * API name: Delete_AVL
 * Usage: Delete a node in an AVL tree
 * Arguements:
 *   -> AVL_tree *AVL: The AVL tree include the node to be deleted
 *   -> int key: The key of the node to be inserted
 * Return: NULL
 */
void Delete_AVL(AVL_tree *AVL, int key) {
  AVL_node *node = search_avl(AVL->root, key);
  if (node != NULL)
    AVL->root = delete_avl(AVL->root, node);
}

/*
 * API name: Traverse_AVL
 * Usage: Traverse the AVL tree
 * Arguements:
 *   -> AVL_tree *AVL: The AVL tree to be traverse
 *   -> int option: pre/in/postorder traverse
 *   -> void (*visit)(int): The visit function
 * Return: NULL
 */
void Traverse_AVL(AVL_tree *AVL, int option, void (*visit)(int)) {
  traverse_avl(AVL->root, option, visit);
}
