#include <stdio.h>
#include <stdlib.h>
#include "read_tree.h"
#include "print_tree.h"
#include "tech_func.h"
#include "tree_calculator_get_vars.h"

int main()
{
    errors err = NO_ERRORS;

    tree_t tree{
        .num_var = 0,
        .root_node = Read_Tree(&tree),
    };

    if (tree.root_node == NULL)                                                                                    
        return 1;                                                                                    

    printf("Tree was read successfully\n");

    Calculator_With_Getting_Vars(&tree, &err);
    if (err)
        return 1;

    Print_Tree(tree.root_node);

    Tree_Destructor(tree.root_node);
    free(tree.hash_table);
    return 0;
}