//************************************************
// filename: othello.cpp
//
// creator:Sangamesh Patil
// 
// Description: this is one of the  code ever written by me for a game called reversi . 
//
// History
//
// date      name              description
// 09Oct2014 Sangamesh Patil   intial creation
// 21Oct2014 Sangamesh Patil	final touchup to make it work.
//***************************************************
#include <cstdlib>
#include<list>
#include<string>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
#define EMPTY *;
#define BLACK X;
#define WHITE O;
//#define ALPHA 999;
//#define BETA -999;
using namespace std;
std::ifstream input;
std::ofstream output;
std::ofstream output1;
int max_count;
int final_val=0,mov_i=-1,mov_j=-1;
char player,maxplayer,minplayer,opp_player;
char board[8][8],boardfinal[8][8],board_current[8][8],output_board[8][8],board_output[8][8],board_final[8][8],board_inter[8][8],board_final_final[8][8],final_board[8][8];
int strategy=-1;
int depth;
int mov_check=-1;
int move[2][60],legal_move[64];
int weight[8][8]={{99,-8,8,6,6,8,-8,99},{-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};
int flipper=0,max_fit=-99, v=-999;
int max_glob=-999;
bool pass_turn=true,found_move=false,move_pass=true,pass=false;
int final_value=-10;
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
int direction_east(int i,int j)
	{
		if( ((i-1) <8) && ((j-1) < 8) && ((i-1) >= 0) && ((j-1) >= 0) )
		{
			if(board[i-1][j-1]==opp_player)
			{
				output_board[i-1][j-1] = player;
				flipper++;
				direction_east(i-1,j-1);
			}
			if (board[i-1][j-1]==player)
			{
				max_count = 1;
			}	
			if (board[i-1][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j+s] = opp_player;
				}
			}
		return 0;	
		}	
	return -1;	
	}
 int direction_up(int i,int j)
	{
		if( ((i-1) <8) && ((i-1) >= 0) )
		{
			if(board[i-1][j]==opp_player)
			{
				output_board[i-1][j] =player;
				flipper++;
				direction_up(i-1,j);
			}
			if (board[i-1][j]==player)
			{
				max_count = 1;
			}	
			if (board[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j] = opp_player;
				}
			}
		return 0;
		}	
	return -1;	
	}
	
int direction_north(int i,int j)
	{
		if( ((i-1) <8) && ((j+1) <8) && ((i-1) >= 0) && ((j+1) >= 0) )
		{
			if(board[i-1][j+1]==opp_player)
			{
				output_board[i-1][j+1] =player;
				flipper++;
				direction_north(i-1,j+1);
			}
			if (board[i-1][j+1]==player)
			{
				max_count = 1;
			}
			if (board[i-1][j+1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j-s] = opp_player;
				}
			}
		return 0;	
		}	
	return -1;	
	}
 int direction_left(int i,int j)
	{
		if( ((j-1) <= 8) && ((j-1) >= 0) )
		{
			if(board[i][j-1]==opp_player)
			{
				output_board[i][j-1] = player;
				flipper++;
				direction_left(i,j-1);
			}
			if (board[i][j-1]==player)
			{
			max_count = 1;
			}
		if (board[i][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j+s] = opp_player;
				}
			}
		return 0;
		}	
	return -1;	
	}
 int direction_right(int i,int j)
	{
		if( ((j+1) < 8) && ((j+1) >= 0) )
		{
			if(board[i][j+1]==opp_player)
			{
				output_board[i][j+1] = player;
				flipper++;
				direction_right(i,j+1);
			}
			if (board[i][j+1]==player)
			{
			max_count = 1;
			}
		if (board[i][j+1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j-s] = opp_player;
				}
			}
		return 0;
		}
	return -1;		
	}
	int direction_south(int i,int j)
	{
		if( ((i+1) <8) && ((j-1) <8) && ((i+1) >= 0) && ((j-1) >= 0) )
		{
			if(board[i+1][j-1]==opp_player)
			{
				output_board[i+1][j-1] = player;
				flipper++;
				direction_south(i+1,j-1);
			}
			if (board[i+1][j-1]==player)
			{
			max_count = 1;
			}
			if (board[i+1][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i-s][j+s] =opp_player;
				}
			}
		return 0;
		}
	return -1;		
	}
     int direction_down(int i,int j)
	{
		if( ((i+1) <8) && ((i+1) >= 0) )
		{
			if(board[i+1][j]==opp_player)
			{
				output_board[i+1][j] = player;
				flipper++;
				direction_down(i+1,j);
			}
			if (board[i+1][j]==player)
			{
			max_count = 1;
			}
			if (board[i+1][j]=='*')
			{
                for(int s=0;s<flipper;s++)
				{
				
					output_board[i-s][j] = opp_player;
				}
			}
		return 0;
		}
	return -1;		
	}
    int direction_west(int i,int j)
	{
		if( ((i+1) <8) && ((j+1) <8) && ((i+1) >= 0) && ((j+1) >= 0) )
		{
			if(board[i+1][j+1]==opp_player)
			{
				output_board[i+1][j+1] = player;
				flipper++;
				direction_west(i+1,j+1);
			}
			if (board[i+1][j+1]==player)
			{
			max_count = 1;
			}
			if (board[i+1][j+1]=='*')
			{
                for(int s=0;s<flipper;s++)
				{
				output_board[i-s][j-s] =opp_player;
				}
			}
		return 0;
		}
	return -1;		
	} 
