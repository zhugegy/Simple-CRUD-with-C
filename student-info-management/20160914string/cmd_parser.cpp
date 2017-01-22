//���ļ������������غ�����

#include "stdafx.h"
#include "cmd_parser.h"

static int cmd_parser_check_cmd_validity(char *szCmd);
static int cmd_parser_send_error_msg(int nErrorNum, Param *ppParam);
static int cmd_parser_pre_process_cmd(char *szCmd);
static int cmd_parser_initialize_sim_win(Param *ppParam);
static int cmd_parser_trim_cmd(Param *ppParam);
static int cmd_parser_parse_options(Param *ppParam);
static int cmd_parser_depre_process_cmd(Param *ppParam);

/*���ڽ����û�ָ��޸Ķ�Ӧ�ṹ�塣�ɹ�ʱ����0��ʧ�ܷ���-1��ʧ��ԭ��ᱻ���͵�
ppParam->piInfoBuffer��*/
int call_cmd_parser(Param *ppParam)
{
  int nCheckValidityResult = 0;

  //�û�ָ����
  nCheckValidityResult = cmd_parser_check_cmd_validity(ppParam->szCmdBuffer);
  if (nCheckValidityResult != 0)
  {
    cmd_parser_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�û�ָ��Ԥ����(��������Ŀո��Ц��)
  cmd_parser_pre_process_cmd(ppParam->szCmdBuffer);

  //�û�ָ����飬ģ��windowsָ�������һ����getopt������
  //�ȳ�ʼ��������
  cmd_parser_initialize_sim_win(ppParam);

  //��ʼ��֮�󣬷����û�ָ�
  nCheckValidityResult = cmd_parser_trim_cmd(ppParam);
  if (nCheckValidityResult != 0)
  {
    cmd_parser_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //�û�ָ�����������Ϊָ����鹤���Ѿ�������Ц������Ӧ�ñ�ؿո񣩡�
  cmd_parser_depre_process_cmd(ppParam);

  //����ָ�
  nCheckValidityResult = cmd_parser_parse_options(ppParam);
  if (nCheckValidityResult != 0)
  {
    cmd_parser_send_error_msg(nCheckValidityResult, ppParam);
    return -1;
  }

  //����ָ����ϣ����������Ѵ���������ppParam�ṹ�塣�������ڿ��Է�����main��

  return 0;
}

static int cmd_parser_parse_options(Param *ppParam)
{
  char *szTmp = NULL;

  //����ֽ�����ֻ֧�ֵ��ֽڶ�ָ�����-a����
  szTmp = ppParam->szArgv[0];
  if (strlen(szTmp) != 2)
  {
    return CMD_PARSER_ERROR_FIRST_OPTION_BYTE_NUM;
  }

  //�����û���һָ����ֽڶ�ָ�
  ppParam->chUserCmd = *(szTmp + 1);

  return 0;
}

//����ʱ������Ϣ�Ĵ���,�Ѵ�����Ϣ���͸�ppParam->piInfoBuffer��
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

//�û�ָ��Ϸ��Լ�顣
static int cmd_parser_check_cmd_validity(char *szCmd)
{
  int nQuoterCounter = 0;    //���ڼ�����Ÿ����Ƿ�Ϊż��
  char *szTmp = szCmd;
  
  while (*szTmp != '\0')
  {
    //����������ţ�������ǰ�治��ת���
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

/*����Ԥ�����û�ָ��:��˫�����м�Ŀո���ʱ�ĳɰ���Ц��'\1'����������Ŀ����Ϊ��
��һ����������ķ��㡣�ⲿ�⺯����ѿո񵱳ɷָ��������ַ����ǿ��԰����ո�ġ�*/
static int cmd_parser_pre_process_cmd(char *szCmd)
{
  int nChangeFlag = 0;    //�жϴ˴��Ƿ�����޸ĵ�flag��
  char *szTmp = szCmd;

  while (*szTmp != '\0')
  {
    //����������ţ�������ǰ�治��ת���.
    if (*szTmp == '"' && *(szTmp - 1) != '\\' )
    {
      //�ı�flag״̬��
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

//�û�ָ�����������Ϊָ����鹤���Ѿ�������Ц������Ӧ�ñ�ؿո񣩡�
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

//��ʼ��ģ��windowsָ�������������
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

//�û�ָ����飬ģ��windowsָ��Ĵ��淽ʽ��������һ��������
static int cmd_parser_trim_cmd(Param *ppParam)
{
  char *szTmp = ppParam->szCmdBuffer;
  char *szTmpTail = NULL;
  int i = 0;
  int j = 0;

  //���ַ�ָ�����е��ǿո񴦣���ֹ�û�����ָ��Ŀ�ͷ�пո񣩡�
  while (*szTmp == ' ')
  {
    szTmp++;
  }

  //�ٰѺ���Ŀո������
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

  //��ʼ���顣
  while (*szTmp != '\0')
  {
    if (*szTmp == ' ')
    {
      ppParam->szArgv[i][j] = '\0';
      i++;
      j = 0;

      //��ֹ��������ո�
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