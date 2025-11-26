#include "differenciator.h"
#include "tech_func.h"
#include "DSL.h"
#include <stdio.h>
#include <assert.h>


differentiator_t Differenciator(differentiator_t tree)
{
    differentiator_t tree_diff = {
        .num_var = tree.num_var,
        .root_node = Proc_Differing(tree.root_node),
        .hash_table = tree.hash_table,
    };

    return tree_diff;
}

Node_t* Proc_Differing(Node_t* node)
{
    if (node->type == NUM_CODE)
        return Make_Node(NUM_CODE, {.num_t = 0});
    else if (node->type == VAR_CODE)
        return Make_Node(NUM_CODE, {.num_t = 1});
    else
    {
        switch(node->value.op_code_t)
        {
            case ADD_CODE: return _ADD(node);
            case SUB_CODE: return _SUB(node);
            case MUL_CODE: return _MUL(node);
            case DIV_CODE: return _DIV(node);
            case STEPEN_CODE: return _STEPEN(node);
            case SIN_CODE: return _SIN(node);
            case COS_CODE: return _COS(node);
            case TAN_CODE: return _TAN(node);
            case COTAN_CODE: return _COTAN(node);
            case ARCSIN_CODE: return _ARCSIN(node);
            case ARCCOS_CODE: return _ARCCOS(node);
            case ARCTAN_CODE: return _ARCTAN(node);
            case ARCCOTAN_CODE: return _ARCCOTAN(node);
            case LN_CODE: return _LN(node);
            default:
            {
                fprintf (stderr, "ERROR IN CHOOSING OPERATIONS IN DIFFERENCIATOR\n");
                return NULL;
            }
        }
    }
}

Node_t* Proc_Copying(Node_t* node)
{
    assert(node);
    Node_t* new_node = Make_Node(node->type, node->value);

    if (node->left != NULL)
        new_node->left = Proc_Copying(node->left);
    if (node->right != NULL)
        new_node->right = Proc_Copying(node->right);

    return new_node;
}

#define IF_CAN_OPTIMYZED_WITH_RETURN_ONLY_VALUE(func_code, number)                                                              \
if (node->value.op_code_t == func_code && (node->left->type == NUM_CODE && Is_Zero(node->left->value.num_t)))                    \
{                                                                                                                               \
    if (node->parent != NULL)                                                                                                   \
    {                                                                                                                           \
        if (node->parent->left == node)                                                                                         \
            node->parent->left = node->right;                                                                                   \
        else                                                                                                                    \
            node->parent->right = node->right;                                                                                  \
        node->right = NULL;                                                                                                     \
        Tree_Destructor(node);                                                                                                  \
    }                                                                                                                           \
    else                                                                                                                        \
        node = node->right;                                                                                                     \
}                                                                                                                               \
else if (node->value.op_code_t == func_code && (node->right->type == NUM_CODE && Is_Zero(node->right->value.num_t)))            \
{                                                                                                                               \
    if (node->parent != NULL)                                                                                                   \
    {                                                                                                                           \
        if (node->parent->left == node)                                                                                         \
            node->parent->left = node->left;                                                                                    \
        else                                                                                                                    \
            node->parent->right = node->left;                                                                                   \
        node->left = NULL;                                                                                                      \
        Tree_Destructor(node);                                                                                                  \
    }                                                                                                                           \
    else                                                                                                                        \
    {                                                                                                                           \
        node = node->left;                                                                                                      \
        node->parent->left = NULL;                                                                                              \
        Tree_Destructor(node);                                                                                                  \
    }                                                                                                                           \
}

void Proc_Optymizing(Node_t* node)
{
    if (node->type == OPER_CODE)
    {
        if (node->left != NULL)
            Proc_Optymizing(node->left);
        if (node->right != NULL)
            Proc_Optymizing(node->right);

        IF_CAN_OPTIMYZED_WITH_RETURN_ONLY_VALUE(ADD_CODE, 0)
    }
}