#include<iostream>
#include<bitset>
using namespace std;

bitset<1000> brutalSum(long long * s, long long n,long long t){
    if(n == 0){
        bitset<1000>ans = bitset<1000>();
        ans.set(0,1);
        return ans;
    }
    else{
        bitset<1000> ans = brutal(s, n-1,t);
        return (ans|(ans<<s[n-1]));
    }
    
}
int main(){
    long long * s = new long long[5];
    s[0] = 2;
    s[1] = 3;
    s[2] = 9;
    s[3] = 27;
    s[4] = 81;
    bitset<1000>ans = bitset<1000>();
    ans.set(0,1);
    return 0;
}  