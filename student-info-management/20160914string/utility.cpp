////此文件是常用小功能相关函数。

#include "stdafx.h"
#include "utility.h"

/*用于构建StrPrepToken字符串，它将会被用作scanf函数的格式化参数。其实也就是接受
除了回车以外的任何输入（比如空格字符可以输入）*/
int build_str_prep_token(char *szToken, int nMaxLengthToken, 
                         int nMaxLengthTarget)
{
  char szTmp[MAX_STR_PREP_TOKEN_LENGTH] = {0};

  sprintf_s(szToken, nMaxLengthToken, "%d", nMaxLengthTarget - 1);
  strcpy_s(szTmp, _countof(szTmp), "%");
  strcat_s(szTmp, _countof(szTmp), szToken);
  strcpy_s(szToken, MAX_STR_PREP_TOKEN_LENGTH, szTmp);
  strcpy_s(szTmp, _countof(szTmp), "[^\n]s");
  strcat_s(szToken, MAX_STR_PREP_TOKEN_LENGTH, szTmp);

  return 0;
}

//用于清除显示缓冲区。
int empty_pi_info_buffer(Param *ppParam)
{
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
    _countof(ppParam->piInfoBuffer.szToBePrinted), "");
  ppParam->piInfoBuffer.nColor = FONT_DEFAULT;

  return 0;
}

//向StringNode填入信息。
int write_in_string_node(StringNode *psnTarget, StringNode *psnTemplate)
{
  psnTarget->nArrayLocation = psnTemplate->nArrayLocation;
  psnTarget->nSerial = psnTemplate->nSerial;
  psnTarget->nStringLength = psnTemplate->nStringLength;
  psnTarget->tCreationTime = psnTemplate->tCreationTime;
  psnTarget->psnNext = NULL;

  return 0;
}

//清空映射文件的heap指针
int free_mapping_heaps(Param *ppParam)
{
  //清空文件到内存的映射
  if (ppParam->pchArrayStorage)
  {
    free((void *) ppParam->pchArrayStorage);
    ppParam->pchArrayStorage = NULL;
  }

  //清空内存模拟数组（指针）
  if (ppParam->pchSim)
  {
    free((void *) ppParam->pchSim);
    ppParam->pchSim = NULL;
  }

  return 0;
}