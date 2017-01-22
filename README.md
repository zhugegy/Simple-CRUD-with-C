# information-management-system
字符串管理系统和学生信息管理系统，因为相似所以放在一起了。实现了数据的增、删、改、查（支持正则表达式查找）。手工简单地模拟了Unix环境下命令行输入的方式（包含基本的输入检测）。数据同步存储到外部文件中，不会随程序的结束而丢失。数据在程序中存储于固定长度的一维数组中，也就是模拟出一块固定大小的内存区域。实现了内存分配、内存容量扩展、内存碎片清理操作。具体功能可进入程序用'-h'指令查看。

## 字符串管理系统功能列表（'-h'指令输出）：
-h
本程序支持指令及其说明：

添加字符串：-a "string" [num]
字符串必须用双引号括起来。可以选填第二参数，手动为字符串指定序号。不填第二参数的
话，系统会自动分配一个序号。

删除字符串：-d num
删除指定序号的字符串。

修改字符串: -m num "string"
修改指定序号的字符串的内容。

查询字符串：-l [num | "string"]
列出指定序号或者匹配正则表达式的字符串。可以选填第二参数，如果不填，会列出所有字
符串。

查询内存地址：-j num
查询指定地址处是否有字符串，若有字符串则显示该字符串。

统计字符：-s

显示内存信息：-i

内存碎片整理: -o

退出：-q

显示本帮助: -h

## 学生信息管理系统功能列表（'-h'指令输出）：
-h
本程序支持指令及其说明：

修改学号：-1 string [string...]
修改学生信息模板的学号。学号可以包含空格。

修改姓名：-2 string [string...]
修改学生信息模板的姓名。姓名可以包含空格。

-3 -4 -5 -6 同样的用法，修改学生信息模板的对应项目。

添加学生信息到数据库：-w [num]
可以选填第二参数，手动为学生信息指定序号。不填第二参数的话，系统会自动分配一个
序号。

从数据库删除学生信息：-r num
删除指定序号的学生信息。

修改数据库内的学生信息: -c num
把指定序号的学生信息的内容修改为当前模板的内容。

查询学生信息：-l [num | "string"]
列出指定序号或者匹配正则表达式的学生信息。可以选填第二参数，如果不填，会列出所
有字符串。

查询内存地址：-j num
查询指定地址处是否有学生信息，若有字符串则显示该学生信息。

统计学生成绩：-g
统计所有学生的C语言成绩，给出结果。

统计字符：-s

显示内存信息：-i

内存碎片整理: -o

退出：-q

显示本帮助: -h