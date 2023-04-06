# include "skl.h"

template <class E, class K>
SkipList<E, K>::SkipList(K large, int maxLev) {
    //!建立空的多级链
    maxLevel = maxLev;  //!最大级链数目
    tailKey = large;    //!控制扫描的最大关键码
    levels = 0;

    tail = new SkipNode<E, K>(0);               //!附加尾结点有0个指针 
    head = new SkipNode<E, K>(maxLevel + 1);    //!附加头结点，有maxLevel+1个指针
    last = new SkipNode<E, K>*[maxLevel + 1];   //!跳表的多级链的头指针
    tail->data = large;
    
    for (int i = 0; i < maxLevel; ++i) {
        head->link[i] = tail;
    }
}

template <class E, class K>
SkipList<E, K>::~SkipList() {
    //!释放链表所有元素结点
    SkipNode<E, K> *next;

    while (head != tail) {
        next = head->link[0]
        delete head;
        head = next;
    }

    delete tail;
    delete[] last;
}

template <class E, class K>
bool SkipList<E, K>::Search(const K k1, E& e1) {
    if (k1 > tailKey)   
        return false;

    SkipNode<E, k> *p = head;
    for (int i = levels; i >= 0; --i) { //!逐级向下搜索
        while (p->link[i]->data < k1) { //!可重载: operator<
            p = p->link[i]
        }
    }

    e1 = p->link[0]->data;  
    return (e1 == k1) ? true : false;   //!可重载: operator==
}

template <class E, class K>
SkipNode<E, K>* SkipList<E, K>::SaveSearch(const K k1) {
    if (k1 > tailKey) 
        return NULL;

    SkipNode<E, K> *p = head;  
    for (int i = levels; i >= 0; --i) { //!逐级向下搜索
        while (p->link[i]->data < k1) { //!可重载: operator<
            p = p->link[i];
        }
        
        last[i] = p;    //!记下最后比较结点
    }

    return p->link[0];  //!返回找到的结点地址
}

template <class E, class K>
int SkipList<E, K>::Level() {
    //!产生一个随机的级别，该级别 < maxLevel
    int lev = 0;
    while (rand() <= RAND_MAX/2) 
        ++lev;
    
    return (lev < maxLevel) ? lev : maxLevel;
}

template <class E, class K>
bool SkipList<E, K>::Insert(const K k1, E& e1) {
    if (k1 >= tailKey) {
        cerr << "the key is too large!" << endl;
        return false;
    }

    SkipNode<E, K> *p = SaveSearch(k1); //!检查是否重复
    if (p->data == e1) {                //!可重载：operator==
        cerr << "duplicate key!" << endl;
        return false;
    }

    int lev = Level();
    if (lev > Levels) {
        lev = ++Levels;
        last[lev] = head;
    }

    SkipNode<E, K> *newNode = new SkipNode<E, K>(lev+1);
    newNode->data = e1;     //!可重载：operator=

    for (int i = 0; i <= lev; i++) {            //!各级链入
        newNode->link[i] = last[i]->link[i];    //!第i级链入
        last[i]->link[i] = newNode;
    }

    return true;
}

template <class E, class K>
bool SkipList<E, K>::Remove(const K k1, E&e1) {
    if (k1 > tailKey) {
        cerr << "the key is too large!" << endl;
        return false;
    }

    SkipNode<E, K> *p = SaveSearch(k1); //!搜索与k1匹配的元素->p
    if (p->data != k1) {    //!可重载：operator!=
        cout << "the key isn't exist!" << endl;
        return false;
    }

    for (int i = 0; i <= levels && last[i]->link[i] == p; ++i) {
        last[i]->link[i] = p->link[i];  //!逐级链摘下该结点
    }

    while(levels > 0 && head->link[levels] == tail) {
        --levels;   //!修改级数
    }

    e1 = p->data;
    delete p;
    p = NULL;

    return true;
}