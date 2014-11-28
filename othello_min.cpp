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
char output_board[8][8],board_final[8][8];
class minimax{
	public:
		char max_player;
		char min_player;
		char board[8][8];
		int depth;
		
		void set_max_player(char max_player)
		{
			this.max_player=max_player;
		}
		void set_min_player(char min_player)
		{
			this.min_player=min_player;
		}
		void set_board(char boar[8][8])
		{
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					this.board[i][j]=board[i][j];
				}
			}
		}
		void set_depth(int depth)
		{
			this.depth=depth;
		}
		char get_max_player()
		{
			return max_player;
		}
		char get_min_player()
		{
			return min_player;
		}
		char get_depth()
		{
			return depth;
		}
		void direction_east_minimax(int i,int j)
	{
		if( ((i-1) <8) && ((j-1) < 8) && ((i-1) >= 0) && ((j-1) >= 0) )
		{
			if(board[i-1][j-1]==min_player)
			{
				output_board[i-1][j-1] =max_player;
				flipper++;
				direction_east(i-1,j-1);
			}
			if (board[i-1][j-1]==max_player)
			{
				max_count = 1;
			}	
			if (board[i-1][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j+s] = min_player;
				}
			}
		}	
	}
 void direction_up_minimax(int i,int j)
	{
		if( ((i-1) <8) && ((i-1) >= 0) )
		{
			if(board[i-1][j]==min_player)
			{
				output_board[i-1][j] =max_player;
				flipper++;
				direction_up(i-1,j);
			}
			if (board[i-1][j]==min_player)
			{
				max_count = 1;
			}	
			if (board[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j] = min_player;
				}
			}
		}	
	}
	
