#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <bitset>
#include <deque>
#include <regex>
#include <unordered_map>
#include <unordered_set>

#define debug(a) std::cout<<#a<<"="<<a<<std::endl
#define lth(i,x,y) for(int i=x;i<=y;i++)
#define htl(i,x,y) for(int i=x;i>=y;i--)
#define mms(x) memset(x, 0, sizeof(x))

using LL = long long;
using ULL = unsigned long long;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 200005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int arr[MAXN];

inline bool isOper(char c){
    return c=='+'||c=='-'||c=='*'||c=='/';
}

inline bool isDigit(char c){
    return c>='0' && c<='9';
}

inline int priority(char oper){
    if(oper=='+' || oper=='-') return 1;
    if(oper=='*' || oper=='/') return 2;
    return -1;
}

std::string toRPN(std::string expr){
    std::string ret;
    
    std::stack<char> oper;
    int esize = expr.size();
    for(int i=0;i<esize;i++){
        char& c = expr[i];
        if(c==' ') continue;
        else if(isOper(c)){
            if(c=='-' && (i==0 || expr[i-1]=='(')){
                //判断一元运算符负号，这里采用了加个0-前缀的方法，如果题目要求输出RPN其实是做不到的
                //TODO: 把toRPN返回一个vector，实现真正的RPN
                ret.push_back('0');
                ret.push_back(' ');
            }
            while(!oper.empty() && priority(oper.top())>=priority(c)){
                //如果是右结合运算符，则要改成大于，如果只有一部分是右结合运算符，分类讨论
                ret.push_back(oper.top());
                ret.push_back(' ');
                oper.pop();
            }
            oper.push(c);
        }
        else if(c=='('){
            oper.push(c);
        }
        else if(c==')'){
            while(oper.top()!='('){
                ret.push_back(oper.top());
                ret.push_back(' ');
                oper.pop();
            }
            oper.pop();
        }
        else{
            while(i<esize && isDigit(expr[i])){
                ret.push_back(expr[i++]);
            }
            ret.push_back(' ');
            i--;
        }
    }
    
    while(!oper.empty()){
        ret.push_back(oper.top());
        ret.push_back(' ');
        oper.pop();
    }
    
    return ret;
}

void processOper(std::stack<int> & st, char oper){
    int r = st.top();
    st.pop();
    int l = st.top();
    st.pop();
    
    switch(oper){
        case '+':
            st.push(l+r);
            break;
        case '-':
            st.push(l-r);
            break;
        case '*':
            st.push(l*r);
            break;
        case '/':
            st.push(l/r);
            break;
    }
}

int RPNCalc(std::string expr){
    int ret = 0;

    std::stack<int> number;
    int esize = expr.size();
    for(int i=0;i<esize;i++){
        char& c = expr[i];
        if(c==' ') continue;
        else if(isOper(c)){
            processOper(number, c);
        }
        else{
            int res = 0;
            while(i<esize && isDigit(expr[i])){
                res = res*10 + expr[i++] - '0';
            }
            i--;
            number.push(res);
        }
    }
    
    ret = number.top();

    return ret;
}

int exprCalc(std::string expr){
    int ret = RPNCalc(toRPN(expr));
    return ret;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	std::string str;
	std::cin>>str;
	
	std::cout<<toRPN(str)<<"\n";
	std::cout<<exprCalc(str)<<"\n";

    return 0;
}
