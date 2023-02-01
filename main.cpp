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

//using namespace std;

std::vector<field> compute(long long l, long long r, std::vector<field>& g, std::vector<field>& f){
    std::cout<<l<<' '<<r<<std::endl;
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



std::vector<field> B(std::vector<field>& s, long long t, std::vector<field> ans){
    std::vector<field> a(t+1);
    for(int j=0;j<1000;j++)std::cout<<a[0];
    for(int i =0; i<ans.size(); i++){
        for(int j=0;j<1000;j++)std::cout<<i;
        if(s[i]<=t)a[s[i].getValue()] ++;
    }
    for(int i =0; i<10000;i++)std::cout << i<<std::endl;
    for(long long k = 1; k <= t; k++){
        std::cout << k<<std::endl;
        for(long long j = 1; j <= t/k ; j++){
            field x = field(-1);
            ans[k*j] = ans[k*j] + a[k]*(x^(j-1))/field(j);
        }
    }
    return ans;
}

std::vector<field> JinWu(std::vector<field>& s, long long t){
    std::vector<field> Bans(t+1);
    Bans= B(s,t,Bans) ;
    std::vector<field> computeAns = mainCompute(t,Bans);
    return computeAns;

}



int main() {
    std::vector<field>S(5,0);
    S[0]=3;
    S[1]=112;
    std::cout<<JinWu(S,15)[3]<<true;
    return  0;
}
