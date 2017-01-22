//���ļ������ݲ���_�޸�ѧ����Ϣģ����غ�����
//�ܶຯ���������Ƶģ�����Ϊ��ά�����㣬���Ƿֿ�д��

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

//-1ָ�ѧ����Ϣģ���޸�:1 StudentCode
//-1 string [string...]
int data_processor_cmd_1_studentcode(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentCodeTmp[MAX_STUDENT_CODE_LENGTH] = {0};
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_cmd_1_studentcode_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�Ѳ�������szStudentCodeTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*�˴�����������һ�û����������������ո���ô����ǰ���cmd_parser(trim)
      �����еĿո�ȥ���ˣ�����ֻ�ܻ�ԭ1���ո�*/
      /*ʱ�䲻�࣬�Ȳ�����*/
      strcat_s(szStudentCodeTmp, _countof(szStudentCodeTmp), " ");
    }

    strcat_s(szStudentCodeTmp, _countof(szStudentCodeTmp), ppParam->szArgv[i]);
  }

  //��szStudentCodeTmpд��ѧ����Ϣģ��
  strcpy_s(ppParam->StudentTemplate.szStudentCode, 
    _countof(ppParam->StudentTemplate.szStudentCode), szStudentCodeTmp);

  //��������piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� ѧ�� ��Ϣ�ѳɹ��޸ġ�\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-1ָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_cmd_1_studentcode_check_secondary_parameters
  (Param *ppParam)
{
  //��������������ԣ������10�������������Ļ�ǰ��ᱨ��ģ����ﲻ�ù�

  return 0;
}

//-2ָ�ѧ����Ϣģ���޸�:2 StudentName
//-2 string [string...]
int data_processor_cmd_2_studentname(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentNameTmp[MAX_STUDENT_NAME_LENGTH] = {0};
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_cmd_2_studentname_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�Ѳ�������szStudentNameTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*�˴�����������һ�û����������������ո���ô����ǰ���cmd_parser(trim)
      �����еĿո�ȥ���ˣ�����ֻ�ܻ�ԭ1���ո�*/
      /*ʱ�䲻�࣬�Ȳ�����*/
      strcat_s(szStudentNameTmp, _countof(szStudentNameTmp), " ");
    }

    strcat_s(szStudentNameTmp, _countof(szStudentNameTmp), ppParam->szArgv[i]);
  }

  //��szStudentNameTmpд��ѧ����Ϣģ��
  strcpy_s(ppParam->StudentTemplate.szStudentName, 
    _countof(ppParam->StudentTemplate.szStudentName), szStudentNameTmp);

  //��������piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� ���� ��Ϣ�ѳɹ��޸ġ�\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-2ָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_cmd_2_studentname_check_secondary_parameters
  (Param *ppParam)
{
  //��������������ԣ������10�������������Ļ�ǰ��ᱨ��ģ����ﲻ�ù�

  return 0;
}

//-3ָ�ѧ����Ϣģ���޸�:3 StudentBirthday
//-3 string [string...]
int data_processor_cmd_3_studentbirthday(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //���ʳ�����ʱ��StudentCode��
  char szStudentBirthdayTmp[MAX_STUDENT_CODE_LENGTH] = {0};   
  int nStudentBirthdayTmp = -1;
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_cmd_3_studentbirthday_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�Ѳ�������szStudentBirthdayTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    strcat_s(szStudentBirthdayTmp, _countof(szStudentBirthdayTmp), ppParam->szArgv[i]);
  }

  //��szStudentBirthdayTmpת��������
  nStudentBirthdayTmp = atoi(szStudentBirthdayTmp);

  //�ж����յĺϷ���
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

  //��nStudentBirthdayTmpд��ѧ����Ϣģ��
  ppParam->StudentTemplate.nStudentBirthday = nStudentBirthdayTmp;

  //��������piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� �������� ��Ϣ�ѳɹ��޸ġ�\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-3ָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_cmd_3_studentbirthday_check_secondary_parameters
  (Param *ppParam)
{
  //��������������ԣ������10�������������Ļ�ǰ��ᱨ��ģ����ﲻ�ù�

  return 0;
}

