//���ļ������ݲ�����غ�����

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
    //����ַ���
    //-a "string" [num]
    nResult = data_processor_add(ppParam);
    break;
  case 'l':
    //��ʾ�ַ���
    //-l [reg|num]
    nResult = data_processor_list(ppParam);
    break;
  /*
  case 'd':
    //ɾ���ַ���
    //-d num
    nResult = data_processor_delete(ppParam);
    break;
  */
  /*
  case 'm':
    //�޸��ַ���
    //-m num "string"
    nResult = data_processor_modify(ppParam);
    break;
  */
  case 's':
    //ͳ���ַ���
    //-s
    nResult = data_processor_stat(ppParam);
    break;
  case 'i':
    //�ڴ�ռ�����
    //-i
    nResult = data_processor_raminfo(ppParam);
    break;
  case 'j':
    //�����ڴ��ض���ַ
    //-j num
    nResult = data_processor_jump(ppParam); 
    break;
  case 'o':
    //�ڴ��Ż�
    //-o
    nResult = data_processor_optimize(ppParam);
    break;
  case 'q':
    //�˳�
    //-q
    nResult = data_processor_quit(ppParam);
    //���ô�ӡѧ��ģ����Ϣ��
    ppParam->nAppendingStudentTemplateControlFlag = 0; 
    break;
  case 'h':
    //����
    //-h
    nResult = data_processor_help(ppParam);
    break;
   //######����������Ϊѧ��ϵͳ�����######//
  case 'w':
    //д��ѧ����Ϣ
    //-w [num]
    nResult = data_processor_write(ppParam);
    break;
  case 'r':
    //ɾ��ѧ����Ϣ
    //-r num
    nResult = data_processor_remove(ppParam);
    break;
  case 'c':
    //����ѧ��(����)��Ϣ
    //-c num
    nResult = data_processor_change(ppParam);
    break;
  case '1':
    //����ѧ����Ϣģ�壺ѧ��
    //-1 string [string...]
    nResult = data_processor_cmd_1_studentcode(ppParam);
    break;
  case '2':
    //����ѧ����Ϣģ�壺����
    //-2 string [string...]
    nResult = data_processor_cmd_2_studentname(ppParam);
    break;
  case '3':
    //����ѧ����Ϣģ�壺��������
    //-3 num [num...]
    nResult = data_processor_cmd_3_studentbirthday(ppParam);
    break;
  case '4':
    //����ѧ����Ϣģ�壺�绰
    //-4 string [string...]
    nResult = data_processor_cmd_4_studenttelphone(ppParam);
    break;
  case '5':
    //����ѧ����Ϣģ�壺C���Գɼ�
    //-5 floatnum
    nResult = data_processor_cmd_5_studentcgrade(ppParam);
    break;
  case '6':
    //����ѧ����Ϣģ�壺������Ϣ
    //-6 string [string...]
    nResult = data_processor_cmd_6_studentextrainfo(ppParam);
    break;
  case 'g':
    //ͳ��C���Գɼ�
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

