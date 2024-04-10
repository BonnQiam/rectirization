#Code 

```cpp
template <typename T>
void Edge_list_complement(
    const Polygon<T> &polygon,
    const Polygon<T> &rectangle, // Pk -> Pl -> Upr -> Upl -> Pk
    Polygon<T> &polygon_complement);
```

# 出发点

1. 在原多边形 `polygon` 找到合适的位置，去除 `Pk-Pl` edge 并插入 `rectangle` 剩余的 edge，进而得到了裁剪后的 ”新多变形“
2. 清洗 ”新多边形“ 中的 “冗余 edge” 或 “冗余 vertex”

# Step 1：裁剪

## 1-1：定位

```cpp
Polygon<T> polygon_tmp = polygon;
polygon_tmp.vertexes = polygon.vertexes;
polygon_tmp.edges = polygon.edges;
```

> 尽管多边形顶点顺时针或逆时针排序并没有实际意义，然而 [[Snippets/Cpp/Container and Data Structure/self-defined/Polygon|Polygon]] 模板类在设计的时候自然地引入了顺序，这给我们带来一点麻烦

- `Pk-Pl` 必然是原多边形  `polygon`  中的一条水平边，对应 line 8
- 尽管 `Pk` 必然位于 `Pl` 的左侧，但是原多边形  `polygon`  中顶点的顺序不一定是顺时针或逆时针，故对应 line 9 与 line 18
- 确定插入位置之后 —— 自然地便在 `Pk` 后的位置插入 `Pl`，或在 `Pl` 后的位置插入 `Pk`

```cpp,nums,{8,9,18}
// find Pk -> Pl edges in polygon
auto itr_kl = polygon_tmp.edges.begin();
auto itr_v  = polygon_tmp.vertexes.begin();

for(; itr_kl != polygon_tmp.edges.end(); itr_kl++){
    itr_v = itr_v + 1;
    
    if(itr_kl->Coor_pair.first.getY() == itr_kl->Coor_pair.second.getY()){
	    if(itr_kl->Coor_pair.first == Pk){
            if(itr_kl->Coor_pair.second == Pl)
                break;
            else {
                polygon_tmp.vertexes.insert(itr_v, Pl);
                polygon_tmp.edges_init();
                break;
            }
        }
        else if(itr_kl->Coor_pair.first == Pl){
            if(itr_kl->Coor_pair.second == Pk)
                break;
            else {
                polygon_tmp.vertexes.insert(itr_v, Pk);
                polygon_tmp.edges_init();
                break;
            }
        }
    }
    else{
        continue;
    }
        
    if( (itr_kl+1) == polygon_tmp.edges.end()){
        std::cout << "Error: Pk -> Pl edge not found in polygon" << std::endl;
        return;
    }
}
```

## 1-2：插入

构造 `polygon_complement`：
- 在 [[Edge_list_complement#1-1]] 的 `Pk-Pl` 或 `Pl-Pk` 位置，插入 `rectangle` 剩余的 edge
- 剩余位置的 edge 则是简单地复制 `polygon_tmp` 的边

```cpp,nums,{3-5,8-10}
for(auto e = polygon_tmp.edges.begin(); e != polygon_tmp.edges.end(); e++){
	if( (e->Coor_pair.first == Pk) && (e->Coor_pair.second == Pl) ){
		polygon_complement.edges.push_back(edge<T>(Pk, Upl));
        polygon_complement.edges.push_back(edge<T>(Upl, Upr));
        polygon_complement.edges.push_back(edge<T>(Upr, Pl));
    }
    else if((e->Coor_pair.first == Pl) && (e->Coor_pair.second == Pk)){
        polygon_complement.edges.push_back(edge<T>(Pl, Upr));
        polygon_complement.edges.push_back(edge<T>(Upr, Upl));
        polygon_complement.edges.push_back(edge<T>(Upl, Pk));
    }
    else
        polygon_complement.edges.push_back(*e);
}

polygon_complement.vertexes_init();

std::cout << "Before shrink, polygon_complement is " << std::endl;
for(auto v : polygon_complement.vertexes){
	std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
}
```

# Step 2：清洗

新多边形可能存在 “冗余 edge” 或 “冗余 vertex”：
- “冗余 edge”：新多边形中可能存在重叠边（*部分交叠的边* 不属于“冗余 edge”）
- “冗余 vertex”：新多边形中可能存在重复的顶点，或者是*部分交叠的边* （即一条直线上存在多个顶点）

![](https://picbed-1306742914.cos.ap-nanjing.myqcloud.com/pics/20240409144657.png)

## 2-1：删除 “冗余 edge”

> 考虑到单次清洗后可能会出现新的 “冗余 edge” —— 因此设计了循环，即若 [[Polygon_shrink_redundancy_edge]] 发现了 “冗余 edge”且完成清洗后，则将清洗后的多边形赋值给 `polygon_complement` ，再次执行清洗操作（对应 line 13-16），直至不再出现冗余 —— 类似 [[递归]] 操作

^bdde00

```cpp,nums,{7, 13-16}
Polygon<int> poly_shrink;
poly_shrink.vertexes = polygon_complement.vertexes;

bool redundancy = true;

while(redundancy){
	redundancy = Polygon_shrink_redundancy_edge(polygon_complement, poly_shrink);
	
	if(poly_shrink.vertexes.size() == 1){
        break;
    }
    
    if(redundancy){
        polygon_complement.vertexes = poly_shrink.vertexes;
        polygon_complement.edges = poly_shrink.edges;
    }
}

// Copy poly_shrink to polygon_complement
polygon_complement.vertexes = poly_shrink.vertexes;
polygon_complement.edges = poly_shrink.edges;
```

## 2-2：删除 “冗余 vertex”

- line 1-3 是发现当前多边形实际上是单独的一个点，则终止操作
- line 2 为删除 “冗余 vertex” 的主要操作，参考 [[Polygon_shrink_redundancy_point]]

```cpp,nums, {1-3, 7}
if(polygon_complement.vertexes.size() == 1){
    return;
}
poly_shrink.vertexes = polygon_complement.vertexes;
poly_shrink.edges = polygon_complement.edges;

Polygon_shrink_redundancy_point(polygon_complement, poly_shrink);

polygon_complement.vertexes = poly_shrink.vertexes;
polygon_complement.edges = poly_shrink.edges;
```