#ifndef READ_TREE
#define READ_TREE

#include <stdio.h>
#include "structs_defines_types.h"

Node_t* Read_Tree(tree_t* tree, oper_t* massive_op);

Node_t* Read_Node(tree_t* tree, oper_t* massive_op, int* position, char* massive);

Node_t* Obrabotka_Node(tree_t* tree, oper_t* massive_op, int* position, char* massive);

Node_t* Spot_Type(tree_t* tree, oper_t* massive_op, Node_t* node, int* position, char* massive);

int Operation_checking(tree_t* tree, oper_t* massive_op, Node_t* node, int* position, char* massive);

bool Var_Checking(tree_t* tree, Node_t* node, int* position, char* massive);

#endif