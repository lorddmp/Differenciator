#ifndef READ_TREE
#define READ_TREE

#include <stdio.h>
#include "structs_defines_types.h"

Node_t* Read_Tree(differentiator_t* tree);

Node_t* Read_Node(differentiator_t* tree, int* position, char* massive);

Node_t* Obrabotka_Node(differentiator_t* tree, int* position, char* massive);

Node_t* Spot_Type(differentiator_t* tree, int* position, char* massive);

int Operation_checking(int* position, char* massive);

int Var_Checking(differentiator_t* tree, int* position, char* massive);

#endif