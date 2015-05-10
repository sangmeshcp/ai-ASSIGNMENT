// ************************************************
// filename: logicalinfer.cpp
//
// creator:Sangamesh Patil
// 
// Description: this is a code ever written by me for logical inference. 
//
// History
//
// date      name              description
// 11Nov2014 Sangamesh Patil   intial creation
// 16Nov2014 Sangamesh Patil	hardcode the out of range index.
// 19Nov2014 Sangamesh Patil    fixing x on LHS
// ***************************************************
#include <cstdlib>
#include<list>
#include<string>
#include <string.h>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
#define TRUE 0;
#define FALSE 1;
using namespace std;
std::ifstream input;
std::ofstream output;
string Mainsentence;
int Noofsentences;
 string x;
 string sentences[20]; int top=0;
 int infer=-1;
 int pointit=1;
 string kb[20];
 string clauses[10];
 string fact[10],x_var;
 string x_val[10];
 int xvar=0;

 string stack_item[100];
 int count=0;
 int kb_count=0,clause_count=0,fact_count=0;
bool flag=false,found_x=false,found_compare=false;

void fileread()
{
	if (input.is_open())
 {
    input>>Mainsentence;
    input>>Noofsentences;
    for(int i=0;i<Noofsentences;i++)
    {
    	input>>sentences[i];
    }
 }
}
void display()
{
	//cout<<"mainclause:"<<Mainsentence;
	//cout<<"\nNoofclauses:"<<Noofsentences;
	for(int i=0;i<Noofsentences;i++)
    {
    	
    //	cout<<"\n"<<sentences[i];
    }
}
void fact_or_clause()
{
	for(int i=0;i<Noofsentences;i++)
    {
    	std::size_t found=sentences[i].find("=>");
     if(found!=std::string::npos)
	   {
		clauses[clause_count]=sentences[i];
	    clause_count++;
	   }
	 else
	   {
	   fact[fact_count]=sentences[i];
	   fact_count++;
	   }  
    }
}
void backchain_it(string clause,int i)
{
 std::size_t found_implies=clause.find("=>");
 
 while(found_implies==std::string::npos);
 	{
	        std::size_t found_and=clause.find("&");
	        if(found_and!=std::string::npos&&top<99)
	        {
	        string temp1=clause.substr(0,found_and);
	        std::size_t open_bracket=temp1.find("(");
			std::size_t close_bracket=temp1.find(")");
			std::size_t comma=temp1.find(",");
			if(comma!=std::string::npos)
				{
				string mainpart1=temp1.substr(0,open_bracket);
				string mainvar1=temp1.substr(open_bracket+1,comma-open_bracket-1);
				string mainvar2=temp1.substr(comma+1,close_bracket-comma-1);
				if(mainvar1==x)
				{
					temp1.replace(open_bracket+1,comma-open_bracket-1,"x");			
				}
				if(mainvar2==x)
				{
				temp1.replace(comma+1,close_bracket-comma-1,"x");	
				}
	    		}
	    	else
			{
			string mainpart1=temp1.substr(0,open_bracket);
			string mainvar1=temp1.substr(open_bracket+1,close_bracket-1);	
			if(mainvar1==x)
			{
			temp1.replace(open_bracket+1,close_bracket-1,"x");	
			}
			}	
			   stack_item[top]=temp1;
			   
//			   cout<<"\n stack item"<<top<<":"<<stack_item[top];
	   		   top++;
//			   cout<<"\n clause being added to stack"<<temp1;
	   		clause.replace(0,found_and+1,"");
//	   		cout<<"\n"<<clause;
	   		backchain_it(clause,0);
 			}
 			else
 			{
 			 if(top<99)
			 	{
			  	
 			 string temp1=clause.substr(0,found_implies);
 			  std::size_t open_bracket=temp1.find("(");
			std::size_t close_bracket=temp1.find(")");
			std::size_t comma=temp1.find(",");
			if(comma!=std::string::npos)
				{
				string mainpart1=temp1.substr(0,open_bracket);
				string mainvar1=temp1.substr(open_bracket+1,comma-open_bracket-1);
				string mainvar2=temp1.substr(comma+1,close_bracket-comma-1);
				if(mainvar1==x)
				{
					temp1.replace(open_bracket+1,comma-open_bracket-1,"x");			
				}
				if(mainvar2==x)
				{
				temp1.replace(comma+1,close_bracket-comma-1,"x");	
				}
	    		}
	    	else
			{
			string mainpart1=temp1.substr(0,open_bracket);
			string mainvar1=temp1.substr(open_bracket+1,close_bracket-1);	
			if(mainvar1==x)
			{
			temp1.replace(open_bracket+1,close_bracket-1,"x");	
			}
			}
			 stack_item[top]=temp1;
//			 cout<<"\n stack item"<<top<<":"<<stack_item[top];
			 top++;
//			 cout<<"\n clause being added to stack"<<temp1;
	   		 clause.replace(0,found_implies+2,"");
//	   		 cout<<"\n"<<clause;
				}
 			}
	 }
     
}
void stack_push()
{
	string compareit=Mainsentence;
	for(int i=0;i<clause_count;i++)
	{
		std::size_t found=clauses[i].find("=>");
		if(found!=std::string::npos)
	   {
	   	string temp=clauses[i].substr(found+2);
	  // 	cout<<"\n result clause:"<<temp<<"\n";
	   	if(temp.compare(compareit)==0)
	   	{
	   		//cout<<"found the asshole";
	   		if(top==0&&top<99)
	   		{
			stack_item[top]=compareit;
		  // cout<<"\n stack item"<<top<<":"<<stack_item[top];
		    top++;
		    backchain_it(clauses[i],i);
		    found_compare=true;
			}
		    
	   		//cout<<"\n next substring:"<<compareit<<"\n";
	   	}
	   	
	   }
	   
	}
	while(pointit!=top&&top<99&&top>0)
	{
		string temp=stack_item[pointit];
		//cout<<"\nnext variable"<<temp<<"poinit"<<pointit;
		for(int i=0;i<clause_count;i++)
		{
		std::size_t found=clauses[i].find("=>");
		if(found!=std::string::npos)
	   {
	   	string temp1=clauses[i].substr(found+2);
	   	//cout<<"\n result clause in poinit:"<<temp<<"\n";
		if(temp==temp1)
		{
		backchain_it(clauses[i],0);	
		}	
		}
		}
	pointit++;	
	}
}
void stack_pop()
{
	infer=top;
	//cout<<"\ntop"<<top;
	while(top!=-1&&top<99)
	{
	for(int i=0;i<kb_count;i++)
	{
	//	cout<<"stack_item before deleting:top"<<top<<"vlue"<<stack_item[top]<<endl;
	if(stack_item[top]==kb[i])
		{
	//	cout<<"\nfound the item in kb"<<infer;
			infer--;	
			break;
		}	
	}
	top--;	
	}
}
void check_it(string clause)
{
	 std::size_t found_implies=clause.find("=>");
 	while(found_implies==std::string::npos);
 	{
	    std::size_t found_and=clause.find("&");
	    if(found_and!=std::string::npos)
	    {
	    	//cout<<clause;
	        string temp1=clause.substr(0,found_and);
	        std::size_t open_bracket=temp1.find("(");
			std::size_t close_bracket=temp1.find(")");
			std::size_t comma=temp1.find(",");
			if(comma!=std::string::npos)
				{
				string mainpart1=temp1.substr(0,open_bracket);
				string mainvar1=temp1.substr(open_bracket+1,comma-open_bracket-1);
				string mainvar2=temp1.substr(comma+1,close_bracket-comma-1);
				if(mainvar1=="x")
				{
				found_x=true;
				x_var=temp1;			
				}
				if(mainvar2=="x")
				{
				found_x=true;
				x_var=temp1;	
				}
			//	cout<<temp1<<"\n";
	    		}
	    	else
			{
			string mainpart1=temp1.substr(0,open_bracket);
			string mainvar1=temp1.substr(open_bracket+1,close_bracket-open_bracket-1);	
			//cout<<temp1<<"    "<<mainvar1;
			if(mainvar1=="x")
			{
			found_x=true;
			x_var=temp1;
			//cout<<"got here";	
			}
			}
			clause.replace(0,found_and+1,"");
//	   		cout<<"\n"<<clause;
	   		check_it(clause);
				
		}
		else
		{
		string temp1=clause.substr(0,found_implies);
 			std::size_t open_bracket=temp1.find("(");
			std::size_t close_bracket=temp1.find(")");
			std::size_t comma=temp1.find(",");
			if(comma!=std::string::npos)
				{
				string mainpart1=temp1.substr(0,open_bracket);
				string mainvar1=temp1.substr(open_bracket+1,comma-open_bracket-1);
				string mainvar2=temp1.substr(comma+1,close_bracket-comma-1);
				if(mainvar1=="x")
				{
				found_x=true;
				x_var=temp1;			
				}
				if(mainvar2=="x")
				{
				found_x=true;
				x_var=temp1;
				}
	    		}
	    	else
			{
			string mainpart1=temp1.substr(0,open_bracket);
			string mainvar1=temp1.substr(open_bracket+1,close_bracket-open_bracket-1);
			//cout<<temp1;	
			if(mainvar1=="x")
			{
				found_x=true;
				x_var=temp1;
			//	cout<<x_var;
			}
			}
	   		 clause.replace(0,found_implies+2,"");
	   		 //cout<<"\n"<<clause;
		}
	}
}
void find_x()
{
	int part1_match=-1,var1_match=-1,var2_match=-1;
	std::size_t open_bracket=Mainsentence.find("(");
	std::size_t close_bracket=Mainsentence.find(")");
	std::size_t comma=Mainsentence.find(",");
	if(comma!=std::string::npos)
	{
	string mainpart1=Mainsentence.substr(0,open_bracket);
	//cout<<"\n firstpart:"<<mainpart1;
	string mainvar1=Mainsentence.substr(open_bracket+1,comma-open_bracket-1);
	//cout<<"\n Variable1:"<<mainvar1;
	string mainvar2=Mainsentence.substr(comma+1,close_bracket-comma-1);
	//cout<<"\n Variable2:"<<mainvar2;
	
	  //check in clauses
	  	for(int i=0;i<clause_count;i++)
		{   //find after implies first
			std::size_t found_implies=clauses[i].find("=>");
			string temp=clauses[i].substr(found_implies+2);
		//	cout<<"\ntempx"<<temp;
			std::size_t open_bracket_implies=temp.find("(");
			std::size_t close_bracket_implies=temp.find(")");
			std::size_t comma_implies=temp.find(",");
			if(comma_implies!=std::string::npos)
			{
			string clausepart1=temp.substr(0,open_bracket_implies);
		//	cout<<"\n clauseimpliesfirstpart:"<<clausepart1;
			string clausevar1=temp.substr(open_bracket_implies+1,comma_implies-open_bracket_implies-1);
			//cout<<"\n clauseImpliesVariable1:"<<clausevar1;
			string clausevar2=temp.substr(comma_implies+1,close_bracket_implies-comma_implies-1);
			//cout<<"\n clauseImpliesVariable2:"<<clausevar2;
			if(mainpart1==clausepart1)
	    		{
	    			part1_match=2;
					if(clausevar1=="x")
					{
						var1_match=0;
						if(mainvar2==clausevar2)
						{
						var2_match=1;	
						}
						else
						{
						//cout<<"iEND here"<<mainvar2<<"\t"<<clausevar2<<endl;	
						var2_match=0;	
						}
					}
					else
					{
						var1_match=1;
						if(clausevar2=="x")
						{
						var2_match=0;	
						}
						else
						{
						var2_match=	1;	
						}
					}	
	    		}
	    		else
	    		{
	    		part1_match=0;	
	    		}
	    		if(part1_match==2&&var2_match==1&&var1_match==0&&flag==false)
				{
				x=mainvar1;	
				flag=true;
				}
				if(part1_match==2&&var1_match==1&&var2_match==0&&flag==false)
				{
				//cout<<"fuckedit up"<<endl;	
				x=mainvar2;	
				flag=true;
				}
				
			}
			else
			{
			string clausepart1=temp.substr(0,open_bracket_implies);
			//cout<<"\n clauseimpliesfirstpart:"<<clausepart1;	
			string clausevar2=temp.substr(open_bracket_implies+1,close_bracket_implies-open_bracket_implies-1);
			//cout<<"\n clauseImpliesVariable2:"<<clausevar2;	
			}
		part1_match=-1;
		var1_match=-1;
		var2_match=-1;	
			
		}
			//check in facts
		for(int i=0;i<fact_count;i++)
		{
			std::size_t open_bracket_fact=fact[i].find("(");
			std::size_t close_bracket_fact=fact[i].find(")");
			std::size_t comma_fact=fact[i].find(",");
			if(comma_fact!=std::string::npos)
			{
			string factpart1=fact[i].substr(0,open_bracket_fact);
		//	cout<<"\n factfirstpart:"<<factpart1;
			string factvar1=fact[i].substr(open_bracket_fact+1,comma_fact-open_bracket_fact-1);
		//cout<<"\n factVariable1:"<<factvar1;
			string factvar2=fact[i].substr(comma_fact+1,close_bracket_fact-comma_fact-1);
		//cout<<"\n factVariable2:"<<factvar2;
	    		if(mainpart1==factpart1)
	    		{
	    			part1_match=2;
					if(factvar1=="x")
					{
						var1_match=1;
						if(mainvar2==factvar2)
						{
						var2_match=1;	
						}
						else
						{
						var2_match=0;	
						}
					}
					else
					{
						var1_match=0;
						if(factvar2=="x")
						{
						var2_match=1;	
						}
						else
						{
						var2_match=0;	
						}
					}	
	    		}
	    		else
	    		{
	    		part1_match=0;	
	    		}
	    		if(part1_match==2&&var2_match==1&&var1_match==0&&flag==false)
				{
				x=mainvar1;	
				flag=true;
				}
				if(part1_match==2&&var1_match==1&&var2_match==0&&flag==false)
				{
				x=mainvar2;	
				flag=true;
				}	
			}
	    	else
	    	{
	    	string factpart1=fact[i].substr(0,open_bracket_fact);
		//	cout<<"\n factfirstpart:"<<factpart1;
			string factvar2=fact[i].substr(open_bracket_fact+1,close_bracket_fact-open_bracket_fact-1);
		//	cout<<"\n factVariable1:"<<factvar2;	
	    	}
		part1_match=-1;
		var1_match=-1;
		var2_match=-1;
		}	
	}
	else
	{
		string mainpart1=Mainsentence.substr(0,open_bracket);
		//cout<<"\n factfirstpart:"<<mainpart1;
		string mainvar1=Mainsentence.substr(open_bracket+1,close_bracket-open_bracket-1);
		//cout<<"\n factVariable1:"<<mainvar1;
	    
		//check in clauses
	  	for(int i=0;i<clause_count;i++)
		{   //find after implies first
			std::size_t found_implies=clauses[i].find("=>");
			string temp=clauses[i].substr(found_implies+2);
			std::size_t open_bracket_implies=temp.find("(");
			std::size_t close_bracket_implies=temp.find(")");
			std::size_t comma_implies=temp.find(",");
			if(comma_implies==std::string::npos)
			{
			string clausepart1=temp.substr(0,open_bracket_implies);
			//cout<<"\n clauseimpliesfirstpart:"<<clausepart1;	
			string clausevar2=temp.substr(open_bracket_implies+1,close_bracket_implies-open_bracket_implies-1);
			//cout<<"\n clauseImpliesVariable2:"<<clausevar2;
			if(mainpart1==clausepart1&&flag==false)
			{
				if(clausevar2=="x")
				{
				
				x=mainvar1;	
				flag=true;
				}
			}
			}
		}
		//check in facts
		for(int i=0;i<fact_count;i++)
		{
			std::size_t open_bracket_fact=fact[i].find("(");
			std::size_t close_bracket_fact=fact[i].find(")");
			std::size_t comma_fact=fact[i].find(",");
			if(comma_fact==std::string::npos)
			{
			string factpart1=fact[i].substr(0,open_bracket_fact);
		//	cout<<"\n factfirstpart:"<<factpart1;
			string factvar2=fact[i].substr(open_bracket_fact+1,close_bracket_fact-open_bracket_fact-1);
		//	cout<<"\n factVariable1:"<<factvar2;	
			if(mainpart1==factpart1&&flag==false)
			{
				x=mainvar1;	
				flag=true;
			}
		    }
			else
	    	{
	    	string factpart1=fact[i].substr(0,open_bracket_fact);
		//cout<<"\n factfirstpart:"<<factpart1;
			string factvar1=fact[i].substr(open_bracket_fact+1,comma_fact-open_bracket_fact-1);
		//	cout<<"\n factVariable1:"<<factvar1;
			string factvar2=fact[i].substr(comma_fact+1,close_bracket_fact-comma_fact-1);
		//	cout<<"\n factVariable2:"<<factvar2;		
	    	}
		}
	
	}
	if(flag==false)
	{
	for(int i=0;i<clause_count;i++)
	 {
	 	//cout<<clauses[i];
		std::size_t found=clauses[i].find("=>");
		if(found!=std::string::npos)
	   {
	   	string temp=clauses[i].substr(found+2);
		    check_it(clauses[i]);
		    
	   }
		    
	 }
	 if(found_x==true)
	 
	 {
	 //	cout<<x_var;
	 std::size_t open_bracket_x=x_var.find("(");
			std::size_t close_bracket_x=x_var.find(")");
			std::size_t comma_x=x_var.find(",");
			if(comma_x!=std::string::npos)
			{
				string mainpart1=x_var.substr(0,open_bracket_x);
				//cout<<"\n firstpart:"<<mainpart1;
				string mainvar1=x_var.substr(open_bracket_x+1,comma_x-open_bracket_x-1);
				//cout<<"\n Variable1:"<<mainvar1;
				string mainvar2=x_var.substr(comma_x+1,close_bracket_x-comma_x-1);
				//cout<<"\n Variable2:"<<mainvar2;	
	 				for(int i=0;i<fact_count;i++)
	 					{

	 								std::size_t open_bracket_fact=fact[i].find("(");
									std::size_t close_bracket_fact=fact[i].find(")");
									std::size_t comma_fact=fact[i].find(",");
									if(comma_fact==std::string::npos)
										{
											string factpart1=fact[i].substr(0,open_bracket_fact);
											//	cout<<"\n factfirstpart:"<<factpart1;
											string factvar2=fact[i].substr(open_bracket_fact+1,close_bracket_fact-open_bracket_fact-1);
											//	cout<<"\n factVariable1:"<<factvar2;	
											if(mainpart1==factpart1&&flag==false)
												{
														x_val[xvar++]=factvar2;	
														flag=true;
												}
		    							}
										else
	    								{
	    									string factpart1=fact[i].substr(0,open_bracket_fact);
											//cout<<"\n factfirstpart:"<<factpart1;
											string factvar1=fact[i].substr(open_bracket_fact+1,comma_fact-open_bracket_fact-1);
											//	cout<<"\n factVariable1:"<<factvar1;
											string factvar2=fact[i].substr(comma_fact+1,close_bracket_fact-comma_fact-1);
											//	cout<<"\n factVariable2:"<<factvar2;
											if(mainpart1==factpart1)
	    									{	
								    			part1_match=2;
												if(mainvar1==factvar1)
												{
													var1_match=1;
													if(mainvar2==factvar2)
													{
													var2_match=1;	
													}
													else
													{
													var2_match=0;	
													}
												}
												else
												{
													var1_match=0;
													if(mainvar2==factvar2)
													{
													var2_match=1;	
													}
													else
													{
													var2_match=0;	
													}
												}	
								    		}
								    		else
								    		{
								    		part1_match=0;	
								    		}
								    		if(part1_match==2&&var2_match==1&&var1_match==0)
											{
											x_val[xvar++]=factvar1;	
											//flag=true;
											}
											if(part1_match==2&&var1_match==1&&var2_match==0)
											{
											x_val[xvar++]=factvar2;	
											//flag=true;
											}		
	    								}
	 					}							
	 		}
			 else
			 {
		string mainpart1=x_var.substr(0,open_bracket_x);
				//cout<<"\n firstpart:"<<mainpart1;
				string mainvar1=x_var.substr(open_bracket_x+1,comma_x-open_bracket_x-1);
				//cout<<"\n Variable1:"<<mainvar1;
				string mainvar2=x_var.substr(comma_x+1,close_bracket_x-comma_x-1);
				//cout<<"\n Variable2:"<<mainvar2;	
	 				for(int i=0;i<fact_count;i++)
	 					{

	 								std::size_t open_bracket_fact=fact[i].find("(");
									std::size_t close_bracket_fact=fact[i].find(")");
									std::size_t comma_fact=fact[i].find(",");
									if(comma_fact==std::string::npos)
										{
											string factpart1=fact[i].substr(0,open_bracket_fact);
											//	cout<<"\n factfirstpart:"<<factpart1;
											string factvar2=fact[i].substr(open_bracket_fact+1,close_bracket_fact-open_bracket_fact-1);
											//	cout<<"\n factVariable1:"<<factvar2;	
											if(mainpart1==factpart1)
												{
													//cout<<factvar2;
														x_val[xvar++]=factvar2;	
												}
		    							}
						}
			 }		
     }			
	}
}
void build_kb()
{
	for(int i=0;i<fact_count;i++)
	{
			std::size_t open_bracket_fact=fact[i].find("(");
			std::size_t close_bracket_fact=fact[i].find(")");
			std::size_t comma_fact=fact[i].find(",");
			if(comma_fact!=std::string::npos)
			{
			string factpart1=fact[i].substr(0,open_bracket_fact);
		//	cout<<"\n factfirstpart:"<<factpart1;
			string factvar1=fact[i].substr(open_bracket_fact+1,comma_fact-open_bracket_fact-1);
		//	cout<<"\n factVariable1:"<<factvar1;
			string factvar2=fact[i].substr(comma_fact+1,close_bracket_fact-comma_fact-1);
		//	cout<<"\n factVariable2:"<<factvar2;
			
			if(factvar1==x)
			{
			fact[i].replace(open_bracket_fact+1,comma_fact-open_bracket_fact-1,"x");	
			}
			if(factvar2==x)
			{
			fact[i].replace(comma_fact+1,close_bracket_fact-comma_fact-1,"x");	
			}
			}
			else
			{
			string factpart1=fact[i].substr(0,open_bracket_fact);
		//	cout<<"\n factfirstpart:"<<factpart1;
			string factvar2=fact[i].substr(open_bracket_fact+1,close_bracket_fact-open_bracket_fact-1);
		//	cout<<"\n factVariable1:"<<factvar2;
			if(factvar2==x)
			{
			fact[i].replace(open_bracket_fact+1,close_bracket_fact-open_bracket_fact-1,"x");	
			}	
			}
	kb[kb_count++]=fact[i];
	}
	for(int i=0;i<clause_count;i++)
	{
			std::size_t found_implies=clauses[i].find("=>");
			std::size_t and_symbol=clauses[i].find("&");
			string temp=clauses[i].substr(found_implies+2);
		//	cout<<"\nprintingbeforetemp"<<temp;
			std::size_t open_bracket_implies=temp.find("(");
			std::size_t close_bracket_implies=temp.find(")");
			std::size_t comma_implies=temp.find(",");
			if(comma_implies==std::string::npos)
			{
			string clausepart1=temp.substr(0,open_bracket_implies);
		//	cout<<"\n clauseimpliesfirstpart:"<<clausepart1;	
			string clausevar2=temp.substr(open_bracket_implies+1,close_bracket_implies-open_bracket_implies-1);
		//	cout<<"\n clauseImpliesVariable2:"<<clausevar2;
			if(clausevar2==x)
			{
				temp.replace(open_bracket_implies+1,close_bracket_implies-open_bracket_implies-1,"x");
		///		cout<<"\ntempvalue"<<temp;
				kb[kb_count++]=temp;	
				clauses[i].replace(found_implies+2,std::string::npos,temp);
			}				
			kb[kb_count++]=temp;
			}
			else
			{
			string clausepart1=temp.substr(0,open_bracket_implies);
		//	cout<<"\n clauseimpliesfirstpart:"<<clausepart1;
			string clausevar1=temp.substr(open_bracket_implies+1,comma_implies-open_bracket_implies-1);
		//	cout<<"\n clauseImpliesVariable1:"<<clausevar1;
			string clausevar2=temp.substr(comma_implies+1,close_bracket_implies-comma_implies-1);
		//	cout<<"\n clauseImpliesVariable2:"<<clausevar2;
			if(clausevar1==x)
			{
			temp.replace(open_bracket_implies+1,comma_implies-open_bracket_implies-1,"x");
		//	cout<<"\ntemp"<<temp;
			clauses[i].replace(found_implies+2,std::string::npos,temp);	
			}
			kb[kb_count++]=temp;			
			if(clausevar2==x)
			{
			temp.replace(comma_implies+1,close_bracket_implies-comma_implies-1,"x");
		//	cout<<"\ntemp"<<temp;
			clauses[i].replace(found_implies+2,std::string::npos,temp);		
			}
			}
/*						if(and_symbol==std::string::npos)
						{
						string tempvar1=clauses[i].substr(0,found_implies);
						cout<<"\n inside buildkb tempvar1:(line386)"<<tempvar1;
						std::size_t open_bracket_before_and=tempvar1.find("(");
						std::size_t close_bracket_before_and=tempvar1.find(")");
						std::size_t comma_implies_before_and=tempvar1.find(",");
						if(comma_implies_before_and==std::string::npos)
						{
						string clausepart1_and=tempvar1.substr(0,open_bracket_before_and);
						cout<<"\n clauseimpliesfirstpart:"<<clausepart1_and;	
						string clausevar2_and=tempvar1.substr(open_bracket_before_and+1,close_bracket_before_and-open_bracket_before_and-1);
						cout<<"\n clauseImpliesVariable2:"<<clausevar2_and;
						if(clausevar2_and=="x")
						{
							tempvar1.replace(open_bracket_before_and+1,close_bracket_before_and-open_bracket_before_and-1,x);
							clauses[i].replace(0,found_implies,tempvar1);
						}
						}
						else
						{
						string clausepart1_and=tempvar1.substr(0,open_bracket_before_and);
						cout<<"\n clauseimpliesfirstpart:"<<clausepart1_and;
						string clausevar1_and=tempvar1.substr(open_bracket_before_and+1,comma_implies_before_and-open_bracket_before_and-1);
						cout<<"\n clauseImpliesVariable1:"<<clausevar1_and;
						string clausevar2_and=tempvar1.substr(comma_implies_before_and+1,close_bracket_before_and-comma_implies_before_and-1);
						cout<<"\n clauseImpliesVariable2:"<<clausevar2_and;
						if(clausevar1_and=="x")
						{
						tempvar1.replace(open_bracket_before_and+1,comma_implies_before_and-open_bracket_before_and-1,x);
						clauses[i].replace(0,found_implies,tempvar1);	
						}			
						if(clausevar2_and=="x")
						{
						tempvar1.replace(comma_implies_before_and+1,close_bracket_before_and-comma_implies_before_and-1,x);
						clauses[i].replace(0,found_implies,tempvar1);		
						}	
						}					
						}
						else
						{
						string tempvar1=clauses[i].substr(0,found_implies);
						cout<<"\n inside buildkb tempvar1:(line425)"<<tempvar1;
						string tempvar2=tempvar1.substr(0,and_symbol);
						cout<<"\n inside buildkb tempvar2:(line427)"<<tempvar2;
						string tempvar3=tempvar1.substr(and_symbol+1,found_implies-and_symbol);
						cout<<"\n inside buildkb tempvar1:(line428)"<<tempvar3;
						std::size_t open_bracket_before_and=tempvar2.find("(");
						std::size_t close_bracket_before_and=tempvar2.find(")");
						std::size_t comma_implies_before_and=tempvar2.find(",");
						std::size_t open_bracket_after_and=tempvar3.find("(");
						std::size_t close_bracket_after_and=tempvar3.find(")");
						std::size_t comma_implies_after_and=tempvar3.find(",");
							if(comma_implies_before_and==std::string::npos)
							{
								string clausepart1_and=tempvar2.substr(0,open_bracket_before_and);
								cout<<"\n clauseimpliesfirstpart:"<<clausepart1_and;	
								string clausevar2_and=tempvar2.substr(open_bracket_before_and+1,close_bracket_before_and-open_bracket_before_and-1);
								cout<<"\n clauseImpliesVariable2:"<<clausevar2_and;
								if(clausevar2_and=="x")
								{
									tempvar2.replace(open_bracket_before_and+1,close_bracket_before_and-open_bracket_before_and-1,x);
									cout<<"\ntempvar2"<<tempvar2;
									tempvar1.replace(0,and_symbol,tempvar2);
									cout<<"\ntempvar1"<<tempvar1;
								}
											
							}
							else
							{
								string clausepart1_and=tempvar2.substr(0,open_bracket_before_and);
								cout<<"\n clauseimpliesfirstpart:"<<clausepart1_and;
								string clausevar1_and=tempvar2.substr(open_bracket_before_and+1,comma_implies_before_and-open_bracket_before_and-1);
								cout<<"\n clauseImpliesVariable1:"<<clausevar1_and;
								string clausevar2_and=tempvar2.substr(comma_implies_before_and+1,close_bracket_before_and-comma_implies_before_and-1);
								cout<<"\n clauseImpliesVariable2:"<<clausevar2_and;
								if(clausevar1_and=="x")
								{
								tempvar2.replace(open_bracket_before_and+1,comma_implies_before_and-open_bracket_before_and-1,x);
								cout<<"\ntempvar2"<<tempvar2;
								tempvar1.replace(0,and_symbol,tempvar2);
								cout<<"\ntempvar1"<<tempvar1;	
								}			
								if(clausevar2_and=="x")
								{
								tempvar2.replace(comma_implies_before_and+1,close_bracket_before_and-comma_implies_before_and-1,x);
								cout<<"\ntempvar2"<<tempvar2;
								tempvar1.replace(0,and_symbol,tempvar2);		
								cout<<"\ntempvar1"<<tempvar1;
								}		
							}
							if(comma_implies_after_and==std::string::npos)
							{
								string clausepart1_and=tempvar3.substr(0,open_bracket_after_and);
								cout<<"\n clauseimpliesfirstpart:"<<clausepart1_and;	
								string clausevar2_and=tempvar3.substr(open_bracket_after_and+1,close_bracket_after_and-open_bracket_after_and-1);
								cout<<"\n clauseImpliesVariable2:"<<clausevar2_and;
								if(clausevar2_and=="x")
								{
									tempvar3.replace(open_bracket_after_and+1,close_bracket_after_and-open_bracket_after_and-1,x);
									cout<<"\ntempvar3"<<tempvar3;
									tempvar1.replace(and_symbol+4,found_implies-and_symbol,tempvar3);
								cout<<"\ntempvar1"<<tempvar1;
								}
											
							}
							else
							{
								string clausepart1_and=tempvar3.substr(0,open_bracket_after_and);
								cout<<"\n clauseimpliesfirstpart:"<<clausepart1_and;
								string clausevar1_and=tempvar3.substr(open_bracket_after_and+1,comma_implies_after_and-open_bracket_after_and-1);
								cout<<"\n clauseImpliesVariable1:"<<clausevar1_and;
								string clausevar2_and=tempvar3.substr(comma_implies_after_and+1,close_bracket_after_and-comma_implies_after_and-1);
								cout<<"\n clauseImpliesVariable2:"<<clausevar2_and;
								if(clausevar1_and=="x")
								{
								tempvar3.replace(open_bracket_after_and+1,comma_implies_after_and-open_bracket_after_and-1,x);
								cout<<"\ntempvar3"<<tempvar3;
								tempvar1.replace(and_symbol+4,found_implies-and_symbol,tempvar3);	
								cout<<"\ntempvar1"<<tempvar1;
								}			
								if(clausevar2_and=="x")
								{
								tempvar3.replace(comma_implies_after_and+1,close_bracket_after_and-comma_implies_after_and-1,x);
								cout<<"\ntempvar3"<<tempvar3;
								tempvar1.replace(and_symbol+4,found_implies-and_symbol,tempvar3);		
								cout<<"\ntempvar1"<<tempvar1;
								}		
							}
							cout<<"\ntempvar1"<<tempvar1;
						clauses[i].replace(0,found_implies,tempvar1);	
						}*/
					
	}
}
void display_kb()
{
	//cout<<"\n Infact";
	for(int i=0;i<fact_count;i++)
	{
	//cout<<"\n"<<fact[i];
	}
	//cout<<"\n Inclause";
	for(int i=0;i<clause_count;i++)
	{
	//	cout<<"\n"<<clauses[i];
	}
//cout<<"\n InKb";
		for(int i=0;i<kb_count;i++)
	{
	//	cout<<"\n"<<kb[i];
	}
	
}
void display_stack()
{
	for(int i=0;i<top;i++)
	{
//cout<<"\n stack item"<<i<<":"<<stack_item[i];
	}
}
int main(int argc, char *argv[])
{
 bool flag_yes=false;	
 input.open("input.txt");
 output.open("output.txt");
 fileread();
 display();
 fact_or_clause();
 find_x();
 //cout<<"\n*********************\n found x:"<<x<<"\n*********************\n";
 if(x.empty())
 {	
 bool fuckit=false;	
 if(xvar>0)
 {
 	for(int i=0;i<xvar;i++)
 	{
 		 top=0;
 infer=-1;
 pointit=1;
 	x=x_val[i];
//	cout<<"x_val"<<x;	
 	build_kb();
 		display_kb();
		 //find_main_clause();
 			std::size_t open_bracket=Mainsentence.find("(");
			std::size_t close_bracket=Mainsentence.find(")");
			std::size_t comma=Mainsentence.find(",");
			if(comma!=std::string::npos)
			{
		string mainpart1=Mainsentence.substr(0,open_bracket);
		//cout<<"\n firstpart:"<<mainpart1;
		string mainvar1=Mainsentence.substr(open_bracket+1,comma-open_bracket-1);
		//cout<<"\n Variable1:"<<mainvar1;
		string mainvar2=Mainsentence.substr(comma+1,close_bracket-comma-1);
		if(mainvar1==x)
		{
		Mainsentence.replace(open_bracket+1,comma-open_bracket-1,"x");	
		}
		if(mainvar2==x)
		{
		Mainsentence.replace(comma+1,close_bracket-comma-1,"x");	
		}
		}
		else
		{
		string clausepart1=Mainsentence.substr(0,open_bracket);	
			string clausevar2=Mainsentence.substr(open_bracket+1,close_bracket-open_bracket-1);
			if(clausevar2==x)
			{
				Mainsentence.replace(open_bracket+1,close_bracket-open_bracket-1,"x");
			}	
		}
//cout<<"\nMainsentence after finding X:"<<Mainsentence;
 stack_push();
 display_stack();
 stack_pop();
 //cout<<"infer"<<infer;
  if(infer==0&&found_compare==true)
  {
  //	cout<<"I'm here";
  	flag_yes=true;
  }
 	}
  if(flag_yes==true)
 {
 output<<"TRUE";	
 }
 else
 {
 output<<"FALSE";	
 }
	
 }
 else
 {
  //cout<<"infer"<<infer;
 
 for(int i=0;i<fact_count;i++)
 {
 	if(Mainsentence==fact[i])
 	{
 		fuckit=true;
 	}
 }
 if(fuckit==false)
 {
 output<<"FALSE";	
 }
 else
 {
 output<<"TRUE";	
 }	
 }
}
 else
 {
 	
 	 build_kb();
 display_kb();
 //find_main_clause();
 	std::size_t open_bracket=Mainsentence.find("(");
	std::size_t close_bracket=Mainsentence.find(")");
	std::size_t comma=Mainsentence.find(",");
	if(comma!=std::string::npos)
	{
		string mainpart1=Mainsentence.substr(0,open_bracket);
		//cout<<"\n firstpart:"<<mainpart1;
		string mainvar1=Mainsentence.substr(open_bracket+1,comma-open_bracket-1);
		//cout<<"\n Variable1:"<<mainvar1;
		string mainvar2=Mainsentence.substr(comma+1,close_bracket-comma-1);
		if(mainvar1==x)
		{
		Mainsentence.replace(open_bracket+1,comma-open_bracket-1,"x");	
		}
		if(mainvar2==x)
		{
		Mainsentence.replace(comma+1,close_bracket-comma-1,"x");	
		}
	}
	else
	{
		string clausepart1=Mainsentence.substr(0,open_bracket);	
			string clausevar2=Mainsentence.substr(open_bracket+1,close_bracket-open_bracket-1);
			if(clausevar2==x)
			{
				Mainsentence.replace(open_bracket+1,close_bracket-open_bracket-1,"x");
			}	
	}
//cout<<"\nMainsentence after finding X:"<<Mainsentence;
 bool hole=false;
 for(int i=0;i<fact_count;i++)
 {
 	if(Mainsentence==fact[i])
 	{
 		hole=true;
 	}
 }
 if(hole==true)
 {
 output<<"TRUE";	
 }
 else
 {	
 stack_push();
 display_stack();
 stack_pop();
 if(infer==0)
 {
 output<<"TRUE";	
 }
 else
 {
 output<<"FALSE";	
 }
 }
}
 input.close();
 output.close();
}
