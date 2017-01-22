//此文件是数据操作相关函数。

#include "stdafx.h"
#include "data_processor.h"

#include "file_operator.h"
#include "data_processor_write.h"
#include "student_info_processor.h"
#include "data_processor_remove.h"
#include "data_processor_change.h"
#include "data_processor_cmd_1_to_6.h"
#include "data_processor_grade_stat.h"

static int data_processor_build_string_node_chain(Param *ppParam, 
                                                  StringNode *psnTemplate);
static int data_processor_add_check_secondary_parameters(Param *ppParam);
static int data_processor_remove_quoter(char *szTarget);
int data_processor_is_serial_avaiable(int nNum, Param *ppParam);
static int data_processor_find_avaiable_serial(Param *ppParam);
static int data_processor_find_avaiable_Array_Location(int nPureLength,
                                                       Param *ppParam);
static int data_processor_write_in_array(char *szTarget, int nArrayLocation,
                                         Param *ppParam);
static int data_processor_list_check_secondary_parameters(Param *ppParam);
static int data_processor_list(Param *ppParam);
static int data_processor_list_decide_operation(Param *ppParam);
static int data_processor_list_operation_all(Param *ppParam);
static int data_processor_list_operation_num(Param *ppParam);
static int data_processor_list_operation_reg(Param *ppParam);
static int data_processor_delete_check_secondary_parameters(Param *ppParam);
static int data_processor_delete_string_node(int nSerial, Param *ppParam);
static int data_processor_modify_check_secondary_parameters(Param *ppParam);
static int data_processor_modify(Param *ppParam);
static int data_processor_stat_initialize_char_array(Param *ppParam);
static int data_processor_stat(Param *ppParam);
static int data_processor_raminfo(Param *ppParam);
static int data_processor_raminfo_check_secondary_parameters(Param *ppParam);
static int initialize_sim_array(Param *ppParam);
static int update_sim_array(Param *ppParam);
static int data_processor_probe_ram_info(int nNum, Param *ppParam);
static StringNode *data_processor_get_ram_info_strnode(int nNum,Param *ppParam);
static int data_processor_jump_check_secondary_parameters(Param *ppParam);
static int data_processor_jump(Param *ppParam);
static int data_processor_optimize_find_the_first_full_empty(Param *ppParam);
static int data_processor_optimize(Param *ppParam);
static int data_processor_optimize_find_the_next_empty_full(int nStartLocation,
                                                            Param *ppParam);
static int data_processor_quit(Param *ppParam);
static int data_processor_quit_check_secondary_parameters(Param *ppParam);
static int data_processor_help(Param *ppParam);
static int data_processor_help_check_secondary_parameters(Param *ppParam);
static int data_processor_decode_string_node_and_push_to_infobuffer(Param *ppParam, 
                                               StringNode *pTarget);

int call_data_processor(Param *ppParam)
{
  int nResult = 0;
  char chOperation = ppParam->chUserCmd;

  switch (chOperation)
  {
  case 'a':
    //添加字符串
    //-a "string" [num]
    nResult = data_processor_add(ppParam);
    break;
  case 'l':
    //显示字符串
    //-l [reg|num]
    nResult = data_processor_list(ppParam);
    break;
  /*
  case 'd':
    //删除字符串
    //-d num
    nResult = data_processor_delete(ppParam);
    break;
  */
  /*
  case 'm':
    //修改字符串
    //-m num "string"
    nResult = data_processor_modify(ppParam);
    break;
  */
  case 's':
    //统计字符串
    //-s
    nResult = data_processor_stat(ppParam);
    break;
  case 'i':
    //内存占用情况
    //-i
    nResult = data_processor_raminfo(ppParam);
    break;
  case 'j':
    //跳到内存特定地址
    //-j num
    nResult = data_processor_jump(ppParam); 
    break;
  case 'o':
    //内存优化
    //-o
    nResult = data_processor_optimize(ppParam);
    break;
  case 'q':
    //退出
    //-q
    nResult = data_processor_quit(ppParam);
    //不用打印学生模板信息了
    ppParam->nAppendingStudentTemplateControlFlag = 0; 
    break;
  case 'h':
    //帮助
    //-h
    nResult = data_processor_help(ppParam);
    break;
   //######以下命令是为学生系统而添加######//
  case 'w':
    //写入学生信息
    //-w [num]
    nResult = data_processor_write(ppParam);
    break;
  case 'r':
    //删除学生信息
    //-r num
    nResult = data_processor_remove(ppParam);
    break;
  case 'c':
    //更改学生(整体)信息
    //-c num
    nResult = data_processor_change(ppParam);
    break;
  case '1':
    //更改学生信息模板：学号
    //-1 string [string...]
    nResult = data_processor_cmd_1_studentcode(ppParam);
    break;
  case '2':
    //更改学生信息模板：姓名
    //-2 string [string...]
    nResult = data_processor_cmd_2_studentname(ppParam);
    break;
  case '3':
    //更改学生信息模板：出生日期
    //-3 num [num...]
    nResult = data_processor_cmd_3_studentbirthday(ppParam);
    break;
  case '4':
    //更改学生信息模板：电话
    //-4 string [string...]
    nResult = data_processor_cmd_4_studenttelphone(ppParam);
    break;
  case '5':
    //更改学生信息模板：C语言成绩
    //-5 floatnum
    nResult = data_processor_cmd_5_studentcgrade(ppParam);
    break;
  case '6':
    //更改学生信息模板：额外信息
    //-6 string [string...]
    nResult = data_processor_cmd_6_studentextrainfo(ppParam);
    break;
  case 'g':
    //统计C语言成绩
    //-g
    nResult = data_processor_grade_stat(ppParam);
    break;

  default:
    nResult = -1;
    ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_CMD_NOT_EXIST);
    break;
  }

  if (nResult != 0)
  {
    return -1;
  }

  return 0;
}

