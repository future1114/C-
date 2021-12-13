#include<iostream>
#include<string>

using namespace std;
typedef int Status;

#define INFINITY 100 //�����
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
	
  // �㷨7.16
  // ��Floyd�㷨��������G�и��Զ���v��w֮������·��P[v][w]����
  // ��Ȩ����D[v][w]����P[v][w][u]ΪTRUE����u�Ǵ�v��w��ǰ�����
  // ��·���ϵĶ��㡣
  int v,w,u,i,j;
  for (v=0; v<G.vexnum; ++v)        // ���Խ��֮���ʼ��֪·��������
    for (w=0; w<G.vexnum; ++w) {
      D[v][w] = G.arcs[v][w].adj;
      for (u=0; u<G.vexnum; ++u) P[v][w][u] = FALSE;
      if (D[v][w] < INFINITY) {     // ��v��w��ֱ��·��
        P[v][w][v] = P[v][w][w] = TRUE;
      }//if
    }//for

  for (u=0; u<G.vexnum; ++u)
    for (v=0; v<G.vexnum; ++v)
      for (w=0; w<G.vexnum; ++w)
        if (D[v][u]+D[u][w] < D[v][w]) {  // ��v��u��w��һ��·������
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
	//��λ����v���±� 
	for(int i=0;i<G.vexnum;i++){
		if (G.vexs[i] == v)
			return i;
	}
	return -1;
}

Status CreateUDN(MGraph &G) {//  �㷨 7.2
  // �������飨�ڽӾ��󣩱�ʾ��������������G��
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
  } // ���춥������
  for (i=0; i<G.vexnum; ++i )  // ��ʼ���ڽӾ���
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  for (k = 0; k < G.vexnum; k++)
  { // �����ڽӾ���
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
        // ����һ���������Ķ��㼰Ȩֵ
        //i = LocateVex(G, v1);
        //j = LocateVex(G, v2);
        cout << k << " " << ix << endl;
        // ȷ��v1��v2��G��λ��
        //G.arcs[k][ix].adj = w;                // ��<v1,v2>��Ȩֵ
        // if (IncInfo) scanf(G.arcs[i][j].info); // ���뻡���������Ϣ
        G.arcs[k][ix].adj = G.arcs[ix][k].adj = w;
      } // ����<v1,v2>�ĶԳƻ�<v2,v1>         
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

void MiniSpanTree_PRIM(MGraph G, VertexType u) {  // �㷨7.9
  // ������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߡ�
  // ��¼�Ӷ��㼯U��V��U�Ĵ�����С�ıߵĸ������鶨�壺
  //  struct {
  //      VertexType  adjvex;
  //      VRType     lowcost;
  //  } closedge[MAX_VERTEX_NUM];
  int i,j,k;
  k = LocateVex ( G, u ); 
  for ( j=0; j<G.vexnum; ++j ) {     // ���������ʼ��
    if (j!=k) 
     { closedge[j].adjvex=u; closedge[j].lowcost=G.arcs[k][j].adj; }
  }
  closedge[k].lowcost = 0;      // ��ʼ��U��{u}
  for (i=1; i<G.vexnum; ++i) {
      int n = G.vexnum;                                  // ѡ������G.vexnum-1������
      k = minimum(closedge,n);
      cout << k << endl;                                 // ���T����һ����㣺��k����
                                                         // ��ʱclosedge[k].lowcost =
                                                         // MIN{ closedge[vi].lowcost | closedge[vi].lowcost>0, vi��V-U }
      printf("%c, %c\n", closedge[k].adjvex, G.vexs[k]); // ����������ı�
      closedge[k].lowcost = 0;                           // ��k���㲢��U��
      for (j = 0; j < G.vexnum; ++j)
          if (G.arcs[k][j].adj < closedge[j].lowcost)
          {
              // �¶��㲢��U������ѡ����С��
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
