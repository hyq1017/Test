// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//
//testlua.c  


#if 1
#include "stdafx.h"
#include <iostream>

using namespace std;

void QuickSort(int a[], int left, int right)
{
	int lower = left;
	int higher = right;
	int key = a[higher];
	int tmp = 0;
	if (lower < higher)
	{
		while (lower < higher)
		{
			while (lower < higher && a[lower] < key)
			{
				lower++;
			}
			a[higher] = a[lower];
			while (lower < higher && a[higher] > key)
			{
				higher--;
			}
			a[lower] = a[higher];	
		}
		a[lower] = key;
		QuickSort(a, left, lower-1);
		QuickSort(a, lower+1, right);
	}
}
void BinarySort(int a[], int count)
{
	int tmp = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = i; j < count-1; j++)
		{
			if (a[j + 1] < a[j])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j + 1] = tmp;
			}
		}
	}
}
struct MyStruct
{
	MyStruct()
	{
		fPosX = 1;
		fPosY = 2;
	}
	int		fPosX;				// ��עXλ��
	int		fPosY;				// ��עYλ��
};
int _tmain(int argc, _TCHAR* argv[])
{
	MyStruct a;
	MyStruct b;
	MyStruct c;
	a.fPosX = 2;
	a.fPosY = 2;
	b.fPosX = 3;
	b.fPosY = 3;
	c.fPosX = 4;
	c.fPosY = 4;
	MyStruct aa[3] = {a,b,c};
	MyStruct*pA = aa;

	cout << pA->fPosX << endl;
	cout << (pA+1)->fPosX << endl;

	//cout << pA->fPosX << endl;

	return 0;
}

#endif
#if 0
#include<iostream> 
#include<deque> 
#include<algorithm> 
#include<iterator> 
using namespace std; 
#define M 3     
class MatrixNode{          
	//����MatrixNode�� 
public:       
	int m;               //��λ����       
	int d;               //���        
	int p;               //������Ŀ��λ��ֱ�Ӳ���֮��    
	int f;               //f=d+p�����ۺ���     
	int place[M][M];     //��ǰ����        
	int placetrue[M][M]; //Ŀ�����    
	int kong_x;          //��λ�ĺ�����        
	int kong_y;          //��λ��������  
	//------------------------------------------------------------------------------- 
public:    MatrixNode();      
		   MatrixNode start(MatrixNode M_Matrix);           //��ʼ����     
		   int TruePlace(MatrixNode T_place );              //������λ��    
		   int p_place(MatrixNode P_place);                 //��������ֵ֮��       
		   int f_kongx(MatrixNode find_kongx);              //�ҳ��ո�ĺ�����    
		   int f_kongy(MatrixNode find_kongy);              //�ҳ��ո��������        
		   bool solved(MatrixNode M_Matrix);                //�ж��Ƿ��н�,��ż����ͬ���н⣬�����޽�     
		   MatrixNode up_move(MatrixNode M_Matrix);         //�ո�����       
		   MatrixNode down_move(MatrixNode M_Matrix);       //�ո�����       
		   MatrixNode left_move(MatrixNode M_Matrix);       //�ո�����       
		   MatrixNode right_move(MatrixNode M_Matrix);      //�ո�����        
		   MatrixNode updata_m(MatrixNode M_Matrix);        //�ƶ������״̬        
		   MatrixNode parents(deque<MatrixNode> ilist,MatrixNode M_Matrix);          //�ҵ��ýڵ�ĸ���  
}; 
//=========================================================================================       
MatrixNode::MatrixNode()
{                           
	//Ŀ�����          
	placetrue[0][0] = 1;                                    
	placetrue[0][1] = 2;       
	placetrue[0][2] = 3;        
	placetrue[1][0] = 8;       
	placetrue[1][1] = -1;         
	placetrue[1][2] = 4;
	placetrue[2][0] = 7;        
	placetrue[2][1] = 6;       
	placetrue[2][2] = 5;
}


