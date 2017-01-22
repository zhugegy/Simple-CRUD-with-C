//���ļ���ѧ����Ϣ������غ�����

#include "stdafx.h"
#include "student_info_processor.h"

//��ʼ��Ĭ��ѧ����Ϣ
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

//��ѧ����Ϣģ��ˢ����Ĭ��
int student_info_processor_refresh_template_to_default(
  Student *pStudentTemplate, Student *pStudentDefault)
{
  *pStudentTemplate = *pStudentDefault;

  return 0;
}

//�ṹ����Ϣ�������ַ���
int student_info_processor_encode_struct_to_string(Param *ppParam)
{
  char szTmp[MAX_STRING_LENGTH] = {0};

  //���buffer
  strcpy_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "\"");

  //����
  //��1��ѧ��
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentCode);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //��2������
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentName);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //��3����������
  sprintf_s(szTmp, _countof(szTmp), "%8d", 
    ppParam->StudentTemplate.nStudentBirthday);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), szTmp);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //��4���绰����
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentTelphone);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //��5��C���Գɼ�
  sprintf_s(szTmp, _countof(szTmp), "%2.2f", 
    ppParam->StudentTemplate.fStudentCGrade);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), szTmp);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  //��6��������Ϣ
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), 
    ppParam->StudentTemplate.szStudentExtraInfo);
  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "#");

  strcat_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), "\"");

  return 0;
}

//���ڴ��еı�������ַ�������buffer
int student_info_processor_move_info_to_buffer(Param *ppParam, char *szEncoded)
{
  strcpy_s(ppParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppParam->szStudentStructEncodeDecodeBuffer), szEncoded);
  return 0;
}

//���ַ�����Ϣ�������ṹ��
int student_info_processor_decode_string_to_struct(Param *ppParam)
{
  char *pTmp = ppParam->szStudentStructEncodeDecodeBuffer;
  char szTmp[MAX_STRING_LENGTH] = {0};
  int i = 0;

  //�����ö�ά�����ѭ�������������׳���û̫��ʱ������ˣ�����һ��һ����

  //���롾1��ѧ��
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

  //���롾2������
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

  //���롾3����������
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

  //���롾4���绰����
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

  //���롾5��C���Գɼ�
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

  //���롾6���绰����
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