//此文件是数据操作_修改学生信息模板相关函数。
//很多函数都是相似的，但是为了维护方便，还是分开写。

#include "stdafx.h"
#include "data_processor_cmd_1_to_6.h"

#include "data_processor.h"

static int data_processor_cmd_1_studentcode_check_secondary_parameters
  (Param *ppParam);
static int data_processor_cmd_2_studentname_check_secondary_parameters
  (Param *ppParam);
static int data_processor_cmd_3_studentbirthday_check_secondary_parameters
  (Param *ppParam);
static int data_processor_cmd_4_studenttelphone_check_secondary_parameters
  (Param *ppParam);
static int data_processor_cmd_5_studentcgrade_check_secondary_parameters
  (Param *ppParam);
static int data_processor_cmd_6_studentextrainfo_check_secondary_parameters
  (Param *ppParam);

//-1指令。学生信息模板修改:1 StudentCode
//-1 string [string...]
int data_processor_cmd_1_studentcode(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentCodeTmp[MAX_STUDENT_CODE_LENGTH] = {0};
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_cmd_1_studentcode_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把参数整理到szStudentCodeTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*此处有隐患，万一用户本意是想输入多个空格，那么由于前面的cmd_parser(trim)
      把所有的空格都去掉了，这里只能还原1个空格。*/
      /*时间不多，先不管了*/
      strcat_s(szStudentCodeTmp, _countof(szStudentCodeTmp), " ");
    }

    strcat_s(szStudentCodeTmp, _countof(szStudentCodeTmp), ppParam->szArgv[i]);
  }

  //把szStudentCodeTmp写入学生信息模板
  strcpy_s(ppParam->StudentTemplate.szStudentCode, 
    _countof(ppParam->StudentTemplate.szStudentCode), szStudentCodeTmp);

  //输出结果到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 学号 信息已成功修改。\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-1指令。判断次要参数合法性。
static int data_processor_cmd_1_studentcode_check_secondary_parameters
  (Param *ppParam)
{
  //参数随便来，都对，最多有10各参数，超过的话前面会报错的，这里不用管

  return 0;
}

//-2指令。学生信息模板修改:2 StudentName
//-2 string [string...]
int data_processor_cmd_2_studentname(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentNameTmp[MAX_STUDENT_NAME_LENGTH] = {0};
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_cmd_2_studentname_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把参数整理到szStudentNameTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*此处有隐患，万一用户本意是想输入多个空格，那么由于前面的cmd_parser(trim)
      把所有的空格都去掉了，这里只能还原1个空格。*/
      /*时间不多，先不管了*/
      strcat_s(szStudentNameTmp, _countof(szStudentNameTmp), " ");
    }

    strcat_s(szStudentNameTmp, _countof(szStudentNameTmp), ppParam->szArgv[i]);
  }

  //把szStudentNameTmp写入学生信息模板
  strcpy_s(ppParam->StudentTemplate.szStudentName, 
    _countof(ppParam->StudentTemplate.szStudentName), szStudentNameTmp);

  //输出结果到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 姓名 信息已成功修改。\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-2指令。判断次要参数合法性。
static int data_processor_cmd_2_studentname_check_secondary_parameters
  (Param *ppParam)
{
  //参数随便来，都对，最多有10各参数，超过的话前面会报错的，这里不用管

  return 0;
}

//-3指令。学生信息模板修改:3 StudentBirthday
//-3 string [string...]
int data_processor_cmd_3_studentbirthday(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //合适长度暂时用StudentCode的
  char szStudentBirthdayTmp[MAX_STUDENT_CODE_LENGTH] = {0};   
  int nStudentBirthdayTmp = -1;
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_cmd_3_studentbirthday_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把参数整理到szStudentBirthdayTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    strcat_s(szStudentBirthdayTmp, _countof(szStudentBirthdayTmp), ppParam->szArgv[i]);
  }

  //把szStudentBirthdayTmp转换成整形
  nStudentBirthdayTmp = atoi(szStudentBirthdayTmp);

  //判断生日的合法性
  if (nStudentBirthdayTmp <= 0 || 
      ((nStudentBirthdayTmp / 10000) > MAX_STUDENT_AGE_YEAR))
  {
    nCheckValidityResult = DATA_PROCESSOR_ERROR_CMD_3_STUDENTBIRTHDAY_NOT_LEGAL;
  }

  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把nStudentBirthdayTmp写入学生信息模板
  ppParam->StudentTemplate.nStudentBirthday = nStudentBirthdayTmp;

  //输出结果到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 出生日期 信息已成功修改。\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-3指令。判断次要参数合法性。
