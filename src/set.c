/*
 * Set implementions
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include "set.h"

/*
 * Set_Init -> Create a new set
 * 
 * return <- The new set created
 */
Set* Set_Init(int kind, int id) {
  Set* new_set = (Set*)malloc(sizeof(Set));
  new_set->Elem = Init_AVL(kind, id);
  return new_set;
}

/*
 * Set_Destroy -> Destroy a set
 * 
 * return <- None
 */
void Set_Destroy(Set *Set) {
  Destroy_AVL(Set->Elem);
  free(Set);
}

/*
 * Set_Clear -> Clear a set
 * 
 * return <- None
 */
void Set_Clear(Set *Set) {
  Clear_AVL(Set->Elem);
}

/*
 * Set_Insert -> Insert an element in a set
 * 
 * return <- None
 */
void Set_Insert(Set *Set, int elem) {
  Insert_AVL(Set->Elem, elem);
}

/*
 * Set_Delete -> Delete an element in a set
 * 
 * return <- None
 */
void Set_Delete(Set *Set, int elem) {
  Delete_AVL(Set->Elem, elem);
}

/*
 * Set_traverse -> Assist function for intersection, union and difference
 * 
 * Here I use inorder traverse to keep the order
 * 
 * The function visit do the operation
 * 
 * return <- None
 */
void Set_traverse(AVL_node *tree, AVL_tree *Set_B, AVL_tree *Set_result, void (*visit)(int, struct AVL_tree*, struct AVL_tree*)) {
  Set_traverse(tree->left_child, Set_B, Set_result, visit);
  visit(tree->key, Set_B, Set_result);
  Set_traverse(tree->right_child, Set_B, Set_result, visit);
}

/* Assist function fot intetsection */
void visit_intersection(int elem, AVL_tree *Set_B, AVL_tree *Set_result) {
  int key = Search_AVL(Set_B, elem);
  if (key != 0)
    Insert_AVL(Set_result, key);
}

/* Assist function fot union */
void visit_union(int elem, AVL_tree *Set_B, AVL_tree *Set_result) {
  Insert_AVL(Set_result, elem);
}

/* Assist function fot difference */
void visit_difference(int elem, AVL_tree *Set_B, AVL_tree *Set_result) {
  int key = Search_AVL(Set_B, elem);
  if (key == 0)
    Insert_AVL(Set_result, key);
}

/*
 * Set_Intersection -> A ∪ B
 * 
 * return <- A ∪ B
 */
Set* Set_Intersection(Set *Set_A, Set *Set_B) {
  Set *new_set = Set_Init(Set_A->Elem->kind, Set_A->Elem->id);
  Set_traverse(Set_A->Elem->root, Set_B->Elem, new_set->Elem, visit_intersection);
  return new_set;
}

/*
 * Set_Union -> A ∩ B
 * 
 * return <- A ∩ B
 */
Set* Set_Union(Set *Set_A, Set* Set_B) {
  Set *new_set = Set_Init(Set_A->Elem->kind, Set_A->Elem->id);
  Set_traverse(Set_A->Elem->root, Set_B->Elem, new_set->Elem, visit_union);
  Set_traverse(Set_B->Elem->root, Set_A->Elem, new_set->Elem, visit_union);
  return new_set;
}

/*
 * Set_Difference -> A - B
 * 
 * return <- A - B
 */
Set* Set_Difference(Set* Set_A, Set* Set_B) {
  Set *new_set = Set_Init(Set_A->Elem->kind, Set_A->Elem->id);
  Set_traverse(Set_A->Elem->root, Set_B->Elem, new_set->Elem, visit_difference);
  return new_set;
}

/*
 * Set_Size -> Get number of elements in a set
 * 
 * return <- The set size
 */
int Set_Size(Set *Set) {
  if (Set == NULL || Set->Elem == NULL)
    return 0;
  else
    return Set->Elem->num;
}

/*
 * Set_Member -> Judeg whether an element is in a set
 * 
 * return <- The status
 */
int Set_Member(Set *Set, int elem) {
  int key = Search_AVL(Set->Elem, elem);
  if (key == 0)
    return ERROR;
  else
    return OK;
}

/*
 * Set_Subset -> Judeg whether set A is subset of B
 * 
 * Here I use A - B = ∅ to judge
 * 
 * return <- The status
 */
int Set_Subset(Set *Set_A, Set* Set_B) {
  Set *new_set = Set_Difference(Set_A, Set_B);
  if (new_set->Elem->num == 0)
    return OK;
  else
    return ERROR;
}

/*
 * Set_Equal -> Judeg whether set A is equal to set B
 * 
 * Here I use A - B = ∅ && B - A = ∅ to judge
 * 
 * return <- The status
 */
int Set_Equal(Set *Set_A, Set* Set_B) {
  if (Set_Subset(Set_A, Set_B) && Set_Subset(Set_B, Set_A))
    return OK;
  else
    return ERROR;
}
