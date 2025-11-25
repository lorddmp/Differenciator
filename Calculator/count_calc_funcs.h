#ifndef COUNT_CALC_FUNCS
#define COUNT_CALC_FUNCS
#include "structs_defines_types.h"

double COUNT_ADD_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_SUB_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_MUL_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_DIV_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_STEPEN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_SIN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_COS_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_TAN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_COTAN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_ARCSIN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_ARCCOS_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_ARCTAN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_ARCCOTAN_CASE(differentiator_t* tree, Node_t* node, errors* err);
double COUNT_LN_CASE(differentiator_t* tree, Node_t* node, errors* err);

#endif