/*
 * PY execute
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../set.h"
#include "../hashtable.h"

/* Database HASH length */
#define HASHLEN 128

/* User database */
const char database_path[] = "./src/data/users.txt";

/* Function prototypes */

/* Add functions */
void Add_user(int user_id, char *user_name);
void Add_friend(int user_id, int friend_id);
void Add_follower(int user_id, int follower_id);
void Add_following(int user_id, int following_id);

/* Delete functions */
void Delete_user(int user_id);
void Delete_friend(int user_id, int friend_id);
void Delete_follower(int user_id, int follower_id);
void Delete_following(int user_id, int following_id);

/* Find functions */
void Find_user(int user_id);
void Find_friend(int user_id, int friend_id);
void Find_follower(int user_id, int follower_id);
void Find_following(int user_id, int following_id);

/* Display functions */
void Display_friend(int user_id);
void Display_follower(int user_id);
void Display_following(int user_id);

/* Common display fuctions */
void Common_friends(int user_a, int user_b);
void Common_followers(int user_a, int user_b);
void Common_followings(int user_a, int user_b);

/* Others */
void Change_name(int user_id, char *new_name);

/*
 * print_help - Print help messages
 */
void print_help(void) {
  printf("Test help [To be writed...]\n");
}

/* Assist function to show users */
void show_users_visit(HashNode *node) {
  printf("%12d,%18s", node->key, node->value);
}

void show_users(void) {
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  printf("%12s %18s", "User ID", "Name");
  Traverse_Hash(MyHash, show_users_visit);
}

/*
 * builtin_cmd -> Judge buildin command
 * 
 * return <- the result
 */
int builtin_cmd(char **argv) {
  /* Not a built-in command */
  if (!strcmp(argv[0], "quit")) {
    printf("[INFO] User-exit. Terminated!\n");
    exit(0);
  }
  if (!strcmp(argv[0], "help")) {
    print_help();
    return 1;
  }
  if (!strcmp(argv[0], "show")) {
    show_users();
    return 1;
  }

  return 0;
}

/*
 * generate_filename -> Generate the data file name
 * 
 * return <- None
 */
void generate_filename(Set *Set, char *filename) {
  sprintf(filename, "%d-%d.txt", Set->Elem->id, Set->Elem->kind);
}

/*
 * py_execute -> The main execute function
 * 
 * return <- None
 */
