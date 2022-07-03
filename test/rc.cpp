#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

const int MAXN = 50005;

struct Point{
	int x,y;
	Point()=default;
	Point(int x, int y):x(x),y(y){}
	Point operator + (Point p){
		return Point(x+p.x, y+p.y);
	}
	Point operator - (Point p){
		return Point(x-p.x, y-p.y);
	}
	Point operator * (int d){
		return Point(x*d, y*d);
	}
	int dot(Point p){
		return (x*p.x+y*p.y);
	}
	int det(Point p){
		return (x*p.y-y*p.x);
	}
};

Point po[MAXN];

bool cmp(Point a, Point b){
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

vector<Point> convexHull(int n){
	vector<Point> ans;
	int k=0;
	for(int i=0;i<n;i++){
		while(k>1&&(ans[k-1]-ans[k-2]).det(po[i]-ans[k-1])<=0){
			ans.erase(ans.end()-1);
			k--;
		}
		ans.push_back(po[i]);
		k++;
	}
	for(int i=n-2,t=k;i>=0;i--){
		while(k>t&&(ans[k-1]-ans[k-2]).det(po[i]-ans[k-1])<=0){
			ans.erase(ans.end()-1);
			k--;
		}
		
		ans.push_back(po[i]);
		k++;
	}
	ans.erase(ans.end()-1);	
	return ans;
}

inline long long dist(Point a, Point b){
	return (a-b).dot(a-b);
}

void rc(vector<Point> ch){
	long long res = 0;
	int n = ch.size();
	if(n==2){
		cout<<dist(ch[0],ch[1])<<endl;
		return;
	}
	int i=0,j=0;
	for(int k=0;k<n;k++){
		if(!cmp(ch[i],ch[k])) i=k;
		if(cmp(ch[j],ch[k]))  j=k;
	}	
	int si=i,sj=j;
	while(si!=j||sj!=i){
		res = max(res,dist(ch[i],ch[j]));
		if((ch[(i+1)%n]-ch[i]).det(ch[(j+1)%n]-ch[j])<0){
			i = (i+1)%n;
		}else{
			j = (j+1)%n;
		}
	}
	cout<<res<<endl;
}

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>po[i].x>>po[i].y;		
	}
	sort(po,po+n,cmp);
	vector<Point> ch = convexHull(n);
	rc(ch);
	return 0;
}

