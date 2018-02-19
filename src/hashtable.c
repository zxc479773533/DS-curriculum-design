/*
 * Hash Table implemention
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include "hashtable.h"

/*
 * HashFunc -> The hash function
 * 
 * return <- the height
 */
int HashFunc(int key, int mod) {
  return key % mod;
}

/*
 * Init_Hash -> Create an hashtable
 * 
 * return <- the ptr to hashtable
 */
HashTable* Init_Hash(int hashlen) {
  HashTable *MyHash = (HashTable*)malloc(sizeof(HashTable));
  MyHash->num = 0;
  MyHash->Hash = (HashNode*)malloc(sizeof(HashNode) * hashlen);
  memset(MyHash->Hash, 0, sizeof(HashNode) * hashlen);
  return MyHash;
}

/*
 * Insert_Hash -> Insert a node in hash func
 * 
 * return <- the state
 *           OK: insert ok
 *        ERROR: insert error
 *       EXISTS: the node has existed, used for no-repated
 */
int Insert_Hash(HashNode **Hash, int key, int hashlen) {
  int states = EXISTS;
  int index = HashFunc(key, hashlen);
  HashNode *node = Hash[index]->next;
  while (node != NULL) {
    if (node->key == key) {
      node->count++;
      break;
    }
    node = node->next;
  }
  if (node == NULL) {
    HashNode *new_node = (HashNode*)malloc(sizeof(HashNode));
    /* Malloc ERROR */
    if (new_node == NULL)
      return ERROR;
    new_node->key = key;
    new_node->count = 1;
    new_node->next = Hash[index]->next;
    Hash[index]->next = new_node;
    states = OK;
  }
  return states;
}
