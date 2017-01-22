////此文件是文件操作相关函数

#include "stdafx.h"
#include "file_operator.h"

static int file_operator_load_string_node_chain(Param *ppParam, 
                                                 StringNode *psnTemplate);

//返回文件的大小（字节数）。
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

//向文件里写入新的内容块
//==错误检查
int file_operator_write_new_content_block_in_storage()
{
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");
  char szContentBlock[STORAGE_FILE_CONTENT_BLOCK_SIZE] = {0};
  int i = 0;

  //初始化内容块
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

//文件到内存建立映射
int file_operator_map_storage_file_to_heap(Param *ppParam)
{
  int i = 0;
  charnumber_t cntFileSizeByte = 0;
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  //计算文件大小
  cntFileSizeByte = file_operator_get_storage_file_size_byte();
    
  ppParam->pchArrayStorage = (char *) malloc(sizeof(char) * cntFileSizeByte);
  //==错误判断


  fseek(pFile, 0, SEEK_SET);
  //文件内容读取
  fread(ppParam->pchArrayStorage, sizeof(char), cntFileSizeByte, pFile);

  fclose(pFile);

  return 0;
}


//内存到文件建立映射
int file_operator_map_heap_to_storage_file(Param *ppParam)
{
  int i = 0;
  charnumber_t cntFileSizeByte = 0;
  FILE *pFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  //计算文件大小
  cntFileSizeByte = file_operator_get_storage_file_size_byte();

  fseek(pFile, 0, SEEK_SET);
  
  //文件内容写入（覆盖原内容）
  fwrite(ppParam->pchArrayStorage, sizeof(char), cntFileSizeByte, pFile);

  fclose(pFile);

  return 0;
}


//从链表信息文件载入链表信息
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

//载入信息记录链表。成功返回0，失败返回DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC。
//和构建信息记录链表的唯一区别，就是加入新的node之后不会对linkinfo文件进行修改。
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

//向文件指定位置写入内容
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

//向链表信息文件写入（字符写入）
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

//删除一个节点在链表信息文件中的记录
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

  //先求出要删除哪一行（nLineNumber）
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

  //重新打开链表信息文件
  //ppParam->pfLinkInfoFile = fopen(FILE_LOCATION_LINK_INFO, "r+");

  return 0;
}

int file_operator_add_extra_content_block(Param *ppParam)
{
  //添加新的一个文件块
  file_operator_write_new_content_block_in_storage();

  //更新文件大小
  ppParam->nStorageFileCharSize = file_operator_get_storage_file_size_byte();

  //释放旧指针
  free_mapping_heaps(ppParam);

  //重新申请新的文件映射heap
  file_operator_map_storage_file_to_heap(ppParam);

  //重新初始化内存模拟数组（指针）
  ppParam->pchSim = (char *) 
    malloc(sizeof(char) * ppParam->nStorageFileCharSize);
  //==错误检查

  return 0;
}