void direction_north_minimax(int i,int j)
	{
		if( ((i-1) <8) && ((j+1) <8) && ((i-1) >= 0) && ((j+1) >= 0) )
		{
			if(board[i-1][j]==min_player)
			{
				output_board[i-1][j+1] =max_player;
				flipper++;
				direction_north(i-1,j+1);
			}
			if (board[i-1][j]==max_player)
			{
				max_count = 1;
			}
			if (board[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i+s][j-s] = min_player;
				}
			}
		}	
	}
 void direction_left_minimax(int i,int j)
	{
		if( ((j-1) <= 8) && ((j-1) >= 0) )
		{
			if(board[i][j-1]==min_player)
			{
				output_board[i][j-1] = max_player;
				flipper++;
				direction_left(i,j-1);
			}
			if (board[i-1][j]==max_player)
			{
			max_count = 1;
			}
		if (board[i-1][j]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j+s] = min_player;
				}
			}
		}	
	}
 void direction_right_minimax(int i,int j)
	{
		if( ((j+1) < 8) && ((j+1) >= 0) )
		{
			if(board[i][j+1]==min_player)
			{
				output_board[i][j+1] = max_player;
				flipper++;
				direction_right(i,j+1);
			}
			if (board[i][j+1]==max_player)
			{
			max_count = 1;
			}
		if (board[i][j+1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i][j-s] = min_player;
				}
			}
		}	
	}
	void direction_south_minimax(int i,int j)
	{
		if( ((i+1) <8) && ((j-1) <8) && ((i+1) >= 0) && ((j-1) >= 0) )
		{
			if(board[i+1][j-1]==min_player)
			{
				output_board[i+1][j-1] = max_player;
				flipper++;
				direction_south(i+1,j-1);
			}
			if (board[i+1][j-1]==max_player)
			{
			max_count = 1;
			}
			if (board[i+1][j-1]=='*')
			{
				for(int s=0;s<flipper;s++)
				{
					output_board[i-s][j+s] =mini_player;
				}
			}
		}	
	}
     void direction_down_minimax(int i,int j)
	{
		if( ((i+1) <8) && ((i+1) >= 0) )
		{
			if(board[i+1][j]==min_player)
			{
				output_board[i+1][j] = max_player;
				flipper++;
				direction_down(i+1,j);
			}
			if (board[i+1][j]==max_player)
			{
			max_count = 1;
			}
			if (board[i+1][j]=='*')
			{
                for(int s=0;s<flipper;s++)
				{
				
					output_board[i-s][j] = min_player;
				}
			}
		}	
	}
    void direction_west_minimax(int i,int j)
	{
		if( ((i+1) <8) && ((j+1) <8) && ((i+1) >= 0) && ((j+1) >= 0) )
		{
			if(board[i+1][j+1]==min_player)
			{
				output_board[i+1][j+1] = max_player;
				flipper++;
				direction_west(i+1,j+1);
			}
			if (board[i+1][j+1]==max_player)
			{
			max_count = 1;
			}
			if (board[i+1][j+1]=='*')
			{
                for(int s=0;s<flipper;s++)
				{
				output_board[i-s][j-s] =min_player;
				}
			}
		}	
	} 
	int find_move_minimax(int i, int j)
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
			if(board[i-1][j-1]==min_player)
			{
				output_board[i-1][j-1] =max_player;
				flipper++;
				direction_east_minimax(i-1,j-1);
				if(max_count == 1)
				{
					output_board[i][j] =max_player ;
					max_count = 0;
				}
			}
		}
		flipper = 0;
		if( ((i-1) <8) && ((i-1) >= 0) ) 
		{		
			if((board[i-1][j]==min_player))
			{
				board[i-1][j] = max_player;
				flipper++;
				direction_up_minimax(i-1,j);
				if(max_count == 1)
				{
					output_board[i][j] =max_player;
					max_count = 0;
				}
						
			}
		}
		
		flipper = 0;
		if( ((i-1) < 8) && ((j+1) < 8) && ((i-1) >= 0) && ((j+1) >= 0) ) 
		{
			if(board[i-1][j+1]==min_player)
			{		
				output_board[i-1][j+1] = max_player;
				flipper++;
				direction_north_minimax(i-1,j+1);
				if(max_count == 1)
				{
					output_board[i][j] = max_player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((j-1) <8) && ((j-1) >= 0) ) 
		{
			if(board[i][j-1]==min_player)
			{		
				output_board[i][j-1] = max_player;
				flipper++;
				direction_left_minimax(i,j-1);
				if(max_count == 1)
				{
					output_board[i][j] = max_player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((j+1) < 8) && ((j+1) >= 0) ) 
		{
				
			if(board_current[i][j+1]==min_player)
			{		
                output_board[i][j+1] = max_player;
				flipper++;
				direction_right_minimax(i,j+1);
				if(max_count == 1)
				{
					output_board[i][j] = max_player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((i+1) <8) && ((j-1) <8) && ((i+1) >= 0) && ((j-1) >= 0) ) 
		{
				
			if(board[i+1][j-1]==min_player)
			{						
				output_board[i+1][j-1] = max_player;
				flipper++;
				direction_south_minimax(i+1,j-1);
				if(max_count == 1)
				{
					output_board[i][j] = max_player;
					max_count = 0;
				}
			}
		}
				
		flipper = 0;
		if( ((i+1) < 8) && ((j+1) >= 0) ) 
		{
					
			if(board[i+1][j]==min_player)
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
			if(board[i+1][j+1](=min_player)
			{			
				output_board[i+1][j+1] = max_player;
				flipper++;
				direction_west_minimax(i+1,j+1);
				if(max_count == 1)
				{
					output_board[i][j] = max_player;
					max_count = 0;
				}
			}
		}
                for(int l=0;l<8;l++)
                {
				   for(int k=0;k<8;k++)
					{
    	             if(output_board[l][k]!=board_[l][k])
    	             {
							pass_turn=false;                   
                     }
                    }
                } 
                if(pass_turn==false)
                {
                  mov_check+=1;
                  sprintf(buf,"%d%d",i,j);
                  move[0][mov_check]=atoi(buf);
                  
                  cout<<"found legal move for "<<buf<<endl;  
                  int player_weight=0,opp_player_weight=0; 
                  for(int l=0;l<8;l++)
		          {
			      for(int k=0;k<8;k++)
			      {
				  if(output_board[l][k]==max_player)
				  {
					player_weight += weight[l][k];
				  }
                  if(output_board[l][k]==min_player)
				  {
					opp_player_weight += weight[l][k];
					
				  }
                  }
                  }
				move[1][mov_check]=player_weight-opp_player_weight;
				if(move[1][mov_check]>max_fit)
				{
                  //max_fit=move[1][mov_check];
                   final_val=atoi(buf);
                   
                   for(int l=0;l<8;l++)
					{
                     for(int m=0;m<8;m++)
					{
                     board_final[l][m]=output_board[l][m];
                     }
                     }
                     return final_val;
                     
                 }
                 }
                 
                    
                 
			
	return -9999;	        
       }  
	}
};
