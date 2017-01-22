////���ļ��ǳ���С������غ�����

#include "stdafx.h"
#include "utility.h"

/*���ڹ���StrPrepToken�ַ����������ᱻ����scanf�����ĸ�ʽ����������ʵҲ���ǽ���
���˻س�������κ����루����ո��ַ��������룩*/
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

//���������ʾ��������
int empty_pi_info_buffer(Param *ppParam)
{
  strcpy_s(ppParam->piInfoBuffer.szToBePrinted, 
    _countof(ppParam->piInfoBuffer.szToBePrinted), "");
  ppParam->piInfoBuffer.nColor = FONT_DEFAULT;

  return 0;
}

//��StringNode������Ϣ��
int write_in_string_node(StringNode *psnTarget, StringNode *psnTemplate)
{
  psnTarget->nArrayLocation = psnTemplate->nArrayLocation;
  psnTarget->nSerial = psnTemplate->nSerial;
  psnTarget->nStringLength = psnTemplate->nStringLength;
  psnTarget->tCreationTime = psnTemplate->tCreationTime;
  psnTarget->psnNext = NULL;

  return 0;
}

//���ӳ���ļ���heapָ��
int free_mapping_heaps(Param *ppParam)
{
  //����ļ����ڴ��ӳ��
  if (ppParam->pchArrayStorage)
  {
    free((void *) ppParam->pchArrayStorage);
    ppParam->pchArrayStorage = NULL;
  }

  //����ڴ�ģ�����飨ָ�룩
  if (ppParam->pchSim)
  {
    free((void *) ppParam->pchSim);
    ppParam->pchSim = NULL;
  }

  return 0;
}