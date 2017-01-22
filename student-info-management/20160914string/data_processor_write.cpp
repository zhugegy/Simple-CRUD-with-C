//���ļ������ݲ���_д��ѧ����Ϣ��غ�����

#include "stdafx.h"
#include "data_processor_write.h"

#include "data_processor.h"
#include "student_info_processor.h"

static int data_processor_write_check_secondary_parameters(Param *ppParam);

//ѧ����Ϣд��
//-w [num]
int data_processor_write(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nSerialNum = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_write_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�ṹ����Ϣ�������ַ���
  student_info_processor_encode_struct_to_string(ppParam);

  //�������ƽ���add
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

  //�Ѹ������ѧ����Ϣ�ݽ���piInfoBuffer��
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "ѧ�� %s ����Ϣ�ѳɹ���ӣ���� %d��\r\n", 
    ppParam->StudentTemplate.szStudentName, nSerialNum);

  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //����ѧ����Ϣģ��
  student_info_processor_refresh_template_to_default(&ppParam->StudentTemplate, 
    &ppParam->StudentDefault);

  return nSerialNum;
}

//-aָ��жϴ�Ҫ�����Ϸ��ԡ�
//�Ϸ���ʽ: -w [num]
static int data_processor_write_check_secondary_parameters(Param *ppParam)
{
  char *pchTmp = NULL;
  int nTmp;

  //�жϲ����������Ϸ�ֵ��1��2��
  if (ppParam->nArgc != 1 && ppParam->nArgc !=2)
  {
    return DATA_PROCESSOR_ERROR_WRITE_PARAMETER_NUM;
  }

  //��2���������кţ���ѡ��
  if (ppParam->nArgc == 2)
  {
    pchTmp = ppParam->szArgv[1];
    nTmp = atoi(pchTmp);

    //�Ƿ�Ϊ����������
    if (nTmp <= 0)
    {
      return DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_NUM;
    }

    //���֣���ţ��Ƿ���ã���δ�������ַ�����ռ�ã�
    if (data_processor_is_serial_avaiable(nTmp, ppParam) != 1)
    {
      return DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_AVAILABLE;
    }

  }

  return 0;
}