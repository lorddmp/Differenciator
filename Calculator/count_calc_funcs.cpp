#include "count_calc_funcs.h"
#include "count_calculator.h"
#include "../tech_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARITHMETIC_FUNC(funcname, sign)                                                                                             \
double funcname(tree_t* tree, Node_t* node, errors* err)                                                                            \
{                                                                                                                                   \
    if (node->left == NULL || node->right == NULL)                                                                                  \
    {                                                                                                                               \
        fprintf (stderr, "Empty node where it needs to be filled");                                                                 \
        *err = NODE_NULL;                                                                                                           \
        return 0;                                                                                                                   \
    }                                                                                                                               \
    return Proc_Count_Calculating(tree, node->left,err) sign Proc_Count_Calculating(tree, node->right, err);    \
}

#define TRIG_FUNCS(funcname, func)                                                      \
double funcname(tree_t* tree, Node_t* node, errors* err)                                \
{                                                                                       \
    if (node->left == NULL && node->right == NULL)                                      \
    {                                                                                   \
        fprintf (stderr, "Empty node where it needs to be filled\n");                   \
        *err = NODE_NULL;                                                               \
        return 1;                                                                       \
    }                                                                                   \
    else if (node->left != NULL && node->right != NULL)                                 \
    {                                                                                   \
        fprintf (stderr, "Trig_func gets only one argument\n");                         \
        *err = TOO_MANY_ARGS;                                                           \
        return 1;                                                                       \
    }                                                                                   \
                                                                                        \
    if (node->left != NULL)                                                             \
        return func(Proc_Count_Calculating(tree, node->left, err));           \
    else                                                                                \
        return func(Proc_Count_Calculating(tree, node->right, err));          \
}

ARITHMETIC_FUNC(COUNT_ADD_CASE, +)
ARITHMETIC_FUNC(COUNT_SUB_CASE, -)
ARITHMETIC_FUNC(COUNT_MUL_CASE, *)

#undef ARITHMETIC_FUNC

double COUNT_DIV_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL || node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }
    double a = Proc_Count_Calculating(tree, node->right, err);
    if (Is_Zero(a))
    {
        fprintf (stderr, "NA NOL DELIT NELZYA!\n");
        *err = ZNAMEN_NULL;
        return 1;
    }
    return Proc_Count_Calculating(tree, node->left, err) / Proc_Count_Calculating(tree, node->right, err);
}

double COUNT_STEPEN_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL || node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }

    return pow(Proc_Count_Calculating(tree, node->left, err), Proc_Count_Calculating(tree, node->right, err));
}

TRIG_FUNCS(COUNT_SIN_CASE, sin)
TRIG_FUNCS(COUNT_COS_CASE, cos)
TRIG_FUNCS(COUNT_TAN_CASE, tan)
double COUNT_COTAN_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL && node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }
    else if (node->left != NULL && node->right != NULL)
    {
        fprintf (stderr, "Trig_func gets only one argument\n");
        *err = TOO_MANY_ARGS;
        return 1;
    }
    double a = tan(Proc_Count_Calculating(tree, node->left, err));
    if (Is_Zero(a))
    {
        fprintf (stderr, "Cotangens doesn't exist at this point\n");;
        *err = ZNAMEN_NULL;
        return 1;
    }
    if (node->left != NULL)
        return 1/tan(Proc_Count_Calculating(tree, node->left, err));
    else
        return 1/tan(Proc_Count_Calculating(tree, node->right, err));
}

TRIG_FUNCS(COUNT_ARCSIN_CASE, asin)
TRIG_FUNCS(COUNT_ARCCOS_CASE, acos)
TRIG_FUNCS(COUNT_ARCTAN_CASE, atan)
double COUNT_ARCCOTAN_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL && node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }
    else if (node->left != NULL && node->right != NULL)
    {
        fprintf (stderr, "Trig_func gets only one argument\n");
        *err = TOO_MANY_ARGS;
        return 1;
    }
    if (node->left != NULL)
        return M_PI/2 - tan(Proc_Count_Calculating(tree, node->left, err));
    else
        return M_PI/2 - tan(Proc_Count_Calculating(tree, node->right, err));
}
#undef TRIG_FUNCS