////���ļ����ļ�������غ���

#include "stdafx.h"
#include "file_operator.h"

static int file_operator_load_string_node_chain(Param *ppParam, 
                                                 StringNode *psnTemplate);

//�����ļ��Ĵ�С���ֽ�������
charnumber_t file_operator_get_storage_file_size_byte()
{
  charnumber_t cntFileSizeByte = 0;
  struct stat st;

  stat(FILE_LOCATION_STORAGE, &st);
 /* fseek(pFile, 0, SEEK_END);
  cntFileSizeByte = (charnumber_t) ftell(pFile);
  fseek(pFile, 0, SEEK_SET);*/

  cntFileSizeByte = st.st_size;

  return cntFileSizeByte;
}

//���ļ���д���µ����ݿ�
//==������
int file_operator_write_new_content_block_in_storage()
{
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");
  char szContentBlock[STORAGE_FILE_CONTENT_BLOCK_SIZE] = {0};
  int i = 0;

  //��ʼ�����ݿ�
  for (i = 0; i < _countof(szContentBlock); i++)
  {
    szContentBlock[i] = STORAGE_FILE_CONTENT_BLOCK_CHAR;
  }
  
  fseek(pFile, 0, SEEK_END);

  fwrite(szContentBlock, sizeof(char), _countof(szContentBlock), pFile);

  fflush(pFile);

  fclose(pFile);

  return 0;
}

//�ļ����ڴ潨��ӳ��
int file_operator_map_storage_file_to_heap(Param *ppParam)
{
  int i = 0;
  charnumber_t cntFileSizeByte = 0;
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  //�����ļ���С
  cntFileSizeByte = file_operator_get_storage_file_size_byte();
    
  ppParam->pchArrayStorage = (char *) malloc(sizeof(char) * cntFileSizeByte);
  //==�����ж�


  fseek(pFile, 0, SEEK_SET);
  //�ļ����ݶ�ȡ
  fread(ppParam->pchArrayStorage, sizeof(char), cntFileSizeByte, pFile);

  fclose(pFile);

  return 0;
}


//�ڴ浽�ļ�����ӳ��
int file_operator_map_heap_to_storage_file(Param *ppParam)
{
  int i = 0;
  charnumber_t cntFileSizeByte = 0;
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  //�����ļ���С
  cntFileSizeByte = file_operator_get_storage_file_size_byte();

  fseek(pFile, 0, SEEK_SET);
  
  //�ļ�����д�루����ԭ���ݣ�
  fwrite(ppParam->pchArrayStorage, sizeof(char), cntFileSizeByte, pFile);

  fclose(pFile);

  return 0;
}


//��������Ϣ�ļ�����������Ϣ
int file_operator_load_link_list_from_file(Param *ppParam)
{
  StringNode snTemplate;
  FILE *pFile = fopen(FILE_LOCATION_LINK_INFO, "r+");
  struct stat st;
  
  
  stat(FILE_LOCATION_LINK_INFO, &st);

  if (st.st_size == 0)
  {
    fclose(pFile);
    return 0;
  }

  snTemplate.psnNext = NULL;
  while (!feof(pFile))
  {
    fscanf(pFile, "%d %d %d %I64d\r\n", &snTemplate.nSerial, 
                                      &snTemplate.nArrayLocation, 
                                      &snTemplate.nStringLength, 
                                      &snTemplate.tCreationTime); 

    //snTemplate.tCreationTime = (time_t) snTemplate.tCreationTime;

    file_operator_load_string_node_chain(ppParam, &snTemplate);

  }

  fclose(pFile);

  return 0;
}

//������Ϣ��¼�����ɹ�����0��ʧ�ܷ���DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC��
//�͹�����Ϣ��¼�����Ψһ���𣬾��Ǽ����µ�node֮�󲻻��linkinfo�ļ������޸ġ�
static int file_operator_load_string_node_chain(Param *ppParam, 
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
  }

  return 0;
}

//���ļ�ָ��λ��д������
int file_operator_write_content_in_storage(char *szContent, 
                                           charnumber_t cntStartLocation)
{
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  fseek(pFile, cntStartLocation, SEEK_SET);

  fwrite(szContent, sizeof(char), strlen(szContent) + 1, pFile);

  fflush(pFile);

  fclose(pFile);

  return 0;
}

//��������Ϣ�ļ�д�루�ַ�д�룩
int file_operator_write_string_node_in_link_info(StringNode *psnTmp)
{
  FILE *pFile = fopen(FILE_LOCATION_LINK_INFO, "r+");

  fseek(pFile, 0, SEEK_END);

  fprintf(pFile, "%d %d %d %I64d\r\n", 
                  psnTmp->nSerial, 
                  psnTmp->nArrayLocation, 
                  psnTmp->nStringLength, 
                  psnTmp->tCreationTime);

  fflush(pFile);

  fclose(pFile);

  return 0;
}

//ɾ��һ���ڵ���������Ϣ�ļ��еļ�¼
int file_operator_delete_string_node_in_link_info(StringNode *psnTmp)
{
  FILE *pFile = fopen(FILE_LOCATION_LINK_INFO, "r+");
  FILE *pfReplicaTmp = fopen(FILE_LOCATION_LINK_INFO_REPLICA, "w");
  StringNode snTemplate;
  char szBuf[MAX_STRING_LENGTH] = {0};
  int nLineNumber = 1;
  int nSerialNumber = 0;
  int nTmp = 1;

  nSerialNumber = psnTmp->nSerial;

  snTemplate.psnNext = NULL;

  fseek(pFile, 0, SEEK_SET);

  //�����Ҫɾ����һ�У�nLineNumber��
  while (!feof(pFile))
  {
    fscanf(pFile, "%d %d %d %I64d\r\n", 
      &snTemplate.nSerial, 
      &snTemplate.nArrayLocation, 
      &snTemplate.nStringLength, 
      &snTemplate.tCreationTime);

    if (snTemplate.nSerial == nSerialNumber)
    {
      break;
    }

    nLineNumber++;
  }

  rewind(pFile);
  
  /*while (chTmp != EOF)
  {
    chTmp = getc(pFile);
    if (chTmp == '\n')
    {
      nTmp++;
    }
    if (nTmp != nLineNumber)
    {
      putc(chTmp, pfReplicaTmp);
    }
  }*/

  while (fgets(szBuf, _countof(szBuf), pFile))
  {
    if (nTmp != nLineNumber)
    {
      fputs(szBuf, pfReplicaTmp);
    }
    nTmp++;
  }

  fclose(pFile);

  fflush(pfReplicaTmp);
  fclose(pfReplicaTmp);
  
  remove(FILE_LOCATION_LINK_INFO);
  rename(FILE_LOCATION_LINK_INFO_REPLICA, FILE_LOCATION_LINK_INFO);

  //���´�������Ϣ�ļ�
  //ppParam->pfLinkInfoFile = fopen(FILE_LOCATION_LINK_INFO, "r+");

  return 0;
}

int file_operator_add_extra_content_block(Param *ppParam)
{
  //����µ�һ���ļ���
  file_operator_write_new_content_block_in_storage();

  //�����ļ���С
  ppParam->nStorageFileCharSize = file_operator_get_storage_file_size_byte();

  //�ͷž�ָ��
  free_mapping_heaps(ppParam);

  //���������µ��ļ�ӳ��heap
  file_operator_map_storage_file_to_heap(ppParam);

  //���³�ʼ���ڴ�ģ�����飨ָ�룩
  ppParam->pchSim = (char *) 
    malloc(sizeof(char) * ppParam->nStorageFileCharSize);
  //==������

  return 0;
}