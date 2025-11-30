#include "structs_defines_types.h"
#include "count_calculator.h"
#include "../tech_func.h"
#include "count_calc_funcs.h"
#include <stdio.h>
#include <math.h>

void Get_Var_Values(differentiator_t* tree);

struct functions{
    double(*funcname)(differentiator_t* tree, Node_t* node, errors* err);
    enum oper_codes func_code;
};

functions mas_count_functions[NUM_OPER] = {
    {COUNT_ADD_CASE,        ADD_CODE},
    {COUNT_SUB_CASE,        SUB_CODE},
    {COUNT_MUL_CASE,        MUL_CODE},
    {COUNT_DIV_CASE,        DIV_CODE},
    {COUNT_STEPEN_CASE,     STEPEN_CODE},
    {COUNT_SIN_CASE,        SIN_CODE},
    {COUNT_COS_CASE,        COS_CODE},
    {COUNT_TAN_CASE,        TAN_CODE},
    {COUNT_COTAN_CASE,      COTAN_CODE},
    {COUNT_ARCSIN_CASE,     ARCSIN_CODE},
    {COUNT_ARCCOS_CASE,     ARCCOS_CODE},
    {COUNT_ARCTAN_CASE,     ARCTAN_CODE},
    {COUNT_ARCCOTAN_CASE,   ARCCOTAN_CODE},
    {COUNT_LN_CASE,         LN_CODE},
};

double Count_Calculator(differentiator_t* tree, errors* err)
{
    Get_Var_Values(tree);

    return Proc_Count_Calculating(tree, tree->root_node, err);;
}

void Get_Var_Values(differentiator_t* tree)
{
    if (tree->num_var > 0)
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
}

double Proc_Count_Calculating(differentiator_t* tree, Node_t* node, errors* err)
{
    if (node->type == NUM_CODE)
        return node->value.num_t;
    else if (node->type == VAR_CODE)
        return tree->hash_table[node->value.var_ind].var_value;
    else
    {
        for (int i = 0; i < NUM_OPER; i++)
            if (mas_count_functions[i].func_code == node->value.op_code_t)
                return mas_count_functions[i].funcname(tree, node, err);
    }

    return 0;
}