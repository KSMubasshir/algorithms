#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
void matrix_chain_order(int n,int *p,int **m,int **s){
    int q;
    for(int i=1; i<=n; i++)
        m[i][i]=0;
    for(int l=2; l<=n; l++){
        for(int i=1; i<=n-l+1; i++){
            int j=i+l-1;
            m[i][j]=INFINITY;
            for(int k=i; k<=j-1; k++){
                q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j]){
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
}
void print_opt_parens(int i,int j,int n,int **s){
    if(i==j)
        cout<<"A"<<i;
    else{
        cout<<"(";
        print_opt_parens(i,s[i][j],n,s);
        print_opt_parens(s[i][j]+1,j,n,s);
        cout<<")";
    }
}
int main(){
    FILE *fp;
    int n ;
    fp = fopen("data/mcm_input.txt","r");
    fscanf(fp,"%d", &n);
    int *p=new int[n+1];
    int mat[n][2];
    for(int i=0; i<n; i++){
        fscanf(fp,"%d%d",&mat[i][0],&mat[i][1]);
        if(i>0&&mat[i-1][1]!=mat[i][0]){
            cout<<"Wrong Dimension"<<endl;
            getchar();
            return 0;
        }
        p[i]=mat[i][0];
    }
    p[n]=mat[n-1][1];
    fclose(fp);
    int **m;
    m= new int *[n+1];
    int **s;
    s = new int *[n+1];
    for(int i = 0; i <n+1; i++){
        m[i] = new int[n+1];
        s[i] = new int[n+1];
    }
    matrix_chain_order(n,p,m,s);
    cout<<m[1][n]<<endl;
    print_opt_parens(1,n,n,s);
    cout<<endl;
    for(int i=0; i<n+1; i++){
        delete m[i];
        delete s[i];
    }
    delete m;
    delete s;
    return 0;
}
