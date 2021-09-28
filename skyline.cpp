#include<bits/stdc++.h>
#define inf 999999
using namespace std;
class point{
public:
    double x;
    double y;
};
void myMerge(point* pt,int lo,int hi);
bool acompare(point lhs, point rhs){
    return lhs.x < rhs.x;
}
void comp(point* pt,int i,int j){
    if(pt[i].x>=pt[j].x&&pt[i].y>=pt[j].y){
        pt[i].x=inf;
        pt[i].y=inf;
    }
    else if(pt[i].x<=pt[j].x&&pt[i].y<=pt[j].y){
        pt[j].x=inf;
        pt[j].y=inf;
    }
}
void skyLine(point* pt,int lo,int hi){
    if(lo==hi)
        return;
    else if(abs(hi-lo)==1){
        comp(pt,lo,hi);
    }
    else{
        int mid=(lo+hi)/2;
        skyLine(pt,lo,mid);
        skyLine(pt,mid+1,hi);
        myMerge(pt,lo,hi);
    }
}
void myMerge(point* pt,int lo,int hi){
    int mid=(lo+hi)/2;
    for(int i=0; i<=mid; i++){
        for(int j=mid+1; j<=hi; j++){
            comp(pt,i,j);
        }
    }
}
int main(){
    int n;
    cin>>n;
    point pt[n];
    for(int i=0; i<n; i++){
        cin>>pt[i].x>>pt[i].y;
    }
    sort(pt,pt+n,acompare);
    skyLine(pt,0,n-1);
    cout<<"Skyline:"<<endl;
    for(int i=0; i<n; i++){
        if(pt[i].x!=inf)
            cout<<pt[i].x<<" "<<pt[i].y<<endl;
    }
    return 0;
}
/*
Input:
8
1 11
2 6
3 13
12 7
14 3
19 18
23 13
24 4
*/