//����ʱ������Ϣ�Ĵ���,�Ѵ�����Ϣ���͸�ppParam->piInfoBuffer��
int data_processor_send_error_msg(int nErrorNum, Param *ppParam)
{
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  /*�����������󣬿���ȡ����ʾģ��*/
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

  //�����һ�����ǿգ��Ǿͷ���0����һ���ڴ�ռ䣩��
  //�����г���ΪarychSim[0 - 1]Խ�硣
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

  //����Ҳ���
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

  //����Ҳ���
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

//�˳�(-q ָ�
static int data_processor_quit(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_quit_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //change flag
  ppParam->nControlFlag = 1;

  //������Ϣ��piInfoBuffer��
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

//����(-h ָ�
static int data_processor_help(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_help_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //��ʾ������������Ϣ��piInfoBuffer��
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    HELP_INFO);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//�Ż��ڴ�ĺ�����������Ƭ(-o ָ�
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

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_optimize_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //����Ѱ�ҿ����ڴ沢��λ��
  while (TRUE)
  {
    //��ʼ���ڴ�ģ���
    initialize_sim_array(ppParam);
	    
    //�����ڴ�ģ���
    update_sim_array(ppParam);

    //�ҵ���һ��Full_Empty��
    nFirstFullEmptyLocation = 
      data_processor_optimize_find_the_first_full_empty(ppParam);
    if (nFirstFullEmptyLocation == -1)
    {
      break;
    }

    //�ҵ���һ��Full_Empty����ĵ�һ��Empty_Full��
    nNextEmptyFullLocation = 
      data_processor_optimize_find_the_next_empty_full(nFirstFullEmptyLocation, 
      ppParam);

    if (nNextEmptyFullLocation == -1)
    {
      break;
    }

    //��λ���ַ���������ڵ�
    psnCurrentStringNode = 
      data_processor_get_ram_info_strnode(nNextEmptyFullLocation, ppParam);

    //�洢�ýڵ��ԭ��ʼ����
    nPrevArrayLocation = psnCurrentStringNode->nArrayLocation;

    //�ڵ�λ�Ƶ���һ��Full_Empty����
    psnCurrentStringNode->nArrayLocation = nFirstFullEmptyLocation;
    
    //�޸Ľڵ���linkinfo�е����ݣ�ɾ��+��ӣ�
    file_operator_delete_string_node_in_link_info(psnCurrentStringNode);
    file_operator_write_string_node_in_link_info(psnCurrentStringNode);

    //�����ַ����洢���飬������ƽ�ơ�
    for (i = 0; i < psnCurrentStringNode->nStringLength; i++)
    {
      ppParam->pchArrayStorage[nFirstFullEmptyLocation + i] =
        ppParam->pchArrayStorage[nPrevArrayLocation + i];
    }

    //������洢�ļ�����ʱ���޸��ˣ���ȫ���Ż�������ͳһ�޸ģ���д��������

    //�洢���������ַ�����š�
    sprintf_s(szTmp, _countof(szTmp), " %d", psnCurrentStringNode->nSerial);
    strcat_s(szInfoBuffer, _countof(szInfoBuffer), szTmp);
  }

  //�ڴ�������ϣ�����������������£���д�洢�ļ���ӳ�䣩
  if (strcmp(szInfoBuffer, "") != 0)
  {
    file_operator_map_heap_to_storage_file(ppParam);
  }
  
  //�ڴ�������ϣ�������Ϣ��piInfoBuffer��
  if (strcmp(szInfoBuffer, "") == 0)
  {
    sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      "����ǰ���ڴ�ṹ�Ѿ����ţ���������\r\n");
  }
  else
  {
    sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
      "�ڴ�������ϣ���ǰ�ƹ����ַ�����ţ�%s��\r\n", szInfoBuffer);
  }
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-jָ���жϲ����Ϸ��ԡ�
//�Ϸ���ʽ��-j num
static int data_processor_jump_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //�жϲ���������
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_JUMP_PARAMETER_NUM;
  }

  //�жϵ�1�����Ƿ�Ϊ���֡�
  nTmp = atoi(ppParam->szArgv[1]);
  
  //�����1������0��ֱ�ӷ���0�������Ϸ�����Ϊ�¸��жϺʹ˲�����ͻ���Ե����жϡ�
  if (strcmp(ppParam->szArgv[1], "0") == 0)
  {
    return 0;
  }

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_NOT_NUM;
  }

  //�ж��û��������������ڴ�����û�����ݣ���ȷ�������������
  if (data_processor_probe_ram_info(nTmp, ppParam) != 1)
  {
    return DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_RAM_NO_CONTENT;
  }

  return 0;
}


//��ʾ�ڴ�ָ��λ�õ���Ϣ�ĺ���(-j ָ�
static int data_processor_jump(Param *ppParam)
{
  int nCheckValidityResult = 0;
  StringNode *psnStringNode = NULL;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_jump_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //��ȡ�ַ����ڵ��ַ
  psnStringNode = data_processor_get_ram_info_strnode(atoi(ppParam->szArgv[1]), 
    ppParam);

  //����ַ�����Ϣ��piInfoBuffr��
  /*sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "�ַ�������: %s �ڴ��ַ: %d - %d , ������ţ�%d��\r\n", 
    ppParam->pchArrayStorage + psnStringNode->nArrayLocation, 
    psnStringNode->nArrayLocation, 
    psnStringNode->nArrayLocation + psnStringNode->nStringLength - 1, 
    psnStringNode->nSerial);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;*/
  data_processor_decode_string_node_and_push_to_infobuffer(ppParam, psnStringNode);

  return 0;
}