void find_move_greedy(int i, int j)
{
    for(int l=0;l<8;l++)
    {
    for(int k=0;k<8;k++)
    {
      output_board[l][k]=board[l][k];
    }
    } 
    //cout<<"finding legal moves for i="<<i<<"and j="<<j;
    flipper = 0;
		if( (i-1 < 8) && (j-1 < 8) && (i-1 >= 0) && (j-1 >= 0) ) 
		{
			if(board[i-1][j-1]==opp_player)
			{
				output_board[i-1][j-1] =player;
				flipper++;
				int check=direction_east(i-1,j-1);
				if(check==-1)
				{
				output_board[i-1][j-1] =opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] =player ;
					max_count = 0;
				}
			}
		}
		flipper = 0;
		if( ((i-1) <8)&&(j<8) && ((i-1) >= 0)&&(j>=0) ) 
		{		
			if((board[i-1][j]==opp_player))
			{
				output_board[i-1][j] = player;
				flipper++;
				int check=direction_up(i-1,j);
				if(check==-1)
				{
				output_board[i-1][j] = opp_player;	
				}
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
			if(board[i-1][j+1]==opp_player)
			{		
				output_board[i-1][j+1] = player;
				flipper++;
				int check=direction_north(i-1,j+1);
				if(check==-1)
				{
				output_board[i-1][j+1] = opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((j-1) <8)&&(i<8) && ((j-1) >= 0)&&(i>=0) ) 
		{
			if(board[i][j-1]==opp_player)
			{		
				output_board[i][j-1] = player;
				flipper++;
				int check=direction_left(i,j-1);
				if(check==-1)
				{
				output_board[i][j-1] = opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( (i<8)&&((j+1) < 8) && ((j+1) >= 0)&&(i>=0) ) 
		{
			
			if(board[i][j+1]==opp_player)
			{		
                output_board[i][j+1] = player;
				flipper++;
				int check=direction_right(i,j+1);
				if(check==-1)
				{
				output_board[i][j-1] = opp_player;	
				}
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
				
			if(board[i+1][j-1]==opp_player)
			{						
				output_board[i+1][j-1] = player;
				flipper++;
				int check=direction_south(i+1,j-1);
				if(check==-1)
				{
				output_board[i+1][j-1] = opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((i+1) < 8)&&(i>=0) && ((j+1) >= 0)&&(j<8) ) 
		{
					
			if(board[i+1][j]==opp_player)
			{			
				output_board[i+1][j] = player;
				flipper++;
				int check=direction_down(i+1,j);
				if(check==-1)
				{
				output_board[i+1][j] = player;	
				}
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
			if(board[i+1][j+1]==opp_player)
			{			
				output_board[i+1][j+1] = player;
				flipper++;
				int check=direction_west(i+1,j+1);
				if(check==-1)
				{
				output_board[i+1][j+1] = opp_player;	
				}
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
    	             if(output_board[l][k]!=board[l][k])
    	             {
							pass_turn=false;                   
                     }
                    }
                } 
                if(pass_turn==false)
                {
		  move_pass=false;
                  mov_check+=1;
                  char buf[10];
                  sprintf(buf,"%d%d",i,j);
                  move[0][mov_check]=atoi(buf);
                  //cout<<"found legal move for "<<buf<<endl;  
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
				if(move[1][mov_check]>max_fit)
				{
                   max_fit=move[1][mov_check];
                   final_val=atoi(buf);
                   for(int l=0;l<8;l++)
					{
                     for(int m=0;m<8;m++)
					{
                     boardfinal[l][m]=output_board[l][m];
                     }
                     }
                     
                 }
                 if(move[1][mov_check]==max_fit)
                 {
                 if(atoi(buf)<final_val)
                 {
                 final_val=atoi(buf);
                 for(int l=0;l<8;l++)
					{
                     for(int m=0;m<8;m++)
					{
                     boardfinal[l][m]=output_board[l][m];
                     }
                     }
                     
                 
			}
		}               
       }           
                      
}
int greedy_strategy(char player, int depth)
{
    setopp_player(player);
               	for(int j=0;j<8;j++)
				{
					for(int k=0;k<8;k++)
					{
    	             if(board[j][k]=='*')
    	             {              
							find_move_greedy(j,k);                   
                     } 
                    }
                }
               // for(int f=0;f<mov_check;f++)
                //{
                  // cout<<move[0][f]<<"=>"<<move[1][f]<<endl;
                //}
                mov_i=((final_val-(final_val%10))/10);
                mov_j=final_val%10;
                //cout<<"mov_i"<<mov_i<<"mov_j"<<mov_j<<endl;
		if(move_pass==true)
			for(int j=0;j<8;j++)
				{
					for(int k=0;k<8;k++)
					{
							output<<board[j][k];                   
                     }
                     output<<endl; 
                    }
		else
		{
			      for(int j=0;j<8;j++)
				{
					for(int k=0;k<8;k++)
					{
							output<<boardfinal[j][k];                   
                     }
                     output<<endl; 
                    }
		}
                  
                
//cout<<"greedy called"<<endl;
return 0;   
} 
int direction_east_ab(int i,int j)
	{
		if( ((i-1) <8) && ((j-1) < 8) && ((i-1) >= 0) && ((j-1) >= 0) )
		{
			if(board_inter[i-1][j-1]==opp_player)
			{
				output_board[i-1][j-1] = player;
				flipper++;
				direction_east_ab(i-1,j-1);
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
			return 0;
		}	
	return -1;
	}
 int  direction_up_ab(int i,int j)
	{
		if( ((i-1) <8) &&(j<8)&& ((i-1) >= 0)&&(j>=0) )
		{
			if(board_inter[i-1][j]==opp_player)
			{
				output_board[i-1][j] =player;
				flipper++;
				direction_up_ab(i-1,j);
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
		return 0;	
		}	
	return -1;
	}
	
int direction_north_ab(int i,int j)
	{
		if( ((i-1) <8) && ((j+1) <8) && ((i-1) >= 0) && ((j+1) >= 0) )
		{
			if(board_inter[i-1][j+1]==opp_player)
			{
				output_board[i-1][j+1] =player;
				flipper++;
				direction_north_ab(i-1,j+1);
			}
			if (board_inter[i-1][j+1]==player)
			{
				max_count = 1;
			}
			if (board_inter[i-1][j+1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j-s] = opp_player;
				}
			}
			return 0;
		}
	return -1;		
	}
 int direction_left_ab(int i,int j)
	{
		if((i<8)&&((j-1) < 8) && ((j-1) >= 0)&&(i>=0) )
		{
			if(board_inter[i][j-1]==opp_player)
			{
				output_board[i][j-1] = player;
				flipper++;
				direction_left_ab(i,j-1);
			}
			if (board_inter[i][j-1]==player)
			{
			max_count = 1;
			}
		if (board_inter[i][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j+s] = opp_player;
				}
			}
		return 0;
		}	
	return -1;
	}
 int direction_right_ab(int i,int j)
	{
		if( ((j+1) < 8)&&(i<8) &&(i>=0)&& ((j+1) >= 0) )
		{
			if(board_inter[i][j+1]==opp_player)
			{
				output_board[i][j+1] = player;
				flipper++;
				direction_right_ab(i,j+1);
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
		return 0;
		}	
	return -1;
	}
	int direction_south_ab(int i,int j)
	{
		if( ((i+1) <8) && ((j-1) <8) && ((i+1) >= 0) && ((j-1) >= 0) )
		{
			if(board_inter[i+1][j-1]==opp_player)
			{
				output_board[i+1][j-1] = player;
				flipper++;
				direction_south_ab(i+1,j-1);
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
		return 0;
		}
	return -1;		
	}
     int direction_down_ab(int i,int j)
	{
		if( ((i+1) <8) &&(j<8)&& ((i+1) >= 0)&&(j>=0) )
		{
			if(board_inter[i+1][j]==opp_player)
			{
				output_board[i+1][j] = player;
				flipper++;
				direction_down_ab(i+1,j);
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
		return 0;
		}
	return -1;		
	}
    int direction_west_ab(int i,int j)
	{
		if( ((i+1) <8) && ((j+1) <8) && ((i+1) >= 0) && ((j+1) >= 0) )
		{
			if(board_inter[i+1][j+1]==opp_player)
			{
				output_board[i+1][j+1] = player;
				flipper++;
				direction_west_ab(i+1,j+1);
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
		return 0;
		}
	return -1;		
	}
int find_move(int i, int j,int max_fit1,char board_current[8][8])
{
	pass_turn=true;
    for(int l=0;l<8;l++)
    {
    for(int k=0;k<8;k++)
    {
    //	cout<<board_current[l][k];
      board_inter[l][k]=board_current[l][k];
      output_board[l][k]=board_current[l][k];
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
				int check=direction_east_ab(i-1,j-1);
				if(check==-1)
				{
					output_board[i-1][j-1]=opp_player;
				}
				if(max_count == 1)
				{
					output_board[i][j] =player ;
					max_count = 0;
				}
			}
		}
		flipper = 0;
		if( ((i-1) <8)&&(j<8) && ((i-1) >= 0 &&(j>=0)) ) 
		{		
			if((board_inter[i-1][j]==opp_player))
			{
				output_board[i-1][j] = player;
				flipper++;
				int check=direction_up_ab(i-1,j);
				if(check==-1)
				{
				output_board[i-1][j] = opp_player;	
				}
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
				int check=direction_north_ab(i-1,j+1);
				if(check==-1)
				{
				output_board[i-1][j+1] = opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( (i<8)&&((j-1) <8) &&(i>=0)&&((j-1) >= 0) ) 
		{
			if(board_inter[i][j-1]==opp_player)
			{		
				output_board[i][j-1] = player;
				flipper++;
				int check=direction_left_ab(i,j-1);
				if(check==-1)
				{
				output_board[i][j-1] = opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( (i<8)&&((j+1) < 8) &&(i>=0) &&((j+1) >= 0) ) 
		{
				
			if(board_inter[i][j+1]==opp_player)
			{		
                output_board[i][j+1] = player;
				flipper++;
				int check=direction_right_ab(i,j+1);
				if(check==-1)
				{
				output_board[i][j+1] = opp_player;	
				}
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
				int check=direction_south_ab(i+1,j-1);
				if(check==-1)
				{
				output_board[i+1][j-1] = opp_player;	
				}
				if(max_count == 1)
				{
					output_board[i][j] = player;
					max_count = 0;
				}
			}
		
	    }
		flipper = 0;
		if( ((i+1) < 8)&&(i>=0) && ((j+1) >= 0)&&(j<8) ) 
		{
					
			if(board_inter[i+1][j]==opp_player)
			{			
				output_board[i+1][j] = player;
				flipper++;
				int check=direction_down_ab(i+1,j);
				if(check==-1)
				{
				output_board[i+1][j] = opp_player;	
				}
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
				int check=direction_west_ab(i+1,j+1);
				if(check==-1)
				{
				output_board[i+1][j+1] = opp_player;	
				}
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
                    }
                } 
                if(pass_turn==false)
                {
                	found_move=true;
                  mov_check+=1;
                  char buf[10];
                  sprintf(buf,"%d%d",i,j);
                  //move[0][mov_check]=atoi(buf);
              //    cout<<"found legal move for "<<buf<<endl;  
                  int player_weight=0,opp_player_weight=0; 
                  for(int l=0;l<8;l++)
		          {
			      for(int k=0;k<8;k++)
			      {
				  if(output_board[l][k]==player)
				  {
					player_weight += weight[l][k];
					//cout<<player_weight;
				  }
                  if(output_board[l][k]==opp_player)
				  {
					opp_player_weight += weight[l][k];
					//cout<<opp_player_weight;
					
				  }
                  }
                  }
                  final_val=atoi(buf);
				//move[1][mov_check]=player_weight-opp_player_weight;
				 
	  // max_fit1=move[1][mov_check];          
                      
				}
return final_val;
}
int find_weight(char maxplayer,char minplayer)
{
	int player_weight=0;
for(int l=0;l<8;l++)
{
for(int k=0;k<8;k++)
{
if(output_board[l][k]==maxplayer)
{
player_weight += weight[l][k];
}
if(output_board[l][k]==minplayer)
{
player_weight-= weight[l][k];
}
}
}
return player_weight;
}
int max_value(char maxplayer,char minplayer,int depth_count,char board_max[8][8],int parent_i,int parent_j,int parent_cost);
int min_value(char maxplayer,char minplayer,int depth_count,char board_min[8][8],int parent_i,int parent_j,int parent_cost)
 {
	int cost;
	int max_return=999;
	int mov_ij_new=-1;
	max_glob=-999;
	char board_current[8][8];
	if(depth_count==depth-1)
	{
		char board_min_if[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_min[l][m];
                     			board_min_if[l][m]=board_min[l][m];
								 }
                     			}
		int max_fit=+999;
		player=minplayer;
		int parent_cost_minif=999;
		opp_player=maxplayer;
		int mov_i_new=-1,mov_ij_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	 {
    	if(board_min_if[j][k]=='*')
    	             {
    	             	player=minplayer;
						opp_player=maxplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_current);//find the legal move and return the max the ij ,value 
						  if(found_move==true)
    	             	 {
    	             	 	    mov_i_new=find_weight(maxplayer,minplayer);
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_final[l][m]=output_board[l][m];
                     			}
                     			}
                     			int mov_i=((final_val-(final_val%10))/10);
                				int mov_j=final_val%10;
                				char print_parent_j=97+parent_j;
                				if(parent_cost_minif==999)
                				{
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost_minif<<endl;
								}
								char print_j= 97+mov_j;
                				output1<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<endl;    									
    							if(mov_i_new<parent_cost_minif)
								{
											
    							parent_cost_minif=mov_i_new;		   										
                   				}
								 		
		 				  
    				      }	
    	             }
		}
		}
    	return parent_cost_minif;
    }
	else
	{
		char board_min_else[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_min[l][m];
                                board_min_else[l][m]=board_min[l][m];
								}
                     			}
		int max_fit=999;
		player=minplayer;
		int return_val=-1;
		opp_player=maxplayer; 
	//	int legal_move[64];
		max_return=parent_cost;
		//int mov_i_new=-1,mov_count=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	{
    
    	if(board_min_else[j][k]=='*')
    	             {
    	             	player=minplayer;
						opp_player=maxplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_current);//find the legal move and return the max the ij ,value 
    	             	 cost=-999;
    	             	 
						  if(found_move==true)
    	             	 {
    	             	 	pass=false;
    	             	 	 return_val=cost;
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_final[l][m]=output_board[l][m];
                     			//board_max[l][m]=output_board[l][m];
                     			//cout<<board_max[l][m];
                     			}
                     			//cout<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				char print_parent_j=97+parent_j;
                				if(parent_cost==999)
                				{
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<endl;
								//output1<<"root,0,"<<"Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost<<endl;
								}
                     			return_val=max_value(maxplayer,minplayer,depth_count+1,board_final_final,mov_i,mov_j,(-max_return));
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val<<endl;
                     			
                     			if(return_val<max_return)
								{	
								max_return=return_val;
								parent_cost=max_return;		
						   		}		
                     			
                     
                 		}
						 
    						
					}
				
						 
    	}
		}	
		return max_return;
	}	
}

int max_value(char maxplayer,char minplayer,int depth_count,char board_max[8][8],int parent_i,int parent_j,int parent_cost)
{
	
	if(depth_count==depth-1)
	{
	
		//int cost=999;
	//int depth_start=depth_count;
	int max_return=-999;
	//int mov_ij_new=-1;
	char board_current[8][8];
	//char board_final_max[8][8];
			for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_max[l][m];
                     			}
                     			}
		int max_fit=+999;
		max_return=parent_cost;
		player=maxplayer;
		opp_player=minplayer;          
		//int legal_move[64];
		int mov_i_new=-1,mov_ij_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	 {
    	if(board_max[j][k]=='*')
    	             {
    	             	player=maxplayer;
						opp_player=minplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_current);//find the legal move and return the max the ij ,value 
						  
						  if(found_move==true)
    	             	 {
    	             	 	    mov_i_new=find_weight(maxplayer,minplayer);
                   				
								for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_final[l][m]=output_board[l][m];
                     			}
                     			}
                     			int mov_i=((final_val-(final_val%10))/10);
                				int mov_j=final_val%10;
                				char print_parent_j=97+parent_j;
                				if(max_return==-999)
                				{	
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"-Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<abs(max_return)<<endl;
								}
								char print_j= 97+mov_j;
                				output1<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<endl;
                				if(mov_i_new>max_return)
								{
								max_return=mov_i_new;		   										
                   				}
    					  }
    				}	
    	}
		}
    	return max_return;
		}
	else if(depth_count==0)
	{
		int cost=999;
	int depth_start=depth_count;
	//int max_return=-999;
	int mov_ij_new=-1;
	//int max_return_depth=-999;
	//char board_current[8][8];
	char board_final_max[8][8];
	char board_max_intial[8][8];
		char board_max_else[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_max_else[l][m]=board_max[l][m];
                     			board_max_intial[l][m]=board_max[l][m];
								 //cout<<board_max_else[l][m];
                     			//output_board[l][m]=board_min[l][m];
                     			}
                     			//cout<<endl;
                     			}
		int max_fit=-999;
		player=maxplayer;
		int return_val_depth=-1;
		opp_player=minplayer;                
		//cout<<"max player else"<<endl;
		//int legal_move[64];
		int max_return_start=-999;
	//	int mov_i_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	{
    		
    	if(board_max_intial[j][k]=='*')
    	             {
    	             	player=maxplayer;
						opp_player=minplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_max_else);//find the legal move and return the max the ij ,value 
    	             	 cost=999;
    	             	 
						  if(found_move==true)
    	             	 {
    	             	 	pass=false;
    	             	 	    //max_return=parent_cost;
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_max[l][m]=output_board[l][m];
                     			//board_max[l][m]=output_board[l][m];
                     			cout<<board_final_max[l][m];
                     			}
                     			cout<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				//cout<<"legal moves"<<print_val<<mov_i;
                     			return_val_depth=min_value(maxplayer,minplayer,depth_start+1,board_final_max,mov_i,mov_j,(-parent_cost));
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<abs(return_val_depth)<<endl;
                     			output1<<"root,0,"<<return_val_depth<<endl;
                     			if(return_val_depth>max_return_start)
								{
								if(return_val_depth!=max_return_start)
								{
									
								max_return_start=return_val_depth;
								//max_return;
								//cout<<"return_val"<<return_val_depth;
								//cout<<"max_return"<<max_return_start;
								for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			final_board[l][m]=board_final_max[l][m];
								//cout<<final_board[l][m];	
								}
							    }
								}
										
                     		    }
                     
                 		}
						 
    						
					}
				
						 
    	}
		}
		if(pass=true)
		{
			
		}
	//return  0;
	}
	else
	{
		int parent_cost_else=parent_cost;
		int cost=999;
	int depth_start=depth_count;
	int max_return_else=-999;
	int mov_ij_new=-1;
	//char board_current[8][8];
	char board_final_max[8][8];
		char board_max_else[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_max_else[l][m]=board_max[l][m];
                     			//cout<<board_max_else[l][m];
                     			//output_board[l][m]=board_min[l][m];
                     			}
                     			//cout<<endl;
                     			}
		int max_fit=-999;
		player=maxplayer;
		int return_val_else=-1;
		opp_player=minplayer;                
		//cout<<"max player else"<<endl;
	//	int legal_move[64];
		max_return_else=parent_cost;//-999;
	//	int mov_i_new=-1,mov_count=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	{
    		
    	if(board_max[j][k]=='*')
    	             {
    	             	pass_turn=false;
    	             	player=maxplayer;
						opp_player=minplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_max_else);//find the legal move and return the max the ij ,value 
    	             	 cost=999;
    	             	 //int max_return_else_pass=parent_cost;
    	             	 //parent_cost_else=max_return_else;
						  if(found_move==true)
    	             	 {
    	             	 	pass=false;
							return_val_else=cost;
    	             	 	    //parent_cost_else=max_return_else;
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_max[l][m]=output_board[l][m];
                     			//board_max[l][m]=output_board[l][m];
                     			//cout<<board_final_max[l][m];
                     			}
                     			//out<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				char print_parent_j=97+parent_j;
                				//if(max_return_else>parent_cost_else)
								//{
									//parent_cost_else=max_return_else;
								//}
                				if(parent_cost_else==-999)
                				{
                				//cout<<"parent_cost_else"<<parent_cost_else;	
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"-Infinity"<<endl;
								//output1<<"root,0,"<<"Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<abs(parent_cost_else)<<endl;
								}//cout<<"max_return_else_pass"<<max_return_else;
                     			return_val_else=min_value(maxplayer,minplayer,depth_start+1,board_final_max,mov_i,mov_j,(-max_return_else));
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_else<<endl;
								if(return_val_else>max_return_else)
								{
								max_return_else=return_val_else;
								//if(max_return_else>parent_cost_else)
								//{
								parent_cost_else=max_return_else;//max_return;
								//cout<<parent_cost_else<<endl;
								}//cout<<"return_val"<<return_val_else<<endl;
								//cout<<"max_return"<<max_return_else<<endl;
								}
								//output1<<"maxelse"<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_else<<endl;
                     
                 		}
						 
    						
					}
				
						 
    	}
		
	return max_return_else;
	}

	return 0;	
}
void minimax_strategy(char maxplayer,char minplayer,int depth)
{
	int depth_count=0;
	output1.open("output1.txt"); 
	output1<<"Node,Depth,Value"<<endl;
	output1<<"root,0,-Infinity"<<endl;
	v=max_value(maxplayer,minplayer,depth_count ,board,0,0,-999);
	output1.close();
	std ::ifstream input1;
	input1.open("output1.txt");
	if(pass==false)
	{
	//cout<<"boardoutputfinal"<<endl;
								for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			output<<final_board[l][m];	
								}
								output<<endl;
								}
    }
    else
    {
    	for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			output<<board[l][m];	
								}
								output<<endl;
								}
    }
