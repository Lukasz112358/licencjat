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
#include"field.h"
#include"fourier.cpp"
#include"find_prime.cpp"


//using namespace std;

std::vector<field>& compute(__int128 l, __int128 r, std::vector<field>& g, std::vector<field>& f){
    std::cout<<toString(l)<<' '<<toString(r)<<std::endl;
    if(l < r){
        __int128 m = (l+r)/2;
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
    //std::cout<<"returned";
    return g;
}

std::vector<field> mainCompute(std::vector<field>& f){
    std::vector<field> g(f.size(),0);
    g[0] = 1;
    return compute(0,f.size()-1,g,f);
}



std::vector<field> B(std::vector<field> s, __int128 t){
    std::vector<field> a(t+1,field(0));
    std::vector<field> ans(t+1,field(0));
    int K;
    for(int i =0; i<s.size(); i++){
        if(s[i].getValue()<=t)a[s[i].getValue()] ++;
    }
    for(__int128 k = 1; k <= t; k++){
        std::cout<<toString(k)<<std::endl;
        for(__int128 j = 1; j <= t/k ; j++){
            if(j%100==0)std::cout<<toString(j)<<std::endl;
            //std::cout<<toString(k*j)<<std::endl;
            field x = field(-1);
            ans[k*j] = ans[k*j] + a[k]*(x^(j-1))/field(j);
        }
    }
    return ans;
}

std::vector<bool> JinWu(std::vector<field>& s, __int128 t){
    __int128 p  = find_prime(s.size(), t);
    //std::cout <<"x"<< toString(p)<<"x"<<std::endl;
    field::setP(p);
    std::vector<field> Bans(t+1,field(0));
    Bans= B(s,t) ;
    std::vector<field> computeAns = mainCompute(Bans);
    std::vector<bool>ans(t+1,false);
    for(int i =0; i< t+1; i++){
        if(computeAns[i].getValue() != 0)ans[i]=true;
    }
    return ans;

}

std::bitset<1000000> brutal(vector<__int128>& s){
    std::bitset<1000000>ans;
    ans[0]=true;
    for(int i = 0; i < s.size(); i++){
        ans = ans|(ans<<s[i]);
    }
    return ans;    
}


int main() {

    __int128 n,t;
    std::string sn,st;
    std::cin>>sn>>st;
    n = fromString(sn);
    t = fromString(st);
    __int128 p  = find_prime(n, t);
    field::setP(p);
    vector<field>S(n,0);
    std::string s;
    for(int i = 0; i < n; i++){
        std::cin>>s;
        S[i] = field(fromString(s));
    }
    std::vector<bool>ans(t+1,false);
    ans =  JinWu(S,t);
    std::cout<<"xx"<<std::endl;
    for(int i=0; i<ans.size();i++){
        std::cout<<ans[i]<<std::endl;
    }
    //std::cout<<"xx"<<ans.size();
    /*std::bitset<10000000>ans = brutal(x);
    for(int i=0;i<100;i++){
        std::cout<<ans[i];
        if(i%10==9)std::cout<<std::endl;
    }*/
    return  0;
}
