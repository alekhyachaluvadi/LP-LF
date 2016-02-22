#include <bits/stdc++.h>

using namespace std;
map <string,set<string> > grammar;
set<string> productions;
set<string> right_productions;
map<string , set<string> > :: iterator it1;

void left_factoring(string l)
{
        set<string> r = it1->second;
        set<string> :: iterator it;
        int a[r.size()];
        int b[r.size()];
        int i =0;
        string common,common2;
        int count1 = 1 , count2 = 1;
        int first = 0,second = r.size();
        while(second - first){
                count1 = 1;
                common = "";
                for(it = r.begin() ,i=0 ; it!=r.end() ; it++,i++)
                {
                        common2 = *it;
                        if(i==first){
                                common = common2.substr(0,1);
                        }
                        else if((i<second)&& (common == common2.substr(0,1))&& common2.length()>0) {
                                a[i] = 1;
                                count1 ++;
                        }
                }
                if(count1>1){
                        int j=2;
                        do
                        {
                                count2 = 1;
                                for(it = r.begin() ,i=0 ; it!=r.end() ; it++,i++)
                                {
                                        common2 = *it;
                                        if(first == i)
                                                common = common2.substr(0,j);
                                        else if((i<second) && (j<= common2.length()) && (common == common2.substr(0,j))) {
                                                count2 ++;
                                        }
                                }
                                j++;
                        }while(count2==count1);
                        j =  j-2;
                        for(it = r.begin() ,i=0 ; it!=r.end() ; it++,i++)
                        {
                                if(i==first){

                                        common = (*it).substr(0,j);
                                        break;
                                }
                        }

                        for(it = r.begin(),i=0;it!=r.end();it++ , i++)
                        {
                                if((*it).length()>=j && common == (*it).substr(0,j))
                                {
                                        if((*it).length()>j){
                                        right_productions.insert((*it).substr(j));}
                                        else
                                                right_productions.insert("*");
                                        r.erase(*it);
                                }
                        }
                        printf("Enter a new terminal \n");
                        string str;
                        cin>>str;
                        common = common + str;
                        r.insert(common);
                        grammar[str] = right_productions;
                        right_productions.clear();

                }
                else first = first + 1;
        }
        grammar[l] = r;
        r.clear();
}
int main()
{
        cout<<"Enter the grammar \n";
        string input = "",key ="";
        // Input the grammar..................
        while(key != "-1")
        {
                input = "";
                cin>>key;

                if(key == "-1")
                        break;
                while(input!="-1")
                {
                        cin>>input;
                        if(input=="-1")
                                break;
                        productions.insert(input);
                }
                grammar[key] = productions;
                productions.clear();
        }

        //For each production left_factoring is done..........

        for(it1 = grammar.begin() ; it1!= grammar.end() ; it1++)
        {
                left_factoring(it1->first);
        }
        set<string> :: iterator it2;
        for(it1 = grammar.begin();it1 != grammar.end() ;it1++)
        {
                cout<<it1->first<<"-->";
                for(it2 = it1->second.begin();it2!=it1->second.end();it2++)
                cout<<*it2<<"|";
                cout<<endl;
        }
}
