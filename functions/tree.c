#include "../headers/tree.h"

int depth(dico* t)
{
    if(t == NULL){return 0;}
    
    int right = depth(t->right), left = depth(t->left);
    
    return (right > left)?right+1:left+1;
}
int bf(dico* tree){
    if(tree == NULL) {
        return 0;
    }
    else{
        return depth(tree->right) - depth(tree->left);
    }
}
void right_rotation(dico** tree){
    if (*tree != NULL){
        dico* temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = *tree;
        *tree = temp;
    }
}
void left_rotation(dico** tree){
    if (*tree != NULL){
        dico* temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = *tree;
        *tree = temp;
    }
}
void balance(dico** tree){
    if (*tree != NULL){
        balance(&((*tree)->left));// Postfix
        balance(&((*tree)->right));

        int balance_factor = bf(*tree);
        if (balance_factor <= -2){
            if(bf((*tree)->left) > 0){
                left_rotation(&((*tree)->left));
            }
            right_rotation(tree);
        }
        else if (balance_factor >= 2){
            if(bf((*tree)->right) < 0){
                right_rotation(&((*tree)->right));
            }
            left_rotation(tree);
        }
    }
}

void trees_balance_BST(dico** tree){
    if(*tree != 0)
    {
        trees_balance_BST(&((*tree)->left));
        trees_balance_BST(&((*tree)->right));
        while(bf(*tree) >= 2 || bf(*tree) <= -2)
        {
            balance(tree);
        }
    }
}

