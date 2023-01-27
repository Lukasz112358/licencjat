#include "field.h"
#include<iostream>
#include<string.h>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<time.h>
#include<stack>

const int mod = 7340033;

field enoughGoodRoot(long long k){
    long long powerof2 = 1;
    while(((field::p - 1)/powerof2 )%2 ==0){
        powerof2 *= 2;
    }
    long long odd = (field::p - 1) / powerof2;
    while(true){
        field candidate = field(rand());
        candidate ^= odd;
        field copy = candidate;
        long long funnyLog = 0;
        while(copy.getValue() != 1){
            funnyLog += 1;
            copy *= copy;
        }
        if(funnyLog >= k){
            //std::cout<<"("<<funnyLog<<")";
            for(long long i = 0; i < funnyLog-k; i++){
                candidate *= candidate;
            }
            field y = candidate^((long long)(32768));
            return candidate;    
        
        }
        
    }
    return field(0);
}

std::string binary(long long x){
    std::string ans = "";
    for(int i = 0; i <64;i++){
        if(x%2 == 0)ans = "0" + ans;
        if((x%2)*(x%2) == 1)ans = "1" + ans;
        x = x>>1;
    }
    return ans;
}


long long reverseBits(long long x, long long n) {
    x = ((x & 0x5555555555555555) << 1)  | ((x & 0xAAAAAAAAAAAAAAAA) >> 1);  
    x = ((x & 0x3333333333333333) << 2)  | ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
    x = ((x & 0x0F0F0F0F0F0F0F0F) << 4)  | ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
    x = ((x & 0x00FF00FF00FF00FF) << 8)  | ((x & 0xFF00FF00FF00FF00) >> 8);
    x = ((x & 0x0000FFFF0000FFFF) << 16) | ((x & 0xFFFF0000FFFF0000) >> 16);
    x = ((x & 0x00000000FFFFFFFF) << 32) | ((x & 0xFFFFFFFF00000000) >> 32);
    x = ((unsigned long long)x)>>(64-n);
    return x;
}

void setToDo(std::vector<field>&coefficients, long long size){
    //std::cout << std::endl <<std::endl;
    long long length = coefficients.size();
    long long log = 0;
    long long s = size;
    while(s > 1){
        s /= 2;
        log +=1;
    }
    for(long long i = 0; i < size - length; i++){
        coefficients.push_back(field(0));
    }
    for(long long i = 0; i < size; i++){
        long long j = reverseBits(i,log);
        if(j>i){
            field a = coefficients[i];
            coefficients[i] = coefficients[j];
            coefficients[j] = a;
        }
    }
}
long long log(long long x){
    long long ans = 0;
    while(x!=0){
        x /=2;
        ans ++;
    }
    return ans - 1;
}


field stupidEvaluation(std::vector<field>&coefficients,field x){
    field ans = 0;
    field xToPower = 1;
    for(size_t i =0;i<coefficients.size();i++){
        ans += coefficients[i]*xToPower;
        xToPower *= x;   
    }
    return ans;
}


std::vector<field> stupidEvaluationComplete(std::vector<field>&coefficients,field x){
    std::vector<field>ans(coefficients.size());
    field xToPower = 1;
    for(size_t i =0; i<coefficients.size(); i++){
        ans[i]=stupidEvaluation(coefficients,xToPower);
        xToPower *= x;    
    }
    return ans;    
}
std::vector<field> copy(std::vector<field> x){
    std::vector<field> ans(x.size());
    for(size_t i = 0; i<x.size(); i++){
        ans[i] = x[i];
    }
    return ans;
}
void inline DFT(std::vector<field>&coefficients, long long size, field omegaM){
    std::vector<field>useLater = copy(coefficients);
    setToDo(coefficients,size);
    field omegaMLater = omegaM;
    field useLaterM = omegaM;
    std::stack<field> omegasM;
    while(omegaM != 1){
        omegasM.push(omegaM);
        omegaM *= omegaM;
    }
    long long m = 1;
    while(!omegasM.empty()){   
        field currentOmegaM= omegasM.top();
        std::cout<<std::endl;
        omegasM.pop();
        field omega = 1;
        m*=2;
        std::cout<<m;
        for(long long j = 0; j<m/2;j+=1){
            for(long long k = j; k<size; k+=m){
                field t = omega * coefficients[k+m/2];
                field u = coefficients[k];
                coefficients[k] = u+t;
                coefficients[k+m/2] =  u - t;
            }
            omega *= currentOmegaM;
        }
    }
}


std::vector<field>multiplication(std::vector<field> A, std::vector<field> B){
    long long size = 1;
    while(size < (long long)((A.size() + B.size()) -1 )){
        size *= 2;
    }
    long long l = log(size);
    field omegaM = enoughGoodRoot(l);
    DFT(A,size,omegaM);  
    DFT(B,size,omegaM);
    for(long long i=0;i<size;i++){
        A[i] = B[i] * A[i]; 
    }
    omegaM = field(1)/omegaM;
    DFT(A,size,omegaM);
    for(long long i=0;i<size;i++){
        A[i] /= field(size);
    }
    return A;
}

std::vector<field> randomVector(int size){
    std::vector<field>ans(size);
    for(int i=0;i<size;i++){
        ans[i] = i;//field(rand());
    }
    return ans;
}

std::vector<field>stupidMultiplication(std::vector<field> A, std::vector<field> B){
    long long size = 1;
    while(size < (long long)((A.size() + B.size()) -1 )){
        size *= 2;
    }
    std::vector<field>ans(size);
    for(int i = 0; i < size; i++){
        ans[i] = 0;
    }
    for(size_t i=0;i<A.size();i++){
        for(size_t j=0;j<B.size();j++){
            ans[i+j] += A[i]*B[j];
        }
    }
    return ans;
}


void test1(long long n){
    std::vector<field> A = randomVector(n);
    std::vector<field> B = randomVector(n);
    //for(int i=0; i< A.size(); i++)std::cout << A[i] << " ";
    //std::cout << std::endl;
    //for(int i=0; i< B.size(); i++)std::cout << B[i] << " ";
    //std::cout << std::endl;
    std::vector<field> C = multiplication(A, B);
    //for(int i=0; i< C.size(); i++)std::cout << C[i] << " ";
    std::vector<field> D = stupidMultiplication(A, B);
    //std::cout << std::endl;
    //for(int i=0; i< D.size(); i++)std::cout << D[i] << " ";
    //std::cout << std::endl;
    for(int i=0; i< D.size(); i++){
        if(D[i]!=C[i])std::cout << "-";
        else std::cout <<"+";
    }
}

/*
a = BigInt(5981298)
b = BigInt(825220) 
c = BigInt(2827091) 
d = BigInt(4409226)
x = BigInt(2306278)
*/

//15 4105828
//16384 16384



//4366140



//32768 32768
//(18)(15 2642941)(16 2065064)(17 3551426)(18 5708487)(18 5982336)7340032