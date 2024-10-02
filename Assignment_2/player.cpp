#include <bits/stdc++.h>

using namespace std;

int husValue;

class Mancala_Board {
public:
    vector<int> mancala;
    int W1=1;
    int W2=2;
    int W3=3;
    int W4=4;
    int added_move=0;
    int stone_captured=0;

    Mancala_Board(vector<int>& board) {
        mancala = board;
    }

    void print_mancala(vector<int>& mancala) {
        cout<<endl;
        cout<<"|-------------------------------|"<<endl;
        cout<<"|   | ";
        for(int i=12;i>6;i--){
                cout<<mancala[i]<<" | ";
        }
        cout<<"  |"<<endl;
        cout << "| " <<mancala[13] << " |-----------------------| " << mancala[6]<<" |" <<endl;
        cout<<"|   | ";
        for(int i=0;i<6;i++){
                cout<<mancala[i]<<" | ";
        }
        cout<<"  |"<<endl;
        cout<<"|-------------------------------|"<<endl;
        
    }

    bool isEnd(int player) {
            if(player==1){
               int sum=0;
                for(int i = 0; i <6;i++){
                        sum+=mancala[i];
                }
                if(sum==0){return true;}
                else{return false;}
            }
            if(player==2){
                int sum=0;
                for(int i =7; i<=12;i++){
                        sum+=mancala[i];
                }
                if(sum==0){return true;}
                return false;
            }
    }

    
    int husVal(int num) {
        if(num==1){
                return husVal_1();
        }
        if(num==2){
                return husVal_2();
        }
        if(num==3){
            return husVal_3();
        }
        if(num==4){
            return husVal_4();
        }
    }

    int husVal_1(){
         return mancala[6]-mancala[13];
    }
    int husVal_2(){
        int sum_max=0;
        int sum_min=0;

        for(int i=0;i<6;i++){
                sum_max+=mancala[i];
        }
        for(int i=7;i<13;i++){
                sum_min+=mancala[i];
        }
        return (W1*(mancala[6]-mancala[13])+W2*(sum_max-sum_min));
    }

    int husVal_3(){
        int sum_max=0;
        int sum_min=0;

        for(int i=0;i<6;i++){
                sum_max+=mancala[i];
        }
        for(int i=7;i<13;i++){
                sum_min+=mancala[i];
        }
        return (W1*(mancala[6]-mancala[13])+W2*(sum_max-sum_min)+W3*added_move);    

    }

    int husVal_4(){
        int sum_max=0;
        int sum_min=0;

        for(int i=0;i<6;i++){
                sum_max+=mancala[i];
        }
        for(int i=7;i<13;i++){
                sum_min+=mancala[i];
        }
        return (W1*(mancala[6]-mancala[13])+W2*(sum_max-sum_min)+W3*added_move+W4*stone_captured); 

    }

    
    bool player_move(int move) {
        // Implement the game logic to simulate a move and return whether the player gets another turn.
        int j=move;
        bool turn=false;
        int val=mancala[j];
        mancala[j]=0;


        //player-1 capture index 6
        //Max player
        if(j<6){
                while(val>0){
                        j++;
                        j=j%14;
                        if(j==13)continue;
                        mancala[j]++;
                        val--;
                }
                if(j<6 && mancala[j]==1){
                        mancala[6]+=mancala[j]+mancala[12-j];
                        mancala[12-j]=0;
                        mancala[j]=0;
                        stone_captured=mancala[j]+mancala[12-j];
                }
                if(j==6){
                        added_move++;
                        turn=true;
                }

        }
        //Captures at 13
        //Min player
        else if(j>6){
                while(val>0){
                        j++;
                        j=j%14;
                        if(j==6)continue;
                        mancala[j]++;
                        val--;

                }
                if(j>6 && j!=13 && mancala[j]==1){
                        mancala[13]+=mancala[j]+mancala[12-j];
                        mancala[12-j]=0;
                        mancala[j]=0;
                        stone_captured=mancala[j]+mancala[12-j];
                }
                if(j==13){
                        added_move++;
                        turn=true;
                }
        }
        return turn;
        
    }
};

pair<int,int> alphabeta(Mancala_Board mancala,int depth,int alpha,int beta,bool MinMax) {


    if (MinMax) {
        if (depth == 0 || mancala.isEnd(1)) {
        return { mancala.husVal(husValue), -1 };
        }
        int v=INT_MIN;
        int player_move =-1;
        for (int i=0;i<6;i++) {
            if (mancala.mancala[i] == 0) continue;

            Mancala_Board a(mancala.mancala);
            bool minmax = a.player_move(i);
            pair<int,int> result = alphabeta(a,depth-1,alpha,beta,minmax);
            int new_val=result.first;
            
            if (v<new_val) {
                player_move=i;
                v=new_val;
            }
            alpha = max(alpha,v);
            if (alpha>=beta) break;
        }
        return {v,player_move };
    } 
    
    
    else {
        if (depth == 0 || mancala.isEnd(2) ) {
        return { mancala.husVal(husValue), -1 };
    }
        int v = INT_MAX;
        int player_move = -1;
        for (int i=7;i<13;i++) {
            if (mancala.mancala[i] == 0) continue;

            Mancala_Board a(mancala.mancala);
            bool minormax = a.player_move(i);
             pair<int, int> result = alphabeta(a, depth-1, alpha, beta, !minormax);
            int new_val = result.first;
            
            if (v>new_val) {
                player_move = i;
                v=new_val;
            }
            beta = min(beta,v);
            if (alpha >= beta) break;
        }
        return { v, player_move };
    }
}

int main() {
    vector<int> initial_board = {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0};
    Mancala_Board m(initial_board);
    m.print_mancala(m.mancala);
    int depth=5; 
    int alpha=INT_MIN;
    int beta=INT_MAX;
    int p;
    bool isMaximizingPlayer = true;
    pair<int,int> result; 

    cout<<"Choose a heuristic value for Computer:";
    cin>>husValue;
    cout<<endl;

    while(true){

    while(true){
        if(m.isEnd(1))break;
        cout<<"Your turn : ";
        cin>>p;
        cout<<endl;
        if(p>5 || m.mancala[p]==0){
                cout<<"You can not give this move. Try again."<<endl;
                continue;
        }
        bool t=m.player_move(p);
        m.print_mancala(m.mancala);
        if(!t){
                break;
        }
        else{
            cout<<"You have got an extra turn!!"<<endl;
        }


    }
    while(true){
        if(m.isEnd(2))break;
        result = alphabeta(m, depth, alpha, beta,!isMaximizingPlayer);
        bool t=m.player_move(result.second);
        cout<<"Computer's turn : "<<result.second<<endl;
        m.print_mancala(m.mancala);
        if(!t){
                break;
        }
        else{
            cout<<"Computer has got an extra turn!!"<<endl;
        }
    }
    if(m.isEnd(1) || m.isEnd(2)){
    if(m.mancala[6]>m.mancala[13]){
        cout<<"You win!"<<endl;
 
    }
       else if(m.mancala[6]<m.mancala[13]){
        cout<<"You loose!"<<endl;
 
    }
        else{
        cout<<"Draw!!"<<endl;
    }
        cout<<" Your Score : "<<m.mancala[6]<<endl;
        cout<<"Computer's Score : "<<m.mancala[13]<<endl;
        break;
        }
 else{
        continue;
        }

      }
      return 0;
}
