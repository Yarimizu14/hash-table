#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

lp_node **new_lp_hash_table() {
    lp_node** hash_table;
    hash_table = malloc(sizeof(lp_node*) * HASH_SIZE);

    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table[i] = NULL;
    }

    return hash_table;
};

lp_node *new_node(char* key, int val) {
    lp_node *new_node = (lp_node*)malloc(sizeof(lp_node));
    new_node->key = key;
    new_node->val = val;
    new_node->st = Used;
    return new_node;
}

int hash_func(char* s) {
    int sum = 0;
    int i = 0;

    while(s[i]) {
        sum += s[i];
        i++;
    }

    return sum % HASH_SIZE;
}

void lp_insert(lp_node** t, char* key, int val) {
    int keyHash = hash_func(key);
    lp_node* nn = new_node(key, val);
    for (int i = 0; i < HASH_SIZE; i++) {
        int target = (keyHash + i) % HASH_SIZE;
        lp_node* c = t[target];
        if (c != NULL) {
            if (c->st == Used) {
                continue;
            }
            if (c->st == Deleted) {
                free(c);
            }
        }
        t[target] = nn;
        break;
    }
}

void lp_delete(lp_node** t, char* key) {
    int keyHash = hash_func(key);
    for (int i = 0; i < HASH_SIZE; i++) {
        int target = (keyHash + i) % HASH_SIZE;
        lp_node* c = t[target];
        if (c == NULL) {
            break;
        }
        if (strcmp(c->key, key) == 0) {
            c->st = Deleted;
            break;
        }
    }
}

int *lp_get(lp_node** t, char* key) {
    int keyHash = hash_func(key);
    for (int i = 0; i < HASH_SIZE; i++) {
        int target = (keyHash + i) % HASH_SIZE;
        lp_node* c = t[target];
        if (c == NULL) {
            return NULL;
        }
        if (strcmp(c->key, key) == 0) {
            return &c->val;
        }
    }
    return NULL;
}

void lp_print_hash_table(lp_node** t) {
    printf("------------------------------\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        lp_node* v = t[i];
        if (v != NULL && v->st != Deleted) {
            printf("Key: %s -> %d \n", v->key, v->val);
        }
    }
    printf("------------------------------\n");
}

int main() {
    lp_node** table = new_lp_hash_table();
    char *key = "abc";
    lp_insert(table, key, 3);
    char *key2 = "defaaaccc";
    lp_insert(table, key2, 5);
    char *key3 = "defaaaccca";
    lp_insert(table, key3, 2);
    char *key4 = "defaaca";
    lp_insert(table, key4, 10);
    // lp_print_hash_table(table);
    // del(table, key);
    lp_print_hash_table(table);
    int *r = lp_get(table, key3);
    if (r != NULL) {
        printf("result %d \n", *r);
    }
    lp_delete(table, key);
    lp_print_hash_table(table);
    return 0;
};
