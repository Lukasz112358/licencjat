#include<iostream>
#include<stdio.h>
#include<time.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#include "field.h"
using namespace std;


long long randomLongLong(long long mod){
    long long candidate = std::abs(rand()); 
    if(mod<=2147483647)return candidate%mod;
    else{
        long long candidate2 = std::abs(((long long)std::rand())%((long long)mod/(long long)2147483648));
        return candidate2*1073741824+candidate;
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
    while(ans <= 2*t)ans *= 2;
    return ans;
}


bool MillerRabinOne(__int128 n, __int128 a){
    if(n==2)return true;
    if(n<2)return false;
    if(n%2==0)return false;
    if(a % n == 1) return true;
    if(a > n) return true;
    __int128 d = n -1;
    __int128 s = 0;
    field::setPstupid(n);
    while(d%2==0){
        d = d/(__int128)2;
        s ++;
    }
    field x(a);
    x ^= d;
    for(int i =0; i< s; i++){
            if(x == (n-1)) return true;
            if(x == 1)return false;
            x ^=2;
    }
    //std::cout<<std::endl<<std::endl;
    return false;
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
    //srand((unsigned int)time(NULL)) ;
    srand(0);
    //std::setSeed(1);
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


