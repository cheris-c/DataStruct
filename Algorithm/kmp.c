/*************************************************************************
  > File Name: kmp.c
  > Description: KMP算法实现及优化
  > Author: Actually
  > Created Time: 2017年09月20日 星期三 14时44分18秒
 ************************************************************************/

/*
 *
 */
#include <stdio.h>

typedef char* String;

//对于某种特殊情况的效率并不是很高。例如Saaaabcde  T : aaaaax
void getNext1(String T, int *next)
{
    int i = 1, j = 0;
    next[1] = 0;

    while (i < T[0])
    {
        if (0 == j || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

void getNext2(String T, int *next)
{
    int i = 1, j = 0;
    next[1] = 0;

    while (i < T[0])
    {   
        if (0 == j || T[i] == T[j])
        {   
            i++;
            j++;
            if (T[i] != T[j])
                next[i] = j;
            else
                next[i] = next[j];
        }   
        else
        {   
            j = next[j];
        }   
    }
}

int Index_KMP(String S, String T, int pos)
{
    int i = pos, j = 1, next[255];

    getNext2(T, next);

    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            j++;
            i++;
        }
        else
        {
            j = next[j];
        }
    }

    //当匹配到T的最后一个位置，并且相等时，j++后大于T[0]的值
    if (j > T[0])
    {
        return i-T[0];
    }

    return 0;
}

int main()
{
    char str[255] = "ababaaaba";
    char s[255] = "aaa";
    int next[255];
    int i = 1;
    int pos = 0;

    str[0] = 9;

    pos = Index_KMP(str, s, 1);
    printf("%d\n", pos);

    return 0;
}
