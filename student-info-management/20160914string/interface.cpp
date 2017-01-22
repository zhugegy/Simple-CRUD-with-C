//此文件是界面相关函数。

#include "stdafx.h"
#include "interface.h"

static int interface_initialize(Param *ppParam);
static int interface_set_title(Param *ppParam);
static int interface_set_window_size(Param *ppParam);
static int interface_set_window_background_color(Param *ppParam);
static int interface_print(Param *ppParam);
static int interface_get_user_cmd(Param *ppParam);
static int interface_appending_student_template_info(Param *ppParam);

//此函数供外部调用。
int call_interface(int nCmd, Param *ppParam)
{
  switch (nCmd)
  {
  case INTERFACE_CMD_INITIALIZE:
    interface_initialize(ppParam);
    break;
  case INTERFACE_CMD_PRINT:
    interface_print(ppParam);
    break;
  case INTERFACE_CMD_GET_USER_CMD:
    interface_get_user_cmd(ppParam);
    break;
  default:
    break;
  }

  return 0;
}

//call_interface过期不再使用的分支。
/*case INTERFACE_CMD_SET_TITLE:    //过期。
interface_set_title(pParam);
break;
case INTERFACE_CMD_SET_WINDOW_BACKGROUND_COLOR:    //过期。
interface_set_window_background_color(pParam);
break;
case INTERFACE_CMD_SET_WINDOW_SIZE:    //过期。
interface_set_window_size(pParam);
break;*/

//用于初始化用户界面。
static int interface_initialize(Param *ppParam)
{
  //PrintingInfo piInformation;    //用于设置欢迎信息

  interface_set_title(ppParam);
  interface_set_window_background_color(ppParam);
  interface_set_window_size(ppParam);

  //输出欢迎信息到piInfoBuffer
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
    _countof(ppParam->piInfoBuffer.szToBePrinted),
    ppParam->szSystemWelcomeInfo);
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;
  
  interface_print(ppParam);

  return 0;
}

//用于设置程序标题。
static int interface_set_title(Param *ppParam)
{
  char szBuffer[MAX_STRING_LENGTH] = {0};

  strcpy_s(szBuffer, _countof(szBuffer), "title ");
  strcat_s(szBuffer, _countof(szBuffer), ppParam->szSystemTitle);
  
  system(szBuffer);

  return 0;
}

//用于设置程序窗口大小。
static int interface_set_window_size(Param *ppParam)
{
  HWND hWindow = GetConsoleWindow();
  
  MoveWindow(hWindow, ppParam->rcWindowSize.nX0, ppParam->rcWindowSize.nY0, 
                      ppParam->rcWindowSize.nX1, ppParam->rcWindowSize.nY1,
                      TRUE);

  return 0;
}

//用于设置窗口背景颜色。
static int interface_set_window_background_color(Param *ppParam)
{
  char szBuffer[MAX_STRING_LENGTH] = {0};

  strcpy_s(szBuffer, _countof(szBuffer), "color ");
  strcat_s(szBuffer, _countof(szBuffer), ppParam->szSystemColor);
  
  system(szBuffer);
  
  return 0;
}

//用于打印信息。传入的参数类型：PrintingInfo *。
static int interface_print(Param *ppParam)
{
  HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
 
  //debug
  ppParam->piInfoBuffer.nColor = FONT_SYSTEM_OUTPUT;

  //设置字体颜色
  SetConsoleTextAttribute(hHandle, ppParam->piInfoBuffer.nColor);
  
  printf("%s", ppParam->piInfoBuffer.szToBePrinted);

  //还原字体颜色
  SetConsoleTextAttribute(hHandle, FONT_DEFAULT);

  //清空ppiInfo，以便下一次打印。
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
    _countof(ppParam->piInfoBuffer.szToBePrinted), "");

  //追加当前学生模板信息到szToBePrinted
  if (ppParam->nAppendingStudentTemplateControlFlag == 1)
  {
    interface_appending_student_template_info(ppParam);

    //debug
    ppParam->piInfoBuffer.nColor = FONT_STUDENT_TEMPLATE;

    //设置字体颜色
    SetConsoleTextAttribute(hHandle, ppParam->piInfoBuffer.nColor);

    printf("%s", ppParam->piInfoBuffer.szToBePrinted);

    //还原字体颜色
    SetConsoleTextAttribute(hHandle, FONT_DEFAULT);

    //清空ppiInfo，以便下一次打印。
    strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
      _countof(ppParam->piInfoBuffer.szToBePrinted), "");
  }
  else
  {
    ppParam->nAppendingStudentTemplateControlFlag = 1;
  }

  return 0;
}

//追加当前学生模板信息到szToBePrinted
static int interface_appending_student_template_info(Param *ppParam)
{
  char szAppendingInfo[MAX_INFO_STRING_LENGTH] = {0};
  char szTmp[MAX_STRING_LENGTH] = {0};

  //此处的维护需要工作量太多，可以考虑函数指针数组
  strcpy_s(szAppendingInfo, _countof(szAppendingInfo), 
    "\r\n当前学生信息模板（按前面的序号进行修改）：\r\n");

  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "【1】学号：");
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), 
    ppParam->StudentTemplate.szStudentCode);
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "\r\n");

  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "【2】姓名：");
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), 
    ppParam->StudentTemplate.szStudentName);
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "\r\n");

  sprintf_s(szTmp, _countof(szTmp), "%8d", 
    ppParam->StudentTemplate.nStudentBirthday);

  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "【3】出生日期：");
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), szTmp);
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "\r\n");

  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "【4】电话：");
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), 
    ppParam->StudentTemplate.szStudentTelphone);
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "\r\n");

  sprintf_s(szTmp, _countof(szTmp), "%2.2f", 
    ppParam->StudentTemplate.fStudentCGrade);

  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "【5】C语言成绩：");
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), szTmp);
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "\r\n");

  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "【6】额外信息：");
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), 
    ppParam->StudentTemplate.szStudentExtraInfo);
  strcat_s(szAppendingInfo, _countof(szAppendingInfo), "\r\n");

  //追加(后来修改成覆盖（从strcat到strcpy）了)
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
    _countof(ppParam->piInfoBuffer.szToBePrinted), szAppendingInfo);

  return 0;
}

//获取用户指令。传入的参数类型：PrimaryParam *。
static int interface_get_user_cmd(Param *ppParam)
{
  char szStrPrepToken[MAX_STR_PREP_TOKEN_LENGTH] = {0};

  //szStrPrepToken的最终格式就是形如“%9s”的字符串，用于下一步的scanf_s函数
  //==20161004好像这个函数不用每次都调用，这样降低效率
  build_str_prep_token(szStrPrepToken, _countof(szStrPrepToken), 
    MAX_CMD_LENGTH);

  scanf_s(szStrPrepToken, ppParam->szCmdBuffer,
    _countof(ppParam->szCmdBuffer));
  
  //fflush(stdin);  //此方法在VS2015中(可能在VS2013 2010 也是这样)，并不能清空stdin

  while (getchar() != '\n');  //better way to clean buffer! (https://www.youtube.com/watch?v=ThRCjUk4nto)

  return 0;
} 

