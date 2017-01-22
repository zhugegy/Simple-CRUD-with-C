//此文件是命令解析相关函数。

#include "stdafx.h"
#include "cmd_parser.h"

static int cmd_parser_check_cmd_validity(char *szCmd);
static int cmd_parser_send_error_msg(int nErrorNum, Param *ppParam);
static int cmd_parser_pre_process_cmd(char *szCmd);
static int cmd_parser_initialize_sim_win(Param *ppParam);
static int cmd_parser_trim_cmd(Param *ppParam);
static int cmd_parser_parse_options(Param *ppParam);
static int cmd_parser_depre_process_cmd(Param *ppParam);

/*用于解析用户指令并修改对应结构体。成功时返回0，失败返回-1，失败原因会被发送到
ppParam->piInfoBuffer。*/
int call_cmd_parser(Param *ppParam)
{
  int nCheckValidityResult = 0;

  //用户指令检查
  nCheckValidityResult = cmd_parser_check_cmd_validity(ppParam->szCmdBuffer);
  if (nCheckValidityResult != 0)
  {
    cmd_parser_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //用户指令预处理(引号里面的空格变笑脸)
  cmd_parser_pre_process_cmd(ppParam->szCmdBuffer);

  //用户指令粉碎，模拟windows指令，便于下一步用getopt操作。
  //先初始化参数。
  cmd_parser_initialize_sim_win(ppParam);

  //初始化之后，粉碎用户指令。
  nCheckValidityResult = cmd_parser_trim_cmd(ppParam);
  if (nCheckValidityResult != 0)
  {
    cmd_parser_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //用户指令后续处理（因为指令粉碎工作已经结束，笑脸现在应该变回空格）。
  cmd_parser_depre_process_cmd(ppParam);

  //解析指令。
  nCheckValidityResult = cmd_parser_parse_options(ppParam);
  if (nCheckValidityResult != 0)
  {
    cmd_parser_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //解析指令完毕，所有内容已处理并发送至ppParam结构体。函数现在可以返回至main。

  return 0;
}

static int cmd_parser_parse_options(Param *ppParam)
{
  char *szTmp = NULL;

  //检查字节数（只支持单字节短指令，例如-a）。
  szTmp = ppParam->szArgv[0];
  if (strlen(szTmp) != 2)
  {
    return CMD_PARSER_ERROR_FIRST_OPTION_BYTE_NUM;
  }

  //更新用户第一指令（单字节短指令）
  ppParam->chUserCmd = *(szTmp + 1);

  return 0;
}

//出错时错误信息的传递,把错误信息发送给ppParam->piInfoBuffer。
static int cmd_parser_send_error_msg(int nErrorNum, Param *ppParam)
{
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  switch (nErrorNum)
  {
    case CMD_PARSER_ERROR_QUOTER_NUM:
      strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
        _countof(ppParam->piInfoBuffer.szToBePrinted), 
        CMD_PARSER_ERROR_MSG_QUOTER_NUM);
      
      break;
    case CMD_PARSER_ERROR_OPTION_NUM:
      strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
        _countof(ppParam->piInfoBuffer.szToBePrinted), 
        CMD_PARSER_ERROR_MSG_OPTION_NUM);

      break;
    case CMD_PARSER_ERROR_FIRST_OPTION_BYTE_NUM:
      strcpy_s(ppParam->piInfoBuffer.szToBePrinted,
        _countof(ppParam->piInfoBuffer.szToBePrinted), 
        CMD_PARSER_ERROR_MSG_FIRST_OPTION_BYTE_NUM);

      break;
    default:
      break;
  }

  return 0;
}

//用户指令合法性检查。
static int cmd_parser_check_cmd_validity(char *szCmd)
{
  int nQuoterCounter = 0;    //用于检查引号个数是否为偶数
  char *szTmp = szCmd;
  
  while (*szTmp != '\0')
  {
    //如果出现引号，且引号前面不是转义符
    if (*szTmp == '"' && *(szTmp - 1) != '\\' )
    {
      nQuoterCounter++;
    }
    szTmp++;
  }

  if (nQuoterCounter % 2 != 0)
  {
    return CMD_PARSER_ERROR_QUOTER_NUM;
  }

  return 0;
}

/*用于预处理用户指令:把双引号中间的空格暂时改成白人笑脸'\1'。这样做的目的是为了
下一步处理命令的方便。外部库函数会把空格当成分隔符，而字符串是可以包含空格的。*/
static int cmd_parser_pre_process_cmd(char *szCmd)
{
  int nChangeFlag = 0;    //判断此处是否进行修改的flag。
  char *szTmp = szCmd;

  while (*szTmp != '\0')
  {
    //如果出现引号，且引号前面不是转义符.
    if (*szTmp == '"' && *(szTmp - 1) != '\\' )
    {
      //改变flag状态。
      nChangeFlag = (nChangeFlag == 0)? 1:0;
    }

    if (nChangeFlag == 1 && *szTmp == ' ')
    {
      *szTmp = '\1';
    }

    szTmp++;
  }

  return 0;
}

//用户指令后续处理（因为指令粉碎工作已经结束，笑脸现在应该变回空格）。
static int cmd_parser_depre_process_cmd(Param *ppParam)
{
  char *szTmp = NULL;
  int i = 0;

  for (i = 0; i < ppParam->nArgc; i++)
  {
    szTmp = ppParam->szArgv[i];

    while (*szTmp != '\0')
    {
      if (*szTmp == '\1')
      {
        *szTmp = ' ';
      }
      szTmp++;
    }

  }
  return 0;
}

//初始化模拟windows指令的两个参数。
static int cmd_parser_initialize_sim_win(Param *ppParam)
{
  int i = 0;

  ppParam->nArgc = 0;
  for(i = 0; i < MAX_OPTION_NUM; i++)
  {
    strcpy_s(ppParam->szArgv[i], _countof(ppParam->szArgv[i]), "");
  }

  return 0;
}

//用户指令粉碎，模拟windows指令的储存方式，便于下一步操作。
static int cmd_parser_trim_cmd(Param *ppParam)
{
  char *szTmp = ppParam->szCmdBuffer;
  char *szTmpTail = NULL;
  int i = 0;
  int j = 0;

  //把字符指针运行到非空格处（防止用户输入指令的开头有空格）。
  while (*szTmp == ' ')
  {
    szTmp++;
  }

  //再把后面的空格清除。
  szTmpTail = szTmp;
  
  while (*szTmpTail != '\0')
  {
    szTmpTail++;
  }

  szTmpTail--;

  while (*szTmpTail == ' ')
  {
    *szTmpTail = '\0';
    szTmpTail--;
  }

  //开始粉碎。
  while (*szTmp != '\0')
  {
    if (*szTmp == ' ')
    {
      ppParam->szArgv[i][j] = '\0';
      i++;
      j = 0;

      //防止多个连续空格
      if (ppParam->szArgv[i - 1][0] == '\0')
      {
        i--;
      }

      if (i > MAX_OPTION_NUM)
      {
        return CMD_PARSER_ERROR_OPTION_NUM;
      }

      szTmp++;
      continue;
    }
    ppParam->szArgv[i][j] = *szTmp;
    szTmp++;
    j++;
  }

  ppParam->szArgv[i][j] = '\0';

  ppParam->nArgc = i + 1;

  return 0;
}