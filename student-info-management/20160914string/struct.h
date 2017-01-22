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
typedef struct PrintingInfo
{
  char szToBePrinted[MAX_INFO_STRING_LENGTH];
  int nColor;
}PrintingInfo;

//�ַ�����Ϣ��������
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

//main�������õ�������Ҫ������
//��������³�Ա��������������ʼ��������
struct Param
{
  int nControlFlag;    //�������flag  

  //�Ƿ������׷��ѧ����Ϣflag��Ĭ��Ϊ1
  int nAppendingStudentTemplateControlFlag;  

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
	    
  Student StudentDefault;   //Ĭ��ѧ����Ϣ����ʵ���Բ��ã����ǻ����ðɣ�
  Student StudentTemplate;    //ѧ����Ϣģ�壬���û��޸��õ�
  Student StudentDecode;    //���ڴ��ַ�������ѧ����Ϣ

  //ѧ����Ϣ�����buffer, ��ͬʱҲ���ڽ���ʱ����Ϣ��ʱ���
  char szStudentStructEncodeDecodeBuffer[MAX_STRING_LENGTH];    

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

};


