/*
scanning line algorithm to calculate the intersection of the rectangles
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <set>
#include <iostream>
#include <stack>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>

#include "../Edge-based_X_Y/Decomposition.hpp"

#define mem(a,b) 							memset(a,b,sizeof(a))
#define inf 								0x3f3f3f3f
#define N 									2200
#define ll 									long long
#define lson 								l,m,rt<<1
#define rson 								m+1,r,rt<<1|1

typedef std::vector<std::pair<double,double>>		Interval;

struct Seg
{
	double l,r,h;
	int f;
	Seg() {}
	Seg(double a,double b,double c,int d):l(a),r(b),h(c),f(d) {}
	bool operator < (const Seg &cmp) const
	{
		return h<cmp.h;
	}
} e[N];
struct node
{
	int cnt;
	double len,s;// cnt是标记，len是长度，s是被标记的长度 —— s 被用来计算交集
} t[N<<2];

double X[N];

void pushdown(int l,int r,int rt)
{
	// l, r是当前节点的区间
	// rt是当前节点的编号

	if(t[rt].cnt)
		t[rt].len=X[r+1]-X[l];//覆盖一次以及以上
	else if(l==r)
		t[rt].len=0;
	else
		t[rt].len=t[rt<<1].len+t[rt<<1|1].len;

	if(t[rt].cnt>1)//覆盖两次以及以上
		t[rt].s=X[r+1]-X[l];
	else if(l==r)
		t[rt].s=0;
	else if(t[rt].cnt==1)//覆盖一次
		t[rt].s=t[rt<<1].len+t[rt<<1|1].len;//两个子节点的长度之和，每个子节点的长度是覆盖一次以及以上，这样就实现了覆盖两次以及以上的长度
	else
		t[rt].s=t[rt<<1].s+t[rt<<1|1].s;
}
void update(int L,int R,int l,int r,int rt,int val)
{
	// L, R是要更新的区间，
	// l, r是当前节点的区间
	// rt是当前节点的编号，val是要加的值
	if(L<=l&&r<=R)// [l,r] \in [L,R]
	{
		t[rt].cnt+=val;
		pushdown(l,r,rt);
		return;
	}
	int m=(l+r)>>1;
	if(L<=m) update(L,R,lson,val);// 更新区间存在部分位于左子树
	if(R>m) update(L,R,rson,val);// 更新区间存在部分位于右子树
	pushdown(l,r,rt);
}

void get(int l,int r,int rt)
{
	std::cout << "l = " << l << " r = " << r << " X[r+1]-X[l] = " << X[r+1]-X[l] << std::endl;
	std::cout << "t[rt].len = " << t[rt].len << std::endl;
	std::cout << "t[rt].s = " << t[rt].s << std::endl;

	if(l==r)
		return;

	int m=(l+r)>>1;
	get(lson);
	get(rson);
}

Interval check_effective_len(int l, int r, int rt){
	if(t[rt].cnt){
		//std::cout << "Find effective len [l, r] = [" << X[l] << ", " << X[r+1] << "]: " <<std::endl;
		return Interval{std::make_pair(X[l], X[r+1])};
	}
	else if(l == r){
		return Interval{};
	}
	else{
		int m = (l + r) >> 1;
		check_effective_len(lson);
		check_effective_len(rson);

		Interval left = check_effective_len(lson);
		Interval right = check_effective_len(rson);

		if(left.size() == 0){
			return right;
		}
		else if(right.size() == 0){
			return left;
		}
		else{
			Interval res;
			if(left.back().second == right.front().first){
				res = std::move(left);
				res.back().second = right.front().second;
				right.erase(right.begin());
				// move right to res.end()
				res.insert(res.end(), right.begin(), right.end());
			}
			else{
				res = std::move(left);
				res.insert(res.end(), right.begin(), right.end());
			}
			return res;
		}
	}
}

//void check_effective_s(int l, int r, int rt){
Interval check_effective_s(int l, int r, int rt){
	if(t[rt].cnt > 1 && t[rt].s > 0){
		//std::cout << "Find effective s [l, r] = [" << X[l] << ", " << X[r+1] << "]: " <<std::endl;
		return Interval{std::make_pair(X[l], X[r+1])};
	}
	else if(l==r)
		return Interval{};
	else if(t[rt].cnt == 1 && t[rt].s > 0){
		int m = (l + r) >> 1;

		Interval left =  check_effective_len(lson);
		Interval right = check_effective_len(rson);

		if(left.size() == 0){
			return right;
		}
		else if(right.size() == 0){
			return left;
		}
		else{
			Interval res;
			if(left.back().second == right.front().first){
				res = std::move(left);
				res.back().second = right.front().second;
				right.erase(right.begin());
				// move right to res.end()
				res.insert(res.end(), right.begin(), right.end());
			}
			else{
				res = std::move(left);
				res.insert(res.end(), right.begin(), right.end());
			}
			return res;
		}
	}
	else{
		int m = (l + r) >> 1;
		
		Interval left  = check_effective_s(lson);
		Interval right = check_effective_s(rson);

		if(left.size() == 0){
			return right;
		}
		else if(right.size() == 0){
			return left;
		}
		else{
			Interval res;
			if(left.back().second == right.front().first){
				res = std::move(left);
				res.back().second = right.front().second;
				right.erase(right.begin());
				// move right to res.end()
				res.insert(res.end(), right.begin(), right.end());
			}
			else{
				res = std::move(left);
				res.insert(res.end(), right.begin(), right.end());
			}
			return res;
		}
	}
}


int main()
{
	int n,q;
	double a,b,c,d;
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&n);
		mem(t,0);
		int num=0;
		for(int i=0; i<n; i++)
		{
			scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
			X[num]=a;
			e[num++]=Seg(a,c,b,1);
			X[num]=c;
			e[num++]=Seg(a,c,d,-1);
		}
		std::sort(X,X+num);
		std::sort(e,e+num);
		int m=std::unique(X,X+num)-X;
		
		double ans=0;

        std::vector< edge<int> > Final_Edge_list;// The edge collection of the intersection area
        std::vector< edge<int> > Check_Edge_list;// effective edge list in the last scanning line
        std::vector< edge<int> > Checked_Edge_list;// effective edge list in the now scanning line

		for(int i=0; i<num; i++)
		{
			int l=std::lower_bound(X,X+m,e[i].l)-X;
			int r=std::lower_bound(X,X+m,e[i].r)-X-1;

			update(l,r,0,m-2,1,e[i].f);

			ans+=t[1].s*(e[i+1].h-e[i].h);

			if(e[i+1].h - e[i].h >0 && t[1].s > 0){
				Interval res = check_effective_s(0, m-2, 1);

                if(Final_Edge_list.size() == 0){
                    std::cout << "Test-1" << std::endl;
                    for(auto& r : res){
                        // For horizontal edge
                        Final_Edge_list.push_back(edge<int>(Coor<int>(r.first, e[i].h), Coor<int>(r.second, e[i].h)));
                        Check_Edge_list.push_back(edge<int>(Coor<int>(r.first, e[i+1].h), Coor<int>(r.second, e[i+1].h)));
                        // For vertical edge
                        Final_Edge_list.push_back(edge<int>(Coor<int>(r.first, e[i].h), Coor<int>(r.first, e[i+1].h)));
                        Final_Edge_list.push_back(edge<int>(Coor<int>(r.second, e[i].h), Coor<int>(r.second, e[i+1].h)));
                    }
                }
                else{
                    std::cout << "Test-2" << std::endl;
                    for(auto& r : res){
                        //For horizontal edge
                        Checked_Edge_list.push_back(edge<int>(Coor<int>(r.first, e[i+1].h), Coor<int>(r.second, e[i+1].h)));

                        std::cout << "( " << r.first << ", " << e[i].h << " ) ( " << r.second << ", " << e[i].h << " )" << std::endl;

                        for(auto& r : Check_Edge_list){
                            std::cout << "Check_Edge_list: " << r.Coor_pair.first << " " << r.Coor_pair.second << std::endl;
                        }

                        edge_list_edge_complement<int>(Check_Edge_list, edge<int>(Coor<int>(r.first, e[i].h), Coor<int>(r.second, e[i].h)), HORIZONTAL);
                        // For vertical edge
                        edge_list_edge_complement<int>(Final_Edge_list, edge<int>(Coor<int>(r.first, e[i].h), Coor<int>(r.first, e[i+1].h)), VERTICAL);
                        edge_list_edge_complement<int>(Final_Edge_list, edge<int>(Coor<int>(r.second, e[i].h), Coor<int>(r.second, e[i+1].h)), VERTICAL);
                    }

                    for(auto& r : Check_Edge_list){
                        Final_Edge_list.push_back(r);
                    }

                    Check_Edge_list.clear();
                    for(auto& r : Checked_Edge_list){
                        Check_Edge_list.push_back(r);
                    }
                    Checked_Edge_list.clear();
                }
			}			
		}

		printf("The intersection area is %.2f\n",ans);

        // Output the check edge list
        for(auto& e : Check_Edge_list){
            std::cout << "Check_Edge_list: " << e.Coor_pair.first << " " << e.Coor_pair.second << std::endl;
            Final_Edge_list.push_back(edge<int>(e.Coor_pair.first, e.Coor_pair.second));
        }

        // Output the edge collection of the intersection area
        for(auto& e : Final_Edge_list){
            std::cout << e.Coor_pair.first << " " << e.Coor_pair.second << std::endl;
        }
	}
	return 0;
}