//出错时错误信息的传递,把错误信息发送给ppParam->piInfoBuffer。
int data_processor_send_error_msg(int nErrorNum, Param *ppParam)
{
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  /*发生输入错误后，可以取消显示模板*/
  //ppParam->nAppendingStudentTemplateControlFlag = 0;

  switch (nErrorNum)
  {
  case DATA_PROCESSOR_ERROR_ADD_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_ADD_PARAMETER_1_LACK_OF_QUOTER:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_1_LACK_OF_QUOTER);
    break;

  case DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_2_NOT_NUM);
    break;

  case DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_AVAILABLE:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_2_NOT_AVAILABLE);
    break;

  case DATA_PROCESSOR_ERROR_ADD_NO_AVAILABLE_SPACE:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_ADD_NO_AVAILABLE_SPACE);
    break;
    
  case DATA_PROCESSOR_ERROR_LIST_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_NEGATIVE_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_1_NEGATIVE_NUM);
    break;

  case DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_LACK_OF_QUOTER:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_1_LACK_OF_QUOTER);
    break;

  case DATA_PROCESSOR_ERROR_DELETE_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NOT_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_1_NOT_NUM);
    break;

  case DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NUM_NOT_EXIST:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_1_NUM_NOT_EXIST);
    break;

  case DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_2_LACK_OF_QUOTER:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_2_LACK_OF_QUOTER);
    break;

  case DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NOT_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_1_NOT_NUM);
    break;

  case DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NUM_NOT_EXIST:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_1_NUM_NOT_EXIST);
    break;

  case DATA_PROCESSOR_ERROR_STAT_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_STAT_PARAMETER_NUM);
    break;
   
  case DATA_PROCESSOR_ERROR_RAMINFO_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_RAMINFO_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_JUMP_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_NOT_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_1_NOT_NUM);
    break;

  case DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_RAM_NO_CONTENT:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_1_RAM_NO_CONTENT);
    break;
  case DATA_PROCESSOR_ERROR_OPTIMIZE_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_OPTIMIZE_PARAMETER_NUM);
    break;
    
  case DATA_PROCESSOR_ERROR_QUIT_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_QUIT_PARAMETER_NUM);
    break;

  case DATA_PROCESSOR_ERROR_HELP_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_HELP_PARAMETER_NUM);
    break;
  case DATA_PROCESSOR_ERROR_WRITE_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_WRITE_PARAMETER_NUM);
    break;
  case DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_WRITE_PARAMETER_1_NOT_NUM);
    break;
  case DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_AVAILABLE:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_WRITE_PARAMETER_1_NOT_AVAILABLE);
    break;
  case DATA_PROCESSOR_ERROR_REMOVE_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_REMOVE_PARAMETER_NUM);
    break;
  case DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NOT_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_REMOVE_PARAMETER_1_NOT_NUM);
    break;
  case DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NUM_NOT_EXIST:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_REMOVE_PARAMETER_1_NUM_NOT_EXIST);
    break;
  case DATA_PROCESSOR_ERROR_CHANGE_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_CHANGE_PARAMETER_NUM);
    break;
  case DATA_PROCESSOR_ERROR_CMD_3_STUDENTBIRTHDAY_NOT_LEGAL:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_CMD_3_STUDENTBIRTHDAY_NOT_LEGAL);
    break;
  case DATA_PROCESSOR_ERROR_CMD_5_STUDENTCGRADE_NOT_LEGAL:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_CMD_5_STUDENTCGRADE_NOT_LEGAL);
    break;
  case DATA_PROCESSOR_ERROR_GRADE_STAT_PARAMETER_NUM:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_GRADE_STAT_PARAMETER_NUM);
    break;
  case DATA_PROCESSOR_ERROR_GRADE_STAT_NO_AVAILABLE_STUDENT_INFO:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      DATA_PROCESSOR_ERROR_MSG_GRADE_STAT_NO_AVAILABLE_STUDENT_INFO);
    break;

  default:
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      ERROR_MSG_DEFAULT);
    break;
  }

  return 0;
}

static int data_processor_optimize_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_OPTIMIZE_PARAMETER_NUM;
  }

  return 0;
}

static int data_processor_optimize_find_the_first_full_empty(Param *ppParam)
{
  int i = 0;

  //如果第一个就是空，那就返回0（第一个内存空间）。
  //单独列出因为arychSim[0 - 1]越界。
  if (ppParam->pchSim[0] == 0)
  {
    return 0;
  }

  for (i = 1; i < ppParam->nStorageFileCharSize; i++)
  {
    if (ppParam->pchSim[i] == 0 && ppParam->pchSim[i - 1] == 1)
    {
      return i;
    }
  }

  //如果找不到
  return -1;
}

