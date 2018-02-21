/*
 * Set function prototype
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#ifndef PY_SET
#define PY_SET

/* Set - implemented by AVL tree */
#include "avltree.h"

typedef struct Set {
  AVL_tree *Elem;
} Set;

/* Set operations */
Set* Set_Init(int kind, int id);
void Set_Destroy(Set *Set);
void Set_Clear(Set *Set);
void Set_Insert(Set *Set, int elem);
void Set_Delete(Set *Set, int elem);
Set* Set_Intersection(Set *Set_A, Set *Set_B);
Set* Set_Union(Set *Set_A, Set* Set_B);
Set* Set_Difference(Set* Set_A, Set* Set_B);
int Set_Size(Set *Set);
int Set_Member(Set *Set, int elem);
int Set_Subset(Set *Set_A, Set* Set_B);
int Set_Equal(Set *Set_A, Set* Set_B);


#endif // !PY_SET
