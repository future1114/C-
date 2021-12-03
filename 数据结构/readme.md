# 使用c语言去完成部分数据结构
## 图的深度遍历.cpp
```cpp

包括函数：
int LocateVex(MGraph G,VertexType v)
Status FirstAdjVex(MGraph G, int v)
Status NextAdjVex(MGraph G, int v, int w)
typedef struct ArcCell {
    VRType adj;
    InfoType* info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum, arcnum;
    GraphKind kind;
}MGraph;
Status CreateUDN(MGraph &G)
void DFS(MGraph G, int v)
void DFSTraverse(MGraph G, Status(*Visit)(int v))
```
## 最小生成树.cpp
使用prim算法进行计算
![1QR30JRCK~T0PKQP1%ZH_68](https://user-images.githubusercontent.com/94292494/144560064-e81b721b-2656-4f03-9631-da538487683d.png)
output：
![NG9_IK@HI)J~P%`8Y}OFE}R](https://user-images.githubusercontent.com/94292494/144560138-014e03cc-5ba1-4095-9cd2-51e78fbf8326.png)
