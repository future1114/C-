#include<iostream>
#include<string>

using namespace std;
typedef int Status;

#define INFINITY 100 //无穷大
#define MAX_VERTEX_NUM 5
#define OK 1
#define TRUE 1
#define FALSE 0

typedef int VRType;
typedef int InfoType;
typedef char VertexType;
typedef enum { DG, DN, UDG, UDN } GraphKind;

int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
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

void ShortestPath_FLOYD(MGraph G) {
	
  // 算法7.16
  // 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其
  // 带权长度D[v][w]。若P[v][w][u]为TRUE，则u是从v到w当前求得最
  // 短路径上的顶点。
  int v,w,u,i,j;
  for (v=0; v<G.vexnum; ++v)        // 各对结点之间初始已知路径及距离
    for (w=0; w<G.vexnum; ++w) {
      D[v][w] = G.arcs[v][w].adj;
      for (u=0; u<G.vexnum; ++u) P[v][w][u] = FALSE;
      if (D[v][w] < INFINITY) {     // 从v到w有直接路径
        P[v][w][v] = P[v][w][w] = TRUE;
      }//if
    }//for

  for (u=0; u<G.vexnum; ++u)
    for (v=0; v<G.vexnum; ++v)
      for (w=0; w<G.vexnum; ++w)
        if (D[v][u]+D[u][w] < D[v][w]) {  // 从v经u到w的一条路径更短
          D[v][w] = D[v][u]+D[u][w];
          for (i=0; i<G.vexnum; ++i)
            P[v][w][i] =(P[v][u][i] || P[u][w][i]);
        }//if
   for(i=0;i<G.vexnum;i++){
     	for(j=0;j<G.vexnum;j++){
   	  	 printf("%d ", D[i][j]);
   	}
   	printf("\n");
     } //print  D
} // ShortestPath_FLOYD

int LocateVex(MGraph G, VertexType v){
	//定位顶点v的下标 
	for(int i=0;i<G.vexnum;i++){
		if (G.vexs[i] == v)
			return i;
	}
	return -1;
}

Status CreateUDN(MGraph &G) {//  算法 7.2
  // 采用数组（邻接矩阵）表示法，构造无向网G。
  int i,j,k,w,ix; 
  VertexType  v1,v2;
  G.vexnum = 5;
  cout << "G.vexnum :" << G.vexnum << endl;
  //cin >> G.vexnum;
  G.arcnum = 10;
  cout << "G.arcnum :" << G.arcnum << endl;
  //cin >> G.arcnum;
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  for (i=0; i<G.vexnum; i++ ) {
      cout << "G.vexs[" << i + 1 << "] : ";
      //cin >> G.vexs[i];
      G.vexs[i] = char(G.vexs[i] + 1);
      cout << "G.vexs[" << i << "] : " << G.vexs[i] << endl;
  } // 构造顶点向量
  for (i=0; i<G.vexnum; ++i )  // 初始化邻接矩阵
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  for (k = 0; k < G.vexnum; k++)
  { // 构造邻接矩阵
    for (ix = k + 1; ix < G.vexnum; ix++)
    {
      if (k != ix)
      {
        v1 = char('a' + k);
        cout << "v1 (char) : " << v1 << endl;
        //cin >> v1;
        v2 = char('a' + ix);
        cout << "v2 (char) : " << v2 << endl;
        //cin >> v2;
        w = rand() % 10 + 1;
        cout << "w (int) : " << w << endl;
        //cin >> w;
        // 输入一条边依附的顶点及权值
        //i = LocateVex(G, v1);
        //j = LocateVex(G, v2);
        cout << k << " " << ix << endl;
        // 确定v1和v2在G中位置
        //G.arcs[k][ix].adj = w;                // 弧<v1,v2>的权值
        // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
        G.arcs[k][ix].adj = G.arcs[ix][k].adj = w;
      } // 设置<v1,v2>的对称弧<v2,v1>         
      }
      //cout << endl;
  }
  cout << "*---------------*" << endl;
  for (int imx = 0; imx < 5;imx++){
      for (int inx = 0; inx < 5;inx++){
          cout << G.arcs[imx][inx].adj <<" ";
      }
      cout << endl;
  }
  cout << "*---------------*" << endl;
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
    ShortestPath_FLOYD(G);
    return 0;
}
