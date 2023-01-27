#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
long long absolutevalue(long long a){
    if(a < 0)return -a;
    return a;
}

long long randomLongLong(long long mod){
    long long candidate = absolutevalue(rand()); 
    if(mod<=2147483647)return candidate%mod;
    else{
        long long candidate2 = absolutevalue(std::rand()%(mod/2147483648));
        return candidate2*2147483648+candidate;
    } 
    return 0;
}
long long pow2(long long t){
    long long ans = 1;
    while(ans <= t)ans *= 2;
    return ans;
}

bool is_prime(long long x){
    if(x <= 1) return false;
    if(x==2) return true;
    if(x%2 == 0) return false;
    long long i = 3;
    while(i*i <= x){
        if(x % i == 0){ 
            return false;
        }
        i+=2;
    }
    return true;
    
}

long long find_prime(long long n, long long t){
    srand((unsigned int)time(NULL)) ;
    long long twotok  = pow2(t);
    long long mod = (t+n)*(n+t)*(n+t);
    while (true){
        long long candidate = absolutevalue(randomLongLong(mod));
        if(candidate > t){
            candidate = candidate * twotok + 1;
            if(is_prime(candidate) == true) return candidate;
        }
    }
    return 0;
}