MatrixNode MatrixNode::start(MatrixNode M_Matrix)
{  
	//��ʼ����       
	cout<<"�밴���¸�ʽ�����ʼ����(��λ��0��ʾ)��"<<endl;    
	cout<<"1 2 3\n4 5 6\n7 0 8"<<endl;        
	cout<<"������ĳ�ʼ״̬����:" << endl;    
	for(int a = 0;a < M;a++)     
		for(int b = 0;b < M;b++ )      
			cin>>M_Matrix.place[a][b];    
	M_Matrix.d = 0;      
	M_Matrix = M_Matrix.updata_m( M_Matrix );        
	M_Matrix.d=M_Matrix.d-1;                             //��ʼ����ʱ��ȶ��1��Ӧ�ü�ȥ        
	M_Matrix.f=M_Matrix.f-1;      
	return M_Matrix;   
}  
//-------------------------
bool solved(MatrixNode M_Matrix)
{                      
	//�ж��Ƿ�ɽ�     
	int num[8];     
	int target[8];     
	int a=0;      
	int b=0;      
	for(int m = 0;m < M;m++)
	{      
		for(int n = 0;n < M;n++ )              
		{
			if(M_Matrix.place[m][n] != 0)                         
				//�����ǿո�       
				num[a++]=M_Matrix.place[m][n];      
			if(M_Matrix.placetrue[m][n] != -1)        
				target[b++]=M_Matrix.placetrue[m][n];    
		}     
	}   
	int i,j;    
	int count_num = 0,count_target = 0;   
	for (i = 0;i < (8-1);i++)
	{    
		for (j = i+1;j < 8;j++)    
		{     
			if(num[j] < num[i])                      
				count_num++;    
			if(target[j]<target[i])                 
				count_target++;       
		} 
	}    
	if ((count_num % 2 == 0 && count_target % 2 == 0) || (count_num % 2 == 1 && count_target % 2 == 1))    
		return true;                 
	else      
		return false;     
}  
//--------------------------------------------
int MatrixNode::TruePlace(MatrixNode T_place) 
{              
	// ������λ��        
	T_place.m = 0;     
	int NumT_place = 0;          
	for(int i = 0;i < M;i++)
	{    
		for(int j = 0;j < M;j++ )
		{     
			if( T_place.place[i][j] == placetrue[i][j]) 
			{        
				T_place.m = T_place.m + 1;      
				NumT_place = NumT_place + 1;      
			}      
		}      
	}        
	return NumT_place;     
}  
//----------------
int MatrixNode::p_place(MatrixNode P_place)
{                   
	//�����ľ���ֵ֮��            
	P_place.p = 0;     
	int num = 0;     
	for(int Pa = 0;Pa < M;Pa++)
	{      
		for(int Pb = 0;Pb < M;Pb++)
		{         
			if(P_place.place[Pa][Pb] == 1)
			{                        
				P_place.p = P_place.p+ (abs(Pa - 0)+abs(Pb - 0));        
			}                     
			if(P_place.place[Pa][Pb] == 2)
			{        
				P_place.p = P_place.p+ (abs(Pa - 0)+abs(Pb - 1));       
			}        
			if(P_place.place[Pa][Pb] == 3)
			{           
				P_place.p = P_place.p+ (abs(Pa - 0)+abs(Pb - 2));       
			}           
			if(P_place.place[Pa][Pb] == 4)
			{         
				P_place.p = P_place.p+ (abs(Pa - 1)+abs(Pb - 2));       
			}        
			if(P_place.place[Pa][Pb] == 5)
			{        
				P_place.p = P_place.p+ (abs(Pa - 2)+abs(Pb - 2));           
			} 
			if (P_place.place[Pa][Pb] == 6)
			{ 
				P_place.p = P_place.p + (abs(Pa - 2) + abs(Pb - 1)); 
			}        
			if (P_place.place[Pa][Pb] == 7)
			{ 
				P_place.p = P_place.p + (abs(Pa - 2) + abs(Pb - 0)); 
			}        
			if (P_place.place[Pa][Pb] == 8)
			{ 
				P_place.p = P_place.p + (abs(Pa - 1) + abs(Pb - 0)); 
			}
		}       
	}         
	num = P_place.p;      
	return num;     
}  
//------------------
int MatrixNode::f_kongx(MatrixNode find_kongx)
{                
	//���ؿո������          
	int num;     
	for(int i = 0;i < M;i++)
	{      
		for(int j = 0;j < M;j++)
		{        
			if(find_kongx.place[i][j] == 0)
			{            
				num = i;       
			}      
		}      
	}      
	return num;     
}  
//-----------------------------------------------
int MatrixNode::f_kongy(MatrixNode find_kongy)
{
	//���ؿո�������     
	int num;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (find_kongy.place[i][j] == 0)
			{
				num = j;
			}
		}
		return num;
	}
}
//----------------------------------------------------------------------------------

MatrixNode MatrixNode::up_move(MatrixNode M_Matrix)
{         
	//�ո�����        
	int num;                                                 
	//numΪ�������м����            
	MatrixNode up_m = M_Matrix;                                     
	num = up_m.place[up_m.kong_x][up_m.kong_y];            
	up_m.place[up_m.kong_x][up_m.kong_y] = up_m.place[up_m.kong_x - 1][up_m.kong_y];            
	up_m.place[up_m.kong_x - 1][up_m.kong_y] = num;                
	up_m = up_m.updata_m(up_m);       
	return up_m;
}  //--------------------------------------------------------------------------------

