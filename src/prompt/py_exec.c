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
void Add_friend(int user_id, int friend_id, int tag);
void Add_follower(int user_id, int follower_id, int tag);
void Add_following(int user_id, int following_id, int tag);

/* Delete functions */
void Delete_user(int user_id);
void Delete_friend(int user_id, int friend_id, int tag);
void Delete_follower(int user_id, int follower_id, int tag);
void Delete_following(int user_id, int following_id, int tag);

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

/* Recommend functions */
void Recommend_friends(int user_id);
void Recommend_followers(int user_id);
void Recommend_followings(int user_id);

/* Others */
void Change_name(int user_id, char *new_name);
void Friends_recommend(int user_id);

/*
 * print_help - Print help messages
 */
void print_help(void) {
  printf("User Manage System vesion 1.1\n");
  printf("Author: Pan Yue\n");
  printf("Basic function:\n");
  printf("    help: Display User's Manual\n");
  printf("    show: Show all users in database\n");
  printf("    rename: Change a user's name\n");
  printf("    rename [user ID] [new name]\n");
  printf("\n");
  printf("    add: Add data\n");
  printf("    add [option] [arg1] [arg2]\n");
  printf("        option=user, add a user, [arg1]=user ID, [arg2]=user name\n");
  printf("        option=friend, add a friend, [arg1]=user ID, [arg2]=friend ID\n");
  printf("        option=follower, add a follower, [arg1]=user ID, [arg2]=follower ID\n");
  printf("        option=following, add a following, [arg1]=user ID, [arg2]=following ID\n");
  printf("\n");
  printf("    delete: Delete data\n");
  printf("    delete [option] [arg1] [arg2]\n");
  printf("        option=user, delete a user, [arg1]=user ID\n");
  printf("        option=friend, delete a friend, [arg1]=user ID, [arg2]=friend ID\n");
  printf("        option=follower, delete a follower, [arg1]=user ID, [arg2]=follower ID\n");
  printf("        option=following, delete a following, [arg1]=user ID, [arg2]=following ID\n");
  printf("\n");
  printf("    find: Find data\n");
  printf("    find [option] [arg1] [arg2]\n");
  printf("        option=user, find a user, [arg1]=user ID\n");
  printf("        option=friend, find a friend, [arg1]=user ID, [arg2]=friend ID\n");
  printf("        option=follower, find a follower, [arg1]=user ID, [arg2]=follower ID\n");
  printf("        option=following, find a following, [arg1]=user ID, [arg2]=following ID\n");
  printf("\n");
  printf("    display: Display data\n");
  printf("    display [option] [user ID]\n");
  printf("        option=friend/follower/following, then display this user's all [option]\n");
  printf("\n");
  printf("    recommend: Recommend for a user\n");
  printf("    recommend [option] [user ID]\n");
  printf("        option=friend/follower/following, then recommend [option] for user\n");
  printf("\n");
  printf("    common: Display common data of 2 users\n");
  printf("    common [option] [user A] [user B]\n");
  printf("        option=friend/follower/following, then display 2 user's common [option]\n");
}

/* Assist function to show users */
void show_users_visit(HashNode *node) {
  printf("%12d %18s\n", node->key, node->value);
}

void show_users(void) {
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  printf("%12s %18s", "User ID", "Name\n");
  Traverse_Hash(MyHash, show_users_visit);
}

/*
 * builtin_cmd -> Judge buildin command
 * 
 * return <- the result
 */
