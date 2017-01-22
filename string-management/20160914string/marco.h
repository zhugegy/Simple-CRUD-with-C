#pragma once
//本文件记录了所有的宏。

/* ######################################## */
/* ######### 用户可以自定义的数值 ######### */
/* ######################################## */

/*20161004
#define STRING_ARRAY_SPACE 2000    //存储器大小（单位：字节）。*/



/* ######################################## */
/* ################ 字符串 ################ */
/* ######################################## */

//界面相关：
#define INTERFACE_INFO_TITLE "字符串动态存储系统"
#define INTERFACE_INFO_VERSION "Version 0.01"
#define INTERFACE_INFO_BACKGROUND_COLOR "30"    //30代表蓝色。
#define FILE_LOCATION_STORAGE "data_storage\\storage.dat"
#define FILE_LOCATION_LINK_INFO "data_storage\\linkinfo.txt"
#define FILE_LOCATION_LINK_INFO_REPLICA "data_storage\\linkinforeplica.txt"
#define HELP_INFO \
"本程序支持指令及其说明：\r\n\
\r\n\
添加字符串：-a \"string\" [num]\r\n\
字符串必须用双引号括起来。可以选填第二参数，手动为字符串指定序号。不填第二参数的\
话，系统会自动分配一个序号。\r\n\
\r\n\
删除字符串：-d num\r\n\
删除指定序号的字符串。\r\n\
\r\n\
修改字符串: -m num \"string\"\r\n\
修改指定序号的字符串的内容。\r\n\
\r\n\
查询字符串：-l [num | \"string\"]\r\n\
列出指定序号或者匹配正则表达式的字符串。可以选填第二参数，如果不填，会列出所有字\
符串。\r\n\
\r\n\
查询内存地址：-j num\r\n\
查询指定地址处是否有字符串，若有字符串则显示该字符串。\r\n\
\r\n\
统计字符：-s\r\n\
\r\n\
显示内存信息：-i\r\n\
\r\n\
内存碎片整理: -o\r\n\
\r\n\
退出：-q\r\n\
\r\n\
显示本帮助: -h\r\n\
"
#define GOODBYE_INFO "再见!\r\n"
#define RAM_INFO_FULL_SYMPOL "★"
#define RAM_INFO_EMPTY_SYMPOL "□"
/* 800x600窗口下，每行最大能打印的字符串长度：
hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello
*/
#define INTERFACE_INFO_WELCOME_INFO \
"\
欢迎使用字符串动态存储系统。查看帮助请使用命令-h。\r\n\
"
#define INTERFACE_INFO_HELP_INFO \
"\
帮助信息预留。\
"
#define CMD_PARSER_ERROR_MSG_QUOTER_NUM \
"\
引号数量不对，请检查用户指令。如果想把引号作为内容输入，需要加转义符。\r\n\
"
#define CMD_PARSER_ERROR_MSG_OPTION_NUM \
"\
指令数量不对，请检查用户指令。是不是输入了过多的指令？每次只支持一个指令。\r\n\
"
#define CMD_PARSER_ERROR_MSG_FIRST_OPTION_BYTE_NUM \
"\
指令字节不对，请检查用户指令。只支持单字节指令，例如-a。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_STRING_NODE_MALLOC \
"\
字符串信息存储链表MALLOC操作失败。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_NUM \
"\
指令参数数量不对。增加字符串只接受1个或2个参数。正确格式：-a \"string\" [num]。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_1_LACK_OF_QUOTER \
"\
指令格式不对。增加字符串需要把字符串用引号括起来。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_2_NOT_NUM \
"\
指令格式不对。第2参数可选填，若使用第2参数，则它必须是正整数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_PARAMETER_2_NOT_AVAILABLE \
"\
第三参数所指定序号已被占用，请重新给一个未被占用的序号。可用-l指令查看所有字符串\
和他们的序号。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_ADD_NO_AVAILABLE_SPACE \
"\
数组中没有可用空间。请尝试整理碎片。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_NUM \
"\
指令参数数量不对。浏览字符串只接受1个或2个参数。正确格式：-l [num | \"reg\"]。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_1_NEGATIVE_NUM \
"\
指令格式不对。浏览字符串只接受1个或2个参数。第二参数可选填，若使用数字作第二参数\
，则它不可以是负数。正确格式：-l [num | \"reg\"]。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_LIST_PARAMETER_1_LACK_OF_QUOTER \
"\
指令格式不对。浏览字符串只接受1个参数。参数可选填，若使用正则表达式作参数，则它\
必须被双引号包起来。正确格式：-l [num | \"reg\"]。\r\n\
"
#define DATA_PROCESSOR_INFO_NO_RESULT_REG \
"\
未能找到和所输入正则表达式匹配的字符串。\r\n\
"
#define DATA_PROCESSOR_INFO_NO_RESULT_NUM \
"\
未能找到所输入序号的字符串，是不是输入了错误的序号？\r\n\
"
#define DATA_PROCESSOR_INFO_NO_RESULT_ALL \
"\
未能找到字符串。目前还没有储存字符串。添加字符串请使用-a \"string\" [num]指令。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_NUM \
"\
指令参数数量不对。删除字符串只接受1个参数。正确格式：-d num。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_1_NOT_NUM \
"\
指令参数不对。参数必须是正整数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_DELETE_PARAMETER_1_NUM_NOT_EXIST \
"\
指令参数不对。所指定的序号不存在。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_NUM \
"\
指令参数数量不对。增加字符串只接受2个参数。正确格式：-m num \"string\"。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_2_LACK_OF_QUOTER \
"\
指令格式不对。修改字符串需要把新的字符串用引号括起来。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_1_NOT_NUM \
"\
指令参数不对。第1参数必须是正整数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_MODIFY_PARAMETER_1_NUM_NOT_EXIST \
"\
指令参数不对。所指定的序号不存在。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_STAT_PARAMETER_NUM \
"\
指令参数不对。-s指令不需要参数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_RAMINFO_PARAMETER_NUM \
"\
指令参数不对。-i指令不需要参数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_NUM \
  "\
指令参数不对。-j指令需要1个参数。正确格式: -j num。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_1_NOT_NUM \
"\
指令参数不对。参数必须是正整数或0。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_JUMP_PARAMETER_1_RAM_NO_CONTENT \
"\
在所给的地址里没有存储字符串。可以使用-i指令查看内存使用情况。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_OPTIMIZE_PARAMETER_NUM \
"\
指令参数不对。-o指令不需要参数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_QUIT_PARAMETER_NUM \
"\
指令参数不对。-q指令不需要参数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_HELP_PARAMETER_NUM \
"\
指令参数不对。-h指令不需要参数。\r\n\
"
#define DATA_PROCESSOR_ERROR_MSG_CMD_NOT_EXIST \
"\
无法识别的指令。请查看帮助，指令:-h。\r\n\
"

/* ######################################## */
/* ################# 参数 ################# */
/* ######################################## */

#define MAX_SYSTEM_PARAM_LENGTH 2000    //系统参数字符串最大长度（系统标题等）。
#define MAX_STRING_LENGTH 2000    //字符串最大长度(单位：字节)。
#define MAX_CMD_LENGTH MAX_STRING_LENGTH + 200    //用户指令最大长度
/*用于预处理字符串，使之适应于scanf_s函数要求*/
#define MAX_STR_PREP_TOKEN_LENGTH 200
/*程序输出所用的字符串最大长度（单位：字节）。*/
#define MAX_INFO_STRING_LENGTH 10248    
#define INTERFACE_SIZE_WINDOW_X0 0
#define INTERFACE_SIZE_WINDOW_Y0 0
#define INTERFACE_SIZE_WINDOW_X1 800
#define INTERFACE_SIZE_WINDOW_Y1 600
#define FONT_DEFAULT 0x30
#define FONT_SYSTEM_OUTPUT  FOREGROUND_RED | FOREGROUND_GREEN |\
                            FOREGROUND_INTENSITY | BACKGROUND_BLUE
#define MAX_OPTION_NUM 10    //用户命令最大选项数目
#define MAX_CHAR_NUM 256    //用于统计字符出现频率

#define STORAGE_FILE_CONTENT_BLOCK_SIZE 2000    //存储文件每一块的大小（字节数）
#define STORAGE_FILE_CONTENT_BLOCK_CHAR 'a'    //存储块默认字符(空格)

/* ######################################## */
/* ################ 操作码 ################ */
/* ######################################## */

//界面相关，起始值0x01000：
#define INTERFACE_CMD_INITIALIZE 0x01000
#define INTERFACE_CMD_SET_TITLE 0x01001    //过期
#define INTERFACE_CMD_SET_WINDOW_BACKGROUND_COLOR 0x01002    //过期
#define INTERFACE_CMD_SET_WINDOW_SIZE 0x01003    //过期
#define INTERFACE_CMD_PRINT 0x01004
#define INTERFACE_CMD_GET_USER_CMD 0x01005
#define DATA_PROCESSOR_OPERATION_LIST_ALL 0x01006
#define DATA_PROCESSOR_OPERATION_LIST_NUM 0x01007
#define DATA_PROCESSOR_OPERATION_LIST_REG 0x01008

/* ######################################## */
/* ################ 错误码 ################ */
/* ######################################## */

//命令解析相关，起始值0x12000：
#define CMD_PARSER_ERROR_QUOTER_NUM 0x12000
#define CMD_PARSER_ERROR_OPTION_NUM 0x12001
#define CMD_PARSER_ERROR_FIRST_OPTION_BYTE_NUM 0x12002

//数据处理相关，起始值0x13000:
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

/* ######################################## */
/* ################# 杂项 ################# */
/* ######################################## */

#define __OUT 
#define __IN 
