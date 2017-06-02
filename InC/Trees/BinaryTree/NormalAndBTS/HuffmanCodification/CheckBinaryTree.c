/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++           BINARY TREE FUNTIONS FILE         ++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>                                                          //Library that we are going to use
#include <stdlib.h>                                                         //Library that we are going to use
#include <math.h>                                                           //Library that we are going to use
#include <string.h>                                                         //Library that we are going to use

#include "BinaryTree.h"                                                     //Our beloved Binary Tree
#include "Stack.h"                                                          //Our beloved Binary Tree

// ================================================
// ===      FUNTIONS THAT I HAVE TO IMPLEMENT   ===
// ================================================
void ShowItem(Item *ItemX){                                                 //=== IMPLEMENTATION OF SHOW ITEM ===
    if (ItemX == NULL) {printf("[ ] "); return;}                           //This is how i draw a NULL
    printf("[%c] ", ItemX->Symbol);                                        //Is an innocent printf
}

Item* CreateNewItem(char Data){                                             //=== IMPLEMENTATION OF CREATE ITEM ===
    Item *Temporal = (Item*) malloc(sizeof(Item));                          //Reserve memory
    Temporal->Symbol = Data;                                                //Just Give the number
    Temporal->Frecuency = 0;                                                //Just Give the number
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
    BinaryTree *TreeX = NULL;                                               //Our test Tree
    int i;                                                                  //Some counter

    FILE *CadenasDeLectura ;              //Sean nuestros lectores
    CadenasDeLectura = fopen(Lectura, "r");                                 //Abramos nuestras archivos

    char LetraQueAnalizo
    while(true){                                                            //Sigamos eternamente XD
        LetraQueAnalizo = fgetc(CadenasDeLectura);                          //Leemos una letra                       

        if (CorreElAutomata(LetraQueAnalizo, Muestra) == true){             //Si acepto la letra actual
            LaCadenaPaso = EstoyEnEstadoFinal();                            //Y vemos si paso sabiendo si esta en estado final
        }

    return 0;
}



    








