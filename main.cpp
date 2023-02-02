#include<complex>
#include<cmath>
#include<cstdio>
#include<stdlib.h>
#include<cstring>
#include<iostream>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<cassert>
//#include"field.h"
#include"fourier.h"
#include"find_prime.h"

//using namespace std;

std::vector<field>& compute(long long l, long long r, std::vector<field>& g, std::vector<field>& f){
    std::cout<<"AA"<<l<<' '<<r<<std::endl;
    if(l < r){
        long long m = (l+r)/2;
        compute(l,m,g,f);
        std::vector<field>F(r-l+1);
        std::vector<field>G(m-l+1);
        for(int i = 0; i < r-l+1; i++){
            F[i] = i*f[i];
        }
        for(int i = 0; i < m-l+1; i++){
            G[i] = g[i+l];
        }
        std::vector<field>H = multiplication(F,G);
        for(int i=(int)(m+1);i<r+1;i++){
            g[i]= g[i]+(H[i-l]/i);
        }
        compute(m+1,r,g,f);
    }
    return g;
}

std::vector<field> mainCompute(long long t, std::vector<field>& f){
    std::vector<field> g(t+1,0);
    g[0] = 1;
    return compute(0,t,g,f);
}



std::vector<field> B(std::vector<field> s, long long t, std::vector<field>& ans){
    std::vector<field> a(t+1,field(0));
    int K;
    for(int i =0; i<s.size(); i++){
        //std::cin >> K;
        std::cout << "BB"<< i<<" "<<s[i].getValue()<<endl;
        if(s[i].getValue()<=t)a[s[i].getValue()] ++;
    }
    for(long long k = 1; k <= t; k++){
        //std::cout << k<<std::endl;
        for(long long j = 1; j <= t/k ; j++){
            field x = field(-1);
            ans[k*j] = ans[k*j] + a[k]*(x^(j-1))/field(j);
        }
    }
    return ans;
}

std::vector<field> JinWu(std::vector<field>& s, long long t){
    long long p  = find_prime(s.size(), t);
    field::setP(p);
    std::vector<field> Bans(t+1);
    Bans= B(s,t,Bans) ;
    std::cout<<"OOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKK";
    std::vector<field> computeAns = mainCompute(t,Bans);
    return computeAns;

}



int main() {
    long long n,t;
    std::cin>>n>>t;
    vector<field>S(n);
    for(int i = 0; i < n; i++)std::cin>>S[i];
    for(int i = 0; i < n; i++)std::cout<<S[i]<<endl;
    JinWu(S,t);
    return  0;
}
