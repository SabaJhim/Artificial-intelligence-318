#include <bits/stdc++.h>

using namespace std;

int hamming_distance(vector<vector<string>> grid)
{
        int count = 0;
        int k=grid.size();

        for (int i = 0; i < k; i++)
        {
                for (int j = 0; j < k; j++)
                {
                        if (grid[i][j] == "*")
                                continue;
                        else
                        {
                                if (stoi(grid[i][j]) != i * k + j + 1)
                                        count++;
                        }
                }
        }
        return count;
}

int manhattan_distance(vector<vector<string>> grid)
{
        int count = 0;
        int k=grid.size();

        for (int i = 0; i < k; i++)
        {
                for (int j = 0; j < k; j++)
                {
                        if (grid[i][j] == "*")
                                continue;
                        int x1 = i, y1 = j;
                        int x2 = (stoi(grid[i][j]) - 1) / k, y2 = (stoi(grid[i][j]) - 1) % k;
                        count += abs(x1 - x2) + abs(y1 - y2);
                }
        }
        return count;
}





class Search_Node
{
        public:
        vector<vector<string>> current_grid;
        int moves;
        vector<vector<string>> previous_grid;

        Search_Node(vector<vector<string>> g, int m , vector<vector<string>> p)
        {
                current_grid = g;
                moves = m;
                previous_grid = p;
        }


};

class p_queue{

        //We will push Searc_Nodes according to the cost function.
        //First element will have the minimum cost.
        public :
        vector<Search_Node> list;

        void insert(Search_Node node){
                list.push_back(node);
                arrange();
        }

        void del(Search_Node node){
                for(int i=0; i<list.size(); i++){
                        if(list[i].current_grid==node.current_grid) {
                                list.erase(list.begin()+i);
        
                        }
                }
        }

      

        void arrange(){
                int i=list.size()-2;
                int j=list.size()-1;

                while(i>=0){
                        if(cost_find(list[i])>cost_find(list[j])){
                                swap(list[i],list[j]);
                                i--;
                                j--;
                        }
                        else{
                                i--;
                        }
                }
        }
        int cost_find(Search_Node node){
                return manhattan_distance(node.current_grid)+node.moves ;
        }

};

class p_queue_hamming{

        //We will push Searc_Nodes according to the cost function.
        //First element will have the minimum cost.
        public :
        vector<Search_Node> list;

        void insert(Search_Node node){
                list.push_back(node);
                arrange();
        }

        void del(Search_Node node){
                for(int i=0; i<list.size(); i++){
                        if(list[i].current_grid==node.current_grid) {
                                list.erase(list.begin()+i);
        
                        }
                }
        }

      

        void arrange(){
                int i=list.size()-2;
                int j=list.size()-1;

                while(i>=0){
                        if(cost_find(list[i])>cost_find(list[j])){
                                swap(list[i],list[j]);
                                i--;
                                j--;
                        }
                        else{
                                i--;
                        }
                }
        }
        int cost_find(Search_Node node){
                return hamming_distance(node.current_grid)+node.moves ;
        }

};
 vector<Search_Node> Node_Generator(Search_Node parent)
        {
                vector<Search_Node> neighbors;
                int size = parent.current_grid.size();

                for (int i = 0; i < size; i++)
                {
                        for (int j = 0; j < size; j++)
                        {
                                if (parent.current_grid[i][j] == "*")
                                {
                                        if (i - 1 >= 0 && parent.current_grid[i - 1][j] != "*")
                                        {
                                                vector<vector<string>> new_grid = parent.current_grid;
                                                swap(new_grid[i][j], new_grid[i - 1][j]);
                                                if(new_grid!=parent.previous_grid){
                                                neighbors.push_back(Search_Node(new_grid, parent.moves + 1, parent.current_grid));
                                                }
                                        }
                                        if (i + 1 < size && parent.current_grid[i + 1][j] != "*")
                                        {
                                                vector<vector<string>> new_grid = parent.current_grid;
                                                swap(new_grid[i][j], new_grid[i + 1][j]);
                                                if(new_grid!=parent.previous_grid){
                                                neighbors.push_back(Search_Node(new_grid, parent.moves + 1, parent.current_grid));
                                                }
                                        }
                                        if (j + 1 < size && parent.current_grid[i][j + 1] != "*")
                                        {
                                                vector<vector<string>> new_grid = parent.current_grid;
                                                swap(new_grid[i][j], new_grid[i][j + 1]);
                                                if(new_grid!=parent.previous_grid){
                                                neighbors.push_back(Search_Node(new_grid, parent.moves + 1, parent.current_grid));
                                                }
                                        }
                                        if (j - 1 >= 0 && parent.current_grid[i][j - 1] != "*")
                                        {
                                                vector<vector<string>> new_grid = parent.current_grid;
                                                swap(new_grid[i][j], new_grid[i][j - 1]);
                                                if(new_grid!=parent.previous_grid){
                                                neighbors.push_back(Search_Node(new_grid, parent.moves + 1, parent.current_grid));
                                                }
                                        }
                                }
                        }
                }

                return neighbors;
        }

