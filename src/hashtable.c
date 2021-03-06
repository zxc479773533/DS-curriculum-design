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
 * insert_Hash -> Insert a node in hash func
 * 
 * return <- the status
 *           OK: insert ok
 *        ERROR: insert error
 *       EXISTS: the node has existed, used for no-repated
 */
int insert_Hash(HashNode **Hash, int key, char *value, int hashlen) {
  int status = EXISTS;
  int index = HashFunc(key, hashlen);
  HashNode *node = Hash[index]->next;
  while (node != NULL) {
    if (node->key == key) {
      /* Here I set no-repeate hash table */
      if (node->count == 0) {
        node->count++;
        status = OK;
      }
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
    strcpy(new_node->value, value);
    new_node->count = 1;
    new_node->next = Hash[index]->next;
    Hash[index]->next = new_node;
    status = OK;
  }
  return status;
}

/*
 * delete_Hash -> Delete a node in hash func
 * 
 * return <- the status
 *           OK: Delete ok
 *        ERROR: Delete error
 */
int delete_Hash(HashNode **Hash, int key, int hashlen) {
  int status = ERROR;
  int index = HashFunc(key, hashlen);
  HashNode *node = Hash[index]->next;
  while (node != NULL) {
    if (node->key == key) {
      if (node->count > 0) {
        node->count--;
        strcpy(node->value, "Disable");
        status = OK;
      }
      break;
    }
    node = node->next;
  }
  return status;
}

/*
 * search_Hash -> Search a node in an Hash table
 * 
 * return <- The node
 */
HashNode* search_Hash(HashNode **Hash, int key, int hashlen) {
  int index = HashFunc(key, hashlen);
  HashNode *node = Hash[index]->next;
  while (node != NULL) {
    if (node->key == key && node->count > 0)
      return node;
    node = node->next;
  }
  return NULL;
}

/*
 * change_Hash -> Change an Hash node's name
 * 
 * return <- The state
 */
int change_Hash(HashNode **Hash, int key, char *value, int hashlen) {
  HashNode *node = search_Hash(Hash, key, hashlen);
  if (node == NULL)
    return ERROR;
  else {
    strcpy(node->value, value);
    return OK;
  }
}

/*
 * traverse_Hash -> Traverse Hash table
 * 
 * return <- None
 */
void traverse_Hash(HashNode **Hash, int hashlen, void (*visit)(struct HashNode*)) {
  int index;
  for (index = 0; index < hashlen; index++) {
    HashNode *node = Hash[index]->next;
    while (node != NULL) {
      (*visit)(node);
      node = node->next;
    }
  }
}

/*
 * save_Hash -> Save Hash table to a file
 * 
 * return <- None
 */
void save_Hash(HashNode **Hash, int hashlen, FILE *fp) {
  int index;
  for (index = 0; index < hashlen; index++) {
    HashNode *node = Hash[index]->next;
    while (node != NULL) {
      fprintf(fp, "%d %s\n", node->key, node->value);
      node = node->next;
    }
  }
}

/*
 * load_Hash -> Load Hash table from a file
 * 
 * return <- None
 */
void load_Hash(HashNode **Hash, int hashlen, FILE *fp) {
  int index;
  int key;
  char value[12];
  while (fscanf(fp, "%d %s\n", &key, value) == 2) {
    insert_Hash(Hash, key, value, hashlen);
  }
}

/*
 * APIs implementions
 */

/*
 * API name: Init_Hash
 * Usage: Initial a new Hash table
 * Arguements:
 *   -> int hashlen: The length of an Hash table
 * Return:
 *   -> HashTable* MyHash: The new Hash table created
 */
HashTable* Init_Hash(int hashlen) {
  HashTable *MyHash = (HashTable*)malloc(sizeof(HashTable));
  MyHash->num = 0;
  MyHash->hashlen = hashlen;
  MyHash->Hash = (HashNode**)malloc(sizeof(HashNode) * hashlen);
  memset(MyHash->Hash, 0, sizeof(HashNode) * hashlen);
  for (int i = 0; i < hashlen; i++) {
    MyHash->Hash[i] = (HashNode*)malloc(sizeof(HashNode));
    MyHash->Hash[i]->key = 0;
    MyHash->Hash[i]->count = 0;
    MyHash->Hash[i]->next = NULL;    
  }
  return MyHash;
}

/*
 * API name: Insert_Hash
 * Usage: Insert a node in hash table
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to be inserted
 *   -> int key: The key of new node
 * Return:
 *   -> int status: The status of this function
 */
int Insert_Hash(HashTable *MyHash, int key, char *value) {
  int status = insert_Hash(MyHash->Hash, key, value, MyHash->hashlen);
  if (status == OK)
    MyHash->num++;
  return status;
}

/*
 * API name: Delete_Hash
 * Usage: Delete a node in hash table
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to be deleted
 *   -> int key: The key of node to be deleted
 * Return:
 *   -> int status: The status of this function
 */
int Delete_Hash(HashTable *MyHash, int key) {
  if (MyHash->num == 0)
    return ERROR;
  int status = delete_Hash(MyHash->Hash, key, MyHash->hashlen);
  /*if (status == OK)
    MyHash->num--;*/
  return status;
}

/*
 * API name: Search_Hash
 * Usage: Search a node in an Hash table
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to be searched
 *   -> int key: The key of node to be searched
 * Return:
 *   -> int status: The value of the node
 */
char* Search_Hash(HashTable *MyHash, int key) {
  if (MyHash->num == 0)
    return NULL;
  HashNode *node = search_Hash(MyHash->Hash, key, MyHash->hashlen);
  if (node != NULL)
    return node->value;
  else
    return NULL;
}

/*
 * API name: Save_Hash
 * Usage: Save Hast table to a file
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to be saved
 *   -> const char *path: The data file path
 * Return: status
 */
int Save_Hash(HashTable *MyHash, const char *path) {
  FILE *fp = fopen(path, "w");
  if (fp == NULL)
    return ERROR;
  fprintf(fp, "%d %d\n", MyHash->num, MyHash->hashlen);
  save_Hash(MyHash->Hash, MyHash->hashlen, fp);
  fclose(fp);
  return OK;
}

/*
 * API name: Load_Hash
 * Usage: Load Hast table from a file
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to receive data
 *   -> const char *path: The data file path
 * Return: status
 */
int Load_Hash(HashTable *MyHash, const char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL)
    return ERROR;
  int num, hashlen;
  fscanf(fp, "%d %d\n", &num, &hashlen);
  MyHash->num = num;
  MyHash->hashlen = hashlen;
  load_Hash(MyHash->Hash, MyHash->hashlen, fp);
  fclose(fp);
  return OK;
}

/*
 * API name: Traverse_Hash
 * Usage: Traverse Hash table
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to be traversed
 *   -> void (*visit)(struct HashNode*): The traverse function
 * Return: None
 */
void Traverse_Hash(HashTable *MyHash ,void (*visit)(struct HashNode*)) {
  traverse_Hash(MyHash->Hash, MyHash->hashlen, visit);
}

/*
 * API name: Change_Hash
 * Usage: Change an Hash node's name
 * Arguements:
 *   -> HashTable *MyHash: The Hash table to be changed
 *   -> int key: The node's key
 *   -> char *value: The new value
 * Return: None
 */
int Change_Hash(HashTable *MyHash, int key, char *value) {
  return change_Hash(MyHash->Hash, key, value, MyHash->hashlen);
}