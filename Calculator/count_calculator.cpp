#include "../structs_defines_types.h"
#include "count_calculator.h"
#include "../tech_func.h"
#include "count_calc_funcs.h"
#include <stdio.h>
#include <math.h>

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

double Count_Calculator(tree_t* tree, errors* err)
{
    Get_Var_Values(tree);

    return Proc_Count_Calculating(tree, tree->root_node, err);;
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

double Proc_Count_Calculating(tree_t* tree, Node_t* node, errors* err)
{
    double x = NAN;
    isnan(x);

    if (node->type == NUM_CODE)
        return node->value.num_t;
    else if (node->type == VAR_CODE)
        return tree->hash_table[node->value.var_ind].var_value;
    else
    {
        for (int i = 0; i < NUM_OPER; i++)
            if (mas_functions[i].func_code == node->value.op_code_t)
                return mas_functions[i].funcname(tree, node, err);
    }

    return 0;
}