#include "read_tree.h"
#include "structs_defines_types.h"
#include "tech_func.h"

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>  

oper_t massive_op[NUM_OPER] = {
        {"-",           SUB_CODE,       1},
        {"+",           ADD_CODE,       1},
        {"*",           MUL_CODE,       1},
        {"/",           DIV_CODE,       1},
        {"^",           STEPEN_CODE,    1},
        {"sin",         SIN_CODE,       3},
        {"cos",         COS_CODE,       3},
        {"tan",         TAN_CODE,       3},
        {"cotan",       COTAN_CODE,     5},
        {"arcsin",      ARCSIN_CODE,    6},
        {"arccos",      ARCCOS_CODE,    6},
        {"arctan",      ARCTAN_CODE,    6},
        {"arccotan",    ARCCOTAN_CODE,  6},
    };

Node_t* Read_Tree(tree_t* tree)
{ 
    printf("Please write number of variables: \n");
    scanf("%d", &tree->num_var);

    tree->hash_table = (hash*)calloc((size_t)tree->num_var, sizeof(hash));

    printf ("Please enter all variables(var -space- var...): ");
    for (int i = 0; i < tree->num_var; i++)
    {
        scanf("%s", tree->hash_table[i].name);
        tree->hash_table[i].index = i;
        tree->hash_table[i].hash_len = (int)strlen(tree->hash_table[i].name);
    }

    for (int i = 0; i < tree->num_var; i++)
    {
        printf("tree->hash_table[i].name = %s\n", tree->hash_table[i].name);
        printf("tree->hash_table[i].index = %d\n", tree->hash_table[i].index);
        printf("tree->hash_table[i].len = %d\n\n", tree->hash_table[i].hash_len);
    }

    FILE* fp = fopen(READ_TREE_FILE, "r");
    struct stat stat1 = {};
    int descriptor = fileno(fp);
    int position = 0;

    fstat(descriptor, &stat1);

    char* massive = (char*)calloc((size_t)stat1.st_size + 1, sizeof(char));
    IF_ERROR(massive);

    fread(massive, sizeof(char), (size_t)stat1.st_size, fp);

    Node_t* node = Read_Node(tree, &position, massive);
    IF_ERROR(node);

    free(massive);
    fclose(fp);

    return(node);
}

Node_t* Read_Node(tree_t* tree, int* position, char* massive)
{
    Skip_Spaces(position, massive);

    if (massive[*position] == '(')
    {
        Node_t* node = Obrabotka_Node(tree, position, massive);
        IF_ERROR(node);
        return node;
    }

    if (!(strncmp(&massive[*position], "nil", 3)))
    {
        *position += 3;
        return NULL;
    }
    else
    {
        fprintf(stderr, "Error in reading file\n");
        return NULL;
    }
}

Node_t* Obrabotka_Node(tree_t* tree, int* position, char* massive)
{
    (*position)++;
    Skip_Spaces(position, massive);

    printf("position: %c\n", massive[*position]);
    Node_t* node = Spot_Type(tree, position, massive);
    IF_ERROR(node);
    Skip_Spaces(position, massive);

    if((node->left = Read_Node(tree, position, massive)) != NULL)
        node->left->parent = node;
    if((node->right = Read_Node(tree, position, massive)) != NULL)
        node->right->parent = node;
    Skip_Spaces(position, massive);

    (*position)++;
    return node;
}

Node_t* Spot_Type(tree_t* tree, int* position, char* massive)
{
    int num = 0, i = -52;
    double new_value_value = 0;
    if (sscanf(&massive[*position], "%lg%n", &new_value_value, &num))
    {
        value_dif a = {.num_t = new_value_value};
        Node_t* node = Make_Node(NUM_CODE, a);
        (*position) += num;
        return node;
    }
    else if ((i = Var_Checking(tree, position, massive)) >= 0)
    {
        value_dif a = {.var_ind = tree->hash_table[i].index};
        Node_t* node = Make_Node(VAR_CODE, a);
        return node;
    }
    else if ((i = Operation_checking(position, massive)) == -1) 
        return NULL;
    else if (i >= 0)
    {
        value_dif a = {.op_code_t = massive_op[i].op_code};
        Node_t* node = Make_Node(OPER_CODE, a);
        return node;
    }
    else
        return NULL;

}

int Operation_checking(int* position, char* massive)
{
    for (int i = 0; i < NUM_OPER; i++)
    {
        if (strncmp(&massive[*position], massive_op[i].op_symb, (size_t)massive_op[i].len) == 0)
        {
            printf("BLYAT KAK\n");
            (*position) += massive_op[i].len;
            Skip_Spaces(position, massive);
            if (massive[*position] == '(')
                return i;
            else
            {
                fprintf(stderr, "ERROR IN READING FILE AAAAA\n");
                return -1;
            }
        }
    }

    return -2;
}

int Var_Checking(tree_t* tree, int* position, char* massive)
{
    for (int i = 0; i <= tree->num_var; i++)
    {
        int len = (int)strlen(tree->hash_table[i].name);
        if (len == tree->hash_table[i].hash_len && strncmp(&massive[*position], tree->hash_table[i].name, (size_t)tree->hash_table[i].hash_len) == 0)
        {
            (*position) += tree->hash_table[i].hash_len;
            return i;
        }
    }

    return -1;
}