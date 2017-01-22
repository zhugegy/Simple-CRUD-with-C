#pragma once
//此文件记录了所有的结构体。

typedef int charnumber_t;

//矩形坐标结构体。
struct RectCoord
{
  int nX0;
  int nY0;
  int nX1;
  int nY1;
};

//打印信息。
typedef struct PrintingInfo
{
  char szToBePrinted[MAX_INFO_STRING_LENGTH];
  int nColor;
}PrintingInfo;

//字符串信息储存链表。
typedef struct StringNode
{
  int nSerial;
  int nArrayLocation;
  int nStringLength;
  time_t tCreationTime;

  struct StringNode *psnNext;
}StringNode;

typedef struct Student
{
  char szStudentCode[MAX_STUDENT_CODE_LENGTH];
  char szStudentName[MAX_STUDENT_NAME_LENGTH];
  int nStudentBirthday;
  char szStudentTelphone[MAX_STUDENT_TEL_LENGTH];
  float fStudentCGrade;
  char szStudentExtraInfo[MAX_STUDENT_EXTRA_INFO_LENGTH];

  StringNode *psnMapping;
}Student;

//main函数所用的所有主要参数。
//在这里加新成员，别忘了立即初始化操作。
struct Param
{
  int nControlFlag;    //程序控制flag  

  //是否在输出追加学生信息flag，默认为1
  int nAppendingStudentTemplateControlFlag;  

  //FILE *pfStorageFile;    //存储文件指针
  charnumber_t nStorageFileCharSize;    //存储文件大小（文件中字符的个数）
  //FILE *pfLinkInfoFile;    //链表信息文件

  /*20161004
  char szArrayStorage[STRING_ARRAY_SPACE];    //字符串存储数组*/
  char *pchArrayStorage;    //字符串存储数组(指针)，程序开始时malloc
  
  StringNode *psnStringNodes;    //辅助字符串存储数组的信息记录链表
  /*20161004
  char arychSim[nFileCharSize];    //一个模拟数组，用来显示内存占用情况*/
  char *pchSim;    //一个模拟数组（指针），用来显示内存占用情况,程序开始时malloc
	    
  Student StudentDefault;   //默认学生信息（其实可以不用，但是还是用吧）
  Student StudentTemplate;    //学生信息模板，给用户修改用的
  Student StudentDecode;    //用于从字符串解码学生信息

  //学生信息编解码buffer, 它同时也用于解码时的信息临时存放
  char szStudentStructEncodeDecodeBuffer[MAX_STRING_LENGTH];    

  char szSystemTitle[MAX_SYSTEM_PARAM_LENGTH];    //系统参数：标题
  char szSystemColor[MAX_SYSTEM_PARAM_LENGTH];    //系统参数:背景颜色
  RectCoord rcWindowSize;    //系统参数：窗口大小
  char szSystemWelcomeInfo[MAX_SYSTEM_PARAM_LENGTH];    //系统参数：欢迎信息

  char szCmdBuffer[MAX_CMD_LENGTH];    //用户指令缓冲区
  
  //模拟windows指令，每次用户输入后需要初始化
  int nArgc;
  char szArgv[MAX_OPTION_NUM][MAX_CMD_LENGTH];   

  char chUserCmd;    //用户第一指令（单字节短指令）

  PrintingInfo piInfoBuffer;    //界面输出内容缓冲
  int nCharArray[MAX_CHAR_NUM];    //统计字符出现频率

};


