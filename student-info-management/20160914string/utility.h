#pragma once

#include <string.h>
#include <stdlib.h>

int build_str_prep_token(char *szToken, int nMaxLengthToken, 
                         int nMaxLengthTarget);
int empty_pi_info_buffer(Param *ppParam);
int write_in_string_node(StringNode *psnTarget, StringNode *psnTemplate);
int free_mapping_heaps(Param *ppParam);