//此文件是数据操作_修改学生信息模板相关函数。
//很多函数都是相似的，但是为了维护方便，还是分开写。

#include "stdafx.h"
#include "data_processor_grade_stat.h"

#include "data_processor.h"
#include "student_info_processor.h"

static int data_processor_grade_stat_check_secondary_parameters(Param *ppParam);

int data_processor_grade_stat(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nCounter = 0;

  float fMinGrade = 0.0f;
  float fMaxGrade = 0.0f;
  float fTotalGrade = 0.0f;
  float fAverageGrade = 0.0f;

  StringNode *psnTmp = NULL;

  //判断次要参数合法性
  nCheckValidityResult = 
    data_processor_grade_stat_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //判断有没有可以统计的学生信息
  if (ppParam->psnStringNodes == NULL)
  {
    nCheckValidityResult = 
      DATA_PROCESSOR_ERROR_GRADE_STAT_NO_AVAILABLE_STUDENT_INFO;
  }

  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //开始统计
  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    nCounter++;
    
    strcpy_s(ppParam->szStudentStructEncodeDecodeBuffer, 
      _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
      ppParam->pchArrayStorage + psnTmp->nArrayLocation);

    student_info_processor_decode_string_to_struct(ppParam);

    if (nCounter == 1)
    {
      fMinGrade = ppParam->StudentDecode.fStudentCGrade;
      fMaxGrade = ppParam->StudentDecode.fStudentCGrade;
    }

    if (ppParam->StudentDecode.fStudentCGrade < fMinGrade)
    {
      fMinGrade = ppParam->StudentDecode.fStudentCGrade;
    }

    if (ppParam->StudentDecode.fStudentCGrade > fMaxGrade)
    {
      fMaxGrade = ppParam->StudentDecode.fStudentCGrade;
    }

    fTotalGrade += ppParam->StudentDecode.fStudentCGrade;
  }

  fAverageGrade = fTotalGrade / ((float) nCounter);

  //统计结果输出
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "学生数量：%d\r\n最高分：%2.2f\r\n最低分：%2.2f\r\n平均分：%2.2f\r\n"
    "所有人的成绩之和：%2.2f\r\n",
    nCounter,
    fMaxGrade,
    fMinGrade,
    fAverageGrade,
    fTotalGrade);

  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

static int data_processor_grade_stat_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_GRADE_STAT_PARAMETER_NUM;
  }

  return 0;
}