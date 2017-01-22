//此文件是数据操作_写入学生信息相关函数。

#include "stdafx.h"
#include "data_processor_write.h"

#include "data_processor.h"
#include "student_info_processor.h"

static int data_processor_write_check_secondary_parameters(Param *ppParam);

//学生信息写入
//-w [num]
int data_processor_write(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nSerialNum = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_write_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //结构体信息编码至字符串
  student_info_processor_encode_struct_to_string(ppParam);

  //将任务移交至add
  if (ppParam->nArgc == 1)
  {
    //-w
    ppParam->nArgc = 2;
    strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-a");
    strcpy_s(ppParam->szArgv[1], _countof(ppParam->szArgv[1]), 
      ppParam->szStudentStructEncodeDecodeBuffer);
  }
  else
  {
    //-w num
    ppParam->nArgc = 3;
    strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-a");
    strcpy_s(ppParam->szArgv[2], _countof(ppParam->szArgv[1]), 
      ppParam->szArgv[1]);
    strcpy_s(ppParam->szArgv[1], _countof(ppParam->szArgv[1]), 
      ppParam->szStudentStructEncodeDecodeBuffer);
  }

  nSerialNum = data_processor_add(ppParam);

  //把刚输入的学生信息递交给piInfoBuffer。
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 %s 的信息已成功添加，序号 %d。\r\n", 
    ppParam->StudentTemplate.szStudentName, nSerialNum);

  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //重置学生信息模板
  student_info_processor_refresh_template_to_default(&ppParam->StudentTemplate, 
    &ppParam->StudentDefault);

  return nSerialNum;
}

//-a指令。判断次要参数合法性。
//合法格式: -w [num]
static int data_processor_write_check_secondary_parameters(Param *ppParam)
{
  char *pchTmp = NULL;
  int nTmp;

  //判断参数个数，合法值：1或2。
  if (ppParam->nArgc != 1 && ppParam->nArgc !=2)
  {
    return DATA_PROCESSOR_ERROR_WRITE_PARAMETER_NUM;
  }

  //第2参数（序列号，可选）
  if (ppParam->nArgc == 2)
  {
    pchTmp = ppParam->szArgv[1];
    nTmp = atoi(pchTmp);

    //是否为正整数数字
    if (nTmp <= 0)
    {
      return DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_NUM;
    }

    //数字（序号）是否可用？（未被现有字符串所占用）
    if (data_processor_is_serial_avaiable(nTmp, ppParam) != 1)
    {
      return DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_AVAILABLE;
    }

  }

  return 0;
}