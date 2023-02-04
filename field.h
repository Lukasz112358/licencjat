#include<iostream>
#include<map>
#include<climits>
//using namespace std;
class field{
    static   long long p;
    static   long long m;
    static field almostPrimitiveRoot;
    static long long odd;
    static long long degreeOfDegree;
    long long value;
public:
    static std::map<  long long,   long long> inverse;
    static void  setEasyThings();
    static void  setAlmostPrimitiveRoot();
    void static setM( long long x){
        m =x;
    }
    long long static getP(){
        return p;
    }
    long long static getM(){
        return m;
    }
    field static getAlmostPrimitiveRoot(){
        return almostPrimitiveRoot;
    }
    long long static getOdd(){
        return odd;
    }
    long long static getDegreeOfDegree(){
        return degreeOfDegree;
    }
    static void setP( long long x);
    static void insertInverse(field a,field b){
        field::inverse[a.value] = b.value;
        field::inverse[b.value] = a.value;
    }
    field(){
        this->value = 0;
    }
    field(  long long val){
        this->value = (val+p)%p;
    }
    /*field(int val){
        this->value = (val+p)%p;
    }*/
    field(field& a){
        this->value = a.value;
    }
    field(const field& a){
        this->value = a.value;
    }
    long long getValue()const{
        return this->value;
    }
    field &operator=(const field &);
    //Post/Pre - Incrementation
    field inline &operator++();
    field inline operator++(int temp);
    field inline &operator--();
    field inline operator--(int temp);
    //Addition and Subtraction
    friend inline field &operator+=(field &, const field &);
    friend inline field operator+(const field &, const field &);
    friend inline field operator-(const  field &, const field &);
    friend inline field &operator-=(field &, const field &);
    //Comparison operators
    friend bool inline operator==(const field &, const field &);
    friend bool inline operator!=(const field &, const field &);
    friend bool inline operator>(const field &, const field &);
    friend bool inline operator>=(const field &, const field &);
    friend bool inline operator<(const field &, const field &);
    friend bool inline operator<=(const field &, const field &);
    //Multiplication and Division
    friend field &operator*=(field &, const field &);
    friend field operator*(const field &, const field &);
    friend field &operator/=(field &, const field &);
    friend field operator/(const field &, const field &);
    //Power Function
    friend field inline &operator ^=(field &,const long long &);
    friend field inline operator^(field &, const long  &);
    //Read and Write
    friend std::ostream &operator<<(std::ostream &,const field &);
    friend std::istream &operator>>(std::istream &, field &);
};
long long field::p = 2;
long long field::m = 1;
long long field::odd = 1;
field field::almostPrimitiveRoot = field(1);
long long field::degreeOfDegree = 0;
std::map<  long long,  long long>field::inverse = std::map<  long long,  long long>();
field &field::operator=(const field &a){
    value = a.value;
    return *this;
}
field &field::operator++(){
    this->value = (value+1)%field::p;
    return *this;
}
field field::operator++(int temp){
    field aux(*this);
    ++(*this);
    return aux;
}
field &field::operator--(){
    this->value = (field::p+value-1)%field::p;
    return *this;
}
field field::operator--(int temp){
    field aux(*this);
    --(*this);
    return aux;
} 
field &operator+=(field &a,const field& b){
    a.value = (a.value+b.value)%field::p;
    return a;
}
field operator+(const field &a, const field &b){
    field temp;
    temp = a;
    temp += b;
    return temp;
}
 
field &operator-=(field&a,const field &b){
    a.value = (a.value-b.value+field::p)%field::p;
    return a;
}
field operator-(const field& a,const field&b){
    field temp;
    temp = a;
    temp -= b;
    return temp;
}
bool operator==(const field &a, const field &b){
    return a.value == b.value;
}
bool operator!=(const field & a,const field &b){
    return !(a == b);
}
bool operator<(const field &a, const field &b){
    return a.value < b.value;
}
bool operator<=(const field & a,const field &b){
    return a.value <= b.value;
}
bool operator>(const field &a, const field &b){
    return a.value > b.value;
}
bool operator>=(const field & a,const field &b){
    return !(a >= b);
}
field &operator*=(field &a, const field &b){
    if(b.getValue() <= field::m) a = field(b.getValue()*a.getValue());
    if(b.getValue() > field::m){
        long long A = a.getValue();
        long long B = b.getValue();
        long long ans1 = (((A*field::m)%field::p)*((long long)(B/field::m)))%field::p;
        long long ans2 = (A*(B%field::m))%field::p;
        a = field((ans1+ans2)%field::p);
    }
    return a;
}
field operator*(const field&a,const field&b){
    field temp;
    temp = a;
    temp *= b;
    return temp;
} 
field &operator^=(field & a, long long const & b){
    long long B = (b%(field::p-1));
    field A(a);
    if(B == 0){
        a  = 1;
    }
    if(B == -1){
        if(a == 0)throw("Arithmetic Error: Division By 0");
        if(field::inverse[a.getValue()] == 0){
            field::insertInverse(a, A^=(( long long)(field::p-2)));
        }
        a = field(field::inverse[a.getValue()]);
    }
    if(B > 1){
        field a0 = a;
        field a1 = a;
        a0^=B/2;
        a1 = a0;
        if(B%2 == 1)a1*=a;
        a = a0*a1;
        return a;
    }
    if(B<-1){
        a^=-1;
        a^=(-B);
    }
    return a;
}
field operator^(field & a, long long b){
    field temp(a);
    temp ^= b;
    return temp;
} 
field &operator/=(field& a,const field &b){
    field B(b.getValue());
    a *= (B^(long long)(-1));
    return a;
}
field operator/(const field &a,const field &b){
    field temp;
    temp = a;
    temp /= b;
    return temp;
} 
std::istream &operator>>(std::istream &in,field&a){
      long long s;
    in >> s;
    a = field(s);
    return in;
}
std::ostream &operator<<(std::ostream &out,const field &a){
    std::cout << a.value;
    return out;
}

void field::setP( long long x){
    field::inverse.clear();
    field::p = x;
    long long y = field::p - 1;
    long long degree = 0;
    while(y % 2 == 0){
        degree++;
        y /= 2;
    }    
    field::odd = y;
    field::degreeOfDegree = degree;
    field z;
    for(int i = 2; i<field::p;i++){
        z = field(i);
        z ^= ((field::p-1)/2);
        if(z.getValue() != 1){
            z = field(i);
            field::almostPrimitiveRoot = z^field::odd;
            break;
        }
    }
    field::setM( LONG_MAX / x );    
} 

