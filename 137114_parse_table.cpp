#include<bits/stdc++.h>
using namespace std;
vector< set<string> > right_productions;
vector< set<string> > first , follow ;
vector<string> terminals , non_terminals , left_productions;
string rule[15][3];
string parse_table[15][15];
int top = 0;
int is_a_terminal(string nt)
{
        for(int i =0;i<terminals.size() ; i++)
        {
                if(nt == terminals[i])
                        return 1;
        }
        return 0;
}
int add_function(string str1,string str2,int tag)
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
        if(tag == 0){
        for(it = first[pos2].begin();it!=first[pos2].end();it++)
        {
                if((*it)=="#")
                        j=1;
                else
                        first[pos1].insert(*it);

        }
        }
        else
        {
        		cout<<"string1 and string2 "<<str1<<"   "<<str2<<endl;
                for(it = follow[pos2].begin();it!=follow[pos2].end();it++)
                {
                		cout<<(*it)<<"  ";
                        follow[pos1].insert(*it);
                }
                cout<<endl;
                j = 0;
        }
        return j;
}
int get_pos(string str)
{
	int i;
        for(i =0;i<terminals.size() ; i++)
        {
                if(str == terminals[i])
                        return i;
        }
        return i;
}
int add_function_1(int pos,string str2,int tag)
{
        int j=0 ,i, pos1 =0,pos2=0,l=0,k=0;
        string temp;
        if(tag!=0)
        {
            temp = str2 ;
            str2 = str2.substr(tag-1,1);
        }
        if(is_a_terminal(str2))
        {
                follow[pos].insert(str2);
                return 0;
        }
        for(i =0;i<left_productions.size();i++)
        {
                if(str2 == left_productions[i])
                {
                        pos2 = i;
                        break;
                }
        }
        set<string>::iterator it;
        if(tag == 0){
        for(it = first[pos2].begin();it!=first[pos2].end();it++)
        {
                if((*it)=="#")
                        j=1;
                else
                        follow[pos].insert(*it);

        }
        }
        else
        {
            for(it = first[pos2].begin();it!=first[pos2].end();it++)
            {
                if((*it)=="#")
                        j=1;
                parse_table[pos][get_pos(*it)] = temp;
            }  
        }
        return j;
}

void scan_rules_and_fill_follow()
{
        int val =  top;
        int tag ;
        int i,j;
        for(j = 0;j<2;j ++){
        for(i = 0;i < val ; i++)
        {
                add_function(rule[i][0],rule[i][1],1);
        }
}
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
                                 k =    add_function(nt,(*it).substr(j,1),0);
                                if(!k)
                                        break;
                        }
                        if((j==(*it).length()) && (k==1))
                                first[i].insert("#");
                }
        }
}

int fill_follow_table(int pos, string beta)
{
        int j = 0 , k;
        for(j=0;j<beta.length();j++)
        {
                k = add_function_1(pos , (beta).substr(j,1),0);
                cout<<k<<"      "<<beta<<endl;
                if(!k)
                        break;
        }

        return k;
}
void calculate_follow_values(int i)
{
        string left = left_productions[i];
        string B , beta ;
        int j=0 ,k,pos;
        set<string> :: iterator it;
        for(it = right_productions[i].begin() ; it!=right_productions[i].end() ; it++)
        {
                for(j = 0 ;j<(*it).length() ; j++)
                {
                        if(((*it)!="#")&&(!is_a_terminal((*it).substr(j,1))))
                        {
                                B  = (*it).substr(j,1);
                                if(j!=(*it).length())
                                        beta = (*it).substr(j+1);
                                cout<<"B is "<<B<<"Beta is "<<beta<<endl;
        						for(pos = 0;pos<left_productions.size() ; pos++)
        					 	{
                					if(B == left_productions[pos])
                        				break;
        						}
                                if(beta.length()!=0)
                                {
                                        k = fill_follow_table(pos,beta);
                                }
                                if(((beta.length()==0)|| (k==1))&&B!=left)
                                {
                                        rule[top][0] += B;
                                        rule[top][1] += left_productions[i];
                                        cout<<B<<" "<<left_productions[i]<<endl;
                                        rule[top][2] += "0";
                                        top ++;
                                }

                        }

                }
        }

}
void add_at_follow(int pos,string str)
{
    set<string> :: iterator it;
    for(it = follow[pos].begin() ; it!=follow[pos].end() ; it++)
    {
        parse_table[pos][get_pos(*it)] += str;
        //cout<<pos<<"   "<<get_pos(*it)<<"   "<<str<<endl;
    }
}
void fill_parse_table()
{
    int i = 0;
    set<string> :: iterator it;
    for(i = 0 ;i<left_productions.size();i++)
    {
        for(it = right_productions[i].begin() ; it!=right_productions[i].end();it++)
        {
                int j = 0 , k;
                cout<<(*it)<<endl;
                if((*it)!="#"){
                for(j=0;j<(*it).length();j++)
                {
                	if(is_a_terminal((*it).substr(j,1)))
                	{
                		parse_table[i][get_pos((*it).substr(j,1))] += (*it);
                		break;
                	}
                    k = add_function_1(i,(*it),j+1);
                    if(!k)
                        break;
                }
                }
                if((k==1)||((*it)=="#"))
                {
                	//cout<<"Entered "<<left_productions[i]<<"  "<<(*it)<<endl;
                    add_at_follow(i,(*it));
                }
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
                        cout<<(*it)<<" ";
                }
                cout<<"----------";
                for(it = follow[i].begin(); it!=follow[i].end();it++)
                {
                        cout<<(*it)<<" ";
                }
                cout<<endl;
                for(int j=0;j<=terminals.size();j++){
                	if(parse_table[i][j]!="")
                	cout<<left_productions[i]<<"->"<<parse_table[i][j]<<"  ";
                	else
                	cout<<"BLANK"<<" ";
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
                follow.push_back(input);
        }

        follow[0].insert("$");
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
//      print_grammar();
        for(int i=0;i<left_productions.size();i++)
                calculate_first_values(left_productions[i]);

        for(int i=0;i<left_productions.size();i++)
                calculate_follow_values(i);

        scan_rules_and_fill_follow();
        fill_parse_table();
        print_grammar();
}

/*
E TA -1
A +TA # -1
T FB -1
B *FB # -1
F (E) i -1
-1
i
+
*
(
)
-1
E
A
T
B
F
-1
*/
