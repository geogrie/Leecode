//原理上错了，此代码弃用
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct clcStr
{
    char * oriStr;
    char * sortStr;
    int len;
}clcStr;
void clcStrCpy(clcStr * p1, clcStr *p2)
{
    p1->len = p2->len;
    p1->oriStr = p2->oriStr;
    p1->sortStr = p2->sortStr;
}
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
int positionInt(clcStr **clcStrArr, int low, int high)
{
    clcStr * key = (clcStr *)malloc(sizeof(clcStr) + 1);
    clcStrCpy(key,clcStrArr[low]);
    while(low < high)
    {
        while(low < high && key->len <= clcStrArr[high]->len)
            high--;
        if(low < high)
            clcStrCpy(clcStrArr[low++],clcStrArr[high]);
        while(low < high && clcStrArr[low]->len <= key->len)
            low++;
        if(low < high)
            clcStrCpy(clcStrArr[high--],clcStrArr[low]);
    }
    clcStrCpy(clcStrArr[low],key);
    return low; 
}
void quickSortInt(clcStr **clcStrArr, int low, int high)
{
    int mid = 0;
    if(low < high)
    {
        mid = positionInt(clcStrArr, low, high);
        quickSortInt(clcStrArr, 0, mid -1);
        quickSortInt(clcStrArr, mid + 1,high);
    }
}
clcStr ** clc(char ** strs,int strsSize)
{
    clcStr **clcS = (clcStr **)malloc(sizeof(clcStr*) * strsSize);
    clcStr *tmp = (clcStr*)malloc(sizeof(clcStr));
    int i = 0, j =0;
    //printf("%d",sizeof(clcStr*)); //4
    for(; i < strsSize; i++)
    {
        clcStr *tmp = (clcStr*)malloc(sizeof(clcStr));
        tmp->oriStr = strs[i];
        tmp->len = strlen(strs[i]);
        tmp->sortStr = (char *)malloc(sizeof(char) * tmp->len + 1);
        strcpy(tmp->sortStr,tmp->oriStr);
        clcS[i] = tmp;
        //字符串中的字符也进行排序
        quickSortChar(clcS[i]->sortStr,0,clcS[i]->len - 1);
    }
    //按照字符串的长度进行排序
    quickSortInt(clcS,0,strsSize - 1);
    //for(i = 0 ; i < strsSize; i++)
    //{
    //    printf(" i = %d  string = %s\n",i,clcS[i]->oriStr);
    //}
    return clcS;
}
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    char ***retGroup = (char ***)malloc(sizeof(char **) * strsSize+1);
    char **charArr = NULL;
    int i = 0, low = 0, high = 1,cnt = 1;

    clcStr ** clcSortArr = clc(strs,strsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * strsSize+1);
    * returnSize = 0;
    if(strsSize < 2)
    {
        * returnSize = strsSize;
        charArr = (char **)malloc(sizeof(char *) *strsSize + 1);
        charArr[0] = strs[0];
        (*returnColumnSizes)[0] = strsSize;
        retGroup[0] = charArr;
    }
    else
    {
        while(high < strsSize)
        {
            high = low + 1;
            cnt = 1;
            i = 0;
            while(high < strsSize && clcSortArr[low]->len == clcSortArr[high]->len && (0 == strcmp(clcSortArr[low]->sortStr,clcSortArr[high]->sortStr)))
            {
                cnt++;
                high++;
            }
            charArr = (char**)malloc(sizeof(char *) * cnt);
            while(i < cnt)
            {
                charArr[i++] = clcSortArr[low++]->oriStr;
            }
            (*returnColumnSizes)[*returnSize] = cnt;
            retGroup[*returnSize] = charArr;
            //printf("%s",*charArr);
             *returnSize += 1;
        }
    }
    return retGroup;
}
void main()
{
    char* str[] = {"eat","tea","tan","ate","nat","bat"};
    int strsSize = 6;
    int returnSize = 0;
    int *returnColumnSize = NULL;
    groupAnagrams(str,strsSize,&returnSize,&returnColumnSize);
    printf("运行结束\n");
    getchar();
    return;
}