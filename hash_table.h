#ifndef _HASH_TABLE
#define _HASH_TABLE

const int HASH_SIZE = 50;

typedef struct node_ {
    char* key;
    int val;
    struct node_ *next;
} node;

node **new_hash_table();
void insert(node** t, char* key, int val);
int *get(node** t, char* key);
void del(node** t, char* key);
void print_hash_table(node** t);

#endif