//-4ָ�ѧ����Ϣģ���޸�:4 StudentTelphone (telephone)
//-4 string [string...]
int data_processor_cmd_4_studenttelphone(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentTelphoneTmp[MAX_STUDENT_TEL_LENGTH] = {0};
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_cmd_4_studenttelphone_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�Ѳ�������szStudentTelphoneTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*�˴�����������һ�û����������������ո���ô����ǰ���cmd_parser(trim)
      �����еĿո�ȥ���ˣ�����ֻ�ܻ�ԭ1���ո�*/
      /*ʱ�䲻�࣬�Ȳ�����*/
      strcat_s(szStudentTelphoneTmp, _countof(szStudentTelphoneTmp), " ");
    }

    strcat_s(szStudentTelphoneTmp, _countof(szStudentTelphoneTmp), 
      ppParam->szArgv[i]);
  }

  //��szStudentNameTmpд��ѧ����Ϣģ��
  strcpy_s(ppParam->StudentTemplate.szStudentTelphone, 
    _countof(ppParam->StudentTemplate.szStudentTelphone), szStudentTelphoneTmp);

  //��������piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� �绰 ��Ϣ�ѳɹ��޸ġ�\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-4ָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_cmd_4_studenttelphone_check_secondary_parameters
  (Param *ppParam)
{
  //��������������ԣ������10�������������Ļ�ǰ��ᱨ��ģ����ﲻ�ù�

  return 0;
}

//-5ָ�ѧ����Ϣģ���޸�:5 StudentCGrade
//-5 string [string...]
int data_processor_cmd_5_studentcgrade(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //������ʱ����StudentCode��
  char szStudentCGradeTmp[MAX_STUDENT_CODE_LENGTH] = {0};
  float fStudentCGradeTmp = 0.0f;
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_cmd_5_studentcgrade_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�Ѳ�������szStudentCGradeTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    strcat_s(szStudentCGradeTmp, _countof(szStudentCGradeTmp), 
      ppParam->szArgv[i]);
  }

  //��szStudentCGradeTmpת���ɸ�����
  fStudentCGradeTmp = (float) atof(szStudentCGradeTmp);

  //�жϳɼ��ĺϷ���
  if (fStudentCGradeTmp <= 0)
  {
    nCheckValidityResult = DATA_PROCESSOR_ERROR_CMD_5_STUDENTCGRADE_NOT_LEGAL;
  }

  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //��fStudentCGradeTmpд��ѧ����Ϣģ��
  ppParam->StudentTemplate.fStudentCGrade = fStudentCGradeTmp;

  //��������piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� C���Գɼ� ��Ϣ�ѳɹ��޸ġ�\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-5ָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_cmd_5_studentcgrade_check_secondary_parameters
  (Param *ppParam)
{
  //��������������ԣ������10�������������Ļ�ǰ��ᱨ��ģ����ﲻ�ù�

  return 0;
}

//-6ָ�ѧ����Ϣģ���޸�:6 StudentExtraInfo
//-6 string [string...]
int data_processor_cmd_6_studentextrainfo(Param *ppParam)
{
  int nCheckValidityResult = 0;
  char szStudentExtraInfoTmp[MAX_STUDENT_EXTRA_INFO_LENGTH] = {0};
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_cmd_6_studentextrainfo_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�Ѳ�������szStudentExtraInfoTmp
  for (i = 1; i < ppParam->nArgc; i++)
  {
    if (i != 1)
    {
      /*�˴�����������һ�û����������������ո���ô����ǰ���cmd_parser(trim)
      �����еĿո�ȥ���ˣ�����ֻ�ܻ�ԭ1���ո�*/
      /*ʱ�䲻�࣬�Ȳ�����*/
      strcat_s(szStudentExtraInfoTmp, _countof(szStudentExtraInfoTmp), " ");
    }

    strcat_s(szStudentExtraInfoTmp, _countof(szStudentExtraInfoTmp), 
      ppParam->szArgv[i]);
  }

  //��szStudentCodeTmpд��ѧ����Ϣģ��
  strcpy_s(ppParam->StudentTemplate.szStudentExtraInfo, 
    _countof(ppParam->StudentTemplate.szStudentExtraInfo), 
    szStudentExtraInfoTmp);

  //��������piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� ������Ϣ �ѳɹ��޸ġ�\r\n");
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-6ָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_cmd_6_studentextrainfo_check_secondary_parameters
  (Param *ppParam)
{
  //��������������ԣ������10�������������Ļ�ǰ��ᱨ��ģ����ﲻ�ù�

  return 0;
}