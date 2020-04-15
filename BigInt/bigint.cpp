#include"bigint.h"

ostream& operator<<(ostream &out, const BigInt &bt)
{
	Symbol sign = bt.GetSymbol();
	if(bt!=0 && sign==NEGATIVE)
		cout<<"-";
	for(size_t i=bt.size(); i>=1; --i)
	{
		out<<(int)bt[i];
	}
	return out;
}																																					   

char* BigInt::toString()  const
{
	int size = big.size();
	char *str = (char *)malloc(size + 2);
	memset(str, 0, size + 2);
	int j = 1;

	for (int i = size; i > 0; --i)
	{
		cout << (int)big[i] << " ";
		str[j++] = (int)big[i] + 48;
	}

	if (big.GetSymbol() == POSITIVE)
		str[0] = ' ';
	else
		str[0] = '-';

	str[j] = '\0';

	return str;
}

void BigInt::SetSymbol(Symbol sign)
{
	big.SetSymbol(sign);
}
Symbol BigInt::GetSymbol()const
{
	return (Symbol)big.GetSymbol();
}

BigInt BigInt::Abs(const BigInt &bt)
{
	BigInt tmp = bt;
	tmp.SetSymbol(POSITIVE);
	return tmp;
}

BigInt::BigInt(long value)
{
	SetSymbol(POSITIVE);
	if(value == 0)
	{
		push_back(0);
	}
	else
	{
		if(value < 0)
		{
			SetSymbol(NEGATIVE);
			value = abs(value);
		}
		while(value > 0)
		{
			push_back(value % 10);
			value /= 10;
		}
	}
}

//bt = 123
BigInt& BigInt::operator=(long value)
{
	(*this).clear();
	SetSymbol(POSITIVE);
	if(value == 0)
	{
		push_back(0);
	}
	else
	{
		if(value < 0)
		{
			SetSymbol(NEGATIVE);
			value = abs(value);
		}
		while(value > 0)
		{
			push_back(value % 10);
			value /= 10;
		}
	}
	return *this;
}
/////////////////////////////////////////////////////////
void BigInt::LoadData(size_t sz)
{
	clear();
	srand(time(NULL));
	SetSymbol((Symbol)(rand()%2));
	for(int i=0; i<sz; ++i)
	{
		big.push_back(rand()%10);
	}
	clear_head_zero();
}
void BigInt::PrintData()const
{
	Symbol sign = GetSymbol();
	if(sign == NEGATIVE)
		cout<<"-";

	for(int i=size(); i>=1; --i)
	{
		cout<<(int)big[i];
	}
	cout<<endl;
}
////////////////////////////////////////////////////////////
u_char BigInt::back()const
{
	return big.back();
}
void BigInt::pop_back()
{
	big.pop_back();
}
size_t BigInt::size()const
{return big.size();}
void BigInt::clear()
{big.clear();}
void BigInt::push_back(u_char x)
{
	big.push_back(x);
}
void BigInt::push_front(u_char x)
{
	big.push_front(x);
}
void BigInt::clear_head_zero()
{
	while(size()>1 && (*this).back() == 0)
	{
		pop_back();
	}
}
////////////////////////////////////////////////////////////
u_char& BigInt::operator[](int pos)
{return big[pos];}
const u_char& BigInt::operator[](int pos)const
{return big[pos];}
bool BigInt::operator>(const BigInt &bt)const
{
	if(GetSymbol()==POSITIVE && bt.GetSymbol()==NEGATIVE)
		return true;
	else if(GetSymbol()==NEGATIVE && bt.GetSymbol()==POSITIVE)
		return false;
	if(GetSymbol() == POSITIVE)
	{
		if(size() > bt.size())
			return true;
		else if(size() < bt.size())
			return false;
		
		size_t i = size();
		while(i >= 1)
		{
			if((*this)[i] > bt[i])
				return true;
			else if((*this)[i] < bt[i])
				return false;
			--i;
		}
		return false;
	}

	if(size() > bt.size())
		return false;
	else if(size() < bt.size())
		return true;
	
	size_t i = size();
	while(i >= 1)
	{
		if((*this)[i] > bt[i])
			return false;
		else if((*this)[i] < bt[i])
			return true;
		--i;
	}
	return false;
}
bool BigInt::operator<=(const BigInt &bt)const
{
	return !(*this > bt);
}
bool BigInt::operator<(const BigInt &bt)const
{
	if(GetSymbol()==POSITIVE && bt.GetSymbol()==NEGATIVE)
		return false;
	else if(GetSymbol()==NEGATIVE && bt.GetSymbol()==POSITIVE)
		return true;
	if(GetSymbol() == POSITIVE)
	{
		if(size() < bt.size())
			return true;
		else if(size() > bt.size())
			return false;
		
		size_t i = size();
		while(i >= 1)
		{
			if((*this)[i] < bt[i])
				return true;
			else if((*this)[i] > bt[i])
				return false;
			--i;
		}
		return false;
	}

	if(size() < bt.size())
		return false;
	else if(size() > bt.size())
		return true;
	
	size_t i = size();
	while(i >= 1)
	{
		if((*this)[i] < bt[i])
			return false;
		else if((*this)[i] > bt[i])
			return true;
		--i;
	}
	return false;
}
bool BigInt::operator>=(const BigInt &bt)const
{
	return !(*this < bt);
}
	
