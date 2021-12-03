#include<iostream>
#include<string>

using namespace std;
typedef int Status;

#define INFINITY 100 //�����
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

Status FirstAdjVex(MGraph G, int v) {    //Ѱ��ͼG��v�ĵ�һ���ڽӵ�
    for (int i = 0; i < G.vexnum; i++) {
        if (G.arcs[v][i].adj != INFINITY) return i;
    }
    return -1;
}

Status NextAdjVex(MGraph G, int v, int w) {   //Ѱ��ͼG��v������w֮�����һ���ڽӵ�
    for (int i = w + 1; i < G.vexnum; i++) {
        if (G.arcs[v][i].adj != INFINITY) return i;
    }
    return -1;
}

int LocateVex(MGraph &G,VertexType v){//����Ԫ��v��һά���� Vertex[] �е��±꣬�������±� 
	int i;
	for(i=0;i<G.vexnum;i++){
		if(v==G.vexs[i]){
			return i;
		}
	}
    cout << "No Such Vertex!" << endl;
    return -1;
}

Status CreateUDN(MGraph &G) {//  �㷨 7.2
  // �������飨�ڽӾ��󣩱�ʾ��������������G��
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
  } // ���춥������
  for (i=0; i<G.vexnum; ++i )  // ��ʼ���ڽӾ���
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  for (k=0; k<G.arcnum; ++k ) {  // �����ڽӾ���
      cout << "v1(char) : ";
      cin >> v1;
      cout << "v2 (char) : ";
      cin >> v2;
      cout << "w (int) : ";
      cin >> w;
      // ����һ���������Ķ��㼰Ȩֵ
      i = LocateVex(G, v1);
      j = LocateVex(G, v2);
      cout << i << " " << j << endl;
      // ȷ��v1��v2��G��λ��
      G.arcs[i][j].adj = w; // ��<v1,v2>��Ȩֵ
      // if (IncInfo) scanf(G.arcs[i][j].info); // ���뻡���������Ϣ
      G.arcs[j][i].adj = G.arcs[i][j].adj; // ����<v1,v2>�ĶԳƻ�<v2,v1>
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
    MiniSpanTree_PRIM(G, 'a');
    return 0;
}