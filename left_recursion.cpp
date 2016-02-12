/***********************************************************
	Eliminates Immediate left Recursion in a grammar
************************************************************/

#include<bits/stdc++.h>
using namespace std;

vector<string> left_productions;
vector< set<string> > right_productions;
set<string> :: iterator it;
string new_non_terminal;
set<string> new_set , temp , temp1;


/*  Function Used to print the grammar */
void print_grammar()
{
	int i=0;
	for(i=0;i<left_productions.size();i++)
	{
		cout<<left_productions[i]<<"---->";
		for(it = right_productions[i].begin(); it!=right_productions[i].end();it++)
		{
			cout<<(*it)<<"|";
		}
		cout<<endl;
	}
}

/*Function which eliminates recursion in a grammar.
*/
  void eliminate_left_recursion()
{
	int i=0,j;
	for(i=0;i<left_productions.size();i++)
	{
		j = 0;
		for(it = right_productions[i].begin();it!=right_productions[i].end();it++)
		{
			if(left_productions[i]==(*it).substr(0,1))
			{
				if(j==0)
				{
					cout<<"enter a new terminal\n";
					cin>>new_non_terminal;
					j=1;
				}
					new_set.insert((*it).substr(1)+new_non_terminal);
					cout<<((*it).substr(1)+new_non_terminal)<<endl;
			}
			else
				temp.insert((*it));
		}

		if(j==1)
		{
			new_set.insert("*");
			left_productions.push_back(new_non_terminal);
			right_productions.push_back(new_set);
			for(it = temp.begin() ; it!=temp.end();it++)
			{
				temp1.insert((*it)+new_non_terminal);
			}
			right_productions[i] = temp1;
			temp.clear();
			temp1.clear();
			new_set.clear();
		}
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

	eliminate_left_recursion();
	print_grammar();
}
