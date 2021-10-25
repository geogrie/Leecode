#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct strHash
{
    char *str;
    char *sortStr;
    int hash;
}strHash;
void strHashCpy(strHash *dest,strHash *sorc)
{
    dest->hash = sorc->hash;
    dest->sortStr = sorc->sortStr;
    dest->str = sorc->str;
}
//�ַ�����
int positionChar(char *str, int low, int high)
{
    char key = str[low];
    while(low < high)
    {
        while(low < high && key <= str[high])
            high--;
        if(low < high)
            str[low++] = str[high];
        while(low < high && str[low] <= key)
            low++;
        if(low < high)
            str[high--] = str[low];
    }
    str[low] = key;
    return low;
}
void quickSortChar(char * str,int low, int high)
{
    int mid = 0;
    if(low < high)
    {
        mid = positionChar(str,low,high);
        quickSortChar(str,0,mid -1);
        quickSortChar(str,mid + 1,high);
    }
}
// (֮ǰĬ���� strs �������ַ��� �ĳ��ȶ���һ���ģ�ʵ����������ַ����ĳ��ȶ��ǲ�һ����)����������ַ������ϣ������Ĺ�ϣֵ ���ַ����͹�ϣֵһ�𷵻�
strHash **clcHash(char** strs, int strSize)
{
    int i = 0, j = 0;
    int len = 0;
    strHash *tmp = NULL;
    strHash **ret = (strHash **)malloc(sizeof(strHash*) * (strSize + 1));
   
    for(i = 0; i < strSize; i++)
    {
        len = strlen(strs[i]);
        if(len)
        {
            tmp = (strHash *)malloc(sizeof(strHash));
            tmp->str = strs[i];
            tmp->hash = 0;
            tmp->sortStr = (char *)malloc(sizeof(char) * (len+1));
            strcpy(tmp->sortStr,tmp->str);
            for( j = 0; j < len; j++)
            {
                tmp->hash += 1 << (strs[i][j] - 96);

            }
            quickSortChar(tmp->sortStr, 0 ,len-1);
            ret[i] = tmp;
         }
       else
       {
            tmp = (strHash *)malloc(sizeof(strHash));
            tmp->str = strs[i];
            tmp->hash = 0;
            tmp->sortStr = tmp->str;
            ret[i] = tmp;
       }
    }
     /*for(i = 0; i < strSize; i++)
     {
         printf( "%s\n", ret[i]->sortStr);
     }*/
    return ret;
}
//�����㷨 �����������裬һ��������ֵ��Ȼ���ʣ�µ����������������ֵ
int position(strHash **strHashArr,int low, int high)
{
    strHash *key = (strHash *)malloc(sizeof(strHash));
    strHashCpy(key,strHashArr[low]);
    while(low < high)
    {
        while(low < high && strHashArr[high]->hash >= key->hash)
            high--;
        if(low < high)
             strHashCpy(strHashArr[low++],strHashArr[high]);
        while(low < high && strHashArr[low]->hash <= key->hash)
            low++;
        if(low < high)
            strHashCpy(strHashArr[high--],strHashArr[low]);
    }
    strHashCpy(strHashArr[low],key);
    return low;
}
void quickSort(strHash **strHashArr,int low, int high)
{
    int mid = 0;
    if(low < high)
    {
        mid = position(strHashArr, low, high);
        quickSort(strHashArr, low, mid -1);
        quickSort(strHashArr, mid + 1, high);
    }
}
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    //�����ά������ÿ���ַ����ĳ��ȶ���һ����
    int low = 0,high = 1,cnt = 1 ,i = 0;
    char **charArr = NULL;
    char ***groupCharArr = (char ***)malloc(sizeof(char**) * (strsSize + 1));
    strHash **strHashArr = clcHash(strs, strsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * (strsSize+1));
    *returnSize = 0;
    //���볤��С�ڵ���1 
    if(strsSize < 2)
    {
        *returnSize = strsSize;
        charArr = (char **)malloc(sizeof(char *) *(strsSize + 1));
        charArr[0] = strs[0];
        (*returnColumnSizes)[0] = strsSize;
        groupCharArr[0] = charArr;
    }
    //���볤�ȴ���1
    //��ϣֵ��ͬ�Ĺ�Ϊһ��
    quickSort(strHashArr,0, strsSize-1);
    /*for(i = 0; i < strsSize; i++)
    {
        printf("ori = %s; sort = %s\n",strHashArr[i]->str,strHashArr[i]->sortStr);
    }*/
    while(high < strsSize)
    {
        high = low + 1;
        cnt = 1;
        i = 0;
        while(high < strsSize && strHashArr[low]->hash == strHashArr[high]->hash  && (0 == strcmp(strHashArr[low]->sortStr ,strHashArr[high]->sortStr)))
        {
            cnt++;
            high++;
        }
        charArr = (char **)malloc(sizeof(char *) * (cnt+1));
        while(i < cnt)
        {
           // printf("%s",strHashArr[low]->str);
            charArr[i++] = strHashArr[low++]->str; 
        }
        (*returnColumnSizes)[*returnSize] = cnt;
        groupCharArr[*returnSize] = charArr;
        *returnSize += 1;
    }
    return groupCharArr;
}
void main()
{
    char* str[] = {"eat","tea","tan","ate","nat","bat"};
    int strsSize = 6;
    int returnSize = 0;
    int *returnColumnSize = NULL;
    int i ,j ;
    char ***ret = groupAnagrams(str,strsSize,&returnSize,&returnColumnSize);
    for(i = 0;i < returnSize; i++)
    {
        printf("i = %d\t",i);
        for(j = 0; j < returnColumnSize[i]; j++)
            printf("str = %s\t",ret[i][j]);
        printf("\n");
    }
    printf("���н���\n");
    getchar();
    return;
}