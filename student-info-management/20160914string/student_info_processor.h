#pragma once

#include <string.h>

int student_info_processor_initialize_default(Student *pStudentDefault);
int student_info_processor_refresh_template_to_default(
  Student *pStudentTemplate, Student *pStudentDefault);
int student_info_processor_encode_struct_to_string(Param *ppParam);
int student_info_processor_move_info_to_buffer(Param *ppParam, char *szEncoded);
int student_info_processor_decode_string_to_struct(Param *ppParam);