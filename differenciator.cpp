#include "differenciator.h"
#include "tech_func.h"
#include <stdio.h>
#include <assert.h>

#define _LEFT  node->left
#define _RIGHT node->right

#define OPER_NODE(a, ...)  Make_Node(OPER_CODE, {.op_code_t = a}, __VA_ARGS__)
#define NUM_NODE(num) Make_Node(NUM_CODE, {.num_t = num})
#define _C(node) Proc_Copying(node)
#define _D(node) Proc_Differing(node)

#define _ADD(node) OPER_NODE(ADD_CODE, _D(_LEFT), _D(_RIGHT))
#define _SUB(node) OPER_NODE(SUB_CODE, _D(_LEFT), _D(_RIGHT))
#define _MUL(node) OPER_NODE(ADD_CODE, _D(_LEFT), _D(_RIGHT))
#define _DIV(node) OPER_NODE(DIV_CODE, OPER_NODE(SUB_CODE, OPER_NODE(MUL_CODE, _D(_LEFT), _C(_RIGHT)), OPER_NODE(MUL_CODE, _C(_LEFT), _D(_RIGHT))), OPER_NODE(STEPEN_CODE, _C(_LEFT), NUM_NODE(2)))
#define _STEPEN(node) OPER_NODE(MUL_CODE, OPER_NODE(STEPEN_CODE, _C(_LEFT), _C(_RIGHT)), OPER_NODE(DIV_CODE, OPER_NODE(ADD_CODE, OPER_NODE(MUL_CODE, OPER_NODE(MUL_CODE, _C(_LEFT), _D(_RIGHT)), OPER_NODE(LN_CODE, _C(_LEFT))), OPER_NODE(MUL_CODE, _D(_LEFT), _C(_RIGHT))), _C(_LEFT)))
#define _SIN(node) OPER_NODE(MUL_CODE, OPER_NODE(COS_CODE, _C(_LEFT)), _D(_LEFT))
#define _COS(node) OPER_NODE(MUL_CODE, OPER_NODE(MUL_CODE, NUM_NODE(-1), OPER_NODE(SIN_CODE, _C(_LEFT))), _D(_LEFT))
#define _TAN(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(1), OPER_NODE(STEPEN_CODE, OPER_NODE(COS_CODE, _C(_LEFT)), NUM_NODE(2))), _D(_LEFT))
#define _COTAN(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(-1), OPER_NODE(STEPEN_CODE, OPER_NODE(SIN_CODE, _C(_LEFT)), NUM_NODE(2))), _D(_LEFT))
#define _ARCSIN(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(1), OPER_NODE(STEPEN_CODE, OPER_NODE(SUB_CODE, NUM_NODE(1), OPER_NODE(STEPEN_CODE, _C(_LEFT), NUM_NODE(2))), NUM_NODE(0.5))), _D(_LEFT))
#define _ARCCOS(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(-1), OPER_NODE(STEPEN_CODE, OPER_NODE(SUB_CODE, NUM_NODE(1), OPER_NODE(STEPEN_CODE, _C(_LEFT), NUM_NODE(2))), NUM_NODE(0.5))), _D(_LEFT))
#define _ARCTAN(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(1), OPER_NODE(ADD_CODE, NUM_NODE(1), OPER_NODE(STEPEN_CODE, _C(_LEFT), NUM_NODE(2)))), _D(_LEFT))
#define _ARCCOTAN(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(-1), OPER_NODE(ADD_CODE, NUM_NODE(1), OPER_NODE(STEPEN_CODE, _C(_LEFT), NUM_NODE(2)))), _D(_LEFT))
#define _LN(node) OPER_NODE(MUL_CODE, OPER_NODE(DIV_CODE, NUM_NODE(1), _C(_LEFT)), _D(_LEFT))

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
    {
        value_dif a = {.num_t = 0};
        return Make_Node(NUM_CODE, a);
    }
    else if (node->type == VAR_CODE)
    {
        value_dif a = {.num_t = 1};
        return Make_Node(NUM_CODE, a);
    }
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