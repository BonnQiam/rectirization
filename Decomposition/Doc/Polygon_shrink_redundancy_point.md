#Code 

类似 ![[Edge_list_complement#^bdde00]]
> [[Polygon_shrink_redundancy_point]] 也是被设计为递归操作，结构与 [[Polygon_shrink_redundancy_edge]] 类似

```cpp
template <typename T>
void Polygon_shrink_redundancy_point(const Polygon<T> &polygon,  Polygon<T> &polygon_shrink)
{
	auto e = polygon.edges.begin();
    auto v = polygon_shrink.vertexes.begin() + 1;
	
	while(e != polygon.edges.end()){
		bool find_duplicate = false;
		// 侦测 
		if(find_duplicate){
			//修正
		}
		else{
			e = e+1;
            v = v+1;
		}
	}
	polygon_shrink.edges_init();
}
```

# 侦测

该部分与 [[Polygon_shrink_redundancy_edge#侦测]] 类似，仅仅在判定条件上做了修改

```cpp
auto e_nxt = ( (e+1) == polygon.edges.end() ) ? polygon.edges.begin() : (e+1);

T e_X     = e->Coor_pair.second.getX() - e->Coor_pair.first.getX();
T e_nxt_X = e_nxt->Coor_pair.second.getX() - e_nxt->Coor_pair.first.getX();

T e_Y     = e->Coor_pair.second.getY() - e->Coor_pair.first.getY();
T e_nxt_Y = e_nxt->Coor_pair.second.getY() - e_nxt->Coor_pair.first.getY();

if(
    (e->Coor_pair.second.getY() == e->Coor_pair.first.getY() ) &&
    (e_nxt->Coor_pair.second.getY() == e_nxt->Coor_pair.first.getY() )
    ){
        if(e_X*e_nxt_X > 0)
        find_duplicate = true;
}
else if ( (e->Coor_pair.second.getX() == e->Coor_pair.first.getX() ) &&
    (e_nxt->Coor_pair.second.getX() == e_nxt->Coor_pair.first.getX() )
){
    if(e_Y*e_nxt_Y > 0)
        find_duplicate = true;
}
```

# 修正

> “冗余 vertex”的修正非常简单，删除相邻两条边的中间顶点即可，但是此处也需要注意 [[迭代器失效]] 的问题

```cpp
if(find_duplicate){
	if( (e+1) == polygon.edges.end() ){
        *(polygon_shrink.vertexes.end()-1) = *(polygon_shrink.vertexes.begin()+1);
        polygon_shrink.vertexes.erase(polygon_shrink.vertexes.begin());
        break;
    }
    else{
        e = e+1;
        v = polygon_shrink.vertexes.erase(v);
    }
}
```