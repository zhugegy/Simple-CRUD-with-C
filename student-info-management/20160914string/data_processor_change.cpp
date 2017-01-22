//���ļ������ݲ���_�޸�ѧ����Ϣ��غ�����

#include "stdafx.h"
#include "data_processor_change.h"

#include "data_processor.h"
#include "data_processor_write.h"
#include "data_processor_remove.h"

static int data_processor_change_check_secondary_parameters(Param *ppParam);

//ѧ����Ϣ�޸�
//-c num
int data_processor_change(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nSerialNum = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_change_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�ƽ���remove��write
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-r");
  data_processor_remove(ppParam);

  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-w");
  nSerialNum = data_processor_write(ppParam);

  //��������piInfoBuffer
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� %s ��Ϣ�ѳɹ��޸ģ���� %d��\r\n", 
    ppParam->StudentTemplate.szStudentName, 
    nSerialNum);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-cָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_change_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //�жϲ�������
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_CHANGE_PARAMETER_NUM;
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