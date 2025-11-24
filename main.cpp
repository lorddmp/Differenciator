#include <stdio.h>
#include <stdlib.h>
#include "read_tree.h"
#include "print_tree.h"
#include "tech_func.h"
#include "tree_calculator.h"

int main()
{
    errors err = NO_ERRORS;
    oper_t massive_op[NUM_OPER] = {
        {"-", SUB_CODE, 1},
        {"+", ADD_CODE, 1},
        {"*", MUL_CODE, 1},
        {"/", DIV_CODE, 1},
        {"^", STEPEN_CODE, 1},
        {"sin", SIN_CODE, 3},
        {"cos", COS_CODE, 3},
        {"tan", TAN_CODE, 3},
        {"cotan", COTAN_CODE, 5},
        {"arcsin", ARCSIN_CODE, 6},
        {"arccos", ARCCOS_CODE, 6},
        {"arctan", ARCTAN_CODE, 6},
        {"arccotan", ARCCOTAN_CODE, 6},
    };

    tree_t tree{
        .num_oper = NUM_OPER,/////////
        .num_var = 0,
        .root_node = Read_Tree(&tree, massive_op),
    };

    if (tree.root_node == NULL)                                                                                    
        return 1;                                                                                    

    printf("Tree was read successfully\n");

    double result = Calculator(&tree, &err);
    if (err)
        return 1;

    printf ("result = %lg\n", result);
    Print_Tree(tree.root_node);

    Tree_Destructor(tree.root_node);
    free(tree.hash_table);
    return 0;
}