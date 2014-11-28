#include <cstdlib>
#include<list>
#include<string>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
//#include"game.h"
#include<conio.h>
#define EMPTY *;
#define BLACK X;
#define WHITE O;
using namespace std;
std::ofstream output;
int max_count;
int mov_i_new=-1;
char player,max_player,min_player;
char square[8][8];
char board[8][8],board_final[8][8],board_current[8][8],board_inter[8][8],final_board[8][8];
char opp_player;
char buf[10];
int max_fit=-1,final_val=0,mov_i=-1,mov_j=-1;
int mov_check=-1;
int move[2][60],legal_move[64];
int weight[8][8]={{99,-8,8,6,6,8,-8,99},{-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};
char output_board[8][8];
int strategy=-1;
int depth;
int flipper=0;
bool found_move=false;
bool pass_turn=true;
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
void direction_east_minimax(int i,int j)
	{
		if( ((i-1) <8) && ((j-1) < 8) && ((i-1) >= 0) && ((j-1) >= 0) )
		{
			if(board_inter[i-1][j-1]==opp_player)
			{
				output_board[i-1][j-1] = player;
				flipper++;
				direction_east_minimax(i-1,j-1);
			}
			if (board_inter[i-1][j-1]==player)
			{
				max_count = 1;
			}	
			if (board_inter[i-1][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j+s] = opp_player;
				}
			}
		}	
	}
 void direction_up_minimax(int i,int j)
	{
		if( ((i-1) <8) && ((i-1) >= 0) )
		{
			if(board_inter[i-1][j]==opp_player)
			{
				output_board[i-1][j] =player;
				flipper++;
				direction_up_minimax(i-1,j);
			}
			if (board_inter[i-1][j]==player)
			{
				max_count = 1;
			}	
			if (board_inter[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j] = opp_player;
				}
			}
		}	
	}
	
void direction_north_minimax(int i,int j)
	{
		if( ((i-1) <8) && ((j+1) <8) && ((i-1) >= 0) && ((j+1) >= 0) )
		{
			if(board_inter[i-1][j]==opp_player)
			{
				output_board[i-1][j+1] =player;
				flipper++;
				direction_north_minimax(i-1,j+1);
			}
			if (board_inter[i-1][j]==player)
			{
				max_count = 1;
			}
			if (board_inter[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j-s] = opp_player;
				}
			}
		}	
	}
 void direction_left_minimax(int i,int j)
	{
		if( ((j-1) <= 8) && ((j-1) >= 0) )
		{
			if(board_inter[i][j-1]==opp_player)
			{
				output_board[i][j-1] = player;
				flipper++;
				direction_left_minimax(i,j-1);
			}
			if (board_inter[i-1][j]==player)
			{
			max_count = 1;
			}
		if (board_inter[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j+s] = opp_player;
				}
			}
		}	
	}
 void direction_right_minimax(int i,int j)
	{
		if( ((j+1) < 8) && ((j+1) >= 0) )
		{
			if(board_inter[i][j+1]==opp_player)
			{
				output_board[i][j+1] = player;
				flipper++;
				direction_right_minimax(i,j+1);
			}
			if (board_inter[i][j+1]==player)
			{
			max_count = 1;
			}
		if (board_inter[i][j+1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j-s] = opp_player;
				}
			}
		}	
	}
	void direction_south_minimax(int i,int j)
	{
		if( ((i+1) <8) && ((j-1) <8) && ((i+1) >= 0) && ((j-1) >= 0) )
		{
			if(board_inter[i+1][j-1]==opp_player)
			{
				output_board[i+1][j-1] = player;
				flipper++;
				direction_south_minimax(i+1,j-1);
			}
			if (board_inter[i+1][j-1]==player)
			{
			max_count = 1;
			}
			if (board_inter[i+1][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i-s][j+s] =opp_player;
				}
			}
		}	
	}
     void direction_down_minimax(int i,int j)
	{
		if( ((i+1) <8) && ((i+1) >= 0) )
		{
			if(board_inter[i+1][j]==opp_player)
			{
				output_board[i+1][j] = player;
				flipper++;
				direction_down_minimax(i+1,j);
			}
			if (board_inter[i+1][j]==player)
			{
			max_count = 1;
			}
			if (board_inter[i+1][j]=='*')
			{
                for(int s=0;s<flipper;s++)
				{
				
					output_board[i-s][j] = opp_player;
				}
			}
		}	
	}
    void direction_west_minimax(int i,int j)
	{
		if( ((i+1) <8) && ((j+1) <8) && ((i+1) >= 0) && ((j+1) >= 0) )
		{
			if(board_inter[i+1][j+1]==opp_player)
			{
				output_board[i+1][j+1] = player;
				flipper++;
				direction_west_minimax(i+1,j+1);
			}
			if (board_inter[i+1][j+1]==player)
			{
			max_count = 1;
			}
			if (board_inter[i+1][j+1]=='*')
			{
                for(int s=0;s<flipper;s++)
				{
				output_board[i-s][j-s] =opp_player;
				}
			}
		}	
	} 
