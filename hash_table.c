#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

node **new_hash_table() {
    // https://stackoverflow.com/questions/34227581/work-around-error-address-of-stack-memory-associated-with-local-variable-return
    // https://stackoverflow.com/questions/15686890/how-to-allocate-array-of-pointers-for-strings-by-malloc-in-c
    node** hash_table;
    hash_table = malloc(sizeof(node*) * HASH_SIZE);

    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        hash_table[i] = NULL;
    }

    return hash_table;
};

node *new_node(char* key, int val) {
    node *new_node = (struct node_ *)malloc(sizeof(struct node_));
    new_node->key = key;
    new_node->val = val;
    new_node->next = NULL;
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

void insert(node** t, char* key, int val) {
    int keyHash = hash_func(key);
    node* c = t[keyHash];
    printf("%d \n", keyHash);
    node* nn = new_node(key, val);
    if (c == NULL) {
        t[keyHash] = nn;
        return;
    }
    while (c->next != NULL) {
        c = c->next;
    }
    c->next = nn;
}

int *get(node** t, char* key) {
    int keyHash = hash_func(key);
    node* c = t[keyHash];
    while (c != NULL) {
        if (strcmp(c->key, key) == 0) {
            return &c->val;
        }
        c = c->next;
    }
    return NULL;
}

void del(node** t, char* key) {
    int keyHash = hash_func(key);
    node* c = t[keyHash];
    node* prev = NULL;
    while (c != NULL) {
        if (strcmp(c->key, key) == 0) {
            if (prev == NULL) {
                t[keyHash] = c->next;
            } else {
                prev->next = c->next;
            }
            free(c);
            printf("Key %s is deleted\n", key);
            return;
        }
        prev = c;
        c = c->next;
    }
}

void print_hash_table(node** t) {
    printf("------------------------------\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        node* v = t[i];
        while (v != NULL) {
            printf("Key: %s -> %d \n", v->key, v->val);
            v = v->next;
        }
    }
    printf("------------------------------\n");
}

int main() {
    node** table = new_hash_table();
    char *key = "abc";
    insert(table, key, 3);
    char *key2 = "defaaaccc";
    insert(table, key2, 5);
    char *key3 = "defaaaccca";
    insert(table, key3, 2);
    char *key4 = "defaaca";
    insert(table, key4, 10);
    print_hash_table(table);
    del(table, key);
    print_hash_table(table);
    del(table, key4);
    print_hash_table(table);
    return 0;
};
