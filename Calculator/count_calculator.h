#ifndef COUNT_CALCULATOR
#define COUNT_CALCULATOR

#include "../structs_defines_types.h"

double Count_Calculator(tree_t* tree, errors* err);

void Get_Var_Values(tree_t* tree);

double Proc_Count_Calculating(tree_t* tree, Node_t* node, errors* err);

#endif