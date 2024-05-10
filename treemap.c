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
    if (tree == NULL)return;
    if (tree->root == NULL)
    {
        tree->root = createTreeNode(key, value);
        return;
    }

    TreeNode * aux = tree->root;
    while (aux != NULL)
        {
            if (is_equal(tree, key, aux->pair->key))
            {
                return;
            }
            if (tree->lower_than(key, aux->pair->key))
            {
                if (aux->left == NULL)
                {
                    TreeNode *new = createTreeNode(key, value);
                    new->parent = aux;
                    aux->left = new;
                    tree->current = new;
                    return;
                }
                if (aux->left != NULL) aux = aux->left;
            }
            if (tree->lower_than(aux->pair->key, key))
            {
                if (aux->right == NULL)
                {
                    TreeNode *new = createTreeNode(key, value);
                    new->parent = aux;
                    aux->right = new;
                    tree->current = new;
                    return;
                }
                if (aux->right != NULL) aux = aux->right;
            }
        }
}

TreeNode * minimum(TreeNode * x){
    while (x->left != NULL){
        if (x->left == NULL)break;
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
