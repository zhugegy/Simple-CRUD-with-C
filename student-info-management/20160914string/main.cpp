// main.cpp : �������̨Ӧ�ó������ڵ㡣
//���ļ������̿�����غ�������Ȩ����interface,option_parser��

#include "stdafx.h"
#include "main.h"
#include "interface.h"
#include "cmd_parser.h"
#include "data_processor.h"
#include "file_operator.h"
#include "student_info_processor.h"

static int initialize_parameter(Param *ppMainParam);
static int free_string_nodes(Param *ppParam);
static int swtich_to_cmd_mode(Param *ppParam, char* szCmd);

int main(int argc, char* argv[])
{
  Param pMain;
  char szTmp[MAX_STRING_LENGTH] = {0};

  //1. ��ʼ��������
  initialize_parameter(&pMain);

  //������ģʽ��ת(ָ��ģʽ���ڽ����ڿ������ѧ����Ϣ��Ҳ����-a "string")
  //��Ϊÿ�ζ��ڽ������д����ѧ����Ϣ����ӣ�������ʽ���ʺ�������Ӳ���
  //�����Ĺ�����ʱ�����
  if (argc != 1)
  {
    strcpy_s(szTmp, _countof(szTmp), argv[2]);
    swtich_to_cmd_mode(&pMain, szTmp);

    return 0;
  }

  //2. ��ʼ�����档
  call_interface(INTERFACE_CMD_INITIALIZE, &pMain);
  
  //3. �������ѭ����
  while (pMain.nControlFlag == 0)
  {
    //3.1 ��ȡ�û�ָ�
    call_interface(INTERFACE_CMD_GET_USER_CMD, &pMain);

    //3.2 �����û�ָ�
    /*�������ʧ�ܣ����ʹ�����Ϣ���û�������Ĵ����Ѿ���cmd_parserд��pMain��
    �����piInfoBuffer�С�*/
    if (call_cmd_parser(&pMain) != 0)
    {
      call_interface(INTERFACE_CMD_PRINT, &pMain);
      continue;
    }

    //printf("�û�ָ��2��%s\r\n", pMain.szCmdBuffer);

    //3.3 �������ݲ�����
    /*������ݲ���ʧ�ܣ����ʹ�����Ϣ���û�������Ĵ����Ѿ���data_processorд��
    pMain�ṹ���piInfoBuffer�С�*/
    /*20161004���ڼ������ļ�������3.3��һ���������ˣ�����ĳ�ָ�룬��Ӧ�ı伴ʱ
    д���ļ���*/
    call_data_processor(&pMain);

    //3.4 ��ʾ���������
	call_interface(INTERFACE_CMD_PRINT, &pMain);
  }


  //4. ����ռ�õĿռ䡣
  free_string_nodes(&pMain);
  free_mapping_heaps(&pMain);
  
  system("pause");
  return 0;
}

//����ģʽ��ת
static int swtich_to_cmd_mode(Param *ppParam, char* szCmd)
{
  char szTmp[MAX_STRING_LENGTH] = {0};

  //�ֶ���д������Ϣ���Ķ���������
  ppParam->chUserCmd = 'a';

  ppParam->nArgc = 2;
  
  //����ϵͳ���Զ����Ҽӵ�˫����ʡ�Ե���ֻ���Լ��������ټ�һ��
  //�����Լ���������ָ��-a "string"�У�string�ﲻ�ܰ����ո���
  strcpy_s(szTmp, _countof(szTmp), "\"");
  strcat_s(szTmp, _countof(szTmp), szCmd);
  strcat_s(szTmp, _countof(szTmp), "\"");

  strcpy_s(ppParam->szArgv[1], _countof(ppParam->szArgv[1]), szTmp);

  //�����еĻ����Ͳ���Ҫ���ѧ��ģ����Ϣ�ˡ�
  ppParam->nAppendingStudentTemplateControlFlag = 0;

  call_data_processor(ppParam);
  call_interface(INTERFACE_CMD_PRINT, ppParam);

  free_string_nodes(ppParam);
  free_mapping_heaps(ppParam);

  return 0;
}

static int free_string_nodes(Param *ppParam)
{
  StringNode *psnTmp = NULL;
  StringNode *psnNext = NULL;

  psnTmp = ppParam->psnStringNodes;

  while (psnTmp)
  {
    psnNext = psnTmp->psnNext;
    free((void *) psnTmp);
    psnTmp = psnNext;
  }

  return 0;
}