static int data_processor_optimize_find_the_next_empty_full(int nStartLocation,
                                                            Param *ppParam)
{
  int i = 0;

  for (i = nStartLocation + 1; i < ppParam->nStorageFileCharSize; i++)
  {
    if (ppParam->pchSim[i] == 1 /*&& ppParam->arychSim[i - 1] == 0*/)
    {
      return i;
    }
  }

  //如果找不到
  return -1;
}

static int data_processor_quit_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_QUIT_PARAMETER_NUM;
  }

  return 0;
}

//退出(-q 指令）
static int data_processor_quit(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_quit_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //change flag
  ppParam->nControlFlag = 1;

  //发送信息到piInfoBuffer。
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    GOODBYE_INFO);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

static int data_processor_help_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_HELP_PARAMETER_NUM;
  }

  return 0;
}

//帮助(-h 指令）
static int data_processor_help(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_help_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //显示帮助，发送信息到piInfoBuffer。
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    HELP_INFO);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//优化内存的函数，整理碎片(-o 指令）
static int data_processor_optimize(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nFirstFullEmptyLocation = 0;
  int nNextEmptyFullLocation = 0;
  StringNode *psnCurrentStringNode = NULL;
  int nPrevArrayLocation = 0;
  int i = 0;
  char szInfoBuffer[MAX_INFO_STRING_LENGTH] = {0};
  char szTmp[MAX_INFO_STRING_LENGTH] = {0};

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_optimize_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //不断寻找空闲内存并作位移
  while (TRUE)
  {
    //初始化内存模拟表
    initialize_sim_array(ppParam);
	    
    //更新内存模拟表
    update_sim_array(ppParam);

    //找到第一个Full_Empty。
    nFirstFullEmptyLocation = 
      data_processor_optimize_find_the_first_full_empty(ppParam);
    if (nFirstFullEmptyLocation == -1)
    {
      break;
    }

    //找到第一个Full_Empty后面的第一个Empty_Full。
    nNextEmptyFullLocation = 
      data_processor_optimize_find_the_next_empty_full(nFirstFullEmptyLocation, 
      ppParam);

    if (nNextEmptyFullLocation == -1)
    {
      break;
    }

    //定位该字符串的链表节点
    psnCurrentStringNode = 
      data_processor_get_ram_info_strnode(nNextEmptyFullLocation, ppParam);

    //存储该节点的原起始坐标
    nPrevArrayLocation = psnCurrentStringNode->nArrayLocation;

    //节点位移到第一个Full_Empty处。
    psnCurrentStringNode->nArrayLocation = nFirstFullEmptyLocation;
    
    //修改节点在linkinfo中的内容（删除+添加）
    file_operator_delete_string_node_in_link_info(psnCurrentStringNode);
    file_operator_write_string_node_in_link_info(psnCurrentStringNode);

    //操作字符串存储数组，做内容平移。
    for (i = 0; i < psnCurrentStringNode->nStringLength; i++)
    {
      ppParam->pchArrayStorage[nFirstFullEmptyLocation + i] =
        ppParam->pchArrayStorage[nPrevArrayLocation + i];
    }

    //在这里存储文件就暂时不修改了，等全部优化结束后统一修改（重写所有区域）

    //存储操作过的字符串序号。
    sprintf_s(szTmp, _countof(szTmp), " %d", psnCurrentStringNode->nSerial);
    strcat_s(szInfoBuffer, _countof(szInfoBuffer), szTmp);
  }

  //内存整理完毕，在有整理动作的情况下，重写存储文件（映射）
  if (strcmp(szInfoBuffer, "") != 0)
  {
    file_operator_map_heap_to_storage_file(ppParam);
  }
  
  //内存整理完毕，发送信息到piInfoBuffer。
  if (strcmp(szInfoBuffer, "") == 0)
  {
    sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      "整理前的内存结构已经最优，无需整理。\r\n");
  }
  else
  {
    sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      "内存整理完毕，被前移过的字符串序号：%s。\r\n", szInfoBuffer);
  }
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-j指令判断参数合法性。
//合法格式：-j num
static int data_processor_jump_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //判断参数个数。
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_JUMP_PARAMETER_NUM;
  }

  //判断第1参数是否为数字。
  nTmp = atoi(ppParam->szArgv[1]);
  
  //如果第1参数是0，直接返回0，参数合法。因为下个判断和此参数冲突所以单独判断。
  if (strcmp(ppParam->szArgv[1], "0") == 0)
  {
    return 0;
  }

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_NOT_NUM;
  }

  //判断用户给的这个序号在内存中有没有内容，正确的情况是有内容
  if (data_processor_probe_ram_info(nTmp, ppParam) != 1)
  {
    return DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_RAM_NO_CONTENT;
  }

  return 0;
}


//显示内存指定位置的信息的函数(-j 指令）
static int data_processor_jump(Param *ppParam)
{
  int nCheckValidityResult = 0;
  StringNode *psnStringNode = NULL;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_jump_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //获取字符串节点地址
  psnStringNode = data_processor_get_ram_info_strnode(atoi(ppParam->szArgv[1]), 
    ppParam);

  //输出字符串信息到piInfoBuffr。
  /*sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "字符串内容: %s 内存地址: %d - %d , 它的序号：%d。\r\n", 
    ppParam->pchArrayStorage + psnStringNode->nArrayLocation, 
    psnStringNode->nArrayLocation, 
    psnStringNode->nArrayLocation + psnStringNode->nStringLength - 1, 
    psnStringNode->nSerial);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;*/
  data_processor_decode_string_node_and_push_to_infobuffer(ppParam, psnStringNode);

  return 0;
}

