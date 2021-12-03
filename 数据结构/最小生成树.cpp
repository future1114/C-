#include<iostream>
#include<string>

using namespace std;
typedef int Status;

#define INFINITY 100 //无穷大
#define MAX_VERTEX_NUM 20
#define OK 1

typedef int VRType;
typedef int InfoType;
typedef char VertexType;
typedef enum { DG, DN, UDG, UDN } GraphKind;

struct close {
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];
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

Status FirstAdjVex(MGraph G, int v) {    //寻找图G中v的第一个邻接点
    for (int i = 0; i < G.vexnum; i++) {
        if (G.arcs[v][i].adj != INFINITY) return i;
    }
    return -1;
}

Status NextAdjVex(MGraph G, int v, int w) {   //寻找图G中v顶点在w之后的下一个邻接点
    for (int i = w + 1; i < G.vexnum; i++) {
        if (G.arcs[v][i].adj != INFINITY) return i;
    }
    return -1;
}

int LocateVex(MGraph &G,VertexType v){//查找元素v在一维数组 Vertex[] 中的下标，并返回下标 
	int i;
	for(i=0;i<G.vexnum;i++){
		if(v==G.vexs[i]){
			return i;
		}
	}
    cout << "No Such Vertex!" << endl;
    return -1;
}

Status CreateUDN(MGraph &G) {//  算法 7.2
  // 采用数组（邻接矩阵）表示法，构造无向网G。
  int i,j,k,w; 
  VertexType  v1,v2;
  cout << "G.vexnum :";
  cin >> G.vexnum;
  cout << "G.arcnum :"; 
  cin >> G.arcnum;
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  for (i=0; i<G.vexnum; i++ ) {
      cout << "G.vexs[" << i + 1 << "] : ";
      cin >> G.vexs[i];
  } // 构造顶点向量
  for (i=0; i<G.vexnum; ++i )  // 初始化邻接矩阵
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接矩阵
      cout << "v1(char) : ";
      cin >> v1;
      cout << "v2 (char) : ";
      cin >> v2;
      cout << "w (int) : ";
      cin >> w;
      // 输入一条边依附的顶点及权值
      i = LocateVex(G, v1);
      j = LocateVex(G, v2);
      cout << i << " " << j << endl;
      // 确定v1和v2在G中位置
      G.arcs[i][j].adj = w; // 弧<v1,v2>的权值
      // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
      G.arcs[j][i].adj = G.arcs[i][j].adj; // 设置<v1,v2>的对称弧<v2,v1>
  }
  return OK;
} // CreateUDN

int minimum(struct close closedge[],int n){
	int i,j=0,min=INFINITY;
	for(i=0;i<n;i++)
	{
		if(closedge[i].lowcost<min&&closedge[i].lowcost!=0)
		{
			min=closedge[i].lowcost;
			j=i;
		}
	}
	return j;

}

void MiniSpanTree_PRIM(MGraph G, VertexType u) {  // 算法7.9
  // 用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。
  // 记录从顶点集U到V－U的代价最小的边的辅助数组定义：
  //  struct {
  //      VertexType  adjvex;
  //      VRType     lowcost;
  //  } closedge[MAX_VERTEX_NUM];
  int i,j,k;
  k = LocateVex ( G, u ); 
  for ( j=0; j<G.vexnum; ++j ) {     // 辅助数组初始化
    if (j!=k) 
     { closedge[j].adjvex=u; closedge[j].lowcost=G.arcs[k][j].adj; }
  }
  closedge[k].lowcost = 0;      // 初始，U＝{u}
  for (i=1; i<G.vexnum; ++i) {
      int n = G.vexnum;                                  // 选择其余G.vexnum-1个顶点
      k = minimum(closedge,n);
      cout << k << endl;                                 // 求出T的下一个结点：第k顶点
                                                         // 此时closedge[k].lowcost =
                                                         // MIN{ closedge[vi].lowcost | closedge[vi].lowcost>0, vi∈V-U }
      printf("%c, %c\n", closedge[k].adjvex, G.vexs[k]); // 输出生成树的边
      closedge[k].lowcost = 0;                           // 第k顶点并入U集
      for (j = 0; j < G.vexnum; ++j)
          if (G.arcs[k][j].adj < closedge[j].lowcost)
          {
              // 新顶点并入U后重新选择最小边
              // closedge[j] = { G.vexs[k], G.arcs[k][j].adj };
              closedge[j].adjvex = G.vexs[k];
              closedge[j].lowcost = G.arcs[k][j].adj;
          }
  }
} // MiniSpanTree

int main(){
    MGraph G;
    CreateUDN(G);
    MiniSpanTree_PRIM(G, 'a');
    return 0;
}