#include "structs_defines_types.h"
#include "tree_calculator.h"
#include "tech_func.h"
#include <stdio.h>
#include <math.h>

#define ARITHMETIC_FUNC(funcname, sign)                                                             \
double funcname(tree_t* tree, Node_t* node, errors* err)                                            \
{                                                                                                   \
    if (node->left == NULL || node->right == NULL)                                                  \
    {                                                                                               \
        fprintf (stderr, "Empty node where it needs to be filled");                                 \
        *err = NODE_NULL;                                                                           \
        return 0;                                                                                   \
    }                                                                                               \
    return Proc_Calculating(tree, node->left,err) sign Proc_Calculating(tree, node->right, err);    \
}

#define TRIG_FUNCS(funcname, func)                                      \
double funcname(tree_t* tree, Node_t* node, errors* err)                \
{                                                                       \
    if (node->left == NULL && node->right == NULL)                      \
    {                                                                   \
        fprintf (stderr, "Empty node where it needs to be filled\n");   \
        *err = NODE_NULL;                                               \
        return 1;                                                       \
    }                                                                   \
    else if (node->left != NULL && node->right != NULL)                 \
    {                                                                   \
        fprintf (stderr, "Trig_func gets only one argument\n");         \
        *err = TOO_MANY_ARGS;                                           \
        return 1;                                                       \
    }                                                                   \
                                                                        \
    if (node->left != NULL)                                             \
        return func(Proc_Calculating(tree, node->left, err));           \
    else                                                                \
        return func(Proc_Calculating(tree, node->right, err));          \
}

struct functions{
    double(*funcname)(tree_t* tree, Node_t* node, errors* err);
    enum oper_codes func_code;
};

functions mas_functions[NUM_OPER] = {
    {ADD_CASE, ADD_CODE},
    {SUB_CASE, SUB_CODE},
    {MUL_CASE, MUL_CODE},
    {DIV_CASE, DIV_CODE},
    {STEPEN_CASE, STEPEN_CODE},
    {SIN_CASE, SIN_CODE},
    {COS_CASE, COS_CODE},
    {TAN_CASE, TAN_CODE},
    {COTAN_CASE, COTAN_CODE},
    {ARCSIN_CASE, ARCSIN_CODE},
    {ARCCOS_CASE, ARCCOS_CODE},
    {ARCTAN_CASE, ARCTAN_CODE},
    {ARCCOTAN_CASE, ARCCOTAN_CODE},
};

double Calculator(tree_t* tree, errors* err)
{
    Get_Var_Values(tree);

    return Proc_Calculating(tree, tree->root_node, err);;
}

void Get_Var_Values(tree_t* tree)
{
    printf("Please write values of all given variables:\n");

    for (int i = 0; i < tree->num_var; i++)
    {
        while(true)
        {
            printf("%s = ?\b", tree->hash_table[i].name);
            if (scanf("%lg", &tree->hash_table[i].var_value) == 1)
                break;
            else
                printf("Error in getting variable. Try again\n");
        }
    }
}

double Proc_Calculating(tree_t* tree, Node_t* node, errors* err)
{
    double x = NAN;
    isnan(x);

    if (node->type == NUM_CODE)
        return node->value.num_t;
    else if (node->type == VAR_CODE)
        return tree->hash_table[node->value.var_ind].var_value;
    else
    {
        for (int i = 0; i < tree->num_oper; i++)
            if (mas_functions[i].func_code == node->value.op_code_t)
                return mas_functions[i].funcname(tree, node, err);
    }

    return 0;
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
    double a = Proc_Calculating(tree, node->right, err);
    if (Is_Zero(a))
    {
        fprintf (stderr, "NA NOL DELIT NELZYA!\n");
        *err = ZNAMEN_NULL;
        return 1;
    }
    return Proc_Calculating(tree, node->left, err) / Proc_Calculating(tree, node->right, err);
}

double STEPEN_CASE(tree_t* tree, Node_t* node, errors* err)
{
    if (node->left == NULL || node->right == NULL)
    {
        fprintf (stderr, "Empty node where it needs to be filled\n");
        *err = NODE_NULL;
        return 1;
    }

    return pow(Proc_Calculating(tree, node->left, err), Proc_Calculating(tree, node->right, err));
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
    double a = tan(Proc_Calculating(tree, node->left, err));
    if (Is_Zero(a))
    {
        fprintf (stderr, "Cotangens doesn't exist at this point\n");;
        *err = ZNAMEN_NULL;
        return 1;
    }
    if (node->left != NULL)
        return 1/tan(Proc_Calculating(tree, node->left, err));
    else
        return 1/tan(Proc_Calculating(tree, node->right, err));
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
        return M_PI/2 - tan(Proc_Calculating(tree, node->left, err));
    else
        return M_PI/2 - tan(Proc_Calculating(tree, node->right, err));
}
#undef TRIG_FUNCS