//���ļ������ݲ���_ɾ��ѧ����Ϣ��غ�����

#include "stdafx.h"
#include "data_processor_remove.h"

#include "data_processor.h"
#include "student_info_processor.h"

static int data_processor_remove_check_secondary_parameters(Param *ppParam);

//ѧ����Ϣɾ��
//-r num
int data_processor_remove(Param *ppParam)
{
  int nCheckValidityResult = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_remove_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�ݽ���delete
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-d");

  data_processor_delete(ppParam);

  //����ѧ������
  student_info_processor_decode_string_to_struct(ppParam);

  //��������piInfoBuffer
  
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� %s �ѳɹ�ɾ������� %s��\r\n", 
    ppParam->StudentDecode.szStudentName, ppParam->szArgv[1]);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-rָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_remove_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //�жϲ�������
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_REMOVE_PARAMETER_NUM;
  }

  //�жϵڶ������ǲ�������
  nTmp = atoi(ppParam->szArgv[1]);

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NOT_NUM;
  }

  //�ж��û������������������д治���ڣ���ȷ������Ǵ���
  if (data_processor_is_serial_avaiable(nTmp, ppParam) != 0)
  {
    return DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NUM_NOT_EXIST;
  }

  return 0;
}