/*************************************************************************
  > File Name: hashtable.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月20日 星期三 23时53分14秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

enum {HASHSIZE = 12, NULLKEY = -32768};

typedef struct HASH 
{
    int *elem; //数据元素的基址，动态分配数组
    int count; //当前数据元素的个数
} HashTable;

int InitHashTable(HashTable *H)
{
    int i;

    H->count = HASHSIZE;
    H->elem = (int *)malloc(HASHSIZE * sizeof(int));

    if (NULL == H->elem)
    {
        return -1;
    }
    for (i = 0; i < HASHSIZE; i++)
    {
        H->elem[i] = NULLKEY;
    }
    H->count = 0;

    return 0;
}

int Hash(int key)
{
    return (key % HASHSIZE);
}

void InsertHash(HashTable *H, int key)
{
    int addr;
    addr = Hash(key);

    //如果H->elem[addr]不为空，则说明发生了冲突，下面处理此冲突
    while (H->elem[addr] != NULLKEY)
    {
        addr = (addr+1) % HASHSIZE;  //开放定址法中的线性探测法
    }

    H->elem[addr] = key;
    H->count++;
}

//散列表查找关键字
int HashSearch(HashTable H, int key, int *addr)
{
    *addr = Hash(key);

    while (H.elem[*addr] != key)
    {
        *addr = (*addr + 1) % HASHSIZE;
        if (H.elem[*addr] == NULLKEY || *addr == Hash(key))
        {
            return -1;
        }
    }
    return 0;
}

void DeleteHashTable(HashTable *hash)
{
    free(hash->elem);
    hash->elem = NULL;
   ethash->count = 0;
}

int main()
{
    HashTable hash;  
    int pos = -1;
    int i =0;

    InitHashTable(&hash);

    for (i = 0; i < 10; i++)
        InsertHash(&hash, i);
    HashSearch(hash, 5, &pos);
    printf("elem 5 : %d\n", pos);
    HashSearch(hash,27, &pos);
    InsertHash(&hash, 27);
    printf("elem 27: %d\n", pos);

    DeleteHashTable(&hash);

    return 0;
}
