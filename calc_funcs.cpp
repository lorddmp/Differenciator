#include "calc_funcs.h"
#include "tree_calculator_get_vars.h"
#include "tech_func.h"
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
    return Proc_Calculating_With_Ginen_Vars(tree, node->left,err) sign Proc_Calculating_With_Ginen_Vars(tree, node->right, err);    \
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
        return func(Proc_Calculating_With_Ginen_Vars(tree, node->left, err));           \
    else                                                                                \
        return func(Proc_Calculating_With_Ginen_Vars(tree, node->right, err));          \
}

ARITHMETIC_FUNC(ADD_CASE, +)
ARITHMETIC_FUNC(SUB_CASE, -)
ARITHMETIC_FUNC(MUL_CASE, *)

#undef ARITHMETIC_FUNC

double DIV_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL || node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }
    double a = Proc_Calculating_With_Ginen_Vars(tree, node->right, err);
    if (Is_Zero(a))
    {
        fprintf (stderr, "NA NOL DELIT NELZYA!\n");
        *err = ZNAMEN_NULL;
        return 1;
    }
    return Proc_Calculating_With_Ginen_Vars(tree, node->left, err) / Proc_Calculating_With_Ginen_Vars(tree, node->right, err);
}

double STEPEN_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL || node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }

    return pow(Proc_Calculating_With_Ginen_Vars(tree, node->left, err), Proc_Calculating_With_Ginen_Vars(tree, node->right, err));
}

TRIG_FUNCS(SIN_CASE, sin)
TRIG_FUNCS(COS_CASE, cos)
TRIG_FUNCS(TAN_CASE, tan)
double COTAN_CASE(tree_t* tree, Node_t* node, errors* err)
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
    double a = tan(Proc_Calculating_With_Ginen_Vars(tree, node->left, err));
    if (Is_Zero(a))
    {
        fprintf (stderr, "Cotangens doesn't exist at this point\n");;
        *err = ZNAMEN_NULL;
        return 1;
    }
    if (node->left != NULL)
        return 1/tan(Proc_Calculating_With_Ginen_Vars(tree, node->left, err));
    else
        return 1/tan(Proc_Calculating_With_Ginen_Vars(tree, node->right, err));
}

TRIG_FUNCS(ARCSIN_CASE, asin)
TRIG_FUNCS(ARCCOS_CASE, acos)
TRIG_FUNCS(ARCTAN_CASE, atan)
double ARCCOTAN_CASE(tree_t* tree, Node_t* node, errors* err)
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
        return M_PI/2 - tan(Proc_Calculating_With_Ginen_Vars(tree, node->left, err));
    else
        return M_PI/2 - tan(Proc_Calculating_With_Ginen_Vars(tree, node->right, err));
}
#undef TRIG_FUNCS