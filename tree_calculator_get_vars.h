#ifndef CALCULATOR
#define CALCULATOR

double Calculator_With_Getting_Vars(tree_t* tree, errors* err);

void Get_Var_Values(tree_t* tree);

double Proc_Calculating_With_Ginen_Vars(tree_t* tree, Node_t* node, errors* err);

#endif