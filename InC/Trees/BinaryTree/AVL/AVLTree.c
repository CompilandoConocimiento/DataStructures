
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++           AVL TREE FUNTIONS FILE         ++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>                                                              //Library that we are going to use
#include <stdlib.h>                                                             //Library that we are going to use
#include <math.h>                                                               //Library that we are going to use
#include <string.h>                                                             //Library that we are going to use
#include "AVLTree.h"                                                            //Our beloved Binary AVL Tree


/*==========================================================
============ FUNTIONS OF A AVL TREE TREE IN C    =============
==========================================================*/

// ===========================================
// ==      NOT ESSENCIAL BY DEFINITION      ==
// ==  BUT ESSENCIAL FOR MY IMPLEMENTATION  ==
// ===========================================
AVLTree* CreateAVLTree(Item *NewItem){                                          // ==== CREATE A NEW NODE OF A AVL TREE ==
    AVLTreeNode *NewNode = (AVLTreeNode*) malloc(sizeof(AVLTreeNode));          //Reserve memory for this node
    NewNode->NodeItem = NewItem;                                                //You will protect this info with your life
    NewNode->Height = 1;                                                        //The Height of the node
    NewNode->Left = NewNode->Right = NULL;                                      //And maybe you're a leaf
    return NewNode;                                                             //Go, go NewNode, you are complete :')
}
    
// ===========================================
// ==       ESSENCIAL BY DEFINITION         ==
// ===========================================
AVLTree* SearchItemAVL(AVLTree *AVLTreeX, Item *Data){                          // ==== SEARCH IN A BALANCE TREE ===============
    if (AVLTreeX == NULL) {free(Data); return NULL;}                            //NULL means fail D:

    int Comparator = CompareItems(AVLTreeX->NodeItem, Data);                    //Now check to see where to move
    if (Comparator == 1) return SearchItemAVL(AVLTreeX->Left, Data);            //If we have to move because Data is bigger
    if (Comparator == -1) return SearchItemAVL(AVLTreeX->Right, Data);          //If we have to move because Data is smaller

    free(Data);                                                                 //Goodbye pointer, it means you found it!
    return AVLTreeX;                                                            //If you make this far it's mean you are correct
}

// =================================
// ==     THE BALANCE PART        ==
// =================================
int Max(int a, int b){                                                          // ==== AUXILIAR FUNCTION ===================== 
    if (a > b) return a;                                                        //How this function is not implemented yet
    return b;                                                                   //How this function is not implemented yet
}

int Deepness(AVLTree *AVLTreeX){                                                // ==== DEEPNESS OF A TREE BY RECURSION ======= 
    if (AVLTreeX == NULL) return 0;                                             //You know, leafs dont have leafs
    int DeepnessLeft = (Deepness(AVLTreeX->Left)) + 1;                          //Calculate Left tree plus me
    int DeepnessRight = (Deepness(AVLTreeX->Right)) + 1;                        //Calculate Right tree plus me

    if (DeepnessLeft > DeepnessRight) return DeepnessLeft;                      //Choose it!, choose it!
    return DeepnessRight;                                                       //Default, just for the compiler
}

int GetHeight(AVLTree *AVLTreeX){                                               // ==== SECURE WAY TO GET THE HEIGHT ========== 
    if (AVLTreeX == NULL) return 0;                                             //If we have an error
    return AVLTreeX->Height;                                                    //If not, just do nothing
}

int GetBalance(AVLTree *AVLTreeX){                                              // ==== SECURE WAY TO GET THE HEIGHT ========== 
    if (AVLTreeX == NULL) return 0;                                             //If you are nothing
    return GetHeight(AVLTreeX->Left) - GetHeight(AVLTreeX->Right);              //This is the definition
}

/*  ================   REPRESENTATION    ==================
    ============    THIS IS WHAT IM DOING       ===========
    ==                                                   ==
    ==        Y                               X          ==
    ==       / \     Right Rotation -->      /  \        ==
    ==      X   T3   <-- Left Rotation      T1   Y       ==
    ==     / \                                  / \      ==
    ==    T1  T2                              T2  T3     ==
    =====================================================*/