MatrixNode MatrixNode::down_move(MatrixNode M_Matrix)
{       
	//�ո�����    
	int num;       
	MatrixNode up_m = M_Matrix;           
	num = up_m.place[up_m.kong_x][up_m.kong_y];          
	up_m.place[up_m.kong_x][up_m.kong_y] =  up_m.place[up_m.kong_x  +  1][up_m.kong_y ];           
	up_m.place[up_m.kong_x + 1][up_m.kong_y ] = num;                
	up_m = up_m.updata_m(up_m);    
	return up_m;     
}  
//-----------------------------------------------------------------------------------        
MatrixNode MatrixNode::left_move(MatrixNode M_Matrix)
{       
	//�ո�����        
	int num;     
	MatrixNode up_m = M_Matrix;            
	num = up_m.place[up_m.kong_x][up_m.kong_y];           
	up_m.place[up_m.kong_x][up_m.kong_y] =  up_m.place[up_m.kong_x ][up_m.kong_y - 1 ];            
	up_m.place[up_m.kong_x ][up_m.kong_y - 1] = num;                 
	up_m = up_m.updata_m(up_m);     
	return up_m;     
}  
//-----------------------------------------------------------------------------------    
MatrixNode MatrixNode::right_move(MatrixNode M_Matrix)
{      
	//�ո�����           
	int num;        
	MatrixNode up_m = M_Matrix;         
	num = up_m.place[up_m.kong_x][up_m.kong_y];            
	up_m.place[up_m.kong_x][up_m.kong_y] =  up_m.place[up_m.kong_x ][up_m.kong_y + 1 ];            
	up_m.place[up_m.kong_x ][up_m.kong_y + 1] = num;             
	up_m = up_m.updata_m(up_m);      
	return up_m; 
}
MatrixNode MatrixNode::updata_m(MatrixNode M_Matrix)
{       
	//�ƶ������״̬         
	MatrixNode up_m = M_Matrix;          
	up_m.m = up_m.TruePlace(up_m);                        
	// ������λ��             
	up_m.p = up_m.p_place(up_m);                          
	//�����                               
	up_m.d = M_Matrix.d+1;                                
	//��ȼ�1       
	up_m.f = up_m.p + up_m.d;                             
	//����ֵ        
	up_m.kong_x = up_m.f_kongx(up_m);                     
	//�ҳ��ո�ĺ��� ��             
	up_m.kong_y = up_m.f_kongy(up_m);                     
	//�ҳ��ո��������              
	return up_m;    
}  
//----------------------------------------------------------------------------------
bool  father(deque<MatrixNode> ilist, MatrixNode M_Matrix)
{  
	//Ѱ�Ҹ��ڵ�      
	MatrixNode M_Matrix1 = ilist.front();            
	MatrixNode up_m;     
	int m;        
	up_m = M_Matrix1.up_move(M_Matrix1);       
	m = 0;      
	for(int a1 = 0;a1 < M;a1++)                   
		for(int b1 = 0;b1 < M;b1++ )
		{              
			if(up_m.place[a1][b1] == M_Matrix.place[a1][b1])       
				m++;       
		}       
	if(m == 9)       
		return true;             
	up_m=M_Matrix1.down_move(M_Matrix1);      
	m = 0;      
	for(int a2 = 0;a2 < M;a2++)                   
		for(int b2 = 0;b2 < M;b2++ )
		{             
			if(up_m.place[a2][b2] == M_Matrix.place[a2][b2])       
				m++;      
		}       
	if(m == 9)          
		return true;              
	up_m=M_Matrix1.left_move(M_Matrix1);     
	m = 0;       
	for(int a3 = 0;a3 < M;a3++)                     
		for(int b3 = 0;b3 < M;b3++ )
		{ 
			if (up_m.place[a3][b3] == M_Matrix.place[a3][b3])        
				m++;
		}           
	if (m == 9)           
		return true;              
	up_m = M_Matrix1.right_move(M_Matrix1);      
	m = 0;      
	for (int a4 = 0; a4 < M; a4++)                   
		for (int b4 = 0; b4 < M; b4++)
		{ 
			if (up_m.place[a4][b4] == M_Matrix.place[a4][b4])            
				m++; 
		}           
	if (m == 9)      
		return true;       
	else       
		return false;   
}  
//----------------------------------------------------------------------------------- 
void printMatrix(const MatrixNode Matrix)
{                          
	//�������            
	for(int i = 0;i < M;i++)
	{        
		for(int j = 0;j < M;j++ )
		{            
			cout<<Matrix.place[i][j]<<",";     
		}              
		cout<<endl;       
	}             
	cout<<endl;     
}  
//-----------------------------------------------------------------------------------       
bool less_f(const MatrixNode M_Matrix1, const MatrixNode M_Matrix2) 
{         
	return M_Matrix1.f < M_Matrix2.f;   
}  
//----------------- ------------------------------------------------------------------       
bool lookout(deque<MatrixNode> ilist, MatrixNode M_Matrix)
{         
	//��������ɵĽڵ��Ƿ�����չ    
	deque<MatrixNode>::iterator Vi = ilist.begin();    
	int i,j,m;     
	while(Vi != ilist.end())
	{      
		m=0;     
		for(i = 0;i < M;i++)                   
			for(j = 0;j < M;j++ )
			{       
				if((*Vi).place[i][j] == M_Matrix.place[i][j])       
					m++;          
			} 
	if (m == 9)        
		return true;              
	//��������չ��      
	Vi++;    
	}       
	return false;                         
	//������չ��     
}  
//=========================================================================

