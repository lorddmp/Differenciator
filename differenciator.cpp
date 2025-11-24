#include "differenciator.h"
#include "tech_func.h"
#include <stdio.h>

tree_t* Differenciator(tree_t* tree, Node_t* node)
{
    tree_t tree_diff = {
        .num_var = tree->num_var,
        .root_node = Proc_Differing(tree->root_node),
        .hash_table = tree->hash_table,
    };
}

Node_t* Proc_Differing(Node_t* node)
{
    if (node->type == NUM_CODE)
    {
        Node_t* diff_node = Make_Node();
        diff_node->type = NUM_CODE;
        diff_node->value.num_t = 0;
        return diff_node;
    }
    else if (node->type == VAR_CODE)
    {
        Node_t* diff_node = Make_Node();
        diff_node->type = NUM_CODE;
        diff_node->value.num_t = 1;
        return diff_node;
    }
    else if (node->value.op_code_t == ADD_CODE)
    {
        Node_t* diff_node = Make_Node();
        diff_node->type = OPER_CODE;
        diff_node->value.num_t = ADD_CODE;
        diff_node->left = Proc_Differing(node->left);
        diff_node->right = Proc_Differing(node->right);
        return diff_node;
    }
}