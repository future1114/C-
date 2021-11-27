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
/*Status LocateVex(MGraph G, VertexType u)//���ض���u��ͼ�е�λ��
{
    for (int i = 0; i < G.vexnum; i++)
        if (G.vexs[i] == u)
            return i;
    return -1;
}
*/
int LocateVex(MGraph G,VertexType v)//����Ԫ��v��һά���� Vertex[] �е��±꣬�������±� 
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


//--- �㷨7.4��7.5ʹ�õ�ȫ�ֱ��� ---
bool visited[MAX_VERTEX_NUM];   // ���ʱ�־����
Status(*VisitFunc)(int v);    // ��������
void DFS(MGraph G, int v) {  // �㷨7.5
   // �ӵ�v����������ݹ��������ȱ���ͼG��
    int w;
    visited[v] = true;   VisitFunc(v);  // ���ʵ�v������
    for (w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w))
        if (!visited[w])   // ��v����δ���ʵ��ڽӶ���w�ݹ����DFS
            DFS(G, w);
}
void DFSTraverse(MGraph G, Status(*Visit)(int v)) {  // �㷨7.4
 // ��ͼG��������ȱ�����
    int v;
    VisitFunc = Visit; // ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
    for (v = 0; v < G.vexnum; ++v) visited[v] = false; // ���ʱ�־�����ʼ��
    for (v = 0; v < G.vexnum; ++v)
        if (!visited[v]) DFS(G, v);         // ����δ���ʵĶ������DFS
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
