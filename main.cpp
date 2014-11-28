#include <cstdlib>
#include<list>
#include<string>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
//#include"game.h"
//#include<conio.h>
#define EMPTY *;
#define BLACK X;
#define WHITE O;
using namespace std;
int max_count;
char player;
char square[8][8];
char board[8][8];
char opp_player;
int mov_i=-1,mov_j=0;
int move[3][60];
int weight[8][8]={{99,-8,8,6,6,8,-8,99},{-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};
char output_board[8][8];
int depth;
std::ifstream input;
void setplayer(char Player)
{
player=Player;
}
void setopp_player(char player)
{
if(player=='X')
{
opp_player='O';
}
else
{
opp_player='X';
}
}
/*void get_moves(char board[8][8],char player,char direction,int i,int j)
{
if(direction=='u')
{
                                    int temp=i;
                                    int p=i;
                                    int check=temp;
                                    int count;
                                  while((p>=0&&p<8)&&(j>=0&&j<8))
                                  {
                                    if(p--&&board[p][j]==opp_player)
                                    {                                                                       
                                    while((check>=0&&check<8))
                                       {
                                       if(check--&&board[check][j]=='*')
                                        {
                                         move[0][mov_i++]=check;
                                         move[1][mov_i]=j;
                                         
                                                        
                                         for(int k=p;k>check;k--)
                                         {
                                             count++;
                                         }
                                         move[2][mov_i]=count+weight[check][j];
                                         }
                                      }
                                  }      
                              }        
                                  
                 }
                 if(direction=='e')
                 {
                             int p=i;
                             int q=j;
                             int check=p;
                             int check1=q;
                             int count;
                             while((p>=0&&p<8)&&(q>=0&&q<8))
                             {
                                if(p--&&q--&&board[p][q]==opp_player)
                                {                            
                                while((check>=0&&check<8)&&(check1>=0&&check1<8))
                                 {
                                   if(check--&&check1--&&board[check][check1]=='*')
                                   {                                              
                                     move[0][mov_i++]=check;
                                         move[1][mov_i]=check1;                                                                                     
                                   for(int k=p,m=q;k>check,m>check1;k--,m--)
                                   {
                       
                                       count++;
                                   }
                              move[2][mov_i]=count+weight[check][check1];
                                 }
                             }
                            
                 }
                 }
                 }
                 if(direction=='l')
                 {
                                     int temp=j;
                                    int p=j;
                                    int count=0;
                                    int check=temp;
                                  while((p>=0&&p<8)&&(i>=0&&i<8))
                                  {  
                                    if(p--&&board[i][p]==opp_player) 
                                    {                                                                    
                                    while((check>=0&&check<8))
                                       {
                                       if(check--&&board[i][check]=='*')
                                       {
                                         move[0][mov_i++]=i;
                                         move[1][mov_i]=check;                                          
                                         for(int k=p;k>check;k--)
                                         {
                                             count++;
                                         }
                                         move[2][mov_i]=count+weight[i][check];
                                      }
                                  }
                                  }
                                  }                         
			  }
			  if(direction=='s')
                 {
                             int p=i;
                             int q=j;
                             int count=0;
                             int check=p;
                             int check1=q;
                             while((p>=0&&p<8)&&(q>=0&&q<8))
                             {
                                if(p++&&q--&&board[p][q]==opp_player)
                                {                            
                                while((check>=0&&check<8)&&(check1>=0&&check1<8))
                                 {
                                   if(check++&&check1--&&board[check][check1]=='*')
                                   {                                              
                                   move[0][mov_i++]=check;
                                   move[1][mov_i]=check1;                                                                                        
                                   for(int k=p, m=q;k<check,m>check1;k++,m--)
                                   {
                       
                                       count++;
                                   }
                                   move[2][mov_i]=count+weight[check][check1];
                                 }
                             }
                             }
                             }         
                 }
                 if(direction=='d')
                 {
                                    int temp=i;
                                    int p=i;
                                    int check=temp;
                                    int count=0;
                                  while((p>=0&&p<8)&&(j>=0&&j<8))
                                  {     
                                        if(p++&&board[p][j]==opp_player)
                                        {                                     
                                        while((check>=0&&check<8))
                                        {
                                        if(check++&&board[check][j]=='*')
                                        {
                                         move[0][mov_i++]=check;
                                         move[1][mov_i]=j;                                                                                
                                         for(int k=p;k<check;k++)
                                         {
                                             count++;
                                         }
                                         move[2][mov_i]=count+weight[check][j]; 
                                      }
                                  }
                                  }
                                  }           
                 }
                  if(direction=='w')
                 {
                             int p=i;
                             int q=j;
                             int check=p;
                             int check1=q;
                             int count;
                             while((p>=0&&p<8)&&(q>=0&&q<8))
                             {
                                if(p++&&q++&&board[p][q]==opp_player)
                                {
                                 while((check>=0&&check<8)&&(check1>=0&&check1<8))
                                 {
                                   if(check++&&check1++&&board[check][j]=='*')
                                   {                                               
                                    move[0][mov_i++]=check;
                                         move[1][mov_i]=check1;                                                                                                                                  
                                   for(int k=p,m=q;k<check,m<check1;k++,m++)
                                   {
                                     count++;
                                   }
                                 move[2][mov_i]=count+weight[check][check1]; 
                                 }
                             }
                             }
                             }
                 }
                 
			  if(direction=='r')
                 {
                                    int temp=j;
                                    int p=j;
                                    int count=0;
                                    int check=temp;
                                  while((p>=0&&p<8)&&(i>=0&&i<8))
                                  {     
                                  if(p++&&board[i][p]==opp_player)
                                  {                                     
                                    while((check>=0&&check<8))
                                       {
                                        if(check++&&board[i][check]=='*')
                                        {                      
                                         move[0][mov_i++]=i;
                                         move[1][mov_i]=check;                                                                                   
                                         for(int k=p;k<check;k++)
                                         {
                                            count++;
                                         }
                                         move[2][mov_i]=count+weight[i][check]; 
                                      }
                                  }
                                  }
                                  }
			  }
			   if(direction=='n')
                 {
                             int p=i;
                             int q=j;
                             int check=p;
                             int check1=q;
                             int count;
                             while((p>=0&&p<8)&&(q>0&&q<8))
                             {
                                if(p--&&q++&&board[p][q]==opp_player)
                                {                           
                                while((check>=0&&check<8)&&(check1>=0&&check1<8))
                                 {
                                  if(check--&&check1++&&board[check][check1]=='8')
                                  {                                               
                                   move[0][mov_i++]=check;
                                   move[1][mov_i]=check1;                                                                                          
                                   for(int k=p,m=q;k>check,m<check1;k--,m++)
                                   {
                                        count++;
                                   }
                                   move[2][mov_i]=count+weight[check][check1];
                                 }
                             }
                             }
                             }     
                 }
			  
                 
     }
void find_move()
{             
for(int i=0;i<8;i++)
      {
      for(int j=0;j<8;j++)
      {
        if(board[i][j]=player)
        {              
        get_moves(board,player,'u',i,j);
        get_moves(board,player,'e',i,j);
        get_moves(board,player,'l',i,j);
        get_moves(board,player,'s',i,j);
        get_moves(board,player,'d',i,j);
        get_moves(board,player,'d',i,j);
        get_moves(board,player,'w',i,j);
        get_moves(board,player,'r',i,j);
        get_moves(board,player,'n',i,j);
        }
      }
      }
}*/

int strategy=-1;
void setmove_zero()
{
for(int i=0;i<3;i++)
      {
       for(int j=0;j<60;j++)
       {
               move[i][j]=0;
       }
       }
}  
void find_move(int i, int j)
{
    for(int j=0;j<8;j++)
    {
    for(int k=0;k<8;k++)
    {
      output_board[j][k]=board[j][k];
    }
    } 
}
                       
//vector<int> board(100);
int greedy_strategy(char player, int depth)
{
    setopp_player(player);
				for(int j=0;j<8;j++)
				{
					for(int k=0;k<8;k++)
					{
    	             if(board[j][k]=='*')
    	             {
							find_move(j,k);                   
                      }   
//find_duplicate(move);
    
cout<<"greedy called"<<endl;
return 0;   
} 


void fileread()
{
if (input.is_open())
 {
    input>>strategy>>player>>depth;
    cout<<strategy<<"\n";
    cout<<player<<"\n";
    cout<<depth<<"\n";
    for(int i=0;i<8;i++)
    {
    for(int j=0;j<8;j++)
     {
     input>>board[i][j];
     
    }
    }
}
}
int main(int argc, char *argv[])
{
 input.open("input.txt");
 fileread();
if(strategy==2)
{
   int check=greedy_strategy(player,depth);
}
input.close();
//_getch();
}
