#include "read_tree.h"
#include "structs_defines_types.h"
#include "tech_func.h"

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ELSE_IF_OPER_OR_VAR_CHECK                                                                           \
else if ((result = Operation_checking(tree, massive_op, node, position, massive)) == 1);                    \
else if ((result = Operation_checking(tree, massive_op, node, position, massive)) == -1) return NULL;       \
else if (Var_Checking(tree, node, position, massive))                                                       

Node_t* Read_Tree(tree_t* tree, oper_t* massive_op)
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

    Node_t* node = Read_Node(tree, massive_op, &position, massive);
    IF_ERROR(node);

    free(massive);
    fclose(fp);

    return(node);
}

Node_t* Read_Node(tree_t* tree, oper_t* massive_op, int* position, char* massive)
{
    Skip_Spaces(position, massive);

    if (massive[*position] == '(')
    {
        Node_t* node = Obrabotka_Node(tree, massive_op, position, massive);
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
        fprintf(stderr, "Error in reading file <here>\n");
        return NULL;
    }
}

Node_t* Obrabotka_Node(tree_t* tree, oper_t* massive_op, int* position, char* massive)
{
    Node_t* node = Make_Node();
    IF_ERROR(node);

    (*position)++;
    Skip_Spaces(position, massive);

    node = Spot_Type(tree, massive_op, node, position, massive);
    IF_ERROR(node);

    if((node->left = Read_Node(tree, massive_op, position, massive)) != NULL)
        node->left->parent = node;
    if((node->right = Read_Node(tree, massive_op, position, massive)) != NULL)
        node->right->parent = node;
    Skip_Spaces(position, massive);

    (*position)++;
    return node;
}

Node_t* Spot_Type(tree_t* tree, oper_t* massive_op, Node_t* node, int* position, char* massive)
{
    int num = 0, result = 0;
    double new_value_value = 0;
    if (sscanf(&massive[*position], "%lg%n", &new_value_value, &num))
        {
            node->type = NUM_CODE;
            node->value.num_t = new_value_value;
            (*position) += num;
        }
    ELSE_IF_OPER_OR_VAR_CHECK;
    else
        return NULL;
    Skip_Spaces(position, massive);

    return node;
}

int Operation_checking(tree_t* tree, oper_t* massive_op, Node_t* node, int* position, char* massive)
{
    for (int i = 0; i < tree->num_oper; i++)
    {
        if (strncmp(&massive[*position], massive_op[i].op_symb, (size_t)massive_op[i].len) == 0)
        {
            (*position) += massive_op[i].len;
            Skip_Spaces(position, massive);
            if (massive[*position] == '(')
            {
                node->type = OPER_CODE;
                node->value.op_code_t = massive_op[i].op_code;
                return 1;
            }
            else
            {
                printf("ERROR IN READING FILE\n");
                return -1;
            }
        }
    }

    return 0;
}

bool Var_Checking(tree_t* tree, Node_t* node, int* position, char* massive)
{
    for (int i = 0; i <= tree->num_var; i++)
    {
        int len = (int)strlen(tree->hash_table[i].name);
        if (len == tree->hash_table[i].hash_len && strncmp(&massive[*position], tree->hash_table[i].name, (size_t)tree->hash_table[i].hash_len) == 0)
        {
            node->type = VAR_CODE;
            node->value.var_ind = tree->hash_table[i].index;
            (*position) += tree->hash_table[i].hash_len;
            return 1;
        }
    }

    return 0;
}