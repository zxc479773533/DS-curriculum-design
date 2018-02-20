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

/* Status define */
#define ERROR 0
#define OK 1
#define EXISTS 2

/* The hash node struct */
typedef struct HashNode {
  int count;
  int key;
  char value[12];
  struct HashNode *next;
} HashNode;

/* The hashtable struct */
typedef struct HashTable {
  int num;
  int hashlen;
  HashNode *Hash;
} HashTable;

/* APIs */
HashTable* Init_Hash(int hashlen);
int Insert_Hash(HashTable *MyHash, int key, char *value);
int Delete_Hash(HashTable *MyHash, int key);
int Save_Hash(HashTable *MyHash, const char *path);
int Load_Hash(HashTable *MyHash, const char *path);

/* Functions */
int HashFunc(int key, int mod);
int insert_Hash(HashNode **Hash, int key, char *value, int hashlen);
int delete_Hash(HashNode **Hash, int key, int hashlen);
void save_Hash(HashNode **Hash, int hashlen, FILE *fp);
void load_Hash(HashNode **Hash, int hashlen, FILE *fp);

#endif // !PY_HASH_LIB