//-iָ���жϲ����Ϸ��ԡ�
//�Ϸ���ʽ: -i
static int data_processor_raminfo_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_RAMINFO_PARAMETER_NUM;
  }

  return 0;
}

//��ʾ�ڴ�ռ����Ϣ����(-i ָ�
static int data_processor_raminfo(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int i = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_raminfo_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //��ʼ���ڴ�ģ�����顣
  initialize_sim_array(ppParam);

  //�����ڴ�ģ�����顣
  update_sim_array(ppParam);

  //����piInfoBuffer��
  empty_pi_info_buffer(ppParam);

  //���ڴ���Ϣ�����piInfoBuffr;
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

//-sָ���жϲ����Ϸ��ԡ�
//�Ϸ���ʽ: -s
static int data_processor_stat_check_secondary_parameters(Param *ppParam)
{
  if (ppParam->nArgc != 1)
  {
    return DATA_PROCESSOR_ERROR_STAT_PARAMETER_NUM;
  }

  return 0;
}

//ͳ�ƺ���(-s ָ��)��
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

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_stat_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //ִ��ͳ�Ʋ�����
  //��ʼ��ͳ�����顣
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
 
  //ͳ���ַ�������
  for (i = 0; i < _countof(ppParam->nCharArray); i++)
  {
    nSum += ppParam->nCharArray[i];
  }

  //����piInfoBuffer��
  empty_pi_info_buffer(ppParam);
  
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //��������piInfoBuffer
  for (i = 0; i < _countof(ppParam->nCharArray); i++)
  {
    if (ppParam->nCharArray[i] != 0)
    {
      fPercentage = (float) (ppParam->nCharArray[i] * 100 / nSum);
      sprintf_s(szTmp, _countof(szTmp), "�ַ� %c ������%d\t%.2f%s\r\n", i, 
        ppParam->nCharArray[i], fPercentage, "%");
      strcat_s(ppParam->piInfoBuffer.szToBePrinted, 
        _countof(ppParam->piInfoBuffer.szToBePrinted), szTmp);
    }
  }

  if (strcmp(ppParam->piInfoBuffer.szToBePrinted, "") == 0)
  {
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
      _countof(ppParam->piInfoBuffer.szToBePrinted), 
      "����û��ͳ�����ݡ�\r\n");
  }

  return 0;
}

//��ʼ���ַ�����Ƶ��ͳ������
static int data_processor_stat_initialize_char_array(Param *ppParam)
{
  int i = 0;

  for (i = 0; i < _countof(ppParam->nCharArray); i++)
  {
    ppParam->nCharArray[i] = 0;
  }

  return 0;
}

//-mָ��жϴ�Ҫ�����Ϸ��ԡ�
//�Ϸ���ʽ: -m num "string"
static int data_processor_modify_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;
  char *pchTmp = NULL;

  //�жϲ����������Ϸ�ֵ��3��
  if (ppParam->nArgc !=3)
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_NUM;
  }

  //�жϵ�1�����ǲ�������
  nTmp = atoi(ppParam->szArgv[1]);

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NOT_NUM;
  }

  //�ж��û������������������д治���ڣ���ȷ������Ǵ���
  if (data_processor_is_serial_avaiable(nTmp, ppParam) != 0)
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NUM_NOT_EXIST;
  }

  //�жϵ�2�����Ƿ����Ű���������
  //������
  pchTmp = ppParam->szArgv[2];
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_2_LACK_OF_QUOTER;
  }

  //������
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