int find_move_minimax(int i, int j,char board_current[8][8],char max_player,char min_player,int max_fit1)
{
     player=max_player;
opp_player=min_player;
    for(int l=0;l<8;l++)
    {
    for(int k=0;k<8;k++)
    {
      output_board[l][k]=board_current[l][k];
      board_inter[l][k]=board_current[l][k];
     // cout<<board_current[l][k];
      
    }
    } 
    //cout<<"finding legal moves for i="<<i<<"and j="<<j;
    flipper = 0;
		if( (i-1 < 8) && (j-1 < 8) && (i-1 >= 0) && (j-1 >= 0) ) 
		{
			if(board_inter[i-1][j-1]==opp_player)
			{
				output_board[i-1][j-1] =player;
				flipper++;
				direction_east_minimax(i-1,j-1);
				if(max_count == 1)
				{
					output_board[i][j] =player ;
					max_count = 0;
				}
			}
		}
		flipper = 0;
		if( ((i-1) <8) && ((i-1) >= 0) ) 
		{		
			if((board_inter[i-1][j]==opp_player))
			{
				output_board[i-1][j] = player;
				flipper++;
				direction_up_minimax(i-1,j);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
						
			}
		}
		
		flipper = 0;
		if( ((i-1) < 8) && ((j+1) < 8) && ((i-1) >= 0) && ((j+1) >= 0) ) 
		{
			if(board_inter[i-1][j+1]==opp_player)
			{		
				output_board[i-1][j+1] = player;
				flipper++;
				direction_north_minimax(i-1,j+1);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((j-1) <8) && ((j-1) >= 0) ) 
		{
			if(board_inter[i][j-1]==opp_player)
			{		
				output_board[i][j-1] = player;
				flipper++;
				direction_left_minimax(i,j-1);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((j+1) < 8) && ((j+1) >= 0) ) 
		{
				
			if(board_inter[i][j+1]==opp_player)
			{		
                output_board[i][j+1] = player;
				flipper++;
				direction_right_minimax(i,j+1);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((i+1) <8) && ((j-1) <8) && ((i+1) >= 0) && ((j-1) >= 0) ) 
		{
				
			if(board_inter[i+1][j-1]==opp_player)
			{						
				output_board[i+1][j-1] = player;
				flipper++;
				direction_south_minimax(i+1,j-1);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((i+1) < 8) && ((j+1) >= 0) ) 
		{
					
			if(board_inter[i+1][j]==opp_player)
			{			
				output_board[i+1][j] = player;
				flipper++;
				direction_down_minimax(i+1,j);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((i+1) <8) && ((j+1) <8) && ((i+1) >= 0) && ((j+1) >= 0) ) 
		{
			if(board_inter[i+1][j+1]==opp_player)
			{			
				output_board[i+1][j+1] = player;
				flipper++;
				direction_west_minimax(i+1,j+1);
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
                for(int l=0;l<8;l++)
                {
				   for(int k=0;k<8;k++)
					{
    	             if(output_board[l][k]!=board_inter[l][k])
    	             {
							pass_turn=false;
							                   
                     }
						//cout<<output_board[l][k];
                    }
                } 
                if(pass_turn==false)
                {
				  found_move=true;
                  mov_check+=1;
                  char buf[10];
                  sprintf(buf,"%d%d",i,j);
                  move[0][mov_check]=atoi(buf);
                  cout<<"found legal move for "<<buf<<endl;  
                  int player_weight=0,opp_player_weight=0; 
                  for(int l=0;l<8;l++)
		          {
			      for(int k=0;k<8;k++)
			      {
				  if(output_board[l][k]==player)
				  {
					player_weight += weight[l][k];
				  }
                  if(output_board[l][k]==opp_player)
				  {
					opp_player_weight += weight[l][k];
					
				  }
                  }
                  }
				move[1][mov_check]=player_weight-opp_player_weight;
				if(move[1][mov_check]>max_fit1)				
				{
                   max_fit1=move[1][mov_check];
                   final_val=atoi(buf);
                   for(int l=0;l<8;l++)
					{
                     for(int m=0;m<8;m++)
					{
                     board_final[l][m]=output_board[l][m];
                     }
                     }
                     
                 }
                 if(move[1][mov_check]==max_fit1)
                 {
                 final_val=atoi(buf);
                 for(int l=0;l<8;l++)
					{
                     for(int m=0;m<8;m++)
					{
                     board_final[l][m]=output_board[l][m];
                     }
                     }
                     
                 
			
				 }               
       			}		 
	   return max_fit1;     	        
       }  
       
                                   

void recur_min(int depth_count,char board_current[8][8],char max_player,char min_player);  

void recur_max(int depth_count,char board_current[8][8],char max_player,char min_player)
{
     
if(depth_count<0)//even
{
                        exit(1);
}                        
player=max_player;
opp_player=min_player;                
int max_fit1=-999;
cout<<"max player"<<endl;
int legal_move[64];
int mov_i_new=-1,mov_count=-1;
found_move=false;
max_count=0;
    for(int j=0;j<8;j++)
    {
    for(int k=0;k<8;k++)
    {
    if(board_current[j][k]=='*')
    	             {      
					          
							mov_i_new=find_move_minimax(j,k,board_current,max_player,min_player,max_fit1);
							//cout<<j<<"\t"<<k;
                            if(found_move==true)
							{
						
								for(int l=0;l<8;l++)
    						{
    							for(int m=0;m<8;m++)
    								{
										board_current[l][m]=board_final[l][m];
										cout<<board_current[l][m];
									}
									cout<<endl;
							}      
							cout<<"got it "<<mov_i_new;
							recur_min(depth_count-1,board_current,min_player,max_player);
							}	
							}       
                     } 
                    }
 
} 

//call the find legal move function and print value;
//make the on the board_current for        
void recur_min(int depth_count,char board_current[8][8],char max_player,char min_player)
{
     int max_fit1=-9999;
if(depth_count<0)//even
{
                        exit(1);
}                        
player=max_player;
opp_player=min_player;                

cout<<"min player"<<endl;
int legal_move[64];
int mov_i_new=-1,mov_count=-1;
    for(int j=0;j<8;j++)
    {
    for(int k=0;k<8;k++)
    {
    if(board_current[j][k]=='*')
    	             {      
					          
							mov_i_new=find_move_minimax(j,k,board_current,max_player,min_player,max_fit1);
                            if(found_move==true)
							{
						for(int l=0;l<8;l++)
    						{
    							for(int m=0;m<8;m++)
    								{
										board_current[l][m]=board_final[l][m];
										cout<<board_current[l][m];
									}
									cout<<endl;
									
							}
							cout<<"got it "<<mov_i_new;
							recur_max(depth_count-1,board_current,min_player,max_player);
							}	
							}       
                     } 
                    }
}

void minimax_strategy(int depth,char max_player,char min_player)
{
     int depth_count=depth;
     recur_max(depth_count,board,max_player,min_player);
  /* mov_i=((final_val-(final_val%10))/10);
                mov_j=final_val%10;
                //cout<<"mov_i"<<mov_i<<"mov_j"<<mov_j<<endl;
                for(int j=0;j<8;j++)
				{
					for(int k=0;k<8;k++)
					{
							output<<boardfinal[j][k];                   
                     }
                     output<<endl; 
    */                }


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
 output.open("output.txt");
 fileread();
 if(player=='X')
{
  max_player=player;
  min_player='O';
}
else
{
  max_player='O';
  min_player=player;
}    

if(strategy==3)
{
minimax_strategy(max_player,min_player,depth);               
}
            
input.close();
output.close();
_getch();
}
