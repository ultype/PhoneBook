#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#define MAX_LAST_NAME_SIZE 16
/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT1
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
typedef enum {MID,LEFT,RIGHT} Direction;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
    struct __PHONE_BOOK_ENTRY *pPrev;
} entry;

typedef struct NODE {
    int key;
    int number;
    struct NODE *left;
    struct NODE *right;
    struct __PHONE_BOOK_ENTRY *entryPtr;
    int height;
} Node;

/*protocol func*/
entry* findName(char lastName[], entry *pHead);
entry* append(char lastName[], entry *e);

/*hash*/
int getHashKey(char *lastName);

/*AVL NODE func*/
int max(int a, int b);
int getHeight(Node* node);
int getBalance(Node *N);
Node* newNode(int key,entry* newPtr);
Node* rightRotate(Node *y);
Node* leftRotate(Node *x);
Node* insertNode(Node* node, int key,entry* newPtr,entry* targetPtr,Direction dir);
Node* findNode(Node* node,int key);
void preOrder(Node *root);
void inOrder(Node *root);
/*entry doubly linked list*/
entry* newEntry(lastName);
void insertEntryPrev(entry *targetPtr,entry *newPtr);
void insertEntryNext(entry *targetPtr,entry *newPtr);
/*global*/
Node *AVLHead;

#endif
