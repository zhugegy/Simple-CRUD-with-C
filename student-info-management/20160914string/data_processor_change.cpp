//此文件是数据操作_修改学生信息相关函数。

#include "stdafx.h"
#include "data_processor_change.h"

#include "data_processor.h"
#include "data_processor_write.h"
#include "data_processor_remove.h"

static int data_processor_change_check_secondary_parameters(Param *ppParam);

//学生信息修改
//-c num
int data_processor_change(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nSerialNum = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_change_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //移交给remove和write
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-r");
  data_processor_remove(ppParam);

  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-w");
  nSerialNum = data_processor_write(ppParam);

  //输出结果到piInfoBuffer
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 %s 信息已成功修改，序号 %d。\r\n", 
    ppParam->StudentTemplate.szStudentName, 
    nSerialNum);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-c指令。判断次要参数合法性。
static int data_processor_change_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //判断参数个数
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_CHANGE_PARAMETER_NUM;
  }

  //判断第二参数是不是数字
  nTmp = atoi(ppParam->szArgv[1]);

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NOT_NUM;
  }

  //判断用户给的这个序号在链表中存不存在，正确的情况是存在
  if (data_processor_is_serial_avaiable(nTmp, ppParam) != 0)
  {
    return DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NUM_NOT_EXIST;
  }

  return 0;
}