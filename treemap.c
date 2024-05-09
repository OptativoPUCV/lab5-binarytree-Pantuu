#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap * treeMap = (TreeMap *)malloc(sizeof(TreeMap));
    if (treeMap == NULL) 
    {
        return NULL;
    }
    treeMap->lower_than = lower_than;
    treeMap->root = NULL;
    
    return treeMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
    newNode->pair = (Pair*)malloc(sizeof(Pair));
    if (newNode->pair == NULL)
    {
        free(newNode);
        return;
    }
    newNode->pair->key = key;
    newNode->pair->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (tree->root == NULL)
    {
        tree->root = newNode;
    }else{
        TreeNode *temp = tree->root;
        while (true){
            if (tree->lower_than(key, temp->pair->key)){
                    if (temp->left == NULL){
                        temp->left = newNode;
                        break;
                    }else{
                        temp = temp->left;
                    }
                }
            else if (tree->lower_than(temp->pair->key, key)){
                if (temp->right == NULL){
                    temp->right = newNode;
                    break;
                }else{
                    temp = temp->right;
                }
            }else{
                free(newNode->pair);
                newNode->pair = temp->pair;
                temp->pair = newNode->pair;
                free(newNode);
                break;
            }
        }
    }
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL){
        return NULL;
    }
    while (x->left != NULL){
        x = x->left;
    }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode *temp = tree->root;
    TreeNode *parent = NULL;

    while(temp !=NULL && temp->pair->key != node->pair->key){
        parent = temp;
        if (node->pair->key < temp->pair->key)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (temp == NULL)
        return;

    if (temp->left == NULL && temp->right == NULL){
        if (temp != tree->root){
            if (parent->left == temp)
                parent->left = NULL;
            else
                parent->right = NULL;
        }else{
            tree->root = NULL;
        }
        free(temp);
    }

    else if (temp->left == NULL || temp->right == NULL){
        TreeNode *child;
        if (temp->left != NULL)
            child = temp->left;
        else
            child = temp->right;

        if (temp != tree->root){
            if (parent->left == temp)
                parent->left = child;
            else
                parent->right = child;
        }else{
            tree->root = child;
        }
        free (temp);
    }

    else{
        TreeNode *successor = minimum(temp->right);
        //int succKey = *((int*)successor->pair->key);
        void *succData = successor->pair->value;
        removeNode(tree, successor);
        //temp->pair->key = succKey;
        temp->pair->value = succData;   
    }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
