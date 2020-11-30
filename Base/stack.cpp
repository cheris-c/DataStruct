#include <iostream>

using namespace std;

/*顺序栈和链式栈的简单实现*/
#if 0
template <class T>
class SeqStack
{
public:
	explicit SeqStack<T>(int sz) : m_nTop(-1), m_nSzie(sz) 
	{
		m_pCapacity = new T[sz];
		if (m_pCapacity == NULL)
		{
			cout << "Application error!" << endl;		
			exit(1);
		}		
	}

	~SeqStack<T>() { delete []m_pCapacity; }

public:
	T getTop();
	T pop();
	void push(T x);
	void print();	

	void clear() {	m_nTop = -1; }
	bool isFull() const { return (m_nTop == m_nSzie-1); }
	bool isEmpty() const { return (m_nTop == -1); }

private:
	T *m_pCapacity;
	int m_nSzie;
	int m_nTop;	
};

template <class T>
void SeqStack<T>::push(T x)
{
	if (isFull())
	{
		cout << "the stack is full !" << endl;
		return ;
	}
	
	m_pCapacity[++m_nTop] = x;
}

template<class T>
T SeqStack<T>::getTop()
{
	if (isEmpty())
	{
		cout << "the stack is empty !" << endl;
		exit(1);
	}

	return m_pCapacity[m_nTop];
}

template <class T>	
void SeqStack<T>::print()
{
	cout << "<--Bottom--";
	for (int i = 0; i <= m_nTop; ++i)
		cout << m_pCapacity[i] << " ";
	cout << "--Top-->" << endl << endl;
}

template <class T>
T SeqStack<T>::pop()
{
	if (isEmpty())
	{
		cout << "the stack is empty !" << endl;
		exit(1);
	}

	return m_pCapacity[m_nTop--];
}

int main()
{
	SeqStack<int> s(15);

	for (int i = 2; i < 15; i++)
		s.push(i);
	cout << s.getTop() << endl;
	s.pop();
	s.push(99);
	s.print();

	system("pause");
	return 0;
}
#endif

#if 1
template <class T>
class LinkStack
{
public:

};

int main()
{


	return 0;
}
#endif