void print_Nodes(Search_Node s_node){
        vector<vector<string>> node = s_node.current_grid;
        for(int i=0;i<node.size();i++){
                for(int j=0;j<node[i].size();j++){
                        cout<<node[i][j]<<" ";
                }
                cout<<endl;
        }
        cout<<endl;

}

//Solvability check 
vector<string> flatten_grid(vector<vector<string>>grid){
        vector<string> flat_grid;
        for(auto& row : grid){
                for(auto& cell : row){
                        if(cell=="*")continue;
                        flat_grid.push_back(cell);
                }
        }
        return flat_grid;
}

int inversion_count(vector<string> flat_grid){
        int inversions = 0;
               for (int i = 0; i < flat_grid.size() - 1; i++) {
                for (int j=i+1; j<flat_grid.size(); j++) {
                        if (stoi(flat_grid[i]) > stoi(flat_grid[j])) {
                                inversions++;
                        }
                }
        }
        return inversions;

}

int star_position(vector<vector<string>> grid){
        for (int i=0; i<grid.size(); i++) {
                for(int j=0;j<grid.size();j++){
                        if(grid[i][j]=="*"){
                                return grid.size()-i;
                        }
                }
        }
        
}

bool is_solvable(vector<vector<string>>grid){
        vector<string> flat_grid = flatten_grid(grid);
        int inversions = inversion_count(flat_grid);
        int k=grid.size();
        int star_pos=star_position(grid);
 
        if(k%2==1){
                return inversions%2==0;
        }
        else{
                if(star_pos%2==0 && inversions%2==1){
                        return true;
                }
                else if(star_pos%2==1 && inversions%2==0){
                        return true;
                }
                else{
                        return false;
                }
        }
}



void get_solve_manhattan(int k,vector<vector<string>> grid,vector<vector<string>>initial,vector<vector<string>> final){
        vector<Search_Node> result;  //closed list
        p_queue pq;  //open list
        int explored=0;
        int expanded=0;

        pq.insert(Search_Node(grid,0,initial));
        explored++;

        while(!pq.list.empty()){
                Search_Node current_node = pq.list.front();
                pq.del(current_node);
                expanded++;

                if(current_node.current_grid==final){
                        result.push_back(current_node);
                        break;
                }

                result.push_back(current_node);
                vector<Search_Node> neighbors = Node_Generator(current_node);

                for(auto& neighbor : neighbors){
                        pq.insert(neighbor);
                        explored++;
                        
                }

        }
        for(int i=result.size()-1; i>0; i--){
                if(result[i].previous_grid!=result[i-1].current_grid){
                        result.erase(result.begin()+i-1);
                }
        }
        cout<<endl<<"Result : Manhattan"<<endl;
        for(auto& node :result){
                print_Nodes(node);
        }
         cout<<"Total Cost (Manhattan) : "<<result.size()-1<<endl;
         cout<<"Total Nodes Explored(Manhattan) : "<<explored<<endl;
         cout<<"Total Nodes Expanded(Manhattan) : "<<expanded<<endl;
}

void get_solve_hamming(int k,vector<vector<string>> grid,vector<vector<string>>initial,vector<vector<string>> final){
        vector<Search_Node> result;  //closed list
        p_queue_hamming pq;  //open list
        int explored=0;
        int expanded=0;

        pq.insert(Search_Node(grid,0,initial));
        explored++;

        while(!pq.list.empty()){
                Search_Node current_node = pq.list.front();
                pq.del(current_node);
                expanded++;

                if(current_node.current_grid==final){
                        result.push_back(current_node);
                        break;
                }

                result.push_back(current_node);
                vector<Search_Node> neighbors = Node_Generator(current_node);

                for(auto& neighbor : neighbors){
                        pq.insert(neighbor);
                        explored++;
                        
                }

        }
        for(int i=result.size()-1; i>0; i--){
                if(result[i].previous_grid!=result[i-1].current_grid){
                        result.erase(result.begin()+i-1);
                }
        }
        cout<<endl<<"Result : Hamming"<<endl;
        for(auto& node :result){
                print_Nodes(node);
        }
        cout<<"Total Cost (Hamming) : "<<result.size()-1<<endl;
        cout<<"Total Nodes Explored(Hamming) : "<<explored<<endl;
        cout<<"Total Nodes Expanded(Hamming) : "<<expanded<<endl;
 
}




int main(){
        int k;
        cout << "Enter the grid size: ";
        cin >> k;
        vector<vector<string>> grid(k, vector<string>(k));
        vector<vector<string>> initial(k, vector<string>(k));
        vector<vector<string>> final(k, vector<string>(k));
        cout << "Enter the grid elements: ";

        for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {

                        cin >> grid[i][j];
                        initial[i][j] = "0";
                        int num=i*k+j+1;
                        final[i][j] =to_string(num);

                }
        }
        final[k-1][k-1]="*";
        bool ans=is_solvable(grid);

        if(ans){
                cout<<"The grid is solvable."<<endl;
                get_solve_manhattan(k,grid,initial,final);
                get_solve_hamming(k,grid,initial,final);

        }
        else{
                cout<<"The grid is not solvable."<<endl;
        }

        return 0;
}