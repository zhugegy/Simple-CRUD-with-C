//���ļ������ݲ���_�޸�ѧ����Ϣģ����غ�����
//�ܶຯ���������Ƶģ�����Ϊ��ά�����㣬���Ƿֿ�д��

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

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_grade_stat_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�ж���û�п���ͳ�Ƶ�ѧ����Ϣ
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

  //��ʼͳ��
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

  //ͳ�ƽ�����
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ��������%d\r\n��߷֣�%2.2f\r\n��ͷ֣�%2.2f\r\nƽ���֣�%2.2f\r\n"
    "�����˵ĳɼ�֮�ͣ�%2.2f\r\n",
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