static int data_processor_cmd_3_studentbirthday_check_secondary_parameters
  (Param *ppParam)
{
  //参数随便来，都对，最多有10各参数，超过的话前面会报错的，这里不用管

  return 0;
}

//-4指令。学生信息模板修改:4 StudentTelphone (telephone)
//-4 string [string...]
int data_processor_cmd_4_studenttelphone(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentTelphoneTmp[MAX_STUDENT_TEL_LENGTH] = {0};
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_cmd_4_studenttelphone_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把参数整理到szStudentTelphoneTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*此处有隐患，万一用户本意是想输入多个空格，那么由于前面的cmd_parser(trim)
      把所有的空格都去掉了，这里只能还原1个空格。*/
      /*时间不多，先不管了*/
      strcat_s(szStudentTelphoneTmp, _countof(szStudentTelphoneTmp), " ");
    }

    strcat_s(szStudentTelphoneTmp, _countof(szStudentTelphoneTmp), 
      ppParam->szArgv[i]);
  }

  //把szStudentNameTmp写入学生信息模板
  strcpy_s(ppParam->StudentTemplate.szStudentTelphone, 
    _countof(ppParam->StudentTemplate.szStudentTelphone), szStudentTelphoneTmp);

  //输出结果到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 电话 信息已成功修改。\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-4指令。判断次要参数合法性。
static int data_processor_cmd_4_studenttelphone_check_secondary_parameters
  (Param *ppParam)
{
  //参数随便来，都对，最多有10各参数，超过的话前面会报错的，这里不用管

  return 0;
}

//-5指令。学生信息模板修改:5 StudentCGrade
//-5 string [string...]
int data_processor_cmd_5_studentcgrade(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //长度暂时先用StudentCode的
  char szStudentCGradeTmp[MAX_STUDENT_CODE_LENGTH] = {0};
  float fStudentCGradeTmp = 0.0f;
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_cmd_5_studentcgrade_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把参数整理到szStudentCGradeTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    strcat_s(szStudentCGradeTmp, _countof(szStudentCGradeTmp), 
      ppParam->szArgv[i]);
  }

  //把szStudentCGradeTmp转换成浮点型
  fStudentCGradeTmp = (float) atof(szStudentCGradeTmp);

  //判断成绩的合法性
  if (fStudentCGradeTmp <= 0)
  {
    nCheckValidityResult = DATA_PROCESSOR_ERROR_CMD_5_STUDENTCGRADE_NOT_LEGAL;
  }

  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把fStudentCGradeTmp写入学生信息模板
  ppParam->StudentTemplate.fStudentCGrade = fStudentCGradeTmp;

  //输出结果到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 C语言成绩 信息已成功修改。\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-5指令。判断次要参数合法性。
static int data_processor_cmd_5_studentcgrade_check_secondary_parameters
  (Param *ppParam)
{
  //参数随便来，都对，最多有10各参数，超过的话前面会报错的，这里不用管

  return 0;
}

//-6指令。学生信息模板修改:6 StudentExtraInfo
//-6 string [string...]
int data_processor_cmd_6_studentextrainfo(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentExtraInfoTmp[MAX_STUDENT_EXTRA_INFO_LENGTH] = {0};
  int i = 0;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_cmd_6_studentextrainfo_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //把参数整理到szStudentExtraInfoTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*此处有隐患，万一用户本意是想输入多个空格，那么由于前面的cmd_parser(trim)
      把所有的空格都去掉了，这里只能还原1个空格。*/
      /*时间不多，先不管了*/
      strcat_s(szStudentExtraInfoTmp, _countof(szStudentExtraInfoTmp), " ");
    }

    strcat_s(szStudentExtraInfoTmp, _countof(szStudentExtraInfoTmp), 
      ppParam->szArgv[i]);
  }

  //把szStudentCodeTmp写入学生信息模板
  strcpy_s(ppParam->StudentTemplate.szStudentExtraInfo, 
    _countof(ppParam->StudentTemplate.szStudentExtraInfo), 
    szStudentExtraInfoTmp);

  //输出结果到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生 额外信息 已成功修改。\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-6指令。判断次要参数合法性。
static int data_processor_cmd_6_studentextrainfo_check_secondary_parameters
  (Param *ppParam)
{
  //参数随便来，都对，最多有10各参数，超过的话前面会报错的，这里不用管

  return 0;
}