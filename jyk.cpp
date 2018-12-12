#include "head.h"
#include <iostream>
#include <vector>
#include <string.h>


extern vector<Quadruple> qua_list;
extern struct Quadruple qua;
extern vector<Word> words;
extern int token_i;

vector<string> A;
vector<string> SEM;

string s = "";
void reset0()
{
while(!A.empty())
    {
        A.pop_back();
    }
    A.push_back("#");
    A.push_back("S");
}

void PU(string s)
{
    SEM.push_back(s);
}
void WE()
{
    qua.s[0] = "we";
    qua.s[1] = "_";
    qua.s[2] = "_";
    qua.s[3] = "_";
    qua_list.push_back(qua);
}
void WH()
{
    qua.s[0] = "wh";
    qua.s[1] = "_";
    qua.s[2] = "_";
    qua.s[3] = "_";
    qua_list.push_back(qua);
}
void DO()
{
    if(SEM.size()==2)
    {
        qua.s[0] = s;
        qua.s[1] = SEM[0];
        qua.s[2] = SEM[1];
        qua.s[3] = "t1";
        qua_list.push_back(qua);
        qua.s[0] = "do";
        qua.s[1] = "t1";
        qua.s[2] = "_";
        qua.s[3] = "_";
        qua_list.push_back(qua);
    }
    else if(SEM.size()==1)
    {
        qua.s[0] = "do";
        qua.s[1] = SEM[0];
        qua.s[2] = "_";
        qua.s[3] = "_";
        qua_list.push_back(qua);
    }

}
int fun_while()
{

    if(A.back().compare("S")==0&&words[token_i].value.compare("while")==0)
    {
        cout<<"S->W D F"<<endl;
        A.pop_back();
        A.push_back("WE");
        A.push_back("F");
        A.push_back("D");
        A.push_back("W");
        return 1;
    }
    else if(A.back().compare("F")==0&&words[token_i].value.compare("{")==0)
    {
        cout<<"F->{f}"<<endl;
        A.pop_back();
        A.push_back("}");
        A.push_back("f");
        A.push_back("{");
        return 1;
    }
    else if(A.back().compare("F")==0&&words[token_i].value.compare("{")!=0)
    {
        cout<<"F->f"<<endl;
        A.pop_back();
        A.push_back("f");
        return 1;
    }
    else if(A.back().compare("W")==0)
    {
        cout<<"W->while"<<endl;
        A.pop_back();
        A.push_back("WH");
        A.push_back("while");
        return 1;
    }
    else if(A.back().compare("D")==0&&words[token_i].value.compare("(")==0)
    {
        cout<<"D->(R)"<<endl;
        A.pop_back();
        A.push_back("DO");
        A.push_back(")");
        A.push_back("R");
        A.push_back("(");
        return 1;
    }
    else if(A.back().compare("R")==0&&(words[token_i].type.compare("I")==0||words[token_i].type.compare("c")==0))
    {
        cout<<"R->I R'"<<endl;
        A.pop_back();
        A.push_back("R'");
        A.push_back("I");
        return 1;
    }
    else if(A.back().compare("R'")==0&&words[token_i].type.compare("P")==0)
    {
        cout<<"R'->w I"<<endl;
        A.pop_back();
        A.push_back("I");
        A.push_back(words[token_i].value);
        return 1;
    }
    else if(A.back().compare("R'")==0&&words[token_i].type.compare("P")!=0)
    {
        cout<<"R'->"<<endl;
        A.pop_back();
        s = words[token_i].value;
        return 1;
    }
    else if(A.back().compare("f")==0)
    {
        fn_body();
        A.pop_back();
        return 1;
    }
    else if(A.back().compare("WE")==0)
    {
        A.pop_back();
        WE();
        return 1;
    }
    else if(A.back().compare("WH")==0)
    {
        A.pop_back();
        WH();
        return 1;
    }
    else if(A.back().compare("DO")==0)
    {
        A.pop_back();
        DO();
        return 1;
    }
    else if(A.back().compare("I")==0&&(words[token_i].type.compare("I")==0||words[token_i].type.compare("c")==0))
    {
        A.pop_back();
        PU(words[token_i].value);
        token_i++;
        return 1;
    }
    else if(A.back().compare("#")==0)
        return 2;
    else{
        if(A.back().compare(words[token_i].value)==0)
        {
          if(A.back().compare(")")==0)
           {
               cout<<" "<<"D->(R)"<<endl;
           }
           if(A.back().compare("}")==0)
           {
               cout<<" "<<"F->{f}"<<endl;
           }
            A.pop_back();
            token_i++;
           return 1;
        }
        else
            return 0;
    }
return 1;
}

void fn_while()
{
    int a = 1;
    reset0();
    while(a==1)
    {
        a = fun_while();
    }
    if(a==2)
        cout<<"RIGHT"<<endl;
    else if(a==0)
        cout<<"WRONG"<<endl;
}