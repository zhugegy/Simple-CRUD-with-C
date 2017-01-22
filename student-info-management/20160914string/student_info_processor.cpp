//此文件是学生信息处理相关函数。

#include "stdafx.h"
#include "student_info_processor.h"

//初始化默认学生信息
int student_info_processor_initialize_default(Student *pStudentDefault)
{
  strcpy_s(pStudentDefault->szStudentCode, 
    _countof(pStudentDefault->szStudentCode), DEFAULT_STUDENT_CODE);

  strcpy_s(pStudentDefault->szStudentName, 
    _countof(pStudentDefault->szStudentName), DEFAULT_STUDENT_NAME);

  pStudentDefault->nStudentBirthday = DEFAULT_STUDENT_BIRTHDAY;

  strcpy_s(pStudentDefault->szStudentTelphone, 
    _countof(pStudentDefault->szStudentTelphone), DEFAULT_STUDENT_TELPHONE);

  pStudentDefault->fStudentCGrade = DEFAULT_STUDENT_C_GRADE;

  strcpy_s(pStudentDefault->szStudentExtraInfo, 
    _countof(pStudentDefault->szStudentExtraInfo), DEFAULT_STUDENT_EXTRA_INFO);

  pStudentDefault->psnMapping = NULL;

  return 0;
}

//将学生信息模板刷新至默认
int student_info_processor_refresh_template_to_default(
  Student *pStudentTemplate, Student *pStudentDefault)
{
  *pStudentTemplate = *pStudentDefault;

  return 0;
}

//结构体信息编码至字符串
int student_info_processor_encode_struct_to_string(Param *ppParam)
{
  char szTmp[MAX_STRING_LENGTH] = {0};

  //清空buffer
  strcpy_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "\"");

  //编码
  //【1】学号
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentCode);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //【2】姓名
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentName);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //【3】出生日期
  sprintf_s(szTmp, _countof(szTmp), "%8d", 
    ppParam->StudentTemplate.nStudentBirthday);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), szTmp);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //【4】电话号码
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentTelphone);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //【5】C语言成绩
  sprintf_s(szTmp, _countof(szTmp), "%2.2f", 
    ppParam->StudentTemplate.fStudentCGrade);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), szTmp);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //【6】其他信息
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentExtraInfo);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "\"");

  return 0;
}

//将内存中的被编码的字符串移至buffer
int student_info_processor_move_info_to_buffer(Param *ppParam, char *szEncoded)
{
  strcpy_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), szEncoded);
  return 0;
}

//将字符串信息解码至结构体
int student_info_processor_decode_string_to_struct(Param *ppParam)
{
  char *pTmp = ppParam->szStudentStructEncodeDecodeBuffer;
  char szTmp[MAX_STRING_LENGTH] = {0};
  int i = 0;

  //可以用二维数组和循环做，但是容易出错，没太多时间调试了，还是一步一步来

  //解码【1】学号
  i = 0;
  while (*pTmp != '#')
  {
    szTmp[i] = *pTmp;
    pTmp++;
    i++;
  }
  szTmp[i] = '\0';
  pTmp++;

  strcpy_s(ppParam->StudentDecode.szStudentCode, 
    _countof(ppParam->StudentDecode.szStudentCode), szTmp);

  //解码【2】姓名
  i = 0;
  while (*pTmp != '#')
  {
    szTmp[i] = *pTmp;
    pTmp++;
    i++;
  }
  szTmp[i] = '\0';
  pTmp++;
  strcpy_s(ppParam->StudentDecode.szStudentName, 
    _countof(ppParam->StudentDecode.szStudentName), szTmp);

  //解码【3】出生日期
  i = 0;
  while (*pTmp != '#')
  {
    szTmp[i] = *pTmp;
    pTmp++;
    i++;
  }
  szTmp[i] = '\0';
  pTmp++;
  ppParam->StudentDecode.nStudentBirthday = atoi(szTmp);

  //解码【4】电话号码
  i = 0;
  while (*pTmp != '#')
  {
    szTmp[i] = *pTmp;
    pTmp++;
    i++;
  }
  szTmp[i] = '\0';
  pTmp++;
  strcpy_s(ppParam->StudentDecode.szStudentTelphone, 
    _countof(ppParam->StudentDecode.szStudentTelphone), szTmp);

  //解码【5】C语言成绩
  i = 0;
  while (*pTmp != '#')
  {
    szTmp[i] = *pTmp;
    pTmp++;
    i++;
  }
  szTmp[i] = '\0';
  pTmp++;
  ppParam->StudentDecode.fStudentCGrade = (float) atof(szTmp);

  //解码【6】电话号码
  i = 0;
  while (*pTmp != '#')
  {
    szTmp[i] = *pTmp;
    pTmp++;
    i++;
  }
  szTmp[i] = '\0';
  pTmp++;
  strcpy_s(ppParam->StudentDecode.szStudentExtraInfo, 
    _countof(ppParam->StudentDecode.szStudentExtraInfo), szTmp);

  return 0;
}