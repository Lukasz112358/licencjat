#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
long long absolutevalue64(long long a){
    if(a < 0)return -a;
    return a;
}
__int128 absolutevalue128(__int128 a){
    if(a < 0)return -a;
    return a;
}


long long randomLongLong(long long mod){
    long long candidate = absolutevalue64(rand()); 
    if(mod<=2147483647)return candidate%mod;
    else{
        long long candidate2 = absolutevalue64(std::rand()%(mod/2147483648));
        return candidate2*2147483648+candidate;
    } 
    return 0;
}
__int128 random128(__int128 mod){
    long long candidate = randomLongLong(9223372036854775807);
    if(mod<=9223372036854775807)return candidate%mod;
    else{
        long long candidate2 = randomLongLong(9223372036854775807)%(mod/9223372036854775807);
        return candidate2*9223372036854775807+candidate;
    } 
    return 0;
}




__int128 pow2(__int128_t  t){
    __int128_t  ans = 1;
    while(ans <= t)ans *= 2;
    return ans;
}

bool is_prime(__int128_t  x){
    if(x <= 1) return false;
    if(x==2) return true;
    if(x%2 == 0) return false;
    __int128_t  i = 3;
    while(i*i <= x){
        if(x % i == 0){ 
            return false;
        }
        i+=2;
    }
    return true;
    
}

__int128_t  find_prime(__int128_t  n, __int128_t  t){
    srand((unsigned int)time(NULL)) ;
    __int128_t  twotok  = pow2(t);
    __int128_t  mod = (t+n)*(n+t)*(n+t);
    while (true){
        __int128_t  candidate = random128(mod);
        if(candidate > t){
            candidate = candidate * twotok + 1;
            if(is_prime(candidate) == true) return candidate;
        }
    }
    return 0;
}
std::string toStringOneNumber(__int128 x){
    if(x % 10 == 0)return "0" ;
	if(x % 10 == 1)return "1" ;
	if(x % 10 == 2)return "2" ;
	if(x % 10 == 3)return "3" ;
	if(x % 10 == 4)return "4" ;
	if(x % 10 == 5)return "5" ;
	if(x % 10 == 6)return "6" ;
	if(x % 10 == 7)return "7" ;
	if(x % 10 == 8)return "8" ;
	return "9" ;
}
__int128 charToDigit(char x){
    if(x == '0')return 0;
	if(x == '1')return 1;
	if(x == '2')return 2;
	if(x == '3')return 3;
	if(x == '4')return 4;
	if(x == '5')return 5;
	if(x == '6')return 6;
	if(x == '7')return 7;
	if(x == '8')return 8;
	return 9 ;
}



std::string toString(__int128 x){
    if(x == 0)return "0";
	std::string ans = "";
	bool minus=false;
	if(x<0){
		minus=true;
		x = -x;
	}
	while(x != 0){
		ans = toStringOneNumber(x)+ans;
		x /=10;
	}
	if(minus)ans="-"+ans;
	return ans;
}
__int128 fromString(std::string x){
	__int128 ans = 0;
	__int128 multiplier = 1;
	for(int i = x.size()-1;i>-1;i--){
		if(x[i]=='-')return -ans;
		ans+=charToDigit(x[i])*multiplier;
		multiplier*=10;
	}
	return ans;
}

int main(){
    std::cout<<toString(find_prime(100000,10000000000));
}
