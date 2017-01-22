#pragma once
//���ļ���¼�����еĺꡣ

/* ######################################## */
/* ######### �û������Զ������ֵ ######### */
/* ######################################## */

/*20161004
#define STRING_ARRAY_SPACE 2000    //�洢����С����λ���ֽڣ���*/
#define STORAGE_FILE_CONTENT_BLOCK_SIZE 2000    //�洢�ļ�ÿһ��Ĵ�С���ֽ�����


/* ######################################## */
/* ############### ������� ############### */
/* ######################################## */

#define INTERFACE_INFO_TITLE "ѧ������ϵͳ"
#define INTERFACE_INFO_VERSION "Version 0.01"

//30�������׺��֡��޸������ʮ���������ݣ�ҲҪ�޸�������ַ����ꡣ����Ҫһ����
#define FONT_DEFAULT 0x30
#define INTERFACE_INFO_BACKGROUND_COLOR "30"

#define FILE_LOCATION_STORAGE "data_storage\\storage.dat"
#define FILE_LOCATION_LINK_INFO "data_storage\\linkinfo.txt"
//linkinforeplica.txt��������ɾ������ʱ�ļ��ļ�ʱͬ����ɾ��ԭ�����¼�ļ���һ�У�
#define FILE_LOCATION_LINK_INFO_REPLICA "data_storage\\linkinforeplica.txt"
#define HELP_INFO \
"������֧��ָ���˵����                                                       \r\n\
                                                                               \r\n\
�޸�ѧ�ţ�-1 string [string...]                                                \r\n\
�޸�ѧ����Ϣģ���ѧ�š�ѧ�ſ��԰����ո�                                     \r\n\
                                                                               \r\n\
�޸�������-2 string [string...]                                                \r\n\
�޸�ѧ����Ϣģ����������������԰����ո�                                     \r\n\
                                                                               \r\n\
-3 -4 -5 -6 ͬ�����÷����޸�ѧ����Ϣģ��Ķ�Ӧ��Ŀ��                           \r\n\
                                                                               \r\n\
���ѧ����Ϣ�����ݿ⣺-w [num]                                                 \r\n\
����ѡ��ڶ��������ֶ�Ϊѧ����Ϣָ����š�����ڶ������Ļ���ϵͳ���Զ�����һ�� \
��š�                                                                         \r\n\
                                                                               \r\n\
�����ݿ�ɾ��ѧ����Ϣ��-r num                                                   \r\n\
ɾ��ָ����ŵ�ѧ����Ϣ��                                                       \r\n\
                                                                               \r\n\
�޸����ݿ��ڵ�ѧ����Ϣ: -c num                                                 \r\n\
��ָ����ŵ�ѧ����Ϣ�������޸�Ϊ��ǰģ������ݡ�                               \r\n\
                                                                               \r\n\
��ѯѧ����Ϣ��-l [num | \"string\"]                                              \r\n\
�г�ָ����Ż���ƥ��������ʽ��ѧ����Ϣ������ѡ��ڶ����������������г��� \
���ַ�����                                                                     \r\n\
                                                                               \r\n\
��ѯ�ڴ��ַ��-j num                                                           \r\n\
��ѯָ����ַ���Ƿ���ѧ����Ϣ�������ַ�������ʾ��ѧ����Ϣ��                     \r\n\
                                                                               \r\n\
ͳ��ѧ���ɼ���-g                                                               \r\n\
ͳ������ѧ����C���Գɼ������������                                            \r\n\
                                                                               \r\n\
ͳ���ַ���-s                                                                   \r\n\
                                                                               \r\n\
��ʾ�ڴ���Ϣ��-i                                                               \r\n\
                                                                               \r\n\
�ڴ���Ƭ����: -o                                                               \r\n\
                                                                               \r\n\
�˳���-q                                                                       \r\n\
                                                                               \r\n\
��ʾ������: -h                                                                 \r\n\
                                                                               \r\n\
"
#define GOODBYE_INFO "�ټ�!\r\n"
#define RAM_INFO_FULL_SYMPOL "��"
#define RAM_INFO_EMPTY_SYMPOL "��"
/* 800x600�����£�ÿ������ܴ�ӡ���ַ������ȣ�
hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello
*/
#define INTERFACE_INFO_WELCOME_INFO \
"\
��ӭʹ��ѧ������ϵͳ���鿴������ʹ������-h��\r\n\
"
/*
#define INTERFACE_INFO_HELP_INFO \
"\
������ϢԤ����\
"
*/
#define CMD_PARSER_ERROR_MSG_QUOTER_NUM \
"\
�����������ԣ������û�ָ�������������Ϊ�������룬��Ҫ��ת�����\r\n\
"
#define CMD_PARSER_ERROR_MSG_OPTION_NUM \
"\
ָ���������ԣ������û�ָ��ǲ��������˹����ָ�ÿ��ֻ֧��һ��ָ�\r\n\
"
#define CMD_PARSER_ERROR_MSG_FIRST_OPTION_BYTE_NUM \
"\
ָ���ֽڲ��ԣ������û�ָ�ֻ֧�ֵ��ֽ�ָ�����-a��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_STRING_NODE_MALLOC \
"\
�ַ�����Ϣ�洢����MALLOC����ʧ�ܡ�\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_NUM \
"\
ָ������������ԡ������ַ���ֻ����1����2����������ȷ��ʽ��-a \"string\" [num]��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_1_LACK_OF_QUOTER \
"\
ָ���ʽ���ԡ������ַ�����Ҫ���ַ�����������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_2_NOT_NUM \
"\
ָ���ʽ���ԡ���2������ѡ���ʹ�õ�2������������������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_2_NOT_AVAILABLE \
"\
����������ָ������ѱ�ռ�ã������¸�һ��δ��ռ�õ���š�����-lָ��鿴����ѧ����\
Ϣ�����ǵ���š�\r\n\
"
/*�������ѧ����Ϣ����ϵͳ��û���ˣ�û�ռ��˻���ļ��Զ�����*/
#define DATA_PROCESSOR_ERROR_MSG_ADD_NO_AVAILABLE_SPACE \
"\
������û�п��ÿռ䡣�볢��������Ƭ��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_NUM \
"\
ָ������������ԡ����ѧ����Ϣֻ����1����������ȷ��ʽ��-l [num | \"reg\"]��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_1_NEGATIVE_NUM \
"\
ָ���ʽ���ԡ����ѧ����Ϣֻ����1���������ڶ�������ѡ���ʹ���������ڶ�������\
�����������Ǹ�������ȷ��ʽ��-l [num | \"reg\"]��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_1_LACK_OF_QUOTER \
"\
ָ���ʽ���ԡ����ѧ����Ϣֻ����1��������������ѡ���ʹ��������ʽ����������\
�����뱻˫���Ű���������ȷ��ʽ��-l [num | \"reg\"]��\r\n\
"
#define DATA_PROCESSOR_INFO_NO_RESULT_REG \
"\
δ���ҵ���������������ʽƥ���ѧ����Ϣ��\r\n\
"
#define DATA_PROCESSOR_INFO_NO_RESULT_NUM \
"\
δ���ҵ���������ŵ�ѧ����Ϣ���ǲ��������˴������ţ�\r\n\
"
#define DATA_PROCESSOR_INFO_NO_RESULT_ALL \
"\
δ���ҵ�ѧ����Ϣ��Ŀǰ��û��ѧ����Ϣ��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_NUM \
"\
ָ������������ԡ�ɾ��ѧ����Ϣֻ����1����������ȷ��ʽ��-d num��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_1_NOT_NUM \
"\
ָ��������ԡ�������������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_1_NUM_NOT_EXIST \
"\
ָ��������ԡ���ָ������Ų����ڡ�\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_NUM \
"\
ָ������������ԡ��޸��ַ���ֻ����2����������ȷ��ʽ��-m num \"string\"��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_2_LACK_OF_QUOTER \
"\
ָ���ʽ���ԡ��޸��ַ�����Ҫ���µ��ַ�����������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_1_NOT_NUM \
"\
ָ��������ԡ���1������������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_1_NUM_NOT_EXIST \
"\
ָ��������ԡ���ָ������Ų����ڡ�\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_STAT_PARAMETER_NUM \
"\
ָ��������ԡ�-sָ���Ҫ������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_RAMINFO_PARAMETER_NUM \
"\
ָ��������ԡ�-iָ���Ҫ������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_NUM \
  "\
ָ��������ԡ�-jָ����Ҫ1����������ȷ��ʽ: -j num��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_1_NOT_NUM \
"\
ָ��������ԡ�������������������0��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_1_RAM_NO_CONTENT \
"\
�������ĵ�ַ��û�д洢ѧ����Ϣ������ʹ��-iָ��鿴�ڴ�ʹ�������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_OPTIMIZE_PARAMETER_NUM \
"\
ָ��������ԡ�-oָ���Ҫ������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_QUIT_PARAMETER_NUM \
"\
ָ��������ԡ�-qָ���Ҫ������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_HELP_PARAMETER_NUM \
"\
ָ��������ԡ�-hָ���Ҫ������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_CMD_NOT_EXIST \
"\
�޷�ʶ���ָ���鿴������ָ��:-h��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_WRITE_PARAMETER_NUM \
"\
ָ������������ԡ����ѧ����Ϣֻ�����ܻ�ֻ����1����������ȷ��ʽ��-w [num]��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_WRITE_PARAMETER_1_NOT_NUM \
"\
ָ���ʽ���ԡ�������ѡ���ʹ�ã�������������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_WRITE_PARAMETER_1_NOT_AVAILABLE \
"\
�ڶ�������ָ������ѱ�ռ�ã������¸�һ��δ��ռ�õ���š�����-lָ��鿴����ѧ����\
���ǵ���š�\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_REMOVE_PARAMETER_NUM \
"\
ָ������������ԡ�ɾ��ѧ����Ϣֻ����1����������ȷ��ʽ��-r num��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_REMOVE_PARAMETER_1_NOT_NUM \
"\
ָ��������ԡ�������������������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_REMOVE_PARAMETER_1_NUM_NOT_EXIST \
"\
ָ��������ԡ���ָ������Ų����ڡ�\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_CHANGE_PARAMETER_NUM \
"\
ָ������������ԡ��޸�ѧ����Ϣֻ����1����������ȷ��ʽ��-c num��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_CMD_3_STUDENTBIRTHDAY_NOT_LEGAL \
"\
����ĳ������ڲ��Ϸ�����ȷ��ʽ�� -3 12340102 ���� -3 1234 01 02��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_CMD_5_STUDENTCGRADE_NOT_LEGAL \
"\
�����C���Գɼ����Ϸ��� ��ȷ��ʽ�� -4 98.89��\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_GRADE_STAT_PARAMETER_NUM \
"\
ָ��������ԡ�-gָ���Ҫ������\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_GRADE_STAT_NO_AVAILABLE_STUDENT_INFO \
"\
���ڻ�û��ѧ����Ϣ���޷����гɼ�ͳ�ơ�\r\n\
"
#define ERROR_MSG_DEFAULT \
"\
���ִ�����⵽���󣬵��Ǵ�����ʾ��Ϣ�������룩�����á�\r\n\
"

/* ######################################## */
/* ################# ���� ################# */
/* ######################################## */

//ϵͳ�����ַ�����󳤶ȣ�ϵͳ����ȣ���
#define MAX_SYSTEM_PARAM_LENGTH STORAGE_FILE_CONTENT_BLOCK_SIZE - 10
//�ַ�����󳤶�(��λ���ֽ�)��
#define MAX_STRING_LENGTH STORAGE_FILE_CONTENT_BLOCK_SIZE - 10
#define MAX_CMD_LENGTH MAX_STRING_LENGTH + 200    //�û�ָ����󳤶�
/*����Ԥ�����ַ�����ʹ֮��Ӧ��scanf_s����Ҫ��*/
#define MAX_STR_PREP_TOKEN_LENGTH 200
/*����������õ��ַ�����󳤶ȣ���λ���ֽڣ���*/
#define MAX_INFO_STRING_LENGTH 20000
#define INTERFACE_SIZE_WINDOW_X0 0
#define INTERFACE_SIZE_WINDOW_Y0 0
#define INTERFACE_SIZE_WINDOW_X1 800
#define INTERFACE_SIZE_WINDOW_Y1 600
//ϵͳ��Ϣ���Ĭ��������ɫ�����׻���
#define FONT_SYSTEM_OUTPUT  FOREGROUND_RED | FOREGROUND_GREEN |\
                            FOREGROUND_INTENSITY | BACKGROUND_BLUE
//ѧ��ģ�����Ĭ��������ɫ�����װ���
#define FONT_STUDENT_TEMPLATE  FOREGROUND_RED | FOREGROUND_GREEN |\
  FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE
#define MAX_OPTION_NUM 10    //�û��������ѡ����Ŀ
#define MAX_CHAR_NUM 256    //����ͳ���ַ�����Ƶ��


#define STORAGE_FILE_CONTENT_BLOCK_CHAR ' '    //�洢��Ĭ���ַ�(�ո�)

#define MAX_STUDENT_CODE_LENGTH 200    //ѧ����󳤶�
#define MAX_STUDENT_NAME_LENGTH 80    //������󳤶�
#define MAX_STUDENT_AGE_YEAR 2016   //�������ڣ��꣩���ޣ�����������䣩
#define MAX_STUDENT_TEL_LENGTH 80   //�绰��󳤶�
#define MAX_STUDENT_EXTRA_INFO_LENGTH 1000    //������ע��Ϣ��󳤶�

#define DEFAULT_STUDENT_CODE "ABCD12345678"
#define DEFAULT_STUDENT_NAME "����"
#define DEFAULT_STUDENT_BIRTHDAY 12340102
#define DEFAULT_STUDENT_TELPHONE "123-123456789"
#define DEFAULT_STUDENT_C_GRADE 91.23f
#define DEFAULT_STUDENT_EXTRA_INFO "����˺�����ʲô��û�����¡�"
#define DEFUALT_STUDENT_INFO_INTERVAL_CHAR '#'    //���ڱ���/�����ַ���

/* ######################################## */
/* ################ ������ ################ */
/* ######################################## */

//������أ���ʼֵ0x01000��
#define INTERFACE_CMD_INITIALIZE 0x01000
#define INTERFACE_CMD_SET_TITLE 0x01001    //����
#define INTERFACE_CMD_SET_WINDOW_BACKGROUND_COLOR 0x01002    //����
#define INTERFACE_CMD_SET_WINDOW_SIZE 0x01003    //����
#define INTERFACE_CMD_PRINT 0x01004
#define INTERFACE_CMD_GET_USER_CMD 0x01005
#define DATA_PROCESSOR_OPERATION_LIST_ALL 0x01006
#define DATA_PROCESSOR_OPERATION_LIST_NUM 0x01007
#define DATA_PROCESSOR_OPERATION_LIST_REG 0x01008

/* ######################################## */
/* ################ ������ ################ */
/* ######################################## */

//���������أ���ʼֵ0x12000��
#define CMD_PARSER_ERROR_QUOTER_NUM 0x12000
#define CMD_PARSER_ERROR_OPTION_NUM 0x12001
#define CMD_PARSER_ERROR_FIRST_OPTION_BYTE_NUM 0x12002

//���ݴ�����أ���ʼֵ0x13000:
#define DATA_PROCESSOR_ERROR_STRING_NODE_MALLOC 0x13000
#define DATA_PROCESSOR_ERROR_ADD_PARAMETER_NUM 0x13001
#define DATA_PROCESSOR_ERROR_ADD_PARAMETER_1_LACK_OF_QUOTER 0x13002
#define DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_NUM 0x13003
#define DATA_PROCESSOR_ERROR_ADD_PARAMETER_2_NOT_AVAILABLE 0x13004
#define DATA_PROCESSOR_ERROR_ADD_NO_AVAILABLE_SPACE 0x13005
#define DATA_PROCESSOR_ERROR_LIST_PARAMETER_NUM 0x13006
#define DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_NEGATIVE_NUM 0x13007
#define DATA_PROCESSOR_ERROR_LIST_PARAMETER_1_LACK_OF_QUOTER 0x13008
#define DATA_PROCESSOR_ERROR_DELETE_PARAMETER_NUM 0x13009
#define DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NOT_NUM 0x1300a
#define DATA_PROCESSOR_ERROR_DELETE_PARAMETER_1_NUM_NOT_EXIST 0x1300b
#define DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_NUM 0x1300c
#define DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_2_LACK_OF_QUOTER 0x1300d
#define DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NOT_NUM 0x1300e
#define DATA_PROCESSOR_ERROR_MODIFY_PARAMETER_1_NUM_NOT_EXIST 0x1300f
#define DATA_PROCESSOR_ERROR_STAT_PARAMETER_NUM 0x13010
#define DATA_PROCESSOR_ERROR_RAMINFO_PARAMETER_NUM 0x13011
#define DATA_PROCESSOR_ERROR_JUMP_PARAMETER_NUM 0x13012
#define DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_NOT_NUM 0x13013
#define DATA_PROCESSOR_ERROR_JUMP_PARAMETER_1_RAM_NO_CONTENT 0x13014
#define DATA_PROCESSOR_ERROR_OPTIMIZE_PARAMETER_NUM 0x13015
#define DATA_PROCESSOR_ERROR_QUIT_PARAMETER_NUM 0x13016
#define DATA_PROCESSOR_ERROR_HELP_PARAMETER_NUM 0x13017
#define DATA_PROCESSOR_ERROR_WRITE_PARAMETER_NUM 0x13018
#define DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_NUM 0x13019
#define DATA_PROCESSOR_ERROR_WRITE_PARAMETER_1_NOT_AVAILABLE 0x1301a
#define DATA_PROCESSOR_ERROR_REMOVE_PARAMETER_NUM 0x1301b
#define DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NOT_NUM 0x1301c
#define DATA_PROCESSOR_ERROR_REMOVE_OR_CHANGE_PARAMETER_1_NUM_NOT_EXIST 0x1301d
#define DATA_PROCESSOR_ERROR_CHANGE_PARAMETER_NUM 0x1301e
#define DATA_PROCESSOR_ERROR_CMD_3_STUDENTBIRTHDAY_NOT_LEGAL 0x1301f
#define DATA_PROCESSOR_ERROR_CMD_5_STUDENTCGRADE_NOT_LEGAL 0x13020
#define DATA_PROCESSOR_ERROR_GRADE_STAT_PARAMETER_NUM 0x13021
#define DATA_PROCESSOR_ERROR_GRADE_STAT_NO_AVAILABLE_STUDENT_INFO 0x13022

/* ######################################## */
/* ################# ���� ################# */
/* ######################################## */

#define __OUT 
#define __IN 
