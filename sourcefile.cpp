#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int n,k;
int answer1=0,answer2=0;

int readInt() {
    int p;
    scanf("%d", &p);
    return p;
}

int main(){
    int cinTemp=0;
    int T,test_case;
    T=readInt();
    for(test_case = 0; test_case  < T; test_case++)
    {
        n=readInt();
        k=readInt();
        vector<int> card1(n+1);
        vector<int> selectionInfoCard1(n+1);
        vector<int> card2(n+1);
        vector<int> selectionInfoCard2(n+1);
        vector<vector<bool>> dp(n+1,vector<bool>(n+1,0));
        vector<vector<int>> dpCard1(n+2,vector<int>(n+2,0));
        vector<vector<int>> dpCard2(n+2,vector<int>(n+2,0));
        int p=1,sum=0;
        for(int i=1;i<=n;i++){
            card1[i]=readInt();
            sum+=card1[i];
            while(i>=2&&sum>k) sum-=card1[p++];
            selectionInfoCard1[i]=p;
        }
        p=1;
        sum=0;
        for(int i=1;i<=n;i++){
            card2[i]=readInt();
            sum+=card2[i];
            while(i>=2&&sum>k) sum-=card2[p++];
            selectionInfoCard2[i]=p;
        }
        for(int i=0;i<=n;i++){
            cout<<selectionInfoCard1[i]<<"\t"<<selectionInfoCard2[i]<<endl;
        }
        int selectedIndex=0;
        dp[0][0]=1;
        dpCard2[1][1]=dpCard1[1][1]=dp[0][0];
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                bool temp=false;
                if(i==0&&j==0) continue;
                if(i>0){
                    selectedIndex=selectionInfoCard1[i];
                    if((dpCard1[i][j+1]-dpCard1[selectedIndex-1][j+1])<(i-selectedIndex+1)){
                        temp=true;
                    }
                }
                if(j>0){
                    selectedIndex=selectionInfoCard2[j];
                    if((dpCard2[i+1][j]-dpCard2[i+1][selectedIndex-1])<(j-selectedIndex+1))
                        temp= true;
                }
                if(temp) dp[i][j]=true;
                dpCard1[i+1][j+1]=dpCard1[i][j+1]+dp[i][j];
                dpCard2[i+1][j+1]=dpCard2[i+1][j]+dp[i][j];
            }
        }
        for(int i=0;i<=n;i++) answer1+=dpCard2[i+1][n+1];
        answer2=(n+1)*(n+1)-answer1;
        printf("Case #%d\n", test_case+1);
        printf("%d %d\n",answer1,answer2);
        answer1=0;
        answer2=0;
    }

}