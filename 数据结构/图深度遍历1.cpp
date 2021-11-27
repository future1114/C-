#include<iostream>
#include<string>
#include<math.h>
using namespace std;
typedef int Status;
#define INFINITY 1<<30
#define MAX_VERTEX_NUM 20
#define OK 1
typedef int VRType;
typedef int InfoType;
typedef int VertexType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
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
/*Status LocateVex(MGraph G, VertexType u)//返回顶点u在图中的位置
{
    for (int i = 0; i < G.vexnum; i++)
        if (G.vexs[i] == u)
            return i;
    return -1;
}
*/
int LocateVex(MGraph G,VertexType v)//查找元素v在一维数组 Vertex[] 中的下标，并返回下标 
{
	int i;
	
	for(i=0;i<G.vexnum;i++)
	{
		if(v==G.vexs[i])
		{
			return i; 
		} 
	 }

     cout << "No Such Vertex!\n";
     return -1;
}

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


//--- 算法7.4和7.5使用的全局变量 ---
bool visited[MAX_VERTEX_NUM];   // 访问标志数组
Status(*VisitFunc)(int v);    // 函数变量
void DFS(MGraph G, int v) {  // 算法7.5
   // 从第v个顶点出发递归地深度优先遍历图G。
    int w;
    visited[v] = true;   VisitFunc(v);  // 访问第v个顶点
    for (w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w))
        if (!visited[w])   // 对v的尚未访问的邻接顶点w递归调用DFS
            DFS(G, w);
}
void DFSTraverse(MGraph G, Status(*Visit)(int v)) {  // 算法7.4
 // 对图G作深度优先遍历。
    int v;
    VisitFunc = Visit; // 使用全局变量VisitFunc，使DFS不必设函数指针参数
    for (v = 0; v < G.vexnum; ++v) visited[v] = false; // 访问标志数组初始化
    for (v = 0; v < G.vexnum; ++v)
        if (!visited[v]) DFS(G, v);         // 对尚未访问的顶点调用DFS
}
Status PrintElement(VertexType e) {
    //printf("%d ",e);
	cout << e + 1 << " ";
    return OK;
}

int main()
{
    MGraph G;
    CreateUDN(G);
    DFSTraverse(G,PrintElement);
	cout<<endl;
    system("pause");
    return 0;
}
