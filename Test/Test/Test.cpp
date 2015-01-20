// Test.cpp : 定义控制台应用程序的入口点。
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
	int		fPosX;				// 下注X位置
	int		fPosY;				// 下注Y位置
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
	//定义MatrixNode类 
public:       
	int m;               //在位个数       
	int d;               //深度        
	int p;               //牌与其目标位置直接步数之和    
	int f;               //f=d+p，估价函数     
	int place[M][M];     //当前矩阵        
	int placetrue[M][M]; //目标矩阵    
	int kong_x;          //空位的横坐标        
	int kong_y;          //空位的纵坐标  
	//------------------------------------------------------------------------------- 
public:    MatrixNode();      
		   MatrixNode start(MatrixNode M_Matrix);           //初始矩阵     
		   int TruePlace(MatrixNode T_place );              //查找在位数    
		   int p_place(MatrixNode P_place);                 //坐标差绝对值之和       
		   int f_kongx(MatrixNode find_kongx);              //找出空格的横坐标    
		   int f_kongy(MatrixNode find_kongy);              //找出空格的纵坐标        
		   bool solved(MatrixNode M_Matrix);                //判断是否有解,奇偶性相同则有解，否则无解     
		   MatrixNode up_move(MatrixNode M_Matrix);         //空格上移       
		   MatrixNode down_move(MatrixNode M_Matrix);       //空格下移       
		   MatrixNode left_move(MatrixNode M_Matrix);       //空格左移       
		   MatrixNode right_move(MatrixNode M_Matrix);      //空格右移        
		   MatrixNode updata_m(MatrixNode M_Matrix);        //移动后更新状态        
		   MatrixNode parents(deque<MatrixNode> ilist,MatrixNode M_Matrix);          //找到该节点的父亲  
}; 
//=========================================================================================       
MatrixNode::MatrixNode()
{                           
	//目标矩阵          
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
	//初始矩阵       
	cout<<"请按如下格式输入初始矩阵(空位用0表示)："<<endl;    
	cout<<"1 2 3\n4 5 6\n7 0 8"<<endl;        
	cout<<"八数码的初始状态如下:" << endl;    
	for(int a = 0;a < M;a++)     
		for(int b = 0;b < M;b++ )      
			cin>>M_Matrix.place[a][b];    
	M_Matrix.d = 0;      
	M_Matrix = M_Matrix.updata_m( M_Matrix );        
	M_Matrix.d=M_Matrix.d-1;                             //初始更新时深度多加1，应该减去        
	M_Matrix.f=M_Matrix.f-1;      
	return M_Matrix;   
}  
//-------------------------
bool solved(MatrixNode M_Matrix)
{                      
	//判断是否可解     
	int num[8];     
	int target[8];     
	int a=0;      
	int b=0;      
	for(int m = 0;m < M;m++)
	{      
		for(int n = 0;n < M;n++ )              
		{
			if(M_Matrix.place[m][n] != 0)                         
				//不考虑空格       
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
	// 查找在位数        
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
	//坐标差的绝对值之和            
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
	//返回空格横坐标          
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
	//返回空格纵坐标     
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
	//空格上移        
	int num;                                                 
	//num为交换的中间变量            
	MatrixNode up_m = M_Matrix;                                     
	num = up_m.place[up_m.kong_x][up_m.kong_y];            
	up_m.place[up_m.kong_x][up_m.kong_y] = up_m.place[up_m.kong_x - 1][up_m.kong_y];            
	up_m.place[up_m.kong_x - 1][up_m.kong_y] = num;                
	up_m = up_m.updata_m(up_m);       
	return up_m;
}  //--------------------------------------------------------------------------------

MatrixNode MatrixNode::down_move(MatrixNode M_Matrix)
{       
	//空格下移    
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
	//空格左移        
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
	//空格右移           
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
	//移动后更新状态         
	MatrixNode up_m = M_Matrix;          
	up_m.m = up_m.TruePlace(up_m);                        
	// 查找在位数             
	up_m.p = up_m.p_place(up_m);                          
	//距离和                               
	up_m.d = M_Matrix.d+1;                                
	//深度加1       
	up_m.f = up_m.p + up_m.d;                             
	//估价值        
	up_m.kong_x = up_m.f_kongx(up_m);                     
	//找出空格的横坐 标             
	up_m.kong_y = up_m.f_kongy(up_m);                     
	//找出空格的纵坐标              
	return up_m;    
}  
//----------------------------------------------------------------------------------
bool  father(deque<MatrixNode> ilist, MatrixNode M_Matrix)
{  
	//寻找父节点      
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
	//输出矩阵            
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
	//检查新生成的节点是否已扩展    
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
	//不是新扩展的      
	Vi++;    
	}       
	return false;                         
	//是新扩展的     
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
		cout << "无法找到路径!!!" << endl;  
		return; 
	}     
	mat_trn = openlist.front();         
	//访问第一个元素     
	while(mat_trn.m != 8)
	{     
		closedlist.push_front(mat_trn);     
		openlist.pop_front();             
		//删除第一个元素  
		//-------向上移     
		mat_trn1 = mat_trn;     
		if(mat_trn1.f_kongx(mat_trn1) >= 1)
		{       
			mat_trn1 = mat_trn1.up_move(mat_trn1);      
			if(lookout(openlist,mat_trn1) == false &&  lookout(closedlist,mat_trn1)  ==  false)
			{          
				//检查新节点是否已扩展      
				openlist.push_front(mat_trn1);    
			}   
		}       
		//--------向下移       
		mat_trn2 = mat_trn;   
		if(mat_trn2.f_kongx(mat_trn2) <= 1)
		{       
			mat_trn2 = mat_trn2.down_move(mat_trn2); 
			if (lookout(openlist, mat_trn2) == false && lookout(closedlist, mat_trn2) == false)
			{          
				//检查新节点是否已扩展      
				openlist.push_front(mat_trn2);    
			}   
		}      
		//--------向左移      
		mat_trn3 =mat_trn;       
		if(mat_trn3.f_kongy(mat_trn3) >= 1)
		{       
			mat_trn3 = mat_trn3.left_move(mat_trn3);      
			if(lookout(openlist,mat_trn3) ==  false  &&  lookout(closedlist,mat_trn3)  ==  false)
			{          
				//检查新节点是否已扩展       
				openlist.push_front(mat_trn3);    
			}    
		}    
		//--------向右移       
		mat_trn4 = mat_trn;       
		if(mat_trn4.f_kongy(mat_trn4) <= 1)
		{       
			mat_trn4 = mat_trn4.right_move(mat_trn4);      
			if(lookout(openlist,mat_trn4) == false && lookout(closedlist,mat_trn4) ==  false)
			{          
				//检查新节点是否已扩展      
				openlist.push_front(mat_trn4);     
			}   
		}        
		sort(openlist.begin(),openlist.end(),less_f);         
		mat_trn=openlist.front();    
	}     
	cout<<"最优路径如下："<<endl;                                       
	//输出路径  
	printMatrix(mat_trn);      
	deque<MatrixNode>::iterator Vi = closedlist.begin();   
	while(Vi != (closedlist.end()-1))
	{                                  
		//由于我的father函数中用到首元素，所以不应该是不等于end    
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
	cout<<"走的步数:"<<step<<endl;  
}
#endif






