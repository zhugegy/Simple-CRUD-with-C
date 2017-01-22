#pragma once

#include <stdio.h>
#include <sys/stat.h>

charnumber_t file_operator_get_storage_file_size_byte();
int file_operator_write_new_content_block_in_storage();
int file_operator_map_storage_file_to_heap(Param *ppParam);
int file_operator_load_link_list_from_file(Param *ppParam);
int file_operator_write_content_in_storage(char *szContent, 
                                   charnumber_t cntStartLocation);
int file_operator_write_string_node_in_link_info(StringNode *psnTmp);
int file_operator_delete_string_node_in_link_info(StringNode *psnTmp);
int file_operator_map_heap_to_storage_file(Param *ppParam);
int file_operator_add_extra_content_block(Param *ppParam);