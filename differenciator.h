#ifndef DIFFERENCIATOR_H
#define DIFFERENCIATOR_H

#include "structs_defines_types.h"

differentiator_t Differenciator(differentiator_t tree);

Node_t* Proc_Differing(Node_t* node);

Node_t* Proc_Copying(Node_t* node);

void Proc_Optymizing(Node_t** node);

#endif