#ifndef _SKL_H_
#define _SKL_H_

#include <iostream.h>

const int DefaultSize = 100;

template <class E, class K>
struct SkipNode {
    E data;                 //!数据域
    SkipNode<E, K> **link;  //!指针数组域

    SkipNode(int size = DefaultSize) {
        link = new SkipNode<E, K>*[size];
        if (link == NULL) {
            cerr << "alloc memory failed!" << endl;
            exit(1);
        }
    }

    ~SkipNode() { delete[] link; }
};


template <class E, class K>
class SkipList {
public:
    SkipList(K large, int maxLev = DefaultSize);
    ~SkipList();

    bool Search(const K k1, E& e1) const;
    E& getData(SkipNode<E, K>* current) {
        if (current != NULL) {
            return &current->data;    
        } else {
            return NULL;
        }
    }

    bool Insert(const K k1, E& e1);     //!插入函数
    bool Remove(const K k1, E& e1);     //!删除函数

private:
    int maxLevel;   //!所允许的最大级数
    int levels;     //!当前非空链的级数
    K tailKey;      //!在TailKey中存有一个大值
    SkipNode<E, K>  *head, *tail, **last;   //!附加头结点、尾结点、指针数组
    
    int level();
    SkipNode<E, K>  *SaveSearch(const K k1);
};


#endif