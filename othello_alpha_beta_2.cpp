//************************************************
// filename: othello.cpp
//
// creator:Sangamesh Patil
// 
// Description: this is one of the shittiest code ever written by me for a game called reversi which unfortunately works for some cases. 
//
// History
//
// date      name              description
// 09Oct2014 Sangamesh Patil   intial creation
// 21Oct2014 Sangamesh Patil	final touchup
//***************************************************
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
#define ALPHA 999999;
#define BETA -999999;
using namespace std;
std::ifstream input;
std::ofstream output;
std::ofstream output1;
char opp_player;
int final_val=0,mov_i=-1,mov_j=-1;
char player,maxplayer,minplayer;
int strategy=-1;
int mov_check=-1;
int depth;
int move[2][60];
int weight[8][8]={{99,-8,8,6,6,8,-8,99},{-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};
char board[8][8],output_board[8][8],board_output[8][8],board_final[8][8],board_inter[8][8],board_final_final[8][8],final_board[8][8];
int flipper=0,max_count,max_fit=-99, v=-999;
int max_glob=-999;
bool found_move=false,pass_turn=true;
bool pass=true;
int final_value=-10;
void direction_east_ab(int i,int j)
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
		}	
	}
 void direction_up_ab(int i,int j)
	{
		if( ((i-1) <8) && ((i-1) >= 0) )
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
		}	
	}
	
void direction_north_ab(int i,int j)
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
		}	
	}
 void direction_left_ab(int i,int j)
	{
		if( ((j-1) <= 8) && ((j-1) >= 0) )
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
		}	
	}
 void direction_right_ab(int i,int j)
	{
		if( ((j+1) < 8) && ((j+1) >= 0) )
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
		}	
	}
	void direction_south_ab(int i,int j)
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
		}	
	}
     void direction_down_ab(int i,int j)
	{
		if( ((i+1) <8) && ((i+1) >= 0) )
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
		}	
	}
    void direction_west_ab(int i,int j)
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
		}	
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
				direction_east_ab(i-1,j-1);
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
				direction_up_ab(i-1,j);
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
				direction_north_ab(i-1,j+1);
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
				direction_left_ab(i,j-1);
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
				direction_right_ab(i,j+1);
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
				direction_south_ab(i+1,j-1);
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
				direction_down_ab(i+1,j);
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
				direction_west_ab(i+1,j+1);
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
	int player_weight;
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
	//	int cost=999;
	//int depth_start=depth_count;
	int max_return=-999;
	//int mov_ij_new=-1;
	char board_current[8][8];
	//char board_final_max[8][8];
	char board_depth_final[8][8];
			for(int l=0;l<8;l++)
								{
                     			for(int m=0;m<8;m++)
								{
                     			board_current[l][m]=board_max[l][m];
                     			board_depth_final[l][m]=board_max[l][m];
								 }
                     			}
		int max_fit=+999;
		max_return=parent_cost;
		player=maxplayer;
		opp_player=minplayer;          
	//	int legal_move[64];
		int mov_i_new=-1,mov_ij_new=-1;
		found_move=false;
		max_count=0;
		for(int j=0;j<8;j++)
    	{
    	for(int k=0;k<8;k++)
    	 {
    	if(board_depth_final[j][k]=='*')
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
								output<<print_parent_j<<parent_i+1<<","<<depth_count<<","<<"-Infinity"<<endl;
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
                     			//cout<<board_final_max[l][m];
                     			}
                     			//cout<<endl;
                     			}
                     			int mov_j=mov_ij_new%10;
								int mov_i=((mov_ij_new-mov_j)/10);
                				char print_val=97+mov_j;
                				//cout<<"legal moves"<<print_val<<mov_i;
                     			return_val_depth=min_value(maxplayer,minplayer,depth_start+1,board_final_max,mov_i,mov_j,(-parent_cost));
								output1<<print_val<<mov_i+1<<","<<depth_count+1<<","<<return_val_depth<<endl;
                     			output1<<"root,0,"<<return_val_depth<<endl;
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
void minimax_strategy(char maxplayer,char minplayer,int depth)
{
	int depth_count=0;
	output1.open("output1.txt"); 
	output1<<"Node,Depth,Value"<<endl;
	output1<<"root,0,-infinity"<<endl;
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
void fileread()
{
if (input.is_open())
 {
    input>>strategy>>maxplayer>>depth;
    //cout<<strategy<<"\n";
    //cout<<maxplayer<<"\n";
    //cout<<depth<<"\n";
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
 
    //std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    //std::cout.rdbuf(output.rdbuf()); 
 fileread();
 if(maxplayer=='X')
{
  minplayer='O';
}
else
{
  minplayer='X';
}    

if(strategy==2)
{
minimax_strategy(maxplayer,minplayer,depth);               
}
            
input.close();
output.close();
//_getch();
}
	
	
