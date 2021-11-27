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
## 
