#include<bits/stdc++.h>
#include<cstdlib>
#include<ctime>
using namespace std;
struct hashNode{
    string key;
    int value;
};
int N=10000;
int stringLength=5;
int hash1(string str){
    int g=41;
    int pos=0;
    int length=str.length();
    for(int i=0; i<length; i++)
        pos=g*pos+(int)str[i];
    return pos%N;
}
int hash2(string str){
    long Hash = 0;
    for(int i = 0; i < str.length(); i++){
        Hash = (int)str[i] + (Hash << 6) + (Hash << 16) - Hash;
    }
    if(Hash<0)
        Hash=-Hash;
    return Hash%N;
}
int hash3(string str){
    long Hash = 0;
    for(int i = 0; i < str.length(); i++){
        Hash = Hash << 7 ^ (int)str[i];
    }
    if(Hash<0)
        Hash=-Hash;
    return Hash%N;
}
class chnMeth{
    int hashCode;
    int collision;
    list<hashNode> mylist[10000];
public:
    chnMeth(int code){
        collision=0;
        hashCode=code;
    }
    void Insert(string str,int val){
        int pos;
        if(hashCode==1)
            pos=hash1(str);
        else if(hashCode==2)
            pos=hash2(str);
        else
            pos=hash3(str);
        hashNode node;
        node.key=str;
        node.value=val;
        if(!mylist[pos].empty())
            collision++;
        mylist[pos].push_back(node);}
    int Search(string str){
        int pos;
        if(hashCode==1)
            pos=hash1(str);
        else if(hashCode==2)
            pos=hash2(str);
        else
            pos=hash3(str);
        hashNode temp;
        if(mylist[pos].empty())
            return -1;
        else{
            for (list<hashNode>::iterator it = mylist[pos].begin(); it != mylist[pos].end(); it++){
                temp=*it;
                if(temp.key==str)
                    return pos;
            }
            return -1;
        }
    }
    void Delete(string str){
        int pos=Search(str);
        hashNode temp;
        if(pos==-1)
            return ;
        else{
            for (list<hashNode>::iterator it = mylist[pos].begin(); it != mylist[pos].end(); it++){
                temp=*it;
                if(temp.key==str){
                    mylist[pos].erase(it);
                    return;
                }
            }
        }
    }
    void printTable(){
        hashNode temp;
        for(int i=0; i<N; i++){
            if(!mylist[i].empty()){
                for (list<hashNode>::iterator it = mylist[i].begin(); it != mylist[i].end(); it++){
                    temp=*it;
                    cout<<temp.key<<" "<<temp.value<<" ";
                }
            }
            cout<<endl;
        }
    }
    int getCollision(){
        return collision;
    }
};