//-i指令判断参数合法性。
//合法格式: -i
static int data_processor_raminfo_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_RAMINFO_PARAMETER_NUM;
  }

  return 0;
}

//显示内存占用信息函数(-i 指令）
static int data_processor_raminfo(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_raminfo_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //初始化内存模拟数组。
  initialize_sim_array(ppParam);

  //更新内存模拟数组。
  update_sim_array(ppParam);

  //清理piInfoBuffer。
  empty_pi_info_buffer(ppParam);

  //把内存信息输出到piInfoBuffr;
  for (i = 0; i < ppParam->nStorageFileCharSize; i++)
  {
    if (ppParam->pchSim[i] == 0)
    {
      strcat_s(ppParam->piInfoBuffer.szToBePrinted, 
        _countof(ppParam->piInfoBuffer.szToBePrinted), RAM_INFO_EMPTY_SYMPOL);
    }
    else
    {
      strcat_s(ppParam->piInfoBuffer.szToBePrinted, 
        _countof(ppParam->piInfoBuffer.szToBePrinted), RAM_INFO_FULL_SYMPOL);
    }
  }

  return 0;
}

//-s指令判断参数合法性。
//合法格式: -s
static int data_processor_stat_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_STAT_PARAMETER_NUM;
  }

  return 0;
}

//统计函数(-s 指令)。
static int data_processor_stat(Param *ppParam)
{
  int nCheckValidityResult = 0;
  StringNode *psnTmp = NULL;
  char *pchTmp = NULL;
  char szTmp[MAX_INFO_STRING_LENGTH] = {0};
  int i = 0;
  int nSum = 0;
  int nTmp = 0;
  float fPercentage = 0.0f;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_stat_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //执行统计操作。
  //初始化统计数组。
  data_processor_stat_initialize_char_array(ppParam);

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    pchTmp = ppParam->pchArrayStorage + psnTmp->nArrayLocation;
    while (*pchTmp != '\0')
    {
      nTmp = (int) *pchTmp;
      ppParam->nCharArray[nTmp]++;
      pchTmp++;
    }
  }
 
  //统计字符总数。
  for (i = 0; i < _countof(ppParam->nCharArray); i++)
  {
    nSum += ppParam->nCharArray[i];
  }

  //清理piInfoBuffer。
  empty_pi_info_buffer(ppParam);
  
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //输出结果到piInfoBuffer
  for (i = 0; i < _countof(ppParam->nCharArray); i++)
  {
    if (ppParam->nCharArray[i] != 0)
    {
      fPercentage = (float) (ppParam->nCharArray[i] * 100 / nSum);
      sprintf_s(szTmp, _countof(szTmp), "字符 %c 次数：%d\t%.2f%s\r\n", i, 
        ppParam->nCharArray[i], fPercentage, "%");
      strcat_s(ppParam->piInfoBuffer.szToBePrinted, 
        _countof(ppParam->piInfoBuffer.szToBePrinted), szTmp);
    }
  }

  if (strcmp(ppParam->piInfoBuffer.szToBePrinted, "") == 0)
  {
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      "现在没有统计数据。\r\n");
  }

  return 0;
}

//初始化字符出现频率统计数组
static int data_processor_stat_initialize_char_array(Param *ppParam)
{
  int i = 0;

  for (i = 0; i < _countof(ppParam->nCharArray); i++)
  {
    ppParam->nCharArray[i] = 0;
  }

  return 0;
}

//-m指令。判断次要参数合法性。
//合法格式: -m num "string"
static int data_processor_modify_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;
  char *pchTmp = NULL;

  //判断参数个数，合法值：3。
  if (ppParam->nArgc !=3)
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_NUM;
  }

  //判断第1参数是不是数字
  nTmp = atoi(ppParam->szArgv[1]);

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NOT_NUM;
  }

  //判断用户给的这个序号在链表中存不存在，正确的情况是存在
  if (data_processor_is_serial_avaiable(nTmp, ppParam) != 0)
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NUM_NOT_EXIST;
  }

  //判断第2参数是否被引号包裹起来。
  //左引号
  pchTmp = ppParam->szArgv[2];
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_2_LACK_OF_QUOTER;
  }

  //右引号
  while (*pchTmp != '\0')
  {
    pchTmp++;
  }
  pchTmp--;
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_2_LACK_OF_QUOTER;
  }

  return 0;
}

//修改字符串函数(-m 指令)。
static int data_processor_modify(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //用于暂时存放用户指令。
  char szTmpArgv1[MAX_CMD_LENGTH] = {0};
  char szTmpArgv2[MAX_CMD_LENGTH] = {0};

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_modify_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //执行修改操作。（删除+添加）
  strcpy_s(szTmpArgv1, _countof(szTmpArgv1), ppParam->szArgv[1]);
  strcpy_s(szTmpArgv2, _countof(szTmpArgv2), ppParam->szArgv[2]);
  
  //删除
  ppParam->nArgc = 2;
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-d");
  //szArgv[1]不用修改
  strcpy_s(ppParam->szArgv[2], _countof(ppParam->szArgv[2]), "");
  data_processor_delete(ppParam);

  //添加
  ppParam->nArgc = 3;
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-a");
  strcpy_s(ppParam->szArgv[1], _countof(ppParam->szArgv[1]), szTmpArgv2);
  strcpy_s(ppParam->szArgv[2], _countof(ppParam->szArgv[2]), szTmpArgv1);
  data_processor_add(ppParam);

  //输出结果到piInfoBuffer
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "字符串已成功修改，序号 %s。\r\n", ppParam->szArgv[2]);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-d指令。判断次要参数合法性。
static int data_processor_delete_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //判断参数个数
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_DELETE_PARAMETER_NUM;
  }

  //判断第二参数是不是数字
  nTmp = atoi(ppParam->szArgv[1]);

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NOT_NUM;
  }

  //判断用户给的这个序号在链表中存不存在，正确的情况是存在
  if (data_processor_is_serial_avaiable(nTmp, ppParam) != 0)
  {
    return DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NUM_NOT_EXIST;
  }
  
  return 0;
}

