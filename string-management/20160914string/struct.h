#pragma once
//���ļ���¼�����еĽṹ�塣

typedef int charnumber_t;

//��������ṹ�塣
struct RectCoord
{
  int nX0;
  int nY0;
  int nX1;
  int nY1;
};

//��ӡ��Ϣ��
struct PrintingInfo
{
  char szToBePrinted[MAX_INFO_STRING_LENGTH];
  int nColor;
};

//�ַ�����Ϣ��������
struct StringNode
{
  int nSerial;
  int nArrayLocation;
  int nStringLength;
  time_t tCreationTime;

  struct StringNode *psnNext;
};

//main�������õ�������Ҫ������
//��������³�Ա��������������ʼ��������
struct Param
{
  //FILE *pfStorageFile;    //�洢�ļ�ָ��
  charnumber_t nStorageFileCharSize;    //�洢�ļ���С���ļ����ַ��ĸ�����
  //FILE *pfLinkInfoFile;    //������Ϣ�ļ�

  /*20161004
  char szArrayStorage[STRING_ARRAY_SPACE];    //�ַ����洢����*/
  char *pchArrayStorage;    //�ַ����洢����(ָ��)������ʼʱmalloc
  
  StringNode *psnStringNodes;    //�����ַ����洢�������Ϣ��¼����
  /*20161004
  char arychSim[nFileCharSize];    //һ��ģ�����飬������ʾ�ڴ�ռ�����*/
  char *pchSim;    //һ��ģ�����飨ָ�룩��������ʾ�ڴ�ռ�����,����ʼʱmalloc
	    
  char szSystemTitle[MAX_SYSTEM_PARAM_LENGTH];    //ϵͳ����������
  char szSystemColor[MAX_SYSTEM_PARAM_LENGTH];    //ϵͳ����:������ɫ
  RectCoord rcWindowSize;    //ϵͳ���������ڴ�С
  char szSystemWelcomeInfo[MAX_SYSTEM_PARAM_LENGTH];    //ϵͳ��������ӭ��Ϣ

  char szCmdBuffer[MAX_CMD_LENGTH];    //�û�ָ�����
  
  //ģ��windowsָ�ÿ���û��������Ҫ��ʼ��
  int nArgc;
  char szArgv[MAX_OPTION_NUM][MAX_CMD_LENGTH];   

  char chUserCmd;    //�û���һָ����ֽڶ�ָ�

  PrintingInfo piInfoBuffer;    //����������ݻ���
  int nCharArray[MAX_CHAR_NUM];    //ͳ���ַ�����Ƶ��

  int nControlFlag;    //�������flag

 
};