bool BigInt::operator==(const BigInt &bt)const
{
	//预防-0情况
	if((GetSymbol()!=bt.GetSymbol()) && size()==1 && big[1]==0 && bt[1]==0)
		return true;
	
	if(GetSymbol() != bt.GetSymbol())
		return false;

	if(size() != bt.size())
		return false;
	size_t i = 1;
	while(i <= size())
	{
		if((*this)[i] != bt[i])
			return false;
		++i;
	}
	return true;
}
bool BigInt::operator==(long x)const
{
	BigInt tmp(x);
	return (*this==tmp);
}
bool BigInt::operator!=(const BigInt &bt)const
{
	return !(*this == bt);
}
bool BigInt::operator!=(long x)const
{
	return !(*this==x);
}

////////////////////////////////////////////////////////////
BigInt& BigInt::operator++()
{
	u_char sign = 1;
	size_t i = 1;
	if(GetSymbol() == POSITIVE)
	{
		while(sign>0 && i<=size())
		{
			(*this)[i] = AddItem((*this)[i], 0, sign);
			++i;
		}
		if(sign > 0)
			push_back(sign);
	}
	else
	{
		while(sign>0 && i<=size())
		{
			(*this)[i] = SubItem((*this)[i], 0, sign);
			++i;
		}    
		if(*this == 0)               //除去-0的符号 
			SetSymbol(POSITIVE);
	}
	clear_head_zero();
	return *this;
}
BigInt BigInt::operator++(int)
{
	BigInt tmp = (*this);
	++(*this);
	return tmp;
}
BigInt& BigInt::operator--()
{
	if(*this == 0)
	{
		*this = 1;
		SetSymbol(NEGATIVE);
		return *this;
	}

	u_char sign = 1;
	size_t i = 1;
	if(GetSymbol() == POSITIVE)
	{
		while(sign>0 && i<=size())
		{
			(*this)[i] = SubItem((*this)[i], 0, sign);
			++i;
		}
	}
	else
	{
		while(sign>0 && i<=size())
		{
			(*this)[i] = AddItem((*this)[i], 0, sign);
			++i;
		}
		if(sign > 0)
			push_back(sign);
	}
	clear_head_zero();
	return *this;
}
BigInt BigInt::operator--(int)
{
	BigInt tmp = *this;
	--(*this);
	return tmp;
}