//删除字符串函数(-d 指令)。
int data_processor_delete(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nArrayLocation = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_delete_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //执行删除操作。（删除链表节点）
  nArrayLocation = data_processor_delete_string_node(atoi(ppParam->szArgv[1]), 
    ppParam);

  //把已删除的信息移至buffer，方便解码，然后提示给用户
  student_info_processor_move_info_to_buffer(ppParam, 
    (ppParam->pchArrayStorage + nArrayLocation));

  //输出结果到piInfoBuffer
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "字符串\"%s\"已成功删除，序号 %s。\r\n", 
    ppParam->pchArrayStorage + nArrayLocation, ppParam->szArgv[1]);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//删除链表节点
static int data_processor_delete_string_node(int nSerial, Param *ppParam)
{
  StringNode *psnPrev = NULL;
  StringNode *psnTmp = NULL;
  int nTmp = 0;

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    
    //如果nSerial不匹配,继续往下走链表
    if (psnTmp->nSerial != nSerial)
    {
      psnPrev = psnTmp;
    }
    //如果nSerial匹配
    else
    {
      //先判断此节点前面有没有节点，如果有，则把前面节点的下一个指向自己的下一个
      if (psnPrev != NULL)
      {
        psnPrev->psnNext = psnTmp->psnNext;
      }
      //如果没有（也就是说这是第一个节点，那么改变ppParam中存储的链表起始位置）
      else
      {
        ppParam->psnStringNodes = psnTmp->psnNext;
      }

      //保存一下他在字符串记录数组中的起始位置，稍后打印结果用
      nTmp = psnTmp->nArrayLocation;

      //删除这个节点在LinkInfo文件中的记录
      file_operator_delete_string_node_in_link_info(psnTmp);

      //释放这个节点的空间
      free(psnTmp);

      return nTmp;
      break;
    }
  }

  //如果没能删除返回-1，不可能的情况。调试用。
  return -1;
}

//查询字符串函数(-l 指令)。
static int data_processor_list(Param *ppParam)
{
  int nCheckValidityResult = 0;

  //判断次要参数合法性
  nCheckValidityResult =
    data_processor_list_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //清除输出缓冲区，准备向里写入将要输出给用户的信息。
  empty_pi_info_buffer(ppParam);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //分析第二参数，确定到底执行什么操作
  switch (data_processor_list_decide_operation(ppParam))
  {
  case DATA_PROCESSOR_OPERATION_LIST_ALL:
    data_processor_list_operation_all(ppParam);
    break;
  case DATA_PROCESSOR_OPERATION_LIST_NUM:
    data_processor_list_operation_num(ppParam);
    break;
  case DATA_PROCESSOR_OPERATION_LIST_REG:
    data_processor_list_operation_reg(ppParam);
    break;
  default:
    break;
  }

  return 0;
}

//list ALL （指令：-l）
static int data_processor_list_operation_all(Param *ppParam)
{
  StringNode *psnTmp = NULL;

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    data_processor_decode_string_node_and_push_to_infobuffer(ppParam, psnTmp);
  }

  if (ppParam->piInfoBuffer.szToBePrinted[0] == '\0')
  {
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      DATA_PROCESSOR_INFO_NO_RESULT_ALL);
    ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;
  }

  return 0;
}

//list NUM (指令：-l 5)
static int data_processor_list_operation_num(Param *ppParam)
{
  StringNode *psnTmp = NULL;
  
  int nTmp = 0;

  nTmp = atoi(ppParam->szArgv[1]);

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    if (nTmp == psnTmp->nSerial)
    {
      data_processor_decode_string_node_and_push_to_infobuffer(ppParam, psnTmp);
    }
  }

  if (ppParam->piInfoBuffer.szToBePrinted[0] == '\0')
  {
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      DATA_PROCESSOR_INFO_NO_RESULT_NUM);
    ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;
  }

  return 0;
}

//list REG （指令： -l "el")
static int data_processor_list_operation_reg(Param *ppParam)
{
  StringNode *psnTmp = NULL;
  char szTmp[MAX_INFO_STRING_LENGTH];

  //去除第二参数左右的引号。
  data_processor_remove_quoter(ppParam->szArgv[1]);

  //修饰正则表达式
  strcpy_s(szTmp, MAX_INFO_STRING_LENGTH, ppParam->szArgv[1]);
  sprintf_s(ppParam->szArgv[1], MAX_CMD_LENGTH, "%s%s%s", 
    "(.*)", szTmp, "(.*)");

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    if (std::regex_match(ppParam->pchArrayStorage + psnTmp->nArrayLocation, 
      std::regex(ppParam->szArgv[1])))
    {
      data_processor_decode_string_node_and_push_to_infobuffer(ppParam, psnTmp);
    }

  }

  if (ppParam->piInfoBuffer.szToBePrinted[0] == '\0')
  {
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      DATA_PROCESSOR_INFO_NO_RESULT_REG);
    ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;
  }

  return 0;
}