void main()
{
	
	int step = 0;  
	MatrixNode mat;     
	MatrixNode mat_trn;   
	MatrixNode mat_trn1;  
	MatrixNode mat_trn2;    
	MatrixNode mat_trn3;  
	MatrixNode mat_trn4;     
	MatrixNode parent;        
	mat = mat.start(mat);      
	deque<MatrixNode> openlist;  
	openlist.push_front(mat);      
	deque<MatrixNode> closedlist;   
	if (solved(mat) == false)   
	{ 
		cout << "�޷��ҵ�·��!!!" << endl;  
		return; 
	}     
	mat_trn = openlist.front();         
	//���ʵ�һ��Ԫ��     
	while(mat_trn.m != 8)
	{     
		closedlist.push_front(mat_trn);     
		openlist.pop_front();             
		//ɾ����һ��Ԫ��  
		//-------������     
		mat_trn1 = mat_trn;     
		if(mat_trn1.f_kongx(mat_trn1) >= 1)
		{       
			mat_trn1 = mat_trn1.up_move(mat_trn1);      
			if(lookout(openlist,mat_trn1) == false &&  lookout(closedlist,mat_trn1)  ==  false)
			{          
				//����½ڵ��Ƿ�����չ      
				openlist.push_front(mat_trn1);    
			}   
		}       
		//--------������       
		mat_trn2 = mat_trn;   
		if(mat_trn2.f_kongx(mat_trn2) <= 1)
		{       
			mat_trn2 = mat_trn2.down_move(mat_trn2); 
			if (lookout(openlist, mat_trn2) == false && lookout(closedlist, mat_trn2) == false)
			{          
				//����½ڵ��Ƿ�����չ      
				openlist.push_front(mat_trn2);    
			}   
		}      
		//--------������      
		mat_trn3 =mat_trn;       
		if(mat_trn3.f_kongy(mat_trn3) >= 1)
		{       
			mat_trn3 = mat_trn3.left_move(mat_trn3);      
			if(lookout(openlist,mat_trn3) ==  false  &&  lookout(closedlist,mat_trn3)  ==  false)
			{          
				//����½ڵ��Ƿ�����չ       
				openlist.push_front(mat_trn3);    
			}    
		}    
		//--------������       
		mat_trn4 = mat_trn;       
		if(mat_trn4.f_kongy(mat_trn4) <= 1)
		{       
			mat_trn4 = mat_trn4.right_move(mat_trn4);      
			if(lookout(openlist,mat_trn4) == false && lookout(closedlist,mat_trn4) ==  false)
			{          
				//����½ڵ��Ƿ�����չ      
				openlist.push_front(mat_trn4);     
			}   
		}        
		sort(openlist.begin(),openlist.end(),less_f);         
		mat_trn=openlist.front();    
	}     
	cout<<"����·�����£�"<<endl;                                       
	//���·��  
	printMatrix(mat_trn);      
	deque<MatrixNode>::iterator Vi = closedlist.begin();   
	while(Vi != (closedlist.end()-1))
	{                                  
		//�����ҵ�father�������õ���Ԫ�أ����Բ�Ӧ���ǲ�����end    
		if(father(closedlist,mat_trn) == true)
		{     
			parent = closedlist.front();     
			printMatrix(parent);     
			mat_trn = parent;   
			step = step+1;   
		}     
		Vi++;      
		closedlist.pop_front();  
	}  
	printMatrix(mat);  
	step++;    
	cout<<"�ߵĲ���:"<<step<<endl;  
}
#endif






