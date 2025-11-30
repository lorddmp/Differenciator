#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "print_tree.h"
#include "tech_func.h"
#include "count_calculator.h"
#include "calculator.h"
#include "differenciator.h" 
#include "reading_tree.h"
// Придумать грамматику для простого языка. В языке есть if, else, new_var, (), +-/*==!=, 
// == !=

int main()
{
    errors err = NO_ERRORS;

    differentiator_t tree = Read_Expression();

    if (tree.root_node == NULL)                                                                                    
        return 1;


    printf("Tree was read successfully\n");
    // printf("result = %lg", Count_Calculator(&tree, &err));

    differentiator_t tree_diff = Differenciator(tree);
    Calculate(&tree_diff, tree_diff.root_node, &err);
    Proc_Optymizing(&tree_diff.root_node);

    if (err)
        return 1;
    // Calculate(&tree, tree.root_node, &err);
    // differentiator_t tree_diff = Differenciator(tree);
    // Calculate(&tree_diff, tree_diff.root_node, &err);

    // // double result = Count_Calculator(&tree, &err);
    // // printf("%lg", result);
    // Proc_Optymizing(&tree_diff.root_node);

    Print_Tree(tree_diff.root_node);
    // Print_Tree(tree.root_node);

    Tree_Destructor(tree.root_node);
    Tree_Destructor(tree_diff.root_node);
    free(tree.hash_table);
    return 0;
}
