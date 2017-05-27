/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++           BINARY TREE FUNTIONS FILE         ++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>                                                          //Library that we are going to use
#include <stdlib.h>                                                         //Library that we are going to use
#include <math.h>                                                           //Library that we are going to use
#include <string.h>                                                         //Library that we are going to use

#include "AVLTree.h"                                                        //Our beloved Binary Tree

// ================================================
// ===      FUNTIONS THAT I HAVE TO IMPLEMENT   ===
// ================================================
void ShowItem(Item *ItemX){                                                //=== IMPLEMENTATION OF SHOW ITEM ===
    if (ItemX == NULL) {printf("[ ] "); return;}                           //This is how i draw a NULL
    printf("[%i] ", ItemX->Symbol);                                        //Is an innocent printf
}

Item* CreateItem(){                                                         //=== IMPLEMENTATION OF CREATE ITEM ===
    Item *Temporal = (Item*) malloc(sizeof(Item));                          //Reserve memory
    printf("Give me a Int: ");                                             //Simple message
    scanf("%i%*c", &Temporal->Symbol);                                      //Give me data!, I need data :3
    return Temporal;                                                        //You are complete, go, and protect the data
}

Item* CreateNewItem(int Data){                                             //=== IMPLEMENTATION OF CREATE ITEM ===
    Item *Temporal = (Item*) malloc(sizeof(Item));                          //Reserve memory
    Temporal->Symbol = Data;                                                //Just Give the number
    return Temporal;                                                        //You are complete, go, and protect the data
}

int CompareItems(Item *DataLeft, Item *DataRight){                          //=== COMPARE FOR BIGGER -1:LEFT, 1:Right ======
    if (DataLeft == NULL) return 1;                                         //If there was nothing in here
    if (DataRight == NULL) return -1;                                       //If there was nothing in here

    if ( (int)DataLeft->Symbol == (int)DataRight->Symbol ) return 0;        //Change
    if ( (int)DataLeft->Symbol < (int)DataRight->Symbol ) return 1;         //Change

    return -1;                                                              //Change (compiler)
}

// ================================================
// ============         MAIN     ==================
// ================================================
int main(){
    AVLTree *AVLTreeX = NULL;                                               //Our test Tree


    InsertAVL(&AVLTreeX, CreateNewItem(10));
    InsertAVL(&AVLTreeX, CreateNewItem(20));
    InsertAVL(&AVLTreeX, CreateNewItem(30));
    InsertAVL(&AVLTreeX, CreateNewItem(40));
    InsertAVL(&AVLTreeX, CreateNewItem(50));
    InsertAVL(&AVLTreeX, CreateNewItem(25));

    ShowInOrder(AVLTreeX);
    return 0;
}



    