//把链表里的信息解码到结构体，并发送到piInfoBuffer
static int data_processor_decode_string_node_and_push_to_infobuffer
  (Param *ppParam, StringNode *pTarget)
{
  StringNode *psnTmp = pTarget;
  char szTmp[MAX_INFO_STRING_LENGTH];

  strcpy_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->pchArrayStorage + psnTmp->nArrayLocation);

  student_info_processor_decode_string_to_struct(ppParam);

  sprintf_s(szTmp, MAX_INFO_STRING_LENGTH, 
    "序号：%d 内存地址：%d - %d 创建时间：%s"
    "学号：%s 姓名：%s 年龄：%d 电话：%s C语言成绩：%2.2f 额外信息：%s\r\n\r\n", 
    psnTmp->nSerial, 
    psnTmp->nArrayLocation,
    psnTmp->nArrayLocation + psnTmp->nStringLength - 1,
    ctime(&(psnTmp->tCreationTime)),
    ppParam->StudentDecode.szStudentCode,
    ppParam->StudentDecode.szStudentName,
    (MAX_STUDENT_AGE_YEAR - 
    (ppParam->StudentDecode.nStudentBirthday / 10000)),
    ppParam->StudentDecode.szStudentTelphone,
    ppParam->StudentDecode.fStudentCGrade,
    ppParam->StudentDecode.szStudentExtraInfo);

  strcat_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    szTmp);

  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-l指令。分析第二参数，确定到底执行什么操作。
static int data_processor_list_decide_operation(Param *ppParam)
{
  int nTmp = 0;

  if (ppParam->nArgc == 1)
  {
    return DATA_PROCESSOR_OPERATION_LIST_ALL;
  }

  //通过atoi函数判断第二参数是数字还是字符串。
  nTmp = atoi(ppParam->szArgv[1]);

  //如果第二参数是数字（已被验证为正整数）
  if (nTmp != 0)
  {
    return DATA_PROCESSOR_OPERATION_LIST_NUM;
  }
  //如果第二参数是正则表达式（已验证它已被双引号括起来了）
  else
  {
    return DATA_PROCESSOR_OPERATION_LIST_REG;
  }

  return 0;
}

//-l指令。判断次要参数合法性。
static int data_processor_list_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;
  char *pchTmp = NULL;

  //判断参数个数
  if (ppParam->nArgc != 1 && ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_LIST_PARAMETER_NUM;
  }

  //如果就一个参数，那也没什么好检查的了,肯定对('-l')
  if (ppParam->nArgc == 1)
  {
    return 0;
  }

  //通过atoi函数判断第二参数是数字还是字符串。
  nTmp = atoi(ppParam->szArgv[1]);
  
  //如果是数字
  if (nTmp != 0)
  {
    if (nTmp < 0)
    {
      return DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_NEGATIVE_NUM;
    }
  }
  //如果是字符串
  else
  {
    /*判断第二参数是否被引号包裹起来。 如果用户输入0,00,000...,也会在此报错。属
    于一种false negative。尽管逻辑不对，但是歪打正着。*/

    //左引号
    pchTmp = ppParam->szArgv[1];
    if (*pchTmp != '"')
    {
      return DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_LACK_OF_QUOTER;
    }

    //右引号
    while (*pchTmp != '\0')
    {
      pchTmp++;
    }
    pchTmp--;
    if (*pchTmp != '"')
    {
      return DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_LACK_OF_QUOTER;
    }
  }

  return 0;
}

//添加字符串函数（-a指令）。
int data_processor_add(Param *ppParam)
{
  int nCheckValidityResult = 0;
  StringNode snTemplate;
  StringNode *psnTmp = NULL;

  //判断次要参数合法性
  nCheckValidityResult = data_processor_add_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //拆除字符串左右的引号
  data_processor_remove_quoter(ppParam->szArgv[1]);

  //构造StringNode模板
  //确定字符串构建时间
  snTemplate.tCreationTime = time(0);

  //确定字符串长度
  snTemplate.nStringLength = strlen(ppParam->szArgv[1]) + 1;

  //确定字符串序号
  if (ppParam->nArgc == 3)
  {
    snTemplate.nSerial = atoi(ppParam->szArgv[2]);
  }
  else
  {
    snTemplate.nSerial = data_processor_find_avaiable_serial(ppParam);
  }

  //确定字符串起始地址
  snTemplate.nArrayLocation = data_processor_find_avaiable_Array_Location(
    snTemplate.nStringLength, ppParam);

  //如果找不到可用空间
  /*if (snTemplate.nArrayLocation == -1)
  {
    nCheckValidityResult = DATA_PROCESSOR_ERROR_ADD_NO_AVAILABLE_SPACE;
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }*/

  /*20161005现在用文件存储了，如果找不到空间，就再加一个文件块，加文件块函数内含
  重置相关系统参数操作（比如更新存储文件大小，重新申请映射文件的内存等等）*/
  while (snTemplate.nArrayLocation == -1)
  {
    file_operator_add_extra_content_block(ppParam);
    snTemplate.nArrayLocation = data_processor_find_avaiable_Array_Location(
      snTemplate.nStringLength, ppParam);
  }

  //把信息写入存储数组
  data_processor_write_in_array(ppParam->szArgv[1], snTemplate.nArrayLocation,
    ppParam);


  //把字符串存储信息加入链表
  psnTmp = &snTemplate;
  data_processor_build_string_node_chain(ppParam, psnTmp);

  //把刚输入的字符串信息递交给piInfoBuffer。
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "字符串\"%s\"已成功添加，序号 %d。\r\n", 
    ppParam->pchArrayStorage + psnTmp->nArrayLocation, psnTmp->nSerial);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return psnTmp->nSerial;
}