char c = input1.get();

  while (input1.good()) {
    output << c;
    c = input1.get();
  }

  input1.close();
}
int max_value_alphabeta(char maxplayer,char minplayer,char board_max[8][8],int depth_count,int parent_i,int parent_j,int parent_cost,int alpha_max,int beta_max);
int min_value_alphabeta(char maxplayer,char minplayer,int depth_count,char board_min[8][8],int parent_i,int parent_j,int parent_cost,int alpha_min,int beta_min)
{
	int cost;
	int max_return=999;
	int mov_ij_new=-1;
	max_glob=-999;
	char board_current[8][8];
	if(depth_count==depth-1)
	{
		int alpha_min_if=alpha_min;
		int beta_min_if=beta_min;
		char board_min_if[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_min[l][m];
                     			board_min_if[l][m]=board_min[l][m];
								 }
                     			}
		int max_fit=+999;
		player=minplayer;
		int parent_cost_minif=999;
		opp_player=maxplayer;
		int mov_i_new=-1,mov_ij_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	 {
    	if(board_min_if[j][k]=='*')
    	             {
    	             	player=minplayer;
						opp_player=maxplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_current);//find the legal move and return the max the ij ,value 
						  if(found_move==true)
    	             	 {
    	             	 	
    	             	 	    mov_i_new=find_weight(maxplayer,minplayer);
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_final[l][m]=output_board[l][m];
                     			}
                     			}
                     			int mov_i=((final_val-(final_val%10))/10);
                				int mov_j=final_val%10;
                				char print_parent_j=97+parent_j;
                			if(999==abs(alpha_min)||999==abs(beta_min))
                			{
                				
                				if(parent_cost_minif==999&&alpha_min_if==-999&&beta_min_if==999)
                				{
								output1<<"minif"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<",-Infinity"<<",Infinity"<<endl;
								}
								else if(999==abs(alpha_min)&&999==abs(beta_min))
								{
									output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost_minif<<",-Infinity"<<",Infinity"<<endl;
								}
								else if(999==abs(alpha_min)&&parent_cost_minif==999)
    							{
    								output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<",-Infinity,"<<beta_min<<endl;
								}
								else if(999==abs(beta_min)&&parent_cost_minif==999)
								{
									output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<","<<alpha_min<<",Infinity"<<endl;	
								}
								else if(999==abs(alpha_min))
								{
								output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost_minif<<",-Infinity,"<<beta_min<<endl;	
								}
								else if(999==abs(beta_min))
								{
									output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost_minif<<","<<alpha_min<<",Infinity"<<endl;
								}
								else if(parent_cost_minif==999)
								{
									output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<","<<alpha_min<<","<<beta_min<<endl;
								}
								else
								{
									output1<<"minifparent"<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost_minif<<","<<alpha_min<<","<<beta_min<<endl;
								}
								char print_j= 97+mov_j;
									if(mov_i_new<beta_min)
								{
								beta_min=mov_i_new;	
								}
								
								if(999==abs(alpha_min_if)&&999==abs(beta_min_if))
								{
                				output1<<"minifchild"<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<",-Infinity"<<",Infinity"<<endl;    									
    							}
    							else if(999==abs(alpha_min_if))
    							{
    							 output1<<"minifchild"<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<",-Infinity,"<<beta_min_if<<endl;	
    							}
    							else if(999==abs(beta_min_if))
    							{
    							output1<<"minifchild"<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<","<<alpha_min_if<<",Infinity"<<endl;	
    							}
    							else
    							{
    							output1<<"minifchild"<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<","<<alpha_min_if<<","<<beta_min_if<<endl;
    							}
    							if(mov_i_new<beta_min_if)
								{
								beta_min_if=mov_i_new;	
								}
								if(mov_i_new<parent_cost_minif)
								{
											
    							parent_cost_minif=mov_i_new;		   										
                   				}
								 		
		 					}
    				      }	
    	             }
		}
		}
    	return parent_cost_minif;
    }
	else
	{
		char board_min_else[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_min[l][m];
                                board_min_else[l][m]=board_min[l][m];
								}
                     			}
		int max_fit=999;
		player=minplayer;
		int return_val=-1;
		opp_player=maxplayer; 
	//	int legal_move[64];
		max_return=parent_cost;
		//int mov_i_new=-1,mov_count=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	{
    
    	if(board_min_else[j][k]=='*')
    	             {
    	             	player=minplayer;
						opp_player=maxplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_current);//find the legal move and return the max the ij ,value 
    	             	 cost=-999;
    	             	 
						  if(found_move==true)
    	             	 {
    	             	 	pass=false;
    	             	 	 return_val=cost;
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_final[l][m]=output_board[l][m];
                     			//board_max[l][m]=output_board[l][m];
                     			//cout<<board_max[l][m];
                     			}
                     			//cout<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				char print_parent_j=97+parent_j;
                				if(parent_cost==999)
                				{
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"Infinity"<<endl;
								//output1<<"root,0,"<<"Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<parent_cost<<endl;
								}
                     			return_val=max_value(maxplayer,minplayer,depth_count+1,board_final_final,mov_i,mov_j,(-max_return));
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val<<endl;
                     			
                     			if(return_val<max_return)
								{	
								max_return=return_val;
								parent_cost=max_return;		
						   		}		
                     			
                     
                 		}
						 
    						
					}
				
						 
    	}
		}	
		return max_return;
	}
	
}
int max_value_alphabeta(char maxplayer,char minplayer,int depth_count,char board_max[8][8],int parent_i,int parent_j,int parent_cost,int alpha_max,int beta_max)
{
	if(depth_count==depth-1)
	{
	
		//int cost=999;
	//int depth_start=depth_count;
	int max_return=-999;
	//int mov_ij_new=-1;
	char board_current[8][8];
	//char board_final_max[8][8];
			for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_max[l][m];
                     			}
                     			}
		int max_fit=+999;
		max_return=alpha_max;
		player=maxplayer;
		opp_player=minplayer;          
		//int legal_move[64];
		int mov_i_new=-1,mov_ij_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	 {
    	if(board_max[j][k]=='*')
    	             {
    	             	player=maxplayer;
						opp_player=minplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_current);//find the legal move and return the max the ij ,value 
						  
						  if(found_move==true)
    	             	 {
    	             	 	    mov_i_new=find_weight(maxplayer,minplayer);
                   				
								for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_final[l][m]=output_board[l][m];
                     			}
                     			}
                     			int mov_i=((final_val-(final_val%10))/10);
                				int mov_j=final_val%10;
                				char print_parent_j=97+parent_j;
                				if(max_return==-999)
                				{	
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"-Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<abs(max_return)<<endl;
								}
								char print_j= 97+mov_j;
                				output1<<print_j<<mov_i+1<<","<<depth_count+1<<","<<mov_i_new<<endl;
                				if(mov_i_new>max_return)
								{
								max_return=mov_i_new;		   										
                   				}
    					  }
    				}	
    	}
		}
    	return max_return;
		}
	else if(depth_count==0)
	{
		int cost=999;
	int depth_start=depth_count;
	//int max_return=-999;
	int mov_ij_new=-1;
	int alpha_max_start=alpha_max;
	int beta_max_start=beta_max;
	//int max_return_depth=-999;
	//char board_current[8][8];
	char board_final_max[8][8];
	char board_max_intial[8][8];
		char board_max_else[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_max_else[l][m]=board_max[l][m];
                     			board_max_intial[l][m]=board_max[l][m];
								 //cout<<board_max_else[l][m];
                     			//output_board[l][m]=board_min[l][m];
                     			}
                     			//cout<<endl;
                     			}
		int max_fit=-999;
		player=maxplayer;
		int return_val_depth=-1;
		opp_player=minplayer;                
		//cout<<"max player else"<<endl;
		//int legal_move[64];
		int max_return_start=-999;
	//	int mov_i_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	{
    		
    	if(board_max_intial[j][k]=='*')
    	             {
    	             	player=maxplayer;
						opp_player=minplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_max_else);//find the legal move and return the max the ij ,value 
    	             	 cost=999;
    	             	 
						  if(found_move==true)
    	             	 {
    	             	 	pass=false;
    	             	 	    //max_return=parent_cost;
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_max[l][m]=output_board[l][m];
                     			//board_max[l][m]=output_board[l][m];
                     			//cout<<board_final_max[l][m];
                     			}
                     			//cout<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				//cout<<"legal moves"<<print_val<<mov_i;
                     			return_val_depth=min_value_alphabeta(maxplayer,minplayer,1,board_final_max,mov_i,mov_j,(-parent_cost),alpha_max,beta_max);
								if(return_val_depth<beta_max_start)
								{
									beta_max_start=return_val_depth;
								}
								if(999==abs(alpha_max_start)&&999==abs(beta_max_start))
								{
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_depth<<",-Infinity"<<",Infinity"<<endl;
                     			}
								else if(999==abs(alpha_max_start))
                     			{
                     			output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_depth<<",-Infinity,"<<beta_max_start<<endl;	
                     			}
                     			else if(999==abs(beta_max_start))
                     			{
                     			output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_depth<<","<<alpha_max_start<<",Infinity"<<endl;		
                     			}
                     			else
                     			{
                     				output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_depth<<","<<alpha_max_start<<","<<beta_max_start<<endl;	
                     			}
                     			if(999==abs(alpha_max)&&999==abs(beta_max))
								{
								output1<<"root,0,"<<return_val_depth<<",-Infinity"<<","<<"Infinity"<<endl;
                     			}
								else if(999==abs(alpha_max))
                     			{
                     			output1<<"root,0,"<<return_val_depth<<","<<",-Infinity"<<beta_max<<endl;	
                     			}
                     			else if(999==abs(beta_max))
                     			{
                     			output1<<"root,0,"<<return_val_depth<<","<<alpha_max<<",Infinity"<<endl;
                     			}
                     			else
                     			{
                     				output1<<"root,0,"<<return_val_depth<<alpha_max_start<<","<<beta_max<<endl;
                     			}
								
								 if(return_val_depth>alpha_max)
                     			{
                     				alpha_max=return_val_depth;
                     			} 
                     			if(return_val_depth>max_return_start)
								{
								if(return_val_depth!=max_return_start)
								{
									
								max_return_start=abs(return_val_depth);
								//max_return;
								//cout<<"return_val"<<return_val_depth;
								//cout<<"max_return"<<max_return_start;
								for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			final_board[l][m]=board_final_max[l][m];
								//cout<<final_board[l][m];	
								}
							    }
								}
										
                     		    }
                     
                 		}
						 
    						
					}
				
						 
    	}
		}
	//return  0;
	}
	else
	{
		int parent_cost_else=parent_cost;
		int cost=999;
	int depth_start=depth_count;
	int max_return_else=-999;
	int mov_ij_new=-1;
	//char board_current[8][8];
	char board_final_max[8][8];
		char board_max_else[8][8];
		for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_max_else[l][m]=board_max[l][m];
                     			//cout<<board_max_else[l][m];
                     			//output_board[l][m]=board_min[l][m];
                     			}
                     			//cout<<endl;
                     			}
		int max_fit=-999;
		player=maxplayer;
		int return_val_else=-1;
		opp_player=minplayer;                
		//cout<<"max player else"<<endl;
	//	int legal_move[64];
		max_return_else=parent_cost;//-999;
	//	int mov_i_new=-1,mov_count=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	{
    		
    	if(board_max[j][k]=='*')
    	             {
    	             	player=maxplayer;
						opp_player=minplayer;
    	             	 found_move=false;
    	             	 mov_ij_new=find_move(j,k,max_fit,board_max_else);//find the legal move and return the max the ij ,value 
    	             	 cost=999;
    	             	 //int max_return_else_pass=parent_cost;
    	             	 //parent_cost_else=max_return_else;
						  if(found_move==true)
    	             	 {
    	             	 	pass=false;
							return_val_else=cost;
    	             	 	    //parent_cost_else=max_return_else;
                   				for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_final_max[l][m]=output_board[l][m];
                     			//board_max[l][m]=output_board[l][m];
                     			//cout<<board_final_max[l][m];
                     			}
                     			//out<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				char print_parent_j=97+parent_j;
                				//if(max_return_else>parent_cost_else)
								//{
									//parent_cost_else=max_return_else;
								//}
                				if(parent_cost_else==-999)
                				{
                				//cout<<"parent_cost_else"<<parent_cost_else;	
								output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"-Infinity"<<endl;
								//output1<<"root,0,"<<"Infinity"<<endl;
								}
								else
								{
									output1<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<abs(parent_cost_else)<<endl;
								}//cout<<"max_return_else_pass"<<max_return_else;
                     			return_val_else=min_value(maxplayer,minplayer,depth_start+1,board_final_max,mov_i,mov_j,(-max_return_else));
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_else<<endl;
								if(return_val_else>max_return_else)
								{
								max_return_else=return_val_else;
								//if(max_return_else>parent_cost_else)
								//{
								parent_cost_else=max_return_else;//max_return;
								//cout<<parent_cost_else<<endl;
								}//cout<<"return_val"<<return_val_else<<endl;
								//cout<<"max_return"<<max_return_else<<endl;
								}
								//output1<<"maxelse"<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_else<<endl;
                     
                 		}
						 
    						
					}
				
						 
    	}
		
	return max_return_else;
	}

	return 0;
	
}
void alphabeta_strategy(char maxplayer,char minplayer,int depth,int alpha,int beta)
{
	int depth_count=0;
	output1.open("output1.txt"); 
	output1<<"Node,Depth,Value,Alpha,Beta"<<endl;
	output1<<"root,0,-Infinity,-Infinity,Infinity"<<endl;
	v=max_value_alphabeta(maxplayer,minplayer,0,board,0,0,-999,-999,999);
	output1.close();
	std ::ifstream input1;
	input1.open("output1.txt");
	if(pass==false)
	{
	//cout<<"boardoutputfinal"<<endl;
								for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			output<<final_board[l][m];	
								}
								output<<endl;
								}
    }
    else
    {
    	for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			output<<board[l][m];	
								}
								output<<endl;
								}
    }
char c = input1.get();

  while (input1.good()) {
    output << c;
    c = input1.get();
  }

  input1.close();
}
void fileread()
{
if (input.is_open())
 {
    input>>strategy>>player>>depth;
//    cout<<strategy<<"\n";
 //   cout<<player<<"\n";
  //  cout<<depth<<"\n";
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
  maxplayer='X';	
  minplayer='O';
}
else
{
  maxplayer='O';	
  minplayer='X';
}     
if(strategy==1)
{
   greedy_strategy(player,depth);
}
if(strategy==2)
{
minimax_strategy(maxplayer,minplayer,depth);               
}
if(strategy==3)
{
//call alpha-beta
alphabeta_strategy(maxplayer,minplayer,depth,-999,999);
}
            
input.close();
output.close();
//_getch();
}
