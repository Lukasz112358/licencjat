#include<iostream>
#include<stdio.h>
#include<time.h>
#include<bits/stdc++.h>
#include "field.h"
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
        long long candidate2 = absolutevalue64(((long long)std::rand())%((long long)mod/(long long)2147483648));
        return candidate2*2147483648+candidate;
    } 
    return 0;
}
__int128 random128(__int128 mod){
    long long candidate = randomLongLong(4611686018427387904);
    if(mod<=4611686018427387904)return candidate%mod;
    else{
        __int128 candidate2 = randomLongLong(4611686018427387904)%(mod/4611686018427387904);
        return candidate2*4611686018427387904+candidate;
    } 
    return candidate;
}




__int128 pow2(__int128_t  t){
    __int128_t  ans = 1;
    while(ans <= t)ans *= 2;
    return ans;
}


bool MillerRabinOne(__int128 n, __int128 a){
    if(n==2)return true;
    if(n<2)return false;
    if(n%2==0)return false;
    __int128 d = n -1;
    __int128 s = 0;
    field::setPstupid(n);
    while(d%2==0){
        d = d/(__int128)2;
        s ++;
    }
    field x(a);
    x ^= d;
    field y;
    for(int i =0; i< s; i++){
            y = x*x;
            if(y==1 && x != 1 && x != (n-1)){
                std::cout<<std::endl<<std::endl;
                return false;
            }
            x = y;     
    }
    //std::cout<<std::endl<<std::endl;
    return (y==1);
}
 bool MillerRabin(__int128 n){
    __int128 limit = n-2;
    if(limit > 2*std::log(n)*std::log(n))limit = 2*std::log(n)*std::log(n);
    for(int i =2; i< ((int)limit)+1; i++){
        if(!MillerRabinOne(n,i))return false;
    }
    return true;
 }

__int128 find_prime(__int128  n, __int128  t){
    srand((unsigned int)time(NULL)) ;
    __int128  twotok  = pow2(t);
    __int128  mod = (t+n)*(n+t)*(n+t);
    while (true){
        __int128  candidate = random128(mod);
        if(candidate > t){
            candidate = candidate * twotok + 1;
            //std::cout<<toString(candidate)<<endl;
            if(MillerRabin(candidate)) return candidate;
        }
    }
    return 0;
}