BigInt& BigInt::operator+=(const BigInt &bt)
{
	if(GetSymbol() == bt.GetSymbol())
	{
		u_char sign = 0;
		size_t i=1,j=1;
		while(i<=size() && j<=bt.size())
		{
			(*this)[i] = AddItem((*this)[i], bt[j], sign);
			++i;
			++j;
		}
		while(sign>0 && i<=size())
		{
			(*this)[i] = AddItem((*this)[i], 0, sign);
			++i;
		}
		if(sign > 0)
			push_back(sign);
	}
	else
	{
		if(Abs(*this) > Abs(bt))
		{
			u_char sign = 0;
			size_t i=1, j=1;
			while(i<=size() && j<=bt.size())
			{
				(*this)[i] = SubItem((*this)[i], bt[j], sign);
				++i;
				++j;
			}
			while(sign>0 && i<=size())
			{
				(*this)[i] = SubItem((*this)[i], 0, sign);
				++i;
			}
		}
		else if(Abs(*this) < Abs(bt))
		{
			u_char sign = 0;
			size_t i=1, j=1;
			while(i<=size() && j<=bt.size())
			{
				(*this)[i] = SubItem(bt[j], (*this)[i], sign);
				++i;
				++j;
			}
			while(sign>0 && j<=size())
			{
				//(*this)[i] = SubItem((*this)[i], 0, sign);
				//++i;
				u_char sub = SubItem(bt[j], 0, sign);
				push_back(sub);
				++j;
			}
		}
		else
		{
			*this = 0;
			SetSymbol(POSITIVE);
		}
	}
	clear_head_zero();
	return *this;
}
BigInt& BigInt::operator-=(const BigInt &bt)
{
	if(GetSymbol() == bt.GetSymbol())
	{
		if(Abs(*this) > Abs(bt))
		{
			u_char sign = 0;
			size_t i=1, j=1;
			while(i<=size() && j<=bt.size())
			{
				(*this)[i] = SubItem((*this)[i], bt[j], sign);
				++i;
				++j;
			}
			while(sign>0 && i<=size())
			{
				(*this)[i] = SubItem((*this)[i], 0, sign);
				++i;
			}
		}
		else if(Abs(*this) < Abs(bt))
		{
			u_char sign = 0;
			size_t i=1, j=1;
			while(i<=size() && j<=bt.size())
			{
				(*this)[i] = SubItem(bt[j], (*this)[i], sign);
				++i;
				++j;
			}
			while(sign>0 && j<=size())
			{
				u_char sub = SubItem(bt[j], 0, sign);
				push_back(sub);
				++j;
			}
		}
		else
		{
			*this = 0;
			SetSymbol(POSITIVE);
		}
	}
	else
	{
		u_char sign = 0;
		size_t i=1,j=1;
		while(i<=size() && j<=bt.size())
		{
			(*this)[i] = AddItem((*this)[i], bt[j], sign);
			++i;
			++j;
		}
		while(sign>0 && i<=size())
		{
			(*this)[i] = AddItem((*this)[i], 0, sign);
			++i;
		}
		if(sign > 0)
			push_back(sign);
	}
	clear_head_zero();
	return *this;	
}
BigInt& BigInt::operator*=(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mul(tmp, *this, bt);
	*this = tmp;
	return *this;
}
BigInt& BigInt::operator/=(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Div(tmp, *this, bt);
	*this = tmp;
	return *this;
}
BigInt& BigInt::operator%=(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mod(tmp, *this, bt);
	*this = tmp;
	return *this;
}
////////////////////////////////////////////////////////////
BigInt BigInt::operator+(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Add(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator-(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Sub(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator*(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mul(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator/(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Div(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator%(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mod(tmp, *this, bt);
	return tmp;
}
////////////////////////////////////////////////////////////
BigInt BigInt::operator/(u_long x)
{
	BigInt tmp(x);
	return *this / tmp;
}
////////////////////////////////////////////////////////////
bool BigInt::operator&(u_long x)
{
	BigInt tmp(2);
    BigInt ans = (*this) % tmp;
	return ans != 0;
}
////////////////////////////////////////////////////////////
u_char BigInt::AddItem(u_char a, u_char b, u_char &sign)
{
	u_char sum = a + b + sign;
	if(sum >= 10)
	{
		sum -= 10;
		sign = 1;
	}
	else
		sign = 0;
	return sum;
}
void BigInt::Add(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	bt.clear();
	if(bt1.GetSymbol() == bt2.GetSymbol())
	{
		u_char sum, sign = 0;
		size_t i=1, j=1;
		while(i<=bt1.size() && j<=bt2.size())
		{
			sum = AddItem(bt1[i],bt2[j],sign);
			bt.push_back(sum);
			++i;
			++j;
		}
		while(i <= bt1.size())
		{
			sum = AddItem(bt1[i], 0, sign);
			bt.push_back(sum);
			++i;
		}
		while(j <= bt2.size())
		{
			sum = AddItem(0, bt2[j], sign);
			bt.push_back(sum);
			++j;
		}
		if(sign > 0)
			bt.push_back(sign);

		bt.SetSymbol(bt1.GetSymbol());
	}
	else
	{
		if(bt1.size()>bt2.size())
		{
			u_char sub, sign = 0;
			size_t i=1, j=1;
			while(i<=bt1.size() && j<=bt2.size())
			{
				sub = SubItem(bt1[i], bt2[j], sign);
				bt.push_back(sub);
				++i;
				++j;
			}
			while(i<=bt1.size())
			{
				sub = SubItem(bt1[i], 0, sign);
				bt.push_back(sub);
				++i;
			}
			bt.clear_head_zero();
			bt.SetSymbol(bt1.GetSymbol());
		}
		else if(bt1.size() < bt2.size())
		{
			u_char sub, sign = 0;
			size_t i=1, j=1;
			while(i<=bt1.size() && j<=bt2.size())
			{
				sub = SubItem(bt2[j], bt1[i], sign);
				bt.push_back(sub);
				++i;
				++j;
			}
			while(j<=bt2.size())
			{
				sub = SubItem(bt2[j], 0, sign);
				bt.push_back(sub);
				++j;
			}
			bt.clear_head_zero();
			bt.SetSymbol(bt.GetSymbol());
		}
		else
		{
			if(Abs(bt1) > Abs(bt2))
			{
				u_char sub, sign = 0;
				size_t i=1, j=1;
				while(i<=bt1.size() && j<=bt2.size())
				{
					sub = SubItem(bt1[i], bt2[j], sign);
					bt.push_back(sub);
					++i;
					++j;
				}
				bt.SetSymbol(bt1.GetSymbol());
			}
			else if(Abs(bt1) < Abs(bt2))
			{
				u_char sub, sign = 0;
				size_t i=1, j=1;
				while(i<=bt1.size() && j<=bt2.size())
				{
					sub = SubItem(bt2[j], bt1[i], sign);
					bt.push_back(sub);
					++i;
					++j;
				}
				bt.SetSymbol(bt2.GetSymbol());
			}
			else
			{
				bt = 0;
				bt.SetSymbol(POSITIVE);
			}
		}
	}
}
u_char BigInt::SubItem(u_char a, u_char b, u_char &sign)
{
	u_char sub;
	if(a >= b+sign)
	{
		sub = a - b - sign;
		sign = 0;
	}
	else
	{
		sub = a + 10 - b - sign;
		sign = 1;
	}
	return sub;
}
void BigInt::Sub(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	bt.clear();
	if(bt1 == bt2)
	{
		bt = 0;
		return;
	}

	if(bt1.GetSymbol() == bt2.GetSymbol()) //符号相同直接相减
	{
		if(bt1 > bt2)
		{
			if(bt1.GetSymbol()== POSITIVE)
			{
				u_char sub, sign = 0;
				size_t i=1, j=1;
				while(i<=bt1.size() && j<=bt2.size())
				{
					sub = SubItem(bt1[i], bt2[j], sign);
					bt.push_back(sub);
					++i;
					++j;
				}
				while(i<=bt1.size())
				{
					sub = SubItem(bt1[i], 0, sign);
					bt.push_back(sub);
					++i;
				}
				bt.clear_head_zero();
				bt.SetSymbol(bt1.GetSymbol());
			}
			else
			{
				u_char sub, sign = 0;
				size_t i=1, j=1;
				while(i<=bt1.size() && j<=bt2.size())
				{
					sub = SubItem(bt2[j], bt1[i], sign);
					bt.push_back(sub);
					++i;
					++j;
				}
				while(j<=bt2.size())
				{
					sub = SubItem(bt2[j], 0, sign);
					bt.push_back(sub);
					++j;
				}
				bt.clear_head_zero();
				if(bt2.GetSymbol() == POSITIVE)
					bt.SetSymbol(NEGATIVE);
				else
					bt.SetSymbol(POSITIVE);
			}
		}
		else
		{
			if(bt1.GetSymbol() == POSITIVE)
			{
				u_char sub, sign = 0;
				size_t i=1, j=1;
				while(i<=bt1.size() && j<=bt2.size())
				{
					sub = SubItem(bt2[j], bt1[i], sign);
					bt.push_back(sub);
					++i;
					++j;
				}
				while(j<=bt2.size())
				{
					sub = SubItem(bt2[j], 0, sign);
					bt.push_back(sub);
					++j;
				}
				bt.clear_head_zero();
				if(bt2.GetSymbol() == POSITIVE)
					bt.SetSymbol(NEGATIVE);
				else
					bt.SetSymbol(POSITIVE);
			}
			else
			{
				u_char sub, sign = 0;
				size_t i=1, j=1;
				while(i<=bt1.size() && j<=bt2.size())
				{
					sub = SubItem(bt1[i], bt2[j], sign);
					bt.push_back(sub);
					++i;
					++j;
				}
				while(i<=bt1.size())
				{
					sub = SubItem(bt1[i], 0, sign);
					bt.push_back(sub);
					++i;
				}
				bt.clear_head_zero();
				bt.SetSymbol(bt1.GetSymbol());
			}
		}
	}
	else
	{
		BigInt::Add(bt, Abs(bt1), Abs(bt2));
		if(bt1.GetSymbol() == POSITIVE)
			bt.SetSymbol(POSITIVE);
		else
			bt.SetSymbol(NEGATIVE);
	}
}

void BigInt::MulItem(BigInt &bt, const BigInt &bt1, u_char x)
{
	bt.clear();
	u_char mul, sign = 0;
	size_t i = 1;
	while(i <= bt1.size())
	{
		mul = bt1[i] * x + sign;
		if(mul >= 10)
		{
			sign = mul / 10;
			mul %= 10;
		}
		else
			sign = 0;
		bt.push_back(mul);
		++i;
	}
	if(sign > 0)
		bt.push_back(sign);
}
void BigInt::AddMove(BigInt &bt, const BigInt &bt1, int offset)
{
	size_t i=offset, j=1;
	u_char sign = 0;
	while(i<=bt.size() && j<=bt1.size())
	{
		bt[i] = AddItem(bt[i], bt1[j], sign);
		++i;
		++j;
	}
	while(i<=bt.size())
	{
		bt[i] = AddItem(bt[i], 0, sign);
		++i;
	}
	while(j<=bt1.size())
	{
		u_char sum = AddItem(0, bt1[j], sign);
		bt.push_back(sum);
		++j;
	}
	if(sign > 0)
		bt.push_back(sign);
}
void BigInt::Mul(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if(bt1==0 || bt2==0)
	{
		bt = 0;
		return;
	}
	bt = 0;
	BigInt tmp;
	for(size_t i=1; i<=bt2.size(); ++i)
	{
		tmp.clear();
		MulItem(tmp, bt1, bt2[i]);
		AddMove(bt, tmp, i);
	}
	if(bt1.GetSymbol() == bt2.GetSymbol())
		bt.SetSymbol(POSITIVE);
	else
		bt.SetSymbol(NEGATIVE);
}
void BigInt::Div(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	assert(bt2 != 0);
	if(Abs(bt1) < Abs(bt2))
	{
		bt = 0;
		return;
	}
	else if(Abs(bt1) == Abs(bt2))
	{
		bt = 1;
		if(bt1.GetSymbol() == bt2.GetSymbol())
			bt.SetSymbol(POSITIVE);
		else
			bt.SetSymbol(NEGATIVE);
		return;
	}

	size_t bt1_len = bt1.size();
	size_t bt2_len = bt2.size();
	int k = bt1_len - bt2_len;

	BigInt btd;
	btd.clear();
	for(size_t i=1; i<=bt2_len; ++i)
	{
		btd.push_back(bt1[k+i]);
	}

	BigInt tmp = Abs(bt2); //比较btd>=tmp时,不带符号比较
	u_char div = 0;
	while(k >= 0)
	{
		//while(btd >= bt2)
		while(btd >= tmp)
		{
			//btd -= bt2;
			btd -= tmp;
			++div;
			btd.clear_head_zero();
		}
		bt.push_front(div);
		if(k > 0)
			btd.push_front(bt1[k]);
		div = 0;
		--k;
	}
	bt.clear_head_zero();
	if(bt1.GetSymbol() == bt2.GetSymbol())
		bt.SetSymbol(POSITIVE);
	else
		bt.SetSymbol(NEGATIVE);
}
void BigInt::Mod(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if(Abs(bt1) < Abs(bt2))
	{
		bt = bt1;
		return;
	}
	else if(bt1 == bt2)
	{
		bt = 0;
		return;
	}
	size_t bt1_len = bt1.size();
	size_t bt2_len = bt2.size();
	int k = bt1_len - bt2_len;

	BigInt btd;
	btd.clear();
	for(size_t i=1; i<=bt2_len; ++i)
	{
		btd.push_back(bt1[k+i]);
	}

	BigInt tmp = Abs(bt2);
	while(k >= 0)
	{
		//while(btd >= bt2)
		while(btd >= tmp)
		{
			//btd -= bt2;
			btd -= tmp;
			btd.clear_head_zero();
		}
		if(k > 0)
			btd.push_front(bt1[k]);
		--k;
	}
	bt = btd;
	bt.SetSymbol(bt1.GetSymbol());
	bt.clear_head_zero();
}
void BigInt::Square(BigInt &bt,const BigInt &bt1)
{
	BigInt::Mul(bt, bt1, bt1);
}
void  BigInt::Power(BigInt &bt, const BigInt &bt1, u_long n)
{
	bt = 1;
	for(u_long i=0; i<n; ++i)
	{
		bt *= bt1;
	}
}
void BigInt::Power(BigInt &bt, const BigInt &bt1,const BigInt &bt2)
{
	bt = 1;
	for(BigInt i=0; i<bt2; ++i)
	{
		bt *= bt1;
	}
}

void BigInt::PowMod(BigInt &bt,  BigInt a, BigInt b, const BigInt &n)
{
	BigInt ans = 1;
	a %= n;
	while(b != 0)
	{
		if(b & 1)
		{
			ans = (ans*a) % n;
		}
		a = (a * a) % n;
		b = b / 2;
	}
	bt = ans;
}

/*

void BigInt::PowMod(BigInt &bt, BigInt a, BigInt b, const BigInt &n)
{
	BigInt tmp;
	BigInt::Power(tmp, a, b);
	BigInt::Mod(bt, tmp, n);
}
*/
