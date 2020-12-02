#include <iostream>

using namespace std;

template <template T>
class ArrayList {
 public:
    ArrayList(int nCap) {
        m_nCapacity = nCap < 16 ? 16 : nCap;
        m_nSize = 0;
        m_cArray = new T[m_nCapacity];
        assert(m_cArray != nullptr);
    }
    ~ArrayList() {
        if (m_cArray != nullptr) {
            delete[] m_cArray;
            m_cArray = nullptr;
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
	T set(int index, T element) {
        rangecheck(index, false);
        T oldElement = m_cArray[index]; 
        m_cArray[index] = element;
        return 
    }
    //! 返回index位置对应的元素
	T get(int index) {
        rangecheck(index, false);
        return m_cArray[index];
    } 
    //! 往index位置添加元素
	void insert(int index, T element) {
        rangecheck(index, true);
        prereserve(m_nSize + 1);
        for (int i = m_nSize; i > index; --i) {
            m_cArray[i] = m_cArray[i-1];
        }
        m_cArray[index] = element;
        m_nSize++;
    }
    //! 添加元素到最后面
	void append(T element) {
        insert(m_nSize, element);
    }
    //! 删除index位置对应的元素
	T remove(int index) {
        rangecheck(index, false);

        T oldElement = m_cArray[index];  
        for (int i = index; i < m_nSize; ++i) {
            m_cArray[i] = m_cArray[i+1];
        }
        m_cArray[--m_nSize] = nullptr;

        return oldElement;
    }
    //! 清除所有元素
	void clear() {
        for (int i = 0; i < m_nSize; i++) {
            m_cArray[i] = nullptr;
        }
        m_nSize = 0;
    } 
    
 private:
    void rangecheck(int index, bool isAdd) {
        if (isAdd) {
            assert(index >= 0 && index <= m_nSize);
        } else {
            assert(index >= 0 && index < m_nSize);
        }
    }

    void prereserve(int nCap) {
        if (nCap < m_nCapacity) {
            return; 
        }

        m_nCapacity = 2 * m_nCapacity;
        T* cArray = new T[m_nCapacity];
        assert(cArrays != nullptr); 

        for (int i = 0; i < m_nSize; ++i) {
            cArrays[i] = m_cArrayp[i];
        }
        
        delete[] m_cArray;
        m_cArray = cArray;
    }

 private:
    int m_nSize;
    T* m_cArray;
    int m_nCapacity;
};