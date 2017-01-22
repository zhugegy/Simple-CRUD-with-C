// main.cpp : 定义控制台应用程序的入口点。
//此文件是流程控制相关函数，有权呼叫interface,option_parser。

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

  //1. 初始化参数。
  initialize_parameter(&pMain);

  //命令行模式跳转(指令模式现在仅用于快速添加学生信息，也就是-a "string")
  //因为每次都在界面里改写单项学生信息再添加，这种形式不适合批量添加测试
  //其他的功能暂时不添加
  if (argc != 1)
  {
    strcpy_s(szTmp, _countof(szTmp), argv[2]);
    swtich_to_cmd_mode(&pMain, szTmp);

    return 0;
  }

  //2. 初始化界面。
  call_interface(INTERFACE_CMD_INITIALIZE, &pMain);
  
  //3. 进入程序循环。
  while (pMain.nControlFlag == 0)
  {
    //3.1 获取用户指令。
    call_interface(INTERFACE_CMD_GET_USER_CMD, &pMain);

    //3.2 解析用户指令。
    /*如果解析失败，则发送错误信息给用户。具体的错误已经被cmd_parser写入pMain结
    构体的piInfoBuffer中。*/
    if (call_cmd_parser(&pMain) != 0)
    {
      call_interface(INTERFACE_CMD_PRINT, &pMain);
      continue;
    }

    //printf("用户指令2：%s\r\n", pMain.szCmdBuffer);

    //3.3 进行数据操作。
    /*如果数据操作失败，则发送错误信息给用户。具体的错误已经被data_processor写入
    pMain结构体的piInfoBuffer中。*/
    /*20161004由于加入了文件操作，3.3这一步有区别了（数组改成指针，相应改变即时
    写入文件）*/
    call_data_processor(&pMain);

    //3.4 显示操作结果。
	call_interface(INTERFACE_CMD_PRINT, &pMain);
  }


  //4. 清理占用的空间。
  free_string_nodes(&pMain);
  free_mapping_heaps(&pMain);
  
  system("pause");
  return 0;
}

