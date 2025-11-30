#ifndef COUNT_CALCULATOR
#define COUNT_CALCULATOR

#include "structs_defines_types.h"

double Count_Calculator(differentiator_t* tree, errors* err);

double Proc_Count_Calculating(differentiator_t* tree, Node_t* node, errors* err);

#endif