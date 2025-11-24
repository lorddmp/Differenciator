#ifndef TECH_FUNC
#define TECH_FUNC

#include "structs_defines_types.h"

Node_t* Make_Node(void);

void Tree_Destructor(Node_t* node);

void Clean_Buffer(void);

void Skip_Spaces(int* position, char* massive);

bool Is_Zero(double a);

#endif