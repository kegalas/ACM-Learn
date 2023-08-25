//三分法求单峰函数的极值点 luogu p3382
//收敛速度是线性收敛
//用二分求函数的导数的零点也可以，但是并不是每次都可以方便的求出导数。三分法可以不用求出导数。
//设函数f在[l,r]上单峰，意味着有且只有一个极大值x，f在[l,x]上严格单增，在[x,r]上严格单减。单谷函数则为极小值x。

//在[l,r]上取两个不等的点，设靠近l的是l1，靠近r的是r1。如果f(l1)<f(r1)，说明极大值一定在[l1,r]，令l=l1
//如果f(l1)>f(r1)，极大值一定在[l,r1]，令r=r1
//持续下去直到r-l<EPS或者迭代次数足够

//取l1和r1时，可以直接取三等分点，也可以取黄金分割点(l1=l+(r-l)(1-0.618),r1=r-(r-l)*(1-0.618))
//还可以让l1=mid-EPS, r1=mid-EPS，但是要令l=mid而不是l=l1，防止死循环

#include <iostream>

using DB = double;

int const MAXN = 200005;
DB const EPS = 1e-8;

DB arr[MAXN];

void solve(){
    int n;
    std::cin>>n;
    DB l,r;
    std::cin>>l>>r;
    for(int i=n;i>=0;i--){
        std::cin>>arr[i];
    }
    
    auto func = [&n](DB x){
        DB ret = 0;
        DB tmp = 1;
        for(int i=0;i<=n;i++){
            ret += arr[i]*tmp;
            tmp *= x;
        }
        return ret;
    };
    
    while(r-l>EPS){
		DB mid = (l+r)/2;
		DB f1 = func(mid-EPS), f2 = func(mid+EPS);//func根据题目要求定义，是一元函数
		if(f1<f2)
			l = mid;
		else
			r = mid;
	}
    std::cout<<r<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