int py_execute(char *func , int argc, char **argv) {
  if (!strcmp(func, "add")) {
    if (!strcmp(argv[1], "user") && argc == 4) {
      Add_user(atoi(argv[2]), argv[3]);
      return 1;
    }
    else if (!strcmp(argv[1], "friend") && argc == 4) {
      Add_friend(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "follower") && argc == 4) {
      Add_follower(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "following") && argc == 4) {
      Add_following(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
  }
  else if (!strcmp(func, "delete")) {
    if (!strcmp(argv[1], "user") && argc == 3) {
      Delete_user(atoi(argv[2]));
      return 1;
    }
    else if (!strcmp(argv[1], "friend") && argc == 4) {
      Delete_friend(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "follower") && argc == 4) {
      Delete_follower(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "following") && argc == 4) {
      Delete_follower(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
  }
  else if (!strcmp(func, "find")) {
    if (!strcmp(argv[1], "user") && argc == 3) {
      Find_user(atoi(argv[2]));
      return 1;
    }
    else if (!strcmp(argv[1], "friend") && argc == 4) {
      Find_friend(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "follower") && argc == 4) {
      Find_follower(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "following") && argc == 4) {
      Find_following(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
  }
  else if (!strcmp(func, "display")) {
    if (!strcmp(argv[1], "friend") && argc == 3) {
      Display_friend(atoi(argv[2]));
      return 1;
    }
    else if (!strcmp(argv[1], "follower") && argc == 3) {
      Display_follower(atoi(argv[2]));
      return 1;
    }
    else if (!strcmp(argv[1], "following") && argc == 3) {
      Display_following(atoi(argv[2]));
      return 1;
    }
  }
  else if (!strcmp(func, "common")) {
    if (!strcmp(argv[1], "friend") && argc == 4) {
      Common_friends(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "follower") && argc == 4) {
      Common_followers(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (!strcmp(argv[1], "following") && argc == 4) {
      Common_followings(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
  }
  else if (!strcmp(func, "rename") && argc == 3) {
    Change_name(atoi(argv[1]), argv[2]);
    return 1;
  }
  return 0;
}

/*
 * check_user - Check if user exists
 */
int check_user(int user_id) {
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  char *user_name = Search_Hash(MyHash, user_id);
  if (user_name == NULL)
    return 0;
  else
    return 1;
}

/*
 * Add_user - Add a new user in database
 */
void Add_user(int user_id, char *user_name) {
  int status;
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  status =  Insert_Hash(MyHash, user_id, user_name);
  Save_Hash(MyHash, database_path);
  /* Print info */
  if (status == EXISTS)
    printf("[ERROR] The user has exists!\n");
  else if (status == ERROR)
    printf("[ERROR] Add user faild! Please check your imput.\n");
}

/*
 * Add_friend - Add a new friend in a user's set
 */
void Add_friend(int user_id, int friend_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(friend_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FRIENDS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Insert(new_set, friend_id);
  Save_AVL(new_set->Elem, filename);
  Add_friend(friend_id, user_id);
}

/*
 * Add_follower - Add a new follower in a user's set
 */
void Add_follower(int user_id, int follower_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(follower_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Insert(new_set, follower_id);
  Save_AVL(new_set->Elem, filename);
  Add_following(follower_id, user_id);
}

/*
 * Add_following - Add a new following in a user's set
 */
void Add_following(int user_id, int following_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(following_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWING, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Insert(new_set, following_id);
  Save_AVL(new_set->Elem, filename);
  Add_follower(following_id, user_id);
}

/*
 * Delete_user - Delete a user in database
 */
void Delete_user(int user_id) {
  int status;
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  status = Delete_Hash(MyHash, user_id);
  Save_Hash(MyHash, database_path);
  if (status == ERROR)
    printf("[ERROR] Detele faild! Please check your input.\n");
}

/*
 * Delete_friend - Delete a friend in a user's set
 */
void Delete_friend(int user_id, int friend_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(friend_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FRIENDS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Delete(new_set, friend_id);
  Save_AVL(new_set->Elem, filename);
  Delete_friend(friend_id, user_id);
}

/*
 * Delete_follower - Delete a follower in a user's set
 */
void Delete_follower(int user_id, int follower_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(follower_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Delete(new_set, follower_id);
  Save_AVL(new_set->Elem, filename);
  Delete_following(follower_id, user_id);
}

/*
 * Delete_following - Delete a follower in a user's set
 */
void Delete_following(int user_id, int following_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(following_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWING, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Delete(new_set, following_id);
  Save_AVL(new_set->Elem, filename);
  Delete_follower(following_id, user_id);
}

/*
 * Find_user - Find a user in database
 */
void Find_user(int user_id) {
  char friend_file[20], follower_file[20], following_file[20];  
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  char *user_name = Search_Hash(MyHash, user_id);
  if (user_name == NULL) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  Set *friend_set = Set_Init(FRIENDS, user_id);
  Set *follower_set = Set_Init(FOLLOWERS, user_id);
  Set *following_set = Set_Init(FOLLOWING, user_id);
  generate_filename(friend_set, friend_file);
  generate_filename(follower_set, follower_file);
  generate_filename(following_set, following_file);
  Load_AVL(friend_set->Elem, friend_file);
  Load_AVL(follower_set->Elem, follower_file);
  Load_AVL(following_set->Elem, following_file);
  printf("User ID: %d\n", user_id);
  printf("User Name: %s", user_name);
  printf("Friend: %d\n", friend_set->Elem->num);
  printf("Follower: %d\n", follower_set->Elem->num);
  printf("Following: %d\n", following_set->Elem->num);
}

/*
 * Find_friend - Find a friend in a user's set
 */
void Find_friend(int user_id, int friend_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(friend_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FRIENDS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  if (Set_Member(new_set, friend_id) == OK){
    HashTable *MyHash = Init_Hash(HASHLEN);
    Load_Hash(MyHash, database_path);
    printf("[INFO] Found it! Your friend %s.\n", Search_Hash(MyHash, user_id));
  }
  else {
    printf("[INFO] Not Found!\n");
  }
}

/*
 * Find_follower - Find a followerin a user's set
 */
void Find_follower(int user_id, int follower_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(follower_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  if (Set_Member(new_set, follower_id) == OK){
    HashTable *MyHash = Init_Hash(HASHLEN);
    Load_Hash(MyHash, database_path);
    printf("[INFO] Found it! Your follower %s.\n", Search_Hash(MyHash, user_id));
  }
  else {
    printf("[INFO] Not Found!\n");
  }
}

/*
 * Find_following - Find a following in a user's set
 */
void Find_following(int user_id, int following_id) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(following_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWING, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  if (Set_Member(new_set, following_id) == OK){
    HashTable *MyHash = Init_Hash(HASHLEN);
    Load_Hash(MyHash, database_path);
    printf("[INFO] Found it! You has followed %s.\n", Search_Hash(MyHash, user_id));
  }
  else {
    printf("[INFO] Not Found!\n");
  }
}

/* Assist function to show users */
void dispaly_visit(int user_id) {
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  char *user_name = Search_Hash(MyHash, user_id);
  printf("User ID: %d, Name: %s\n", user_id, user_name);
}

/*
 * Display_friend - Display all of a user's friends
 */
void Display_friend(int user_id) {
  /* Check if user exists */
  if (!check_user(user_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FRIENDS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Traverse_AVL(new_set->Elem, INORDER, dispaly_visit);
}

/*
 * Display_follower - Display all of a user's followers
 */
void Display_follower(int user_id) {
  /* Check if user exists */
  if (!check_user(user_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Traverse_AVL(new_set->Elem, INORDER, dispaly_visit);
}

/*
 * Display_following - Display all of a user's followings
 */
void Display_following(int user_id) {
  /* Check if user exists */
  if (!check_user(user_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[20];
  Set *new_set = Set_Init(FOLLOWING, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Traverse_AVL(new_set->Elem, INORDER, dispaly_visit);
}

/*
 * Common_friends - Show 2 users'common friends
 */
void Common_friends(int user_a, int user_b) {
  /* Check if user exists */
  if (!check_user(user_a) || !check_user(user_b)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename_a[20], filename_b[20];
  Set *set_a = Set_Init(FRIENDS, user_a);
  Set *set_b = Set_Init(FRIENDS, user_b);
  generate_filename(set_a, filename_a);
  generate_filename(set_b, filename_b);
  Load_AVL(set_a->Elem, filename_a);
  Load_AVL(set_b->Elem, filename_b);
  Set *common_set = Set_Intersection(set_a, set_b);
  Traverse_AVL(common_set->Elem, INORDER, dispaly_visit);
}

/*
 * Common_followers - Show 2 users'common followers
 */
void Common_followers(int user_a, int user_b) {
  /* Check if user exists */
  if (!check_user(user_a) || !check_user(user_b)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename_a[20], filename_b[20];
  Set *set_a = Set_Init(FOLLOWERS, user_a);
  Set *set_b = Set_Init(FOLLOWERS, user_b);
  generate_filename(set_a, filename_a);
  generate_filename(set_b, filename_b);
  Load_AVL(set_a->Elem, filename_a);
  Load_AVL(set_b->Elem, filename_b);
  Set *common_set = Set_Intersection(set_a, set_b);
  Traverse_AVL(common_set->Elem, INORDER, dispaly_visit);
}

/*
 * Common_followings - Show 2 users'common followings
 */
void Common_followings(int user_a, int user_b) {
  /* Check if user exists */
  if (!check_user(user_a) || !check_user(user_b)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename_a[20], filename_b[20];
  Set *set_a = Set_Init(FOLLOWING, user_a);
  Set *set_b = Set_Init(FOLLOWING, user_b);
  generate_filename(set_a, filename_a);
  generate_filename(set_b, filename_b);
  Load_AVL(set_a->Elem, filename_a);
  Load_AVL(set_b->Elem, filename_b);
  Set *common_set = Set_Intersection(set_a, set_b);
  Traverse_AVL(common_set->Elem, INORDER, dispaly_visit);
}

/*
 * Change_name - Change a user's name
 */
void Change_name(int user_id, char *new_name) {
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  if(Change_Hash(MyHash, user_id, new_name) ==  ERROR)
    printf("[ERROR] Change failed! Please check your input.\n");
}