int builtin_cmd(char **argv) {
  /* Not a built-in command */
  if (!strcmp(argv[0], "exit")) {
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
  sprintf(filename, "./src/data/%d-%d.txt", Set->Elem->id, Set->Elem->kind);
}

/*
 * py_execute -> The main execute function
 * 
 * return <- None
 */
int py_execute(char *func , int argc, char **argv) {
  if (!strcmp(func, "add")) {
    if (argc == 4 && !strcmp(argv[1], "user")) {
      Add_user(atoi(argv[2]), argv[3]);
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "friend")) {
      Add_friend(atoi(argv[2]), atoi(argv[3]), 1);
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "follower")) {
      Add_follower(atoi(argv[2]), atoi(argv[3]), 1);
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "following")) {
      Add_following(atoi(argv[2]), atoi(argv[3]), 1);
      return 1;
    }
  }
  else if (!strcmp(func, "delete")) {
    if (argc == 3 && !strcmp(argv[1], "user")) {
      Delete_user(atoi(argv[2]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "friend")) {
      Delete_friend(atoi(argv[2]), atoi(argv[3]), 1);
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "follower")) {
      Delete_follower(atoi(argv[2]), atoi(argv[3]), 1);
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "following")) {
      Delete_follower(atoi(argv[2]), atoi(argv[3]), 1);
      return 1;
    }
  }
  else if (!strcmp(func, "find")) {
    if (argc == 3 && !strcmp(argv[1], "user")) {
      Find_user(atoi(argv[2]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "friend")) {
      Find_friend(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "follower")) {
      Find_follower(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "following")) {
      Find_following(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
  }
  else if (!strcmp(func, "display")) {
    if (argc == 3 && !strcmp(argv[1], "friend")) {
      Display_friend(atoi(argv[2]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "follower")) {
      Display_follower(atoi(argv[2]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "following")) {
      Display_following(atoi(argv[2]));
      return 1;
    }
  }
  else if (!strcmp(func, "common")) {
    if (argc == 4 && !strcmp(argv[1], "friend")) {
      Common_friends(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "follower")) {
      Common_followers(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
    else if (argc == 4 && !strcmp(argv[1], "following")) {
      Common_followings(atoi(argv[2]), atoi(argv[3]));
      return 1;
    }
  }
  else if (argc == 3 && !strcmp(func, "recommend")) {
    if (argc == 3 && !strcmp(argv[1], "friend")) {
      Recommend_friends(atoi(argv[2]));
      return 1;
    }
    else if (argc == 3 && !strcmp(argv[1], "follower")) {
      Recommend_followers(atoi(argv[2]));
      return 1;
    }
    else if (argc == 3 && !strcmp(argv[1], "following")) {
      Recommend_followings(atoi(argv[2]));
      return 1;
    }
  }
  else if (argc == 3 && !strcmp(func, "rename")) {
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
  status = Insert_Hash(MyHash, user_id, user_name);
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
void Add_friend(int user_id, int friend_id, int tag) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(friend_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *new_set = Set_Init(FRIENDS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Insert(new_set, friend_id);
  Save_AVL(new_set->Elem, filename);
  if (tag == 1)
    Add_friend(friend_id, user_id, 0);
}

/*
 * Add_follower - Add a new follower in a user's set
 */
void Add_follower(int user_id, int follower_id, int tag) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(follower_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *new_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Insert(new_set, follower_id);
  Save_AVL(new_set->Elem, filename);
  if (tag == 1)
    Add_following(follower_id, user_id, 0);
}

/*
 * Add_following - Add a new following in a user's set
 */
void Add_following(int user_id, int following_id, int tag) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(following_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *new_set = Set_Init(FOLLOWING, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Insert(new_set, following_id);
  Save_AVL(new_set->Elem, filename);
  if (tag == 1)
    Add_follower(following_id, user_id, 0);
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
void Delete_friend(int user_id, int friend_id, int tag) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(friend_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *new_set = Set_Init(FRIENDS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Delete(new_set, friend_id);
  Save_AVL(new_set->Elem, filename);
  if (tag == 1)
    Delete_friend(friend_id, user_id, 0);
}

/*
 * Delete_follower - Delete a follower in a user's set
 */
void Delete_follower(int user_id, int follower_id, int tag) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(follower_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *new_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Delete(new_set, follower_id);
  Save_AVL(new_set->Elem, filename);
  if (tag == 1)
    Delete_following(follower_id, user_id, 0);
}

/*
 * Delete_following - Delete a follower in a user's set
 */
void Delete_following(int user_id, int following_id, int tag) {
  /* Check if user exists */
  if (!check_user(user_id) || !check_user(following_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *new_set = Set_Init(FOLLOWING, user_id);
  generate_filename(new_set, filename);
  Load_AVL(new_set->Elem, filename);
  Set_Delete(new_set, following_id);
  Save_AVL(new_set->Elem, filename);
  if (tag == 1)
    Delete_follower(following_id, user_id, 0);
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
  printf("User Name: %s\n", user_name);
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
  char filename[25];
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
  char filename[25];
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
  char filename[25];
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
  char filename[25];
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
  char filename[25];
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
  char filename[25];
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
  char filename_a[25], filename_b[25];
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
  char filename_a[25], filename_b[25];
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
  char filename_a[25], filename_b[25];
  Set *set_a = Set_Init(FOLLOWING, user_a);
  Set *set_b = Set_Init(FOLLOWING, user_b);
  generate_filename(set_a, filename_a);
  generate_filename(set_b, filename_b);
  Load_AVL(set_a->Elem, filename_a);
  Load_AVL(set_b->Elem, filename_b);
  Set *common_set = Set_Intersection(set_a, set_b);
  Traverse_AVL(common_set->Elem, INORDER, dispaly_visit);
}

/* Assist function fow recommending */
void traverse_and_add(AVL_node *node, Set *recommend_set) {
  if (node == NULL)
    return;
  traverse_and_add(node->left_child, recommend_set);
  Set_Insert(recommend_set, node->key);
  traverse_and_add(node->right_child, recommend_set);
}

/* Assist function fow recommending */
void traverse_and_recommend(AVL_node *node, Set *recommend_set) {
  if (node == NULL)
    return;
  traverse_and_recommend(node->left_child, recommend_set);
  char filename[25];
  Set *friend_set = Set_Init(FRIENDS, node->key);
  generate_filename(friend_set, filename);
  Load_AVL(friend_set->Elem, filename);
  traverse_and_add(friend_set->Elem->root, recommend_set);
  traverse_and_recommend(node->right_child, recommend_set);
}

/*
 * Recommend_friends - Recommend friends for a user
 */
void Recommend_friends(int user_id) {
  /* Check if user exists */
  if (!check_user(user_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *friend_set = Set_Init(FRIENDS, user_id);
  Set *recommend_set = Set_Init(FRIENDS, user_id);
  generate_filename(friend_set, filename);
  Load_AVL(friend_set->Elem, filename);
  traverse_and_recommend(friend_set->Elem->root, recommend_set);
  Set_Delete(recommend_set, user_id);
  recommend_set = Set_Difference(recommend_set, friend_set);  
  Traverse_AVL(recommend_set->Elem, INORDER, dispaly_visit);
}

/*
 * Recommend_followers - Recommend followers for a user
 */
void Recommend_followers(int user_id) {
  /* Check if user exists */
  if (!check_user(user_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *follower_set = Set_Init(FOLLOWERS, user_id);
  Set *recommend_set = Set_Init(FOLLOWERS, user_id);
  generate_filename(follower_set, filename);
  Load_AVL(follower_set->Elem, filename);
  traverse_and_recommend(follower_set->Elem->root, recommend_set);
  Set_Delete(recommend_set, user_id);
  recommend_set = Set_Difference(recommend_set, follower_set);
  Traverse_AVL(recommend_set->Elem, INORDER, dispaly_visit);
}

/*
 * Recommend_followings - Recommend followings for a user
 */
void Recommend_followings(int user_id) {
  /* Check if user exists */
  if (!check_user(user_id)) {
    printf("[ERROR] Failed! This user is not exists!\n");
    return;
  }
  char filename[25];
  Set *following_set = Set_Init(FOLLOWING, user_id);
  Set *recommend_set = Set_Init(FOLLOWING, user_id);
  generate_filename(following_set, filename);
  Load_AVL(following_set->Elem, filename);
  traverse_and_recommend(following_set->Elem->root, recommend_set);
  Set_Delete(recommend_set, user_id);
  recommend_set = Set_Difference(recommend_set, following_set);
  Traverse_AVL(recommend_set->Elem, INORDER, dispaly_visit);
}

/*
 * Change_name - Change a user's name
 */
void Change_name(int user_id, char *new_name) {
  HashTable *MyHash = Init_Hash(HASHLEN);
  Load_Hash(MyHash, database_path);
  if(Change_Hash(MyHash, user_id, new_name) ==  ERROR)
    printf("[ERROR] Change failed! Please check your input.\n");
  Save_Hash(MyHash, database_path);
}
