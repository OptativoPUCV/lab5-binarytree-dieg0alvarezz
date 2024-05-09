#include <stdio.h>
#include <stdlib.h>
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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;
    return new;
}    



void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * new = createTreeNode(key, value);
    if (tree->root == NULL)
    {
        tree->root = new;
        tree->current = new;
        return;
    }
    TreeNode * current = tree->root;
    TreeNode * parent = NULL;
    while (current != NULL)
        {
            parent = current;
            if (is_equal(tree, key, current->pair->key)) return;
            if (tree->lower_than(key, current->pair->key) == 1)
            {
                current = current->left;
                
            }
            else
            {
                current = current->right;
                
            }
            
        }
    new->parent = parent;
    if (tree->lower_than(key, parent->pair->key) == 1)
    {
        parent->left = new;
        
    }
    else
    {
        parent->right = new;
        
    }
    tree->current = new;
}




TreeNode * minimum(TreeNode * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;


}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;

    TreeNode * current = tree->root;
    while (current != NULL)
        {
            if (is_equal(tree,key,current->pair->key) == 1)
            {
                tree->current = current;
                return current->pair;
                
            }
            if (tree->lower_than(key,current->pair->key) == 1)
            {
                current = current->left;
                
            }
            else
            {
                current = current->right;
                
            }
            
        }
    
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * current = tree->root;
    TreeNode * ub = NULL;
    while (current != NULL)
        {
            if (is_equal(tree,key,current->pair->key) == 1)
            {
                ub = current;
                tree->current = current;
                return current->pair;
            }
            if (tree->lower_than(key,current->pair->key) == 1)

            {
                current = current->left;
                
                
                
            }
            else
            {
                ub = current;
                current = current->right;
                
            }
        }
    tree->current = ub;
    return ub->pair;
  
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * current = minimum(tree->root);
    tree->current = current;
    return current->pair;
    

}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) {
        return NULL;
    }
    TreeNode * current = tree->current;
    if (current->right != NULL) {
        current = minimum(current->right);
        tree->current = current;
        return current->pair;
    }
    TreeNode * parent = current->parent;
    while (parent != NULL && current == parent->right) {
        current = parent;
        parent = parent->parent;   
    }
    tree->current = parent;
    if (parent != NULL) {
        return parent->pair;
    }
    else {
        return NULL;
    }
}