//命令模式跳转
static int swtich_to_cmd_mode(Param *ppParam, char* szCmd)
{
  char szTmp[MAX_STRING_LENGTH] = {0};

  //手动覆写命令信息，改动命令数量
  ppParam->chUserCmd = 'a';

  ppParam->nArgc = 2;
  
  //发现系统会自动把我加的双引号省略掉，只好自己在这里再加一次
  //而且自己的命令行指令-a "string"中，string里不能包含空格了
  strcpy_s(szTmp, _countof(szTmp), "\"");
  strcat_s(szTmp, _countof(szTmp), szCmd);
  strcat_s(szTmp, _countof(szTmp), "\"");

  strcpy_s(ppParam->szArgv[1], _countof(ppParam->szArgv[1]), szTmp);

  //命令行的话，就不需要输出学生模板信息了。
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

  //初始化程序控制flag。
  ppMainParam->nControlFlag = 0;

  //是否在输出追加学生信息flag，默认为1
  ppMainParam->nAppendingStudentTemplateControlFlag = 1;

  //如果存储文件不存在（第一次运行时），建立文件。
  file_operator_create_files();

  //打开存储文件
  //ppMainParam->pfStorageFile = fopen(FILE_LOCATION_STORAGE, "rb+");

  //读取文件大小
  ppMainParam->nStorageFileCharSize = 
    file_operator_get_storage_file_size_byte();

  //如果是新文件（0字节），那么向里写入一个块的内容
  if (ppMainParam->nStorageFileCharSize == 0)
  {
    file_operator_write_new_content_block_in_storage();
    ppMainParam->nStorageFileCharSize = 
      file_operator_get_storage_file_size_byte();
  }
  /*20161004
  //初始化字符串存储数组。
  for (i = 0; i < _countof(ppMainParam->szArrayStorage); i++)
  {
    ppMainParam->szArrayStorage[i] = 0;
  }*/

  //载入字符串存储数组(指针)。
  file_operator_map_storage_file_to_heap(ppMainParam);

  //初始化辅助字符串存储数组的信息记录链表。
  ppMainParam->psnStringNodes = NULL;

  //打开链表信息文件
  //ppMainParam->pfLinkInfoFile = fopen(FILE_LOCATION_LINK_INFO, "r+");

  //从链表信息文件载入链表信息
  file_operator_load_link_list_from_file(ppMainParam);

  /*20161004
  //初始化内存模拟数组
  for (i = 0; i < _countof(ppMainParam->arychSim); i++)
  {
    ppMainParam->arychSim[i] = 0;
  }*/

  //初始化内存模拟数组（指针）
  ppMainParam->pchSim = (char *) 
    malloc(sizeof(char) * ppMainParam->nStorageFileCharSize);
  //==错误检查

  for (i = 0; i < ppMainParam->nStorageFileCharSize; i++)
  {
    ppMainParam->pchSim[i] = 0;
  }

  //初始化学生默认信息结构体。
  student_info_processor_initialize_default(&ppMainParam->StudentDefault);

  //将学生信息模板结构体刷新至默认
  student_info_processor_refresh_template_to_default(
    &ppMainParam->StudentTemplate, &ppMainParam->StudentDefault);

  //将学生信息解码结构体刷新至默认
  student_info_processor_refresh_template_to_default(
    &ppMainParam->StudentDecode, &ppMainParam->StudentDefault);

  //初始化学生信息编解码buffer
  strcpy_s(ppMainParam->szStudentStructEncodeDecodeBuffer, 
    _countof(ppMainParam->szStudentStructEncodeDecodeBuffer), "");

  //初始化系统参数：标题。
  strcpy_s(ppMainParam->szSystemTitle, _countof(ppMainParam->szSystemTitle),
    INTERFACE_INFO_TITLE);

  //初始化系统参数:背景颜色。
  //sprintf_s(szTmp, _countof(szTmp), "%d", INTERFACE_INFO_BACKGROUND_COLOR);

  strcpy_s(ppMainParam->szSystemColor, _countof(ppMainParam->szSystemColor),
    INTERFACE_INFO_BACKGROUND_COLOR);

  //初始化系统参数:窗口口大小。
  ppMainParam->rcWindowSize.nX0 = INTERFACE_SIZE_WINDOW_X0;
  ppMainParam->rcWindowSize.nY0 = INTERFACE_SIZE_WINDOW_Y0;
  ppMainParam->rcWindowSize.nX1 = INTERFACE_SIZE_WINDOW_X1;
  ppMainParam->rcWindowSize.nY1 = INTERFACE_SIZE_WINDOW_Y1;
  
  //初始化系统参数：欢迎信息。
  strcpy_s(ppMainParam->szSystemWelcomeInfo, 
    _countof(ppMainParam->szSystemWelcomeInfo), INTERFACE_INFO_WELCOME_INFO);

  //初始化用户指令缓冲区。
  for (i = 0; i < _countof(ppMainParam->szCmdBuffer); i++)
  {
    ppMainParam->szCmdBuffer[i] = 0;
  }
  
  //初始化模拟windows指令的两个参数。
  ppMainParam->nArgc = 0;
  for(i = 0; i < MAX_OPTION_NUM; i++)
  {
    strcpy_s(ppMainParam->szArgv[i], _countof(ppMainParam->szArgv[i]), "");
  }

  //初始化用户单字节指令。
  ppMainParam->chUserCmd = '\0';

  //初始化界面输出内容缓冲。
  strcpy_s(ppMainParam->piInfoBuffer.szToBePrinted, 
    _countof(ppMainParam->piInfoBuffer.szToBePrinted), "");
  ppMainParam->piInfoBuffer.nColor = FONT_DEFAULT;
  
  //初始化字符出现频率统计数组
  for (i = 0; i < _countof(ppMainParam->nCharArray); i++)
  {
    ppMainParam->nCharArray[i] = 0;
  }

  return 0;
}