AVLTree* RightRotate(AVLTree *Y){                                               // ==== RIGHT ROTATE  ========================= 
    AVLTree *X = Y->Left;                                                       //Temporal Node
    AVLTree *T2 = X->Right;                                                     //Temporal Node

    X->Right = Y;                                                               //Perform Rotation
    Y->Left = T2;                                                               //Perform Rotation

    Y->Height = Max(GetHeight(Y->Left), GetHeight(Y->Right))+1;                 //Update Height
    X->Height = Max(GetHeight(X->Left), GetHeight(X->Right))+1;                 //Update Height
 
    return X;                                                                   //Return the new Root
}

AVLTree* LeftRotate(AVLTree *X){                                                // ==== LEFT ROTATE   ========================= 
    AVLTree *Y = X->Right;                                                      //Temporal Node
    AVLTree *T2 = Y->Left;                                                      //Temporal Node

    Y->Left = X;                                                                //Perform Rotation
    X->Right = T2;                                                              //Perform Rotation

    X->Height = Max(GetHeight(X->Left), GetHeight(X->Right))+1;                 //Update Height
    Y->Height = Max(GetHeight(Y->Left), GetHeight(Y->Right))+1;                 //Update Height
 
    return Y;                                                                   //Return the new Root
}

void InsertAVL(AVLTree **AVLTreeX, Item *Data){                                 // ==== INSERT IN A BALANCE TREE ============== 
    if (AVLRoot == NULL) {AVLRoot = CreateAVLTree(Data); return;}               //If null tree

    int Comparator = CompareItems(AVLRoot->NodeItem, Data);                     //Now check to see where to move
    if (Comparator==1) InsertAVL(GoRightAVLSubTree, Data);                      //If we have to move because Data is bigger
    else if (Comparator==-1) InsertAVL(GoLeftAVLSubTree, Data);                 //If we have to move because Data is smaller
    else return;                                                                //Return all like anything


    AVLRoot->Height=1+Max(GetHeight(AVLRoot->Left),GetHeight(AVLRoot->Right));  //Update the Height   
    int Balance = GetBalance(AVLRoot);                                          //Now get me the Balance


    if (Balance > 1){                                                           //If we are not balance
        Comparator = CompareItems(AVLRoot->Left->NodeItem, Data);               //Tell me, where is the problem
        if (Comparator == 1) AVLRoot->Left = LeftRotate(AVLRoot->Left);         //If Data is bigger that the left
        if (Comparator != 0) AVLRoot = RightRotate(AVLRoot);                    //If Balance < -1 alway do this
    }

    if (Balance < -1){                                                          //If we are not balance
        Comparator = CompareItems(AVLRoot->Right->NodeItem, Data);              //Tell me, where is the problem
        if (Comparator == -1) AVLRoot->Right = RightRotate(AVLRoot->Right);     //If Data is bigger that the right
        if (Comparator !=  0) AVLRoot = LeftRotate(AVLRoot);                    //If Balance < -1 alway do this
    }

}


// ===========================================
// ==      NOT ESSENCIAL BY DEFINITION      ==
// ==       BUT JUST REALLY REALLY COOL     ==
// ===========================================
void ShowInOrder(AVLTree *AVLTreeX){                                            // ==== SHOW INORDER BY A AVL TREE == 
    if (AVLTreeX == NULL) {printf(" * "); return;}                              //If you are a NULL, sorry
    if (!(AVLTreeX->Right) && !(AVLTreeX->Left))                                //If you are a leaf
        {ShowItem(AVLTreeX->NodeItem); return;}                                 //We should stop here

    printf("< ");                                                               //Give some style
    ShowInOrder(AVLTreeX->Left);                                                //Show the left subtree
    ShowItem(AVLTreeX->NodeItem);                                               //Show the current Item
    ShowInOrder(AVLTreeX->Right);                                               //Show the right subtree
    printf("> ");                                                               //Give some style
}