string ranStrGen(int length){
    string ranStr;
    char c;
    for(int i=0; i<length; i++){
        c='A'+rand()%26;
        ranStr+=c;
    }
    return ranStr;
}
string* getSrchList(set<string> inputList){
    string* inputString;
    inputString=new string[N];
    set<string>::iterator p=inputList.begin();
    int i=0;
    while(p!=inputList.end()){
        inputString[i]=*p;
        p++;
        i++;
    }
    return inputString;
}
class linProb{
    hashNode* hashTable;
    int hashCode;
    int N;
    int collision;
public:
    linProb(int n,int code){
        hashCode=code;
        N=n;
        collision=0;
        hashTable=new hashNode[N];
        for(int i=0; i<N; i++){
            hashTable[i].key="";
            hashTable[i].value=-1;
        }
    }
    void Insert(string str,int val){
        int pos;
        if(hashCode==1)
            pos=hash1(str);
        else if(hashCode==2)
            pos=hash2(str);
        else
            pos=hash3(str);
        int pos2=pos;
        if(hashTable[pos].key==""||hashTable[pos].key=="DELETED"){
            hashTable[pos].key=str;
            hashTable[pos].value=val;
        }
        else{
            collision++;
            while(!(hashTable[pos].key==""||hashTable[pos].key=="DELETED"||(pos+1)%N==pos2)){
                pos=(pos+1)%N;
            }
            hashTable[pos].key=str;
            hashTable[pos].value=val;
        }
    }
    int Search(string str){
        int pos;
        if(hashCode==1)
            pos=hash1(str);
        else if(hashCode==2)
            pos=hash2(str);
        else
            pos=hash3(str);
        int pos2=pos;
        if(hashTable[pos].key==str){
            return pos;
        }
        else if(hashTable[pos].key==""){
            return -1;
        }
        else{
            while(!(hashTable[pos].key==""||hashTable[pos].key==str||(pos+1)%N==pos2)){
                pos=(pos+1)%N;
            }
            if(hashTable[pos].key==str)
                return pos;
            else
                return -1;
        }
    }
    void Delete(string str){
        int pos=Search(str);
        if(pos==-1)
            return ;
        else{
            hashTable[pos].key="DELETED";
            hashTable[pos].value=-1;
        }
    }
    void printTable(){
        for(int i=0; i<N; i++){
            cout<<hashTable[i].key<<" "<<hashTable[i].value<<endl;
        }
    }
    int getCollision(){
        return collision;
    }
};
double getSrchTmLinHash(linProb linHash,string* srchStrList){
    double start_s=clock();
    for(int i=0; i<N; i++){
        linHash.Search(srchStrList[i]);
    }
    double stop_s=clock();
    return (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
}
double getSrchTmChnHash(chnMeth chnHash,string* srchStrList){
    double start_s=clock();
    for(int i=0; i<N; i++){
        chnHash.Search(srchStrList[i]);
    }
    double stop_s=clock();
    return (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 ;
}
int main(){
    srand(time(0));
    string ranStr;
    int i=0;
    linProb linHash1(N,1);
    linProb linHash2(N,2);
    linProb linHash3(N,3);
    chnMeth chnHash1(1);
    chnMeth chnHash2(2);
    chnMeth chnHash3(3);
    while(i!=N){
        ranStr=ranStrGen(stringLength);
        if(linHash1.Search(ranStr)==-1){
            linHash1.Insert(ranStr,i+1);
            linHash2.Insert(ranStr,i+1);
            linHash3.Insert(ranStr,i+1);
            chnHash1.Insert(ranStr,i+1);
            chnHash2.Insert(ranStr,i+1);
            chnHash3.Insert(ranStr,i+1);
            i++;
        }
    }
    set<string> inputList;
    while(inputList.size()!=N){
        ranStr=ranStrGen(stringLength);
        inputList.insert(ranStr);
    }
    string* srchStrList=getSrchList(inputList);
    double srchTmLinHash1=getSrchTmLinHash(linHash1,srchStrList);
    double srchTmLinHash2=getSrchTmLinHash(linHash2,srchStrList);
    double srchTmLinHash3=getSrchTmLinHash(linHash3,srchStrList);
    double srchTmChnHash1=getSrchTmChnHash(chnHash1,srchStrList);
    double srchTmChnHash2=getSrchTmChnHash(chnHash2,srchStrList);
    double srchTmChnHash3=getSrchTmChnHash(chnHash3,srchStrList);
    printf("\t\t\t\tHash1\tHash2\tHash3\n");
    cout<<"Linear Probing:"<<endl;
    cout<<"#Collisions:\t\t\t"<<linHash1.getCollision()<<"\t"<<linHash2.getCollision()<<"\t"<<linHash3.getCollision()<<endl;
    printf("Search Time(ms):\t\t%.2lf\t%.2lf\t%.2lf\n\n",srchTmLinHash1,srchTmLinHash2,srchTmLinHash3);
    cout<<"Separate Chaining:"<<endl;
    cout<<"#Collisions:\t\t\t"<<chnHash1.getCollision()<<"\t"<<chnHash2.getCollision()<<"\t"<<chnHash3.getCollision()<<endl;
    printf("Search Time(ms):\t\t%.2lf\t%.2lf\t%.2lf\n",srchTmChnHash1,srchTmChnHash2,srchTmChnHash3);
    return 0;
}