//把信息写入存储数组。
static int data_processor_write_in_array(char *szTarget, int nArrayLocation,
                                         Param *ppParam)
{
  int i = 0;
  char *pchTmp = szTarget;

  while (*pchTmp != '\0')
  {
    /*20161004
    if ((nArrayLocation + i) < STRING_ARRAY_SPACE)  //越界检查
      //20161004有了文件系统之后，越界检查，降低效率，检查过了
    {
      ppParam->szArrayStorage[nArrayLocation + i] = *pchTmp;
      i++;
    }*/
    ppParam->pchArrayStorage[nArrayLocation + i] = *pchTmp;
    i++;
    
    pchTmp++;
  }

  /*20161004
  //20161004有了文件系统之后，越界检查，降低效率，检查过了
  if ((nArrayLocation + i) < STRING_ARRAY_SPACE)
  {
    ppParam->szArrayStorage[nArrayLocation + i] = '\0';
  }
  else
  {
    ppParam->szArrayStorage[STRING_ARRAY_SPACE - 1] = '\0';
  }*/
  ppParam->pchArrayStorage[nArrayLocation + i] = '\0';
  
  //把信息即时同步到文件
  file_operator_write_content_in_storage(szTarget, nArrayLocation);

  return i;
}

//拆除字符串左右的引号。
static int data_processor_remove_quoter(char *szTarget)
{
  int i = 0;
  char *pchTemp = szTarget;

  for (i = 0; i < (int) strlen(szTarget) - 1; i++)
  {
    *(pchTemp + i) = *(pchTemp + i + 1);
  }

  *(pchTemp + (strlen(szTarget) - 2)) = '\0';

  return 0;
}

//-a指令。判断次要参数合法性。
//合法格式: -a "string" [num]
static int data_processor_add_check_secondary_parameters(Param *ppParam)
{
  char *pchTmp = NULL;
  int nTmp;

  //判断参数个数，合法值：2或3。
  if (ppParam->nArgc != 2 && ppParam->nArgc !=3)
  {
    return DATA_PROCESSOR_ERROR_ADD_PARAMETER_NUM;
  }

  //判断第二参数是否被引号包裹起来。
  //左引号
  pchTmp = ppParam->szArgv[1];
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_ADD_PARAMETER_1_LACK_OF_QUOTER;
  }

  //右引号
  while (*pchTmp != '\0')
  {
    pchTmp++;
  }
  pchTmp--;
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_ADD_PARAMETER_1_LACK_OF_QUOTER;
  }

  //第三参数（序列号，可选）
  if (ppParam->nArgc == 3)
  {
    pchTmp = ppParam->szArgv[2];
    nTmp = atoi(pchTmp);

    //是否为正整数数字
    if (nTmp <= 0)
    {
      return DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_NUM;
    }

    //数字（序号）是否可用？（未被现有字符串所占用）
    if (data_processor_is_serial_avaiable(nTmp, ppParam) != 1)
    {
      return DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_AVAILABLE;
    }
    
  }

  return 0;
}

//数字对应的内存区域是否有内容？
/*此函数用于多种场合，所以和data_processor_get_ram_info_strnode形式相似，功能实
则不同*/
static int data_processor_probe_ram_info(int nNum, Param *ppParam)
{
  StringNode *psnTemp = NULL;

  for (psnTemp = ppParam->psnStringNodes; psnTemp; psnTemp = psnTemp->psnNext)
  {
    if ((nNum >= psnTemp->nArrayLocation) &&
        (nNum < psnTemp->nArrayLocation + psnTemp->nStringLength))
    {
      //这里有内容
      return 1;
    }
  }

  //该内存位置没有内容
  return 0;
}

//根据内存地址获取链表节点地址。
static StringNode *data_processor_get_ram_info_strnode(int nNum, Param *ppParam)
{
  StringNode *psnTemp = NULL;

  for (psnTemp = ppParam->psnStringNodes; psnTemp; psnTemp = psnTemp->psnNext)
  {
    if ((nNum >= psnTemp->nArrayLocation) &&
      (nNum < psnTemp->nArrayLocation + psnTemp->nStringLength))
    {
      //定位成功，返回节点地址。
      return psnTemp;
    }
  }

  /*定位失败，这种情况不会发生，因为已经用data_processor_probe_ram_info函数验证
  过此节点的存在，所以必定会成功。*/
  return NULL;
}

