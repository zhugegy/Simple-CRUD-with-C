//���ļ��ǽ�����غ�����

#include "stdafx.h"
#include "interface.h"

static int interface_initialize(Param *ppParam);
static int interface_set_title(Param *ppParam);
static int interface_set_window_size(Param *ppParam);
static int interface_set_window_background_color(Param *ppParam);
static int interface_print(PrintingInfo *ppiInfo);
static int interface_get_user_cmd(Param *ppParam);

//�˺������ⲿ���á�
int call_interface(int nCmd, Param *ppParam)
{
  switch (nCmd)
  {
  case INTERFACE_CMD_INITIALIZE:
    interface_initialize(ppParam);
    break;
  case INTERFACE_CMD_PRINT:
    interface_print(&(ppParam->piInfoBuffer));
    break;
  case INTERFACE_CMD_GET_USER_CMD:
    interface_get_user_cmd(ppParam);
    break;
  default:
    break;
  }

  return 0;
}

//call_interface���ڲ���ʹ�õķ�֧��
/*case INTERFACE_CMD_SET_TITLE:    //���ڡ�
interface_set_title(pParam);
break;
case INTERFACE_CMD_SET_WINDOW_BACKGROUND_COLOR:    //���ڡ�
interface_set_window_background_color(pParam);
break;
case INTERFACE_CMD_SET_WINDOW_SIZE:    //���ڡ�
interface_set_window_size(pParam);
break;*/

//���ڳ�ʼ���û����档
static int interface_initialize(Param *ppParam)
{
  PrintingInfo piInformation;    //�������û�ӭ��Ϣ

  interface_set_title(ppParam);
  interface_set_window_background_color(ppParam);
  interface_set_window_size(ppParam);

  //��ӡ��ӭ��Ϣ
  strcpy_s(piInformation.szToBePrinted, _countof(piInformation.szToBePrinted),
    ppParam->szSystemWelcomeInfo);
  piInformation.nColor = FONT_SYSTEM_OUTPUT;
  interface_print(&piInformation);

  return 0;
}

//�������ó�����⡣
static int interface_set_title(Param *ppParam)
{
  char szBuffer[MAX_STRING_LENGTH] = {0};

  strcpy_s(szBuffer, _countof(szBuffer), "title ");
  strcat_s(szBuffer, _countof(szBuffer), ppParam->szSystemTitle);
  
  system(szBuffer);

  return 0;
}

//�������ó��򴰿ڴ�С��
static int interface_set_window_size(Param *ppParam)
{
  HWND hWindow = GetConsoleWindow();
  
  MoveWindow(hWindow, ppParam->rcWindowSize.nX0, ppParam->rcWindowSize.nY0, 
                      ppParam->rcWindowSize.nX1, ppParam->rcWindowSize.nY1,
                      TRUE);

  return 0;
}

//�������ô��ڱ�����ɫ��
static int interface_set_window_background_color(Param *ppParam)
{
  char szBuffer[MAX_STRING_LENGTH] = {0};

  strcpy_s(szBuffer, _countof(szBuffer), "color ");
  strcat_s(szBuffer, _countof(szBuffer), ppParam->szSystemColor);
  
  system(szBuffer);
  
  return 0;
}

//���ڴ�ӡ��Ϣ������Ĳ������ͣ�PrintingInfo *��
static int interface_print(PrintingInfo *ppiInfo)
{
  HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
 
  //����������ɫ
  SetConsoleTextAttribute(hHandle, ppiInfo->nColor);
  
  printf("%s", ppiInfo->szToBePrinted);

  //��ԭ������ɫ
  SetConsoleTextAttribute(hHandle, FONT_DEFAULT);

  return 0;
}

//��ȡ�û�ָ�����Ĳ������ͣ�PrimaryParam *��
static int interface_get_user_cmd(Param *ppParam)
{
  char szStrPrepToken[MAX_STR_PREP_TOKEN_LENGTH] = {0};

  //szStrPrepToken�����ո�ʽ�������硰%9s�����ַ�����������һ����scanf_s����
  //==20161004���������������ÿ�ζ����ã���������Ч��
  build_str_prep_token(szStrPrepToken, _countof(szStrPrepToken), 
    MAX_CMD_LENGTH);

  scanf_s(szStrPrepToken, ppParam->szCmdBuffer,
    _countof(ppParam->szCmdBuffer));

  //fflush(stdin);  //�˷�����VS2015��(������VS2013 2010 Ҳ������)�����������stdin

  while (getchar() != '\n');  //better way to clean buffer! (https://www.youtube.com/watch?v=ThRCjUk4nto)

  return 0;
} 