static int initialize_parameter(Param *ppMainParam)
{
  int i = 0;
  //char szTmp[MAX_SYSTEM_PARAM_LENGTH] = {0};

  //��ʼ���������flag��
  ppMainParam->nControlFlag = 0;

  //�Ƿ������׷��ѧ����Ϣflag��Ĭ��Ϊ1
  ppMainParam->nAppendingStudentTemplateControlFlag = 1;

  //����洢�ļ������ڣ���һ������ʱ���������ļ���
  file_operator_create_files();

  //�򿪴洢�ļ�
  //ppMainParam->pfStorageFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  //��ȡ�ļ���С
  ppMainParam->nStorageFileCharSize = 
    file_operator_get_storage_file_size_byte();

  //��������ļ���0�ֽڣ�����ô����д��һ���������
  if (ppMainParam->nStorageFileCharSize == 0)
  {
    file_operator_write_new_content_block_in_storage();
    ppMainParam->nStorageFileCharSize = 
      file_operator_get_storage_file_size_byte();
  }
  /*20161004
  //��ʼ���ַ����洢���顣
  for (i = 0; i < _countof(ppMainParam->szArrayStorage); i++)
  {
    ppMainParam->szArrayStorage[i] = 0;
  }*/

  //�����ַ����洢����(ָ��)��
  file_operator_map_storage_file_to_heap(ppMainParam);

  //��ʼ�������ַ����洢�������Ϣ��¼����
  ppMainParam->psnStringNodes = NULL;

  //��������Ϣ�ļ�
  //ppMainParam->pfLinkInfoFile = fopen(FILE_LOCATION_LINK_INFO, "r+");

  //��������Ϣ�ļ�����������Ϣ
  file_operator_load_link_list_from_file(ppMainParam);

  /*20161004
  //��ʼ���ڴ�ģ������
  for (i = 0; i < _countof(ppMainParam->arychSim); i++)
  {
    ppMainParam->arychSim[i] = 0;
  }*/

  //��ʼ���ڴ�ģ�����飨ָ�룩
  ppMainParam->pchSim = (char *) 
    malloc(sizeof(char) * ppMainParam->nStorageFileCharSize);
  //==������

  for (i = 0; i < ppMainParam->nStorageFileCharSize; i++)
  {
    ppMainParam->pchSim[i] = 0;
  }

  //��ʼ��ѧ��Ĭ����Ϣ�ṹ�塣
  student_info_processor_initialize_default(&ppMainParam->StudentDefault);

  //��ѧ����Ϣģ��ṹ��ˢ����Ĭ��
  student_info_processor_refresh_template_to_default(
    &ppMainParam->StudentTemplate, &ppMainParam->StudentDefault);

  //��ѧ����Ϣ����ṹ��ˢ����Ĭ��
  student_info_processor_refresh_template_to_default(
    &ppMainParam->StudentDecode, &ppMainParam->StudentDefault);

  //��ʼ��ѧ����Ϣ�����buffer
  strcpy_s(ppMainParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppMainParam->szStudentStructEncodeDecodeBuffer), "");

  //��ʼ��ϵͳ���������⡣
  strcpy_s(ppMainParam->szSystemTitle, _countof(ppMainParam->szSystemTitle),
    INTERFACE_INFO_TITLE);

  //��ʼ��ϵͳ����:������ɫ��
  //sprintf_s(szTmp, _countof(szTmp), "%d", INTERFACE_INFO_BACKGROUND_COLOR);

  strcpy_s(ppMainParam->szSystemColor, _countof(ppMainParam->szSystemColor),
    INTERFACE_INFO_BACKGROUND_COLOR);

  //��ʼ��ϵͳ����:���ڿڴ�С��
  ppMainParam->rcWindowSize.nX0 = INTERFACE_SIZE_WINDOW_X0;
  ppMainParam->rcWindowSize.nY0 = INTERFACE_SIZE_WINDOW_Y0;
  ppMainParam->rcWindowSize.nX1 = INTERFACE_SIZE_WINDOW_X1;
  ppMainParam->rcWindowSize.nY1 = INTERFACE_SIZE_WINDOW_Y1;
  
  //��ʼ��ϵͳ��������ӭ��Ϣ��
  strcpy_s(ppMainParam->szSystemWelcomeInfo, 
    _countof(ppMainParam->szSystemWelcomeInfo), INTERFACE_INFO_WELCOME_INFO);

  //��ʼ���û�ָ�������
  for (i = 0; i < _countof(ppMainParam->szCmdBuffer); i++)
  {
    ppMainParam->szCmdBuffer[i] = 0;
  }
  
  //��ʼ��ģ��windowsָ�������������
  ppMainParam->nArgc = 0;
  for(i = 0; i < MAX_OPTION_NUM; i++)
  {
    strcpy_s(ppMainParam->szArgv[i], _countof(ppMainParam->szArgv[i]), "");
  }

  //��ʼ���û����ֽ�ָ�
  ppMainParam->chUserCmd = '\0';

  //��ʼ������������ݻ��塣
  strcpy_s(ppMainParam->piInfoBuffer.szToBePrinted, 
    _countof(ppMainParam->piInfoBuffer.szToBePrinted), "");
  ppMainParam->piInfoBuffer.nColor = FONT_DEFAULT;
  
  //��ʼ���ַ�����Ƶ��ͳ������
  for (i = 0; i < _countof(ppMainParam->nCharArray); i++)
  {
    ppMainParam->nCharArray[i] = 0;
  }

  return 0;
}

