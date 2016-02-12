#include<bits/stdc++.h>
using namespace std;
vector< set<string> > right_productions;
vector< set<string> > first;
vector<string> terminals , non_terminals , left_productions;

int is_a_terminal(string nt)
{
	for(int i =0;i<terminals.size() ; i++)
	{
		if(nt == terminals[i])
			return 1;
	}
	return 0;
}
int add_check_epsilon(string str1,string str2)
{
	int j=0 ,i, pos1 =0,pos2=0,l=0,k=0;
	for(i =0;i<left_productions.size();i++)
	{
		if(str1 == left_productions[i])
		{
			pos1 = i;
			l=1;
		}
		if(str2 == left_productions[i])
		{
			pos2 = i;
			k=1;
		}
		if(l+k==2)
			break;
	}
	set<string>::iterator it;
	for(it = first[pos2].begin();it!=first[pos2].end();it++)
	{	
		if((*it)=="#")
			j=1;
		else
			first[pos1].insert(*it);

	}
	return j;
}

void calculate_first_values(string nt)
{
	set<string> :: iterator it;
	int i=0;
	for(i = 0;i<left_productions.size() ; i++)
	{
		if(nt == left_productions[i])
			break;
	}
			if(first[i].size()!=0)
			return ;
	for(it = right_productions[i].begin() ;it!=right_productions[i].end();it++)
	{

		cout<<"alekhya"<<"  "<<nt<<"  "<<i<<"  "<<(*it)<<endl;
		if(is_a_terminal(*it))
			first[i].insert(*it);
		else if(is_a_terminal((*it).substr(0,1)))
			first[i].insert((*it).substr(0,1));
		else if((*it)=="#")
			first[i].insert((*it));
		else 
		{
			int k =0,j;
			for(j=0;j<(*it).length();j++)
			{
				calculate_first_values((*it).substr(j,1));
				 k =	add_check_epsilon(nt,(*it).substr(j,1));
				if(!k)
					break;
			}
			if((j==(*it).length()) && (k==1))
				first[i].insert("#");
		}
	}
}
void print_grammar()
{
	set<string> :: iterator it;
	int i=0;
	for(i=0;i<left_productions.size();i++)
	{
		cout<<left_productions[i]<<"---->";
		for(it = first[i].begin(); it!=first[i].end();it++)
		{
			cout<<(*it)<<"|";
		}
		cout<<endl;
	}
}
int main()
{
	set<string> input;
	string left = "",right = "";
		/*...........Productions Input............*/
	while(left!= "-1")
	{
		cin>>left;
		if(left =="-1")
			break;
		left_productions.push_back(left);
		right = "";
		while(right!="-1")
		{
			cin>>right;
			if(right=="-1")
				break;
			input.insert(right);
		}
		right_productions.push_back(input);
		input.clear();
	}

	for(int i = 0;i<left_productions.size();i++)
	{
		first.push_back(input);
	}

	cout<<"enter the terminal list\n";
	while(1)
	{
		cin>>right;
		if(right=="-1")
			break;
		terminals.push_back(right);
	}

	cout<<"enter the non terminals list\n";
	while(1)
	{
		cin>>right;
		if(right=="-1")
			break;
		non_terminals.push_back(right);
	}
//	print_grammar();
	for(int i=0;i<left_productions.size();i++)
		calculate_first_values(left_productions[i]);
	print_grammar();
}