//�޸��ַ�������(-m ָ��)��
static int data_processor_modify(Param *ppParam)
{
  int nCheckValidityResult = 0;
  //������ʱ����û�ָ�
  char szTmpArgv1[MAX_CMD_LENGTH] = {0};
  char szTmpArgv2[MAX_CMD_LENGTH] = {0};

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_modify_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //ִ���޸Ĳ�������ɾ��+��ӣ�
  strcpy_s(szTmpArgv1, _countof(szTmpArgv1), ppParam->szArgv[1]);
  strcpy_s(szTmpArgv2, _countof(szTmpArgv2), ppParam->szArgv[2]);
  
  //ɾ��
  ppParam->nArgc = 2;
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-d");
  //szArgv[1]�����޸�
  strcpy_s(ppParam->szArgv[2], _countof(ppParam->szArgv[2]), "");
  data_processor_delete(ppParam);

  //���
  ppParam->nArgc = 3;
  strcpy_s(ppParam->szArgv[0], _countof(ppParam->szArgv[0]), "-a");
  strcpy_s(ppParam->szArgv[1], _countof(ppParam->szArgv[1]), szTmpArgv2);
  strcpy_s(ppParam->szArgv[2], _countof(ppParam->szArgv[2]), szTmpArgv1);
  data_processor_add(ppParam);

  //��������piInfoBuffer
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "�ַ����ѳɹ��޸ģ���� %s��\r\n", ppParam->szArgv[2]);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//-dָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_delete_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;

  //�жϲ�������
  if (ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_DELETE_PARAMETER_NUM;
  }

  //�жϵڶ������ǲ�������
  nTmp = atoi(ppParam->szArgv[1]);

  if (nTmp <= 0)
  {
    return DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NOT_NUM;
  }

  //�ж��û������������������д治���ڣ���ȷ������Ǵ���
  if (data_processor_is_serial_avaiable(nTmp, ppParam) != 0)
  {
    return DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NUM_NOT_EXIST;
  }
  
  return 0;
}

//ɾ���ַ�������(-d ָ��)��
int data_processor_delete(Param *ppParam)
{
  int nCheckValidityResult = 0;
  int nArrayLocation = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = 
    data_processor_delete_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //ִ��ɾ����������ɾ������ڵ㣩
  nArrayLocation = data_processor_delete_string_node(atoi(ppParam->szArgv[1]), 
    ppParam);

  //����ɾ������Ϣ����buffer��������룬Ȼ����ʾ���û�
  student_info_processor_move_info_to_buffer(ppParam, 
    (ppParam->pchArrayStorage + nArrayLocation));

  //��������piInfoBuffer
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "�ַ���\"%s\"�ѳɹ�ɾ������� %s��\r\n", 
    ppParam->pchArrayStorage + nArrayLocation, ppParam->szArgv[1]);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return 0;
}

//ɾ������ڵ�
static int data_processor_delete_string_node(int nSerial, Param *ppParam)
{
  StringNode *psnPrev = NULL;
  StringNode *psnTmp = NULL;
  int nTmp = 0;

  for (psnTmp = ppParam->psnStringNodes; psnTmp; psnTmp = psnTmp->psnNext)
  {
    
    //���nSerial��ƥ��,��������������
    if (psnTmp->nSerial != nSerial)
    {
      psnPrev = psnTmp;
    }
    //���nSerialƥ��
    else
    {
      //���жϴ˽ڵ�ǰ����û�нڵ㣬����У����ǰ��ڵ����һ��ָ���Լ�����һ��
      if (psnPrev != NULL)
      {
        psnPrev->psnNext = psnTmp->psnNext;
      }
      //���û�У�Ҳ����˵���ǵ�һ���ڵ㣬��ô�ı�ppParam�д洢��������ʼλ�ã�
      else
      {
        ppParam->psnStringNodes = psnTmp->psnNext;
      }

      //����һ�������ַ�����¼�����е���ʼλ�ã��Ժ��ӡ�����
      nTmp = psnTmp->nArrayLocation;

      //ɾ������ڵ���LinkInfo�ļ��еļ�¼
      file_operator_delete_string_node_in_link_info(psnTmp);

      //�ͷ�����ڵ�Ŀռ�
      free(psnTmp);

      return nTmp;
      break;
    }
  }

  //���û��ɾ������-1�������ܵ�����������á�
  return -1;
}

