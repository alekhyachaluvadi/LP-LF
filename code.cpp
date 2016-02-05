#include <bits/stdc++.h>

string new ; 
set<string> right_productions;

void left_factoring(string l, set<string> r)
{
	set<string> :: iterator it2;
	int a[r.size()] = {0};
	int b[r.size()]	= {0};
	int count1 = 0 , count2 = 0;
	string common = *r.begin().substr(0,1);
	for(it = r.begin() ,i=0 ; it!=r.end() ; it++,i++)
	{
		if(common == *it.substr(0,1)) {
			a[i] = 1;
			count1 ++;
		}
	}
	do
	{
		count2 = 0;
		common = *r.begin().substr(0,j);
		for(it = r.begin() ,i=0 ; it!=r.end() ; it++,i++)
		{
			if(common == *it.substr(0,j)) {
				//a[i] = 1;
				count2 ++;
			}
		}
		j++;
	}while(count2==count1);

	
}
int main()
{
	map <string,set<string> > grammar;
	set<string> productions;
	string key;
	printf("enter the grammar\n");
	string input = "";

	// Input the grammar..................
	while(key ! = -1)
	{
		scanf("%s",key);

		if(key == "-1")
			break;
		while(input!=-1)
		{
			scanf("%s",input);
			productions.insert(input);
		}
		grammar[key] = productions;
		productions.clear();
	}

	//For each production left_factoring is done..........
	map<string,set<string> > :: iterator it1;

	for(it1 = grammar.begin() ; it1! = grammar.end() ; it1++)
	{
		left_factoring(it1->first() , it1->second());
		right_productions.clear();
	}

}
