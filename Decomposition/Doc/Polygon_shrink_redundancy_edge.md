#Code 

```cpp
template <typename T>
bool Polygon_shrink_redundancy_edge(const Polygon<T> &polygon,  Polygon<T> &polygon_shrink);
```

```cpp
int original_size = polygon_shrink.vertexes.size();

auto e = polygon.edges.begin();
auto v = polygon_shrink.vertexes.begin() + 1;

while( e != polygon.edges.end()){
	bool find_duplicate = false;
	// 侦测部分
	if(find_duplicate){
		// 修正部分
	}
	else{
		e = e+1;
        v = v+1;
	}
}
```

> 重点在于如何侦测到多边形红中 “冗余 edge” 并进行修正，对应 `while` 循环遍历多边形的所有的 edge

# 侦测

> 侦测部分的工作主要是依序比对相邻的 edge，故设置了  `e_nxt`，通过比对相邻 edge 在 X、Y 方面的投影来确定相邻的 edge 是否完全重叠

```cpp,nums,{1}
auto e_nxt = ( (e+1) == polygon.edges.end() ) ? polygon.edges.begin() : (e+1);

T e_X     = e->Coor_pair.second.getX() - e->Coor_pair.first.getX();
T e_nxt_X = e_nxt->Coor_pair.second.getX() - e_nxt->Coor_pair.first.getX();

T e_Y     = e->Coor_pair.second.getY() - e->Coor_pair.first.getY();
T e_nxt_Y = e_nxt->Coor_pair.second.getY() - e_nxt->Coor_pair.first.getY();

int e_X_sign = (e_X > 0) ? 1 : -1;
int e_Y_sign = (e_Y > 0) ? 1 : -1;
int e_nxt_X_sign = (e_nxt_X > 0) ? 1 : -1;
int e_nxt_Y_sign = (e_nxt_Y > 0) ? 1 : -1;

if(
    (e->Coor_pair.second.getY() == e->Coor_pair.first.getY() ) &&
    (e_nxt->Coor_pair.second.getY() == e_nxt->Coor_pair.first.getY() )
	){
    if(e_X_sign != e_nxt_X_sign)
        find_duplicate = true;
 }
else if ( (e->Coor_pair.second.getX() == e->Coor_pair.first.getX() ) &&
        (e_nxt->Coor_pair.second.getX() == e_nxt->Coor_pair.first.getX() )
        ){
    if(e_Y_sign != e_nxt_Y_sign){
        find_duplicate = true;
    }
}
```

# 修正

> 侦测到 “冗余 edge” 后自然删除对应的顶点 —— 针对多边形第一条 edge 与最后一条 edge构成 ”冗余边“ 的情况作了特殊处理，对应 line 17-27

> 此外还需要注意 [[迭代器失效]] 的问题，

```cpp,nums,{17-27}
if(find_duplicate){
    T v_NewX  = e_nxt->Coor_pair.second.getX();
    T v_NewY  = e_nxt->Coor_pair.second.getY();

    if( (v_NewX == e->Coor_pair.first.getX()) && (v_NewY == e->Coor_pair.first.getY()) ){
        if( (e+1) == polygon.edges.end() ){
            polygon_shrink.vertexes.erase(v);
	        polygon_shrink.vertexes.erase(polygon_shrink.vertexes.begin());
            break;
        }
        else{
            v = polygon_shrink.vertexes.erase(v);
            v = polygon_shrink.vertexes.erase(v);
            e = e+2;
        }
    }
    else{
        if( (e+1) == polygon.edges.end() ){
            *(polygon_shrink.vertexes.end()-1) = *(polygon_shrink.vertexes.begin()+1);
	        polygon_shrink.vertexes.erase(polygon_shrink.vertexes.begin());
            break;
        }
        else{
            v = polygon_shrink.vertexes.erase(v)+1;
            e = e+2;
        }
    }
}
```


# 冗余判定

通过比对清洗前后多边形的顶点数目便可以判定是否出现冗余边

```cpp
int shrink_size = polygon_shrink.vertexes.size();
if(original_size == shrink_size)
	return false;
else
    polygon_shrink.edges_init();
    return true;
```