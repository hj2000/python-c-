#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<stdexcept>
#include<algorithm>
#include<iomanip>
using namespace std;
class pystring
{
private:
    char* S = nullptr;
    int n = 0;
    int num = 0;
public:
    pystring() = default;
    friend ostream& operator<<(ostream& os, pystring& p) {
        os << p.S;
        return os;
    }
    friend ostream& operator<<(ostream& os, pystring&& p) {
        os << p.S;
        return os;
    }
    friend int len(pystring const& a) {
        return a.n;
    }
    pystring capitalize();
    pystring casefold();
    char center();
    int count(char a);
    int count(const char* p);
    //pystring encode();编码问题
    bool endswith(const char* p, int start = 0, int end = -1);
    pystring expandtabs(int tabsize=8);
    int find(const char*p, int start = 0, int end = -1);
    int index(const char*p, int start = 0, int end = -1);
    bool isalnum();
    pystring(const char* p);
    ~pystring();
};

pystring::pystring(const char* p)
{
    n = strlen(p);
    num = n + 1;
    S = new char [num];
    if (S != nullptr) {
        memcpy(S, p, n + 1);
    }
    else {
        throw range_error("字符串内存不够");
    }
}
pystring pystring::capitalize() {
    pystring a(this->S);
    if (islower(a.S[0])) {
        a.S[0] = toupper(a.S[0]);
    }
    return a;
}
pystring pystring::casefold() {
    pystring a(this->S);
    int i = 0;
    for (int i = 0; i < a.n; i++)
    {
        if (islower(a.S[i])) {
            a.S[i] = toupper(a.S[i]);
        }
    }
    return a;
}
char pystring::center() {
    return this->S[n / 2];
}
#ifndef cstr
int pystring::count(char a) {
    int cou = 0;
    for (int i = 0; i < this->n; i++)
    {
        if (this->S[i] == a)
        {
            cou++;
        }
    }
    return cou;
}
int pystring::count(const char* p) {
    int cou = 0;
    int np = strlen(p);
    for (int i = 0; i < this->n; i++)
    {
        if (strncmp(p, S + i, np) == 0) {
            cou++;
            i += np-1;
        }
    }
    return cou;
}
pystring pystring::expandtabs(int tabsize){
    int sizet=this->count('\t');
    char*p=new char[sizet*tabsize+num];
    for (int i = 0,j = 0; i < num; i++)
    {
        if(this->S[i]=='\t'){
            for (int k = 0; k < tabsize; k++)
            {
                p[i+k]=' ';
            }
            j+=tabsize;
        }
        else{
            p[j]=this->S[i];
            j++;
        }
    }
    return pystring(p);
}
int pystring::find(const char*p, int start, int end){
    int np=strlen(p);
    if(end<0)
    end+=n;
    if (end - start + 1 < np) {
       return -1;
    }
    for (int i = start; i <= end-np+1; i++)
    {
        int j=0;
        while (p[j]==this->S[i+j]&&j<np)
        {
            j++;
        }
        if(j==np){
            return i;
        }
        
    }
    return -1;
}
int pystring::index(const char*p, int start, int end){
    int k=this->find(p,start,end);
    if(n<0){
        throw out_of_range("can't find the string");
    }
    else
    {
        return k;
    }
    
}
bool pystring::isalnum(){
    for (int i = 0; i < n; i++)
    {
        if(!std::isalnum(this->S[i]))
        return false;
    }
    return true; 
}
#elif defined cppago 
int pystring::count(char a) {
    int cou = std::count(this->S, this->S + this->n, a);
    return cou;
}
int pystring::count(const char* p) {
    int cou = 0;
    size_t np=strlen(p);
    string s(this->S);
    size_t a=s.find(p);
    while(a!=string::npos){
        cou++;
        a=s.find(p,a+np);
    }
    return cou;
}
pystring pystring::expandtabs(int tabsize){
    string tabs(tabsize,' ');
    string p(this->S);
    size_t t=p.find("\t");
    while(t!=string::npos){
        p.replace(t,1,tabs);
        t=p.find("\t",t+1);
    }
    return pystring(p.c_str());
}
#else
int pystring::count(char a) {
    int cou=0;
    char* p=strchr(this->S,a);
    while (p) {
        cou++;
        p = strchr(p, a);
    }
    return cou;
}
int pystring::count(const char* p) {
    int cou = 0;
    char*q=strstr(this->S,p);
    while(q){
        cou++;
        q=strstr(q,p);
    }
    return cou;
}
#endif
bool pystring::endswith(const char*p,int start,int end) {
    int np = strlen(p);
    int qi = 0;
    if (end < 0) {
        end += this->n;
    }
    if (end - start + 1 < np) {
       return false;
    }
    return strncmp(p, this->S+end-np+1, np)==0;
}
pystring::~pystring()
{
}