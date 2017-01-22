// main.cpp : �������̨Ӧ�ó������ڵ㡣
//���ļ������̿�����غ�������Ȩ����interface,option_parser��

#include "stdafx.h"
#include "main.h"
#include "interface.h"
#include "cmd_parser.h"
#include "data_processor.h"
#include "file_operator.h"

static int initialize_parameter(Param *ppMainParam);
static int free_string_nodes(Param *ppParam);

int _tmain(int argc, _TCHAR* argv[])
{
  Param pMain;

  //1. ��ʼ��������
  initialize_parameter(&pMain);

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

  //��ʼ��ϵͳ���������⡣
  strcpy_s(ppMainParam->szSystemTitle, _countof(ppMainParam->szSystemTitle),
    INTERFACE_INFO_TITLE);

  //��ʼ��ϵͳ����:������ɫ��
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

  //��ʼ���������flag��
  ppMainParam->nControlFlag = 0;

  return 0;
}