//��ѯ�ַ�������(-l ָ��)��
static int data_processor_list(Param *ppParam)
{
  int nCheckValidityResult = 0;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult =
    data_processor_list_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //��������������׼������д�뽫Ҫ������û�����Ϣ��
  empty_pi_info_buffer(ppParam);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //�����ڶ�������ȷ������ִ��ʲô����
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

//list ALL ��ָ�-l��
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

//list NUM (ָ�-l 5)
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

//list REG ��ָ� -l "el")
static int data_processor_list_operation_reg(Param *ppParam)
{
  StringNode *psnTmp = NULL;
  char szTmp[MAX_INFO_STRING_LENGTH];

  //ȥ���ڶ��������ҵ����š�
  data_processor_remove_quoter(ppParam->szArgv[1]);

  //����������ʽ
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

//�����������Ϣ���뵽�ṹ�壬�����͵�piInfoBuffer
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
    "��ţ�%d �ڴ��ַ��%d - %d ����ʱ�䣺%s"
    "ѧ�ţ�%s ������%s ���䣺%d �绰��%s C���Գɼ���%2.2f ������Ϣ��%s\r\n\r\n", 
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

//-lָ������ڶ�������ȷ������ִ��ʲô������
static int data_processor_list_decide_operation(Param *ppParam)
{
  int nTmp = 0;

  if (ppParam->nArgc == 1)
  {
    return DATA_PROCESSOR_OPERATION_LIST_ALL;
  }

  //ͨ��atoi�����жϵڶ����������ֻ����ַ�����
  nTmp = atoi(ppParam->szArgv[1]);

  //����ڶ����������֣��ѱ���֤Ϊ��������
  if (nTmp != 0)
  {
    return DATA_PROCESSOR_OPERATION_LIST_NUM;
  }
  //����ڶ�������������ʽ������֤���ѱ�˫�����������ˣ�
  else
  {
    return DATA_PROCESSOR_OPERATION_LIST_REG;
  }

  return 0;
}

//-lָ��жϴ�Ҫ�����Ϸ��ԡ�
static int data_processor_list_check_secondary_parameters(Param *ppParam)
{
  int nTmp = 0;
  char *pchTmp = NULL;

  //�жϲ�������
  if (ppParam->nArgc != 1 && ppParam->nArgc != 2)
  {
    return DATA_PROCESSOR_ERROR_LIST_PARAMETER_NUM;
  }

  //�����һ����������Ҳûʲô�ü�����,�϶���('-l')
  if (ppParam->nArgc == 1)
  {
    return 0;
  }

  //ͨ��atoi�����жϵڶ����������ֻ����ַ�����
  nTmp = atoi(ppParam->szArgv[1]);
  
  //���������
  if (nTmp != 0)
  {
    if (nTmp < 0)
    {
      return DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_NEGATIVE_NUM;
    }
  }
  //������ַ���
  else
  {
    /*�жϵڶ������Ƿ����Ű��������� ����û�����0,00,000...,Ҳ���ڴ˱�����
    ��һ��false negative�������߼����ԣ�����������š�*/

    //������
    pchTmp = ppParam->szArgv[1];
    if (*pchTmp != '"')
    {
      return DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_LACK_OF_QUOTER;
    }

    //������
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

//����ַ���������-aָ���
int data_processor_add(Param *ppParam)
{
  int nCheckValidityResult = 0;
  StringNode snTemplate;
  StringNode *psnTmp = NULL;

  //�жϴ�Ҫ�����Ϸ���
  nCheckValidityResult = data_processor_add_check_secondary_parameters(ppParam);
  if (nCheckValidityResult != 0)
  {
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //����ַ������ҵ�����
  data_processor_remove_quoter(ppParam->szArgv[1]);

  //����StringNodeģ��
  //ȷ���ַ�������ʱ��
  snTemplate.tCreationTime = time(0);

  //ȷ���ַ�������
  snTemplate.nStringLength = strlen(ppParam->szArgv[1]) + 1;

  //ȷ���ַ������
  if (ppParam->nArgc == 3)
  {
    snTemplate.nSerial = atoi(ppParam->szArgv[2]);
  }
  else
  {
    snTemplate.nSerial = data_processor_find_avaiable_serial(ppParam);
  }

  //ȷ���ַ�����ʼ��ַ
  snTemplate.nArrayLocation = data_processor_find_avaiable_Array_Location(
    snTemplate.nStringLength, ppParam);

  //����Ҳ������ÿռ�
  /*if (snTemplate.nArrayLocation == -1)
  {
    nCheckValidityResult = DATA_PROCESSOR_ERROR_ADD_NO_AVAILABLE_SPACE;
    data_processor_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }*/

  /*20161005�������ļ��洢�ˣ�����Ҳ����ռ䣬���ټ�һ���ļ��飬���ļ��麯���ں�
  �������ϵͳ����������������´洢�ļ���С����������ӳ���ļ����ڴ�ȵȣ�*/
  while (snTemplate.nArrayLocation == -1)
  {
    file_operator_add_extra_content_block(ppParam);
    snTemplate.nArrayLocation = data_processor_find_avaiable_Array_Location(
      snTemplate.nStringLength, ppParam);
  }

  //����Ϣд��洢����
  data_processor_write_in_array(ppParam->szArgv[1], snTemplate.nArrayLocation,
    ppParam);


  //���ַ����洢��Ϣ��������
  psnTmp = &snTemplate;
  data_processor_build_string_node_chain(ppParam, psnTmp);

  //�Ѹ�������ַ�����Ϣ�ݽ���piInfoBuffer��
  sprintf_s(ppParam->piInfoBuffer.szToBePrinted, MAX_INFO_STRING_LENGTH, 
    "�ַ���\"%s\"�ѳɹ���ӣ���� %d��\r\n", 
    ppParam->pchArrayStorage + psnTmp->nArrayLocation, psnTmp->nSerial);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  return psnTmp->nSerial;
}

//����Ϣд��洢���顣
static int data_processor_write_in_array(char *szTarget, int nArrayLocation,
                                         Param *ppParam)
{
  int i = 0;
  char *pchTmp = szTarget;

  while (*pchTmp != '\0')
  {
    /*20161004
    if ((nArrayLocation + i) < STRING_ARRAY_SPACE)  //Խ����
      //20161004�����ļ�ϵͳ֮��Խ���飬����Ч�ʣ�������
    {
      ppParam->szArrayStorage[nArrayLocation + i] = *pchTmp;
      i++;
    }*/
    ppParam->pchArrayStorage[nArrayLocation + i] = *pchTmp;
    i++;
    
    pchTmp++;
  }

  /*20161004
  //20161004�����ļ�ϵͳ֮��Խ���飬����Ч�ʣ�������
  if ((nArrayLocation + i) < STRING_ARRAY_SPACE)
  {
    ppParam->szArrayStorage[nArrayLocation + i] = '\0';
  }
  else
  {
    ppParam->szArrayStorage[STRING_ARRAY_SPACE - 1] = '\0';
  }*/
  ppParam->pchArrayStorage[nArrayLocation + i] = '\0';
  
  //����Ϣ��ʱͬ�����ļ�
  file_operator_write_content_in_storage(szTarget, nArrayLocation);

  return i;
}

//����ַ������ҵ����š�
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

//-aָ��жϴ�Ҫ�����Ϸ��ԡ�
//�Ϸ���ʽ: -a "string" [num]
static int data_processor_add_check_secondary_parameters(Param *ppParam)
{
  char *pchTmp = NULL;
  int nTmp;

  //�жϲ����������Ϸ�ֵ��2��3��
  if (ppParam->nArgc != 2 && ppParam->nArgc !=3)
  {
    return DATA_PROCESSOR_ERROR_ADD_PARAMETER_NUM;
  }

  //�жϵڶ������Ƿ����Ű���������
  //������
  pchTmp = ppParam->szArgv[1];
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_ADD_PARAMETER_1_LACK_OF_QUOTER;
  }

  //������
  while (*pchTmp != '\0')
  {
    pchTmp++;
  }
  pchTmp--;
  if (*pchTmp != '"')
  {
    return DATA_PROCESSOR_ERROR_ADD_PARAMETER_1_LACK_OF_QUOTER;
  }

  //�������������кţ���ѡ��
  if (ppParam->nArgc == 3)
  {
    pchTmp = ppParam->szArgv[2];
    nTmp = atoi(pchTmp);

    //�Ƿ�Ϊ����������
    if (nTmp <= 0)
    {
      return DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_NUM;
    }

    //���֣���ţ��Ƿ���ã���δ�������ַ�����ռ�ã�
    if (data_processor_is_serial_avaiable(nTmp, ppParam) != 1)
    {
      return DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_AVAILABLE;
    }
    
  }

  return 0;
}

//���ֶ�Ӧ���ڴ������Ƿ������ݣ�
/*�˺������ڶ��ֳ��ϣ����Ժ�data_processor_get_ram_info_strnode��ʽ���ƣ�����ʵ
��ͬ*/
static int data_processor_probe_ram_info(int nNum, Param *ppParam)
{
  StringNode *psnTemp = NULL;

  for (psnTemp = ppParam->psnStringNodes; psnTemp; psnTemp = psnTemp->psnNext)
  {
    if ((nNum >= psnTemp->nArrayLocation) &&
        (nNum < psnTemp->nArrayLocation + psnTemp->nStringLength))
    {
      //����������
      return 1;
    }
  }

  //���ڴ�λ��û������
  return 0;
}

//�����ڴ��ַ��ȡ����ڵ��ַ��
static StringNode *data_processor_get_ram_info_strnode(int nNum, Param *ppParam)
{
  StringNode *psnTemp = NULL;

  for (psnTemp = ppParam->psnStringNodes; psnTemp; psnTemp = psnTemp->psnNext)
  {
    if ((nNum >= psnTemp->nArrayLocation) &&
      (nNum < psnTemp->nArrayLocation + psnTemp->nStringLength))
    {
      //��λ�ɹ������ؽڵ��ַ��
      return psnTemp;
    }
  }

  /*��λʧ�ܣ�����������ᷢ������Ϊ�Ѿ���data_processor_probe_ram_info������֤
  ���˽ڵ�Ĵ��ڣ����Աض���ɹ���*/
  return NULL;
}

//���֣���ţ��Ƿ���ã���δ�������ַ�����ռ�ã�
int data_processor_is_serial_avaiable(int nNum, Param *ppParam)
{
  StringNode *psnTemp = NULL;

  //�����ʱ��δ���ַ������루�����ǿյģ�
  if (ppParam->psnStringNodes == NULL) 
  {
    return 1;
  }

  for (psnTemp = ppParam->psnStringNodes; psnTemp/*->psnNext*/; psnTemp =
    psnTemp->psnNext)
  {
    if (nNum == psnTemp->nSerial)
    {
      //�����к��ѱ�ռ��
      return 0;
    }
  }

  //�����кſ���ʹ��
  return 1;
}

//��һ�����õ���š�
static int data_processor_find_avaiable_serial(Param *ppParam)
{
  StringNode *psnTemp = NULL;
  int i = 0;

  //�����ʱ��δ���ַ������루�����ǿյģ�
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

  //�����������-1������ԡ�
  return -1;
}

//��һ�����õ���ʼ��ַ��
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

  //�����ʱ��δ���ַ������루�����ǿյģ�,��ô�͸�����һ����ַ�ɣ�Ҳ����0��
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
          /*Խ���飬Խ���˾��ټ�һ���ļ���*/
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

  //����õ��Ŀռ�Խ��
  if (nTempLocationEnd >= ppParam->nStorageFileCharSize)
  {
    return -1;
  }

  //����Ҳ������ÿռ䣬����-1��
  return -1;
}

//������Ϣ��¼�����ɹ�����0��ʧ�ܷ���DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC��
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
    //������������ɺ�ͬ���������ļ�
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
    //������������ɺ�ͬ���������ļ�
    file_operator_write_string_node_in_link_info(psnTmp);
  }
   
  return 0;
}

//�����ڴ�ģ��������Ϣ����������ʾ�ڴ�ռ�������
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

//��ʼ���ڴ����飬��������ʾ�ڴ�ռ�������
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