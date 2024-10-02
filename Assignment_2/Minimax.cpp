#include<bits/stdc++.h>

using namespace std;
//depth-> Current depth in game tree
//nodeIndex is the index of the current node in scores
//isMax : true if current move is maximizer, else false
//scores[] stores leaves of game tree
//h maximum height of game tree
int minimax(int depth, int nodeIndex, bool isMax,int scores[], int h){
        if(depth==h){
                return scores[nodeIndex];
        }

        if(isMax){
                return max(minimax(depth+1, nodeIndex*2, false,scores,h),minimax(depth+1, nodeIndex*2+1,false,scores,h));
        }
        
        else{
                return min(minimax(depth+1, nodeIndex*2, true,scores,h),minimax(depth+1, nodeIndex*2+1,true,scores,h));
        }
}

int log2(int n)
{
  return (n==1)? 0 : 1 + log2(n/2);
}

int main()
{
    // The number of elements in scores must be
    // a power of 2.
    int scores[] = {3, 5, 2, 9, 12, 5, 23, 23};
    int n = sizeof(scores)/sizeof(scores[0]);
    int h = log2(n);
    int res = minimax(0, 0, true, scores, h);
    cout << "The optimal value is : " << res << endl;
    return 0;
}