#include "phonebook_opt.h"
/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
Node *AVLHead;

entry* findName(char lastName[], entry *pHead)
{
    int i;
    int key=getHashKey(lastName);
    Node *keynode=findNode(AVLHead,key);
    if(keynode==NULL) {
        return NULL;
    } else {
        entry* currEntry=keynode->entryPtr;
        for(i=0; i<keynode->number; i++) {
            if (strcasecmp(lastName, currEntry->lastName) == 0)
                return currEntry;
            currEntry = currEntry->pNext;
        }
    }
    return NULL;
}

entry* append(char lastName[], entry *headEntry)
{
    /*
    note the input will never be NULL but e->pNext==NULL
    first this func input e pointed to undefine lastName head entry
    always return head
    */
    if(lastName==NULL) {
        return NULL;
    }


    int key=getHashKey(lastName);
    entry* nentry=newEntry(lastName);
    if(headEntry->pNext==NULL) { //first insert
        headEntry->pNext=nentry;
        nentry->pNext=nentry;
        nentry->pPrev=nentry;
        AVLHead=newNode(key,nentry); //this will cause segment fault
    } else {
        AVLHead=insertNode(AVLHead,key,nentry,NULL,MID);
    }
    return headEntry;
}
//phoonbook func
entry* newEntry(char *lastName)
{
    entry* new=(entry*)malloc(sizeof(entry));
    strcpy(new->lastName, lastName);
    new->pNext=NULL;
    new->pPrev=NULL;

    return new;
}

int getHashKey(char lastName[])
{
    int key=0;
    int i;
    for(i=0; i<6; i++) {
        if(lastName[i]=='\0') break;
        key=(key*26)+tolower(lastName[i])-(int)'a'+1;
    }
    return key;
}
//AVL func
int getHeight(Node* node)
{
    if(node==NULL) return 0;
    return node->height;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}



Node* newNode(int key,entry* newPtr)
{
    Node* new=(Node*)malloc(sizeof(Node));
    if(new!=NULL) {
        new->key=key;
        new->number=1;
        new->left=NULL;
        new->right=NULL;
        new->entryPtr=newPtr;
        new->height=0;
    }
    return new;
}

Node* rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Node* insertNode(Node* node, int key,entry* newPtr,entry* targetPtr,Direction dir)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) {
        if(dir==LEFT) {
            insertEntryPrev(targetPtr,newPtr);
        } else if(dir==RIGHT) {
            insertEntryNext(targetPtr,newPtr);
        }
        return newNode(key,newPtr);
    }

    if (key < node->key) {
        node->left  = insertNode(node->left , key, newPtr, node->entryPtr,LEFT);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key, newPtr, node->entryPtr,RIGHT);
    } else { // Equal keys are not allowed in BST
        insertEntryNext(node->entryPtr,newPtr);
        node->number++;
        return node;
    }
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(getHeight(node->left),
                           getHeight(node->right));
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node* findNode(Node* keynode,int key)
{
    if(keynode==NULL) return NULL;

    if(key>keynode->key) {
        return findNode(keynode->right,key);
    } else if(key<keynode->key) {
        return findNode(keynode->left,key);
    }

    return keynode;

}
void insertEntryPrev(entry *targetPtr,entry *newPtr)
{
    if(targetPtr==NULL || newPtr==NULL) return;

    entry *prevTemp=targetPtr->pPrev;
    newPtr->pPrev=prevTemp;
    newPtr->pNext=targetPtr;

    targetPtr->pPrev=newPtr;
    prevTemp->pNext=newPtr;
}

void insertEntryNext(entry *targetPtr,entry *newPtr)
{
    if(targetPtr==NULL || newPtr==NULL) return;

    entry *nextTemp=targetPtr->pNext;
    newPtr->pNext=nextTemp;
    newPtr->pPrev=targetPtr;

    targetPtr->pNext=newPtr;
    nextTemp->pPrev=newPtr;
}

// The function also prints height of every node
void preOrder(Node *root)
{
    if(root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root)
{
    if(root != NULL) {
        inOrder(root->left);
        printf("%d %d\n", root->key,root->number);
        inOrder(root->right);
    }
}