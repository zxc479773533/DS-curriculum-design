/*
 * Hash Table library
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#ifndef PY_HASH_LIB
#define PY_HASH_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* States define */
#define ERROR 0
#define OK 1
#define EXISTS 2

/* The hash node struct */
typedef struct HashNode {
  int count;
  int key;
  struct HashNode *next;
} HashNode;

/* The hashtable struct */
typedef struct HashTable {
  int num;
  HashNode *Hash;
} HashTable;

/* APIs */

/* Functions */
int HashFunc(int key, int mod);
HashTable* Init_Hash(int hashlen);
int Insert_Hash(HashNode **Hash, int key, int hashlen);

#endif // !PY_HASH_LIB
