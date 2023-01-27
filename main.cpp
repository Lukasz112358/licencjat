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
#include"furier.h"


typedef long long int LL;

LL p = 7340033;//7 * 2^20 + 1
LL psemilog2 = 20;
LL pr = 2187;//(pr^n)%p = 1<=>2^psemilog|n 
vector<field> compute(field l, field r, vector<field>& g, vector<field>& f){
    cout<<l<<' '<<r<<endl;
    if(l < r){
        LL m = (l+r)/2;
        compute(l,m,g,f);
        vector<LL>F(r-l+1);
        vector<LL>G(m-l+1);
        for(int i = 0; i < r-l+1; i++){
            F[i] = i*f[i];
        }
        for(int i = 0; i < m-l+1; i++){
            G[i] = g[i+l];
        }
        vector<LL>H = multiplication(F,G);
        for(int i=(int)(m+1);i<r+1;i++){
            g[i]= add(g[i],div1(H[i-l],i));
        }
        compute(m+1,r,g,f);
    }
    return g;
}

vector<LL> mainCompute(LL t, vector<field>& f){
    vector<LL> g(t+1,0);
    g[0] = 1;
    return compute(0,t,g,f);
}



vector<LL> B(vector<LL>& s, LL n, LL t, vector<LL> ans){
    vector<LL> a(t+1);
    for(int i =0; i<n; i++){
        if(s[i]<=t)a[s[i]] ++;
    }
    for(LL k = 1; k <= t; k++){
        cout << k<<endl;
        for(LL j = 1; j <= t/k ; j++){
            ans[k*j] = add(ans[k*j] , div1(mul(a[k],power((-1),j-1)),j));
        }
    }
    return ans;
}

vector<LL> final(vector<LL>& s,LL n, LL t){
    vector<LL> Bans(t+1) = B(s,n,t,Bans) ;
    vector<LL> computeAns = mainCompute(t,Bans);
    return computeAns;
}


int main() {
    test();
    return  0;
}