//数字（序号）是否可用？（未被现有字符串所占用）
int data_processor_is_serial_avaiable(int nNum, Param *ppParam)
{
  StringNode *psnTemp = NULL;

  //如果此时尚未有字符串加入（链表是空的）
  if (ppParam->psnStringNodes == NULL) 
  {
    return 1;
  }

  for (psnTemp = ppParam->psnStringNodes; psnTemp/*->psnNext*/; psnTemp =
    psnTemp->psnNext)
  {
    if (nNum == psnTemp->nSerial)
    {
      //该序列号已被占用
      return 0;
    }
  }

  //该序列号可以使用
  return 1;
}

//找一个可用的序号。
static int data_processor_find_avaiable_serial(Param *ppParam)
{
  StringNode *psnTemp = NULL;
  int i = 0;

  //如果此时尚未有字符串加入（链表是空的）
  if (ppParam->psnStringNodes == NULL) 
  {
    return 1;
  }

  for (i = 2; ; i++)
  {
    for (psnTemp = ppParam->psnStringNodes; psnTemp/*->psnNext*/; psnTemp =
      psnTemp->psnNext)
    {
      if (i == psnTemp->nSerial)
      {
        break;
      }
    }

    if (psnTemp == NULL)
    {
      return i;
    }
  }

  //如果出错，返回-1方便调试。
  return -1;
}

//找一个可用的起始地址。
static int data_processor_find_avaiable_Array_Location(int nPureLength,
                                                       Param *ppParam)
{
  StringNode *psnTemp = NULL;
  StringNode *psnTempIntern = NULL;
  int i = 0;
  int nTempLocationSrt = 0;
  int nTempLocationEnd = 0;
  int nExistingSrt = 0;
  int nExistingEnd = 0;

  //如果此时尚未有字符串加入（链表是空的）,那么就给他第一个地址吧（也就是0）
  if (ppParam->psnStringNodes == NULL) 
  {
    return 0;
  }

  for (psnTemp = ppParam->psnStringNodes; psnTemp/*->psnNext*/; psnTemp =
    psnTemp->psnNext)
  {
    nTempLocationSrt = psnTemp->nArrayLocation + psnTemp->nStringLength - 1 + 1;
    nTempLocationEnd = nTempLocationSrt + nPureLength - 1;

    for (psnTempIntern = ppParam->psnStringNodes; psnTempIntern/*->psnNext*/;
      psnTempIntern = psnTempIntern->psnNext)
    {
      nExistingSrt = psnTempIntern->nArrayLocation;
      nExistingEnd = psnTempIntern->nArrayLocation +
        psnTempIntern->nStringLength - 1;

      if (   ( (nTempLocationSrt < nExistingSrt)
            && (nTempLocationEnd < nExistingSrt) ) 
                              || 
             ( (nTempLocationSrt > nExistingEnd) 
            && (nTempLocationEnd > nExistingEnd) )
         )
      {
        if (psnTempIntern->psnNext == NULL)
        {
          /*越界检查，越界了就再加一个文件块*/
          if (nTempLocationSrt + nPureLength >= 
            ppParam->nStorageFileCharSize - 10)
          {
            return -1;
          }
          return nTempLocationSrt;
        }
        continue;
      }
      else
      {
        break;
      }
    }
  }

  //如果得到的空间越界
  if (nTempLocationEnd >= ppParam->nStorageFileCharSize)
  {
    return -1;
  }

  //如果找不到可用空间，返回-1。
  return -1;
}

//构建信息记录链表。成功返回0，失败返回DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC。
static int data_processor_build_string_node_chain(Param *ppParam, 
                                                  StringNode *psnTemplate)
{
  struct StringNode *psnTmp;

  if (ppParam->psnStringNodes == NULL)
  {
    ppParam->psnStringNodes = (struct StringNode *) 
      malloc(sizeof(struct StringNode));

    if (ppParam->psnStringNodes == NULL)
    {
      return DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC;
    }

    write_in_string_node(ppParam->psnStringNodes, psnTemplate);
    //链表加入操作完成后，同步到链表文件
    file_operator_write_string_node_in_link_info(ppParam->psnStringNodes);
  }
  else
  {
    for (psnTmp = ppParam->psnStringNodes; psnTmp->psnNext; psnTmp =
      psnTmp->psnNext);
    
    psnTmp->psnNext = (struct StringNode *) malloc(sizeof(struct StringNode));

    if (psnTmp->psnNext == NULL)
    {
      return DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC;
    }

    psnTmp = psnTmp->psnNext;
    write_in_string_node(psnTmp, psnTemplate);
    //链表加入操作完成后，同步到链表文件
    file_operator_write_string_node_in_link_info(psnTmp);
  }
   
  return 0;
}

//更新内存模拟数组信息，它用来显示内存占用情况。
static int update_sim_array(Param *ppParam)
{
  StringNode *psnTmp = NULL;
  int i = 0;

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {

    for (i = 0; i < psnTmp->nStringLength; i++)
    {
      ppParam->pchSim[psnTmp->nArrayLocation + i] = 1;
    }
  }
  
  return 0;
}

//初始化内存数组，它用来显示内存占用情况。
static int initialize_sim_array(Param *ppParam)
{
  int i = 0;

  for (i = 0; i < ppParam->nStorageFileCharSize; i++)
  {
    ppParam->pchSim[i] = 0;
  }

  return 0;
}

/*
time_t mytime = time(0);
printf("%s", ctime(&mytime));*/

/*
char s[] = "nmmu";

int num = atoi(s);
printf("%d", num);*/

/*
if (std::regex_match("subject", std::regex("(.*)e(.*)")))
{
  printf("1");
}*/