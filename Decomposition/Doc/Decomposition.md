#Code 

> 考虑到 [[PTR 算法]] 的缺点（无法处理重复点以及存在无法处理的 case），对 [[PTR 算法]] 进行了 trivial 的改进

# 出发点

![](https://picbed-1306742914.cos.ap-nanjing.myqcloud.com/pics/20240409144608.png)

上图是 [[PTR 算法]] 筛选的 $P_k$、$P_l$、$P_m$ （对应红色部分） —— 在去掉/*裁剪*该部分后，若不考虑去掉所谓的 “冗余 edge” 或 “冗余 vertex”，剩余的部分所构成的多边形则如下图所示。

![](https://picbed-1306742914.cos.ap-nanjing.myqcloud.com/pics/20240409144657.png)

> 若不考虑算法优化等问题，实际上对上述多边形进行*清洗* —— 即去掉冗余的 edge 与 vertex 后便自然地规避了 [[PTR 算法#Drawback]]

# 整体框架

- `const auto& coor_tuple = findCoorTuple_Refactor(poly_copy)` 参考 [[模板函数 PTR#Pk, Pl, Pm 的筛选]]，但是进行了适当修正（参考 [[Decomposition#修正：findCoorTuple_Refactor]] ），自然得到了由 `Pk`、`Pl`、`Upl`、`Pm` 构成的矩形多边形 `Rectangle`
- 裁剪与清晰的结果为 `poly_complement`，即 `Edge_list_complement(poly_copy, Rectangle, poly_complement);` 参考 [[Edge_list_complement]]

```cpp,nums,{13-50}
template <typename T>
void Decomposition(
    const Polygon<T>& poly,
    std::vector< Polygon<T> >& result
)
{
    result.clear();

    Polygon<T> poly_copy = poly;
    poly_copy.vertexes   = poly.vertexes;
    poly_copy.edges      = poly.edges;

    while(poly_copy.vertexes.size() > 1){
//    for(int i=0; i<13; i++){
        const auto& coor_tuple = findCoorTuple_Refactor(poly_copy);
        
        const auto Pk = std::get<0>(coor_tuple);
        const auto Pl = std::get<1>(coor_tuple);
        const auto Pm = std::get<2>(coor_tuple);

        std::cout << "Pk: " << Pk << std::endl;
        std::cout << "Pl: " << Pl << std::endl;
        std::cout << "Pm: " << Pm << std::endl;

        Coor<T> Upl(Pk.getX(), Pm.getY()), Upr(Pl.getX(), Pm.getY());

        Polygon<T> Rectangle;
        Rectangle.vertexes.push_back(Pk);
        Rectangle.vertexes.push_back(Pl);
        Rectangle.vertexes.push_back(Upr);
        Rectangle.vertexes.push_back(Upl);
        
        Rectangle.edges_init();

        result.push_back(Rectangle);

        Polygon<T> poly_complement;
        Edge_list_complement(poly_copy, Rectangle, poly_complement);

        std::cout << "poly_complement: " << std::endl;
        for(auto v: poly_complement.vertexes){
            std::cout << v << std::endl;
        }

        // copy poly_complement to poly_copy
        poly_copy.vertexes = poly_complement.vertexes;
        poly_copy.edges    = poly_complement.edges;

        std::cout << "==========================" << std::endl;
    }

    std::cout << "The rectangle list is " << std::endl;
    for(auto rec: result){
        for(auto v: rec.vertexes){
            std::cout << v << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }
}
```

## 修正：findCoorTuple_Refactor

> 在测试中发现了下面这种 case，第一张为当前 case 的多变形示意图，第二张图为其修正后实现正确分解的情况，第三图为未修正出现分解异常的情况（即直接使用 [[模板函数 PTR#Pk, Pl, Pm 的筛选]]）

![](https://picbed-1306742914.cos.ap-nanjing.myqcloud.com/pics/20240409175823.png)

![](https://picbed-1306742914.cos.ap-nanjing.myqcloud.com/pics/20240409175735.png)

![](https://picbed-1306742914.cos.ap-nanjing.myqcloud.com/pics/20240409175723.png)

> 我们可以发现未修正情况下，算法只分解出了左下角第一个矩形后便出现异常 —— 原因是 [[模板函数 PTR#Pk, Pl, Pm 的筛选]] 定位出的 `Pk`、`Pl` 、`Pm` 默认其构成的矩形属于原多边形，但第二张图指出分解出了左下角第一个矩形后原多边形要想继续分解，是不能继续选择左小角的点为 `Pk` 的！

> 因此需要对  `Pk`、`Pl` 、`Pm` 默认其构成的矩形是否属于原多边形进行判定 —— 本质上是利用 [[WiKi/boost/polygon|polygon]] 中的 `isInside` 对 `Test` 进行判定

```cpp
bool legal_Pk = false;
auto Pk = poly_copy.vertexes.begin();
while(1){
	Pk = std::min_element(poly_copy.vertexes.begin(), poly_copy.vertexes.end(), 
        [](const auto& lhs, const auto& rhs) -> bool {
                if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                    }
            }
        );

    // Check the Pk
    Coor<T> Test = *Pk;
    Test.addToX(1);
    Test.addToY(1);

    legal_Pk = polygon.isInside(Test);

    if(legal_Pk){
        break;
    }
    else{
        poly_copy.vertexes.erase(Pk);
    }    
}
```