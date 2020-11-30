#include <iostream>

using namespace std;

template <template T>
class ArrayList {
 public:
    ArrayList(int nCap) {
        m_nCapacity = nCap < 16 ? 16 : nCap;
        m_nSize = 0;
        m_cArray = new T[m_nCapacity];
        assert(m_cArray != NULL);
    }
    ~ArrayList() {
        if (m_cArray != NULL) {
            delete[] m_cArray;
            m_cArray = NULL;
        }
    }

 public:
    //! 元素的数量
	int size() { return m_nSize; }
    //! 是否为空
    bool empty() { return m_nSize == 0; }

    //! 查看元素的位置 	
    int indexOf(T element) {
        for (int i = 0; i < m_nSize; ++i) {
            if (m_cArray[i] == element) {
                return i;
            }
        }
        return -1;
    } 

    //! 设置index位置的元素
	T set(int index, T element);
    //! 返回index位置对应的元素
	T get(int index); 
    //! 往index位置添加元素
	void add(int index, T element); 
    //! 添加元素到最后面
	void add(T element); 
    //! 删除index位置对应的元素
	T remove(int index); 
    //! 清除所有元素
	void clear(); 
    
 private:
    
    

 private:
    int m_nSize;
    T* m_cArray;
    int m_nCapacity;
};