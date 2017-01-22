#pragma once

#include <windows.h>


int call_data_processor(Param *ppParam);
int data_processor_send_error_msg(int nErrorNum, Param *ppParam);
int data_processor_is_serial_avaiable(int nNum, Param *ppParam);
int data_processor_add(Param *ppParam);
int data_processor_delete(Param *ppParam);