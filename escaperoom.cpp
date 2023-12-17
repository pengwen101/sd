#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

class EscapeRoomGame{
    public:

    int jumlahVertex;
    vector<vector<int>> adjMatrix;
    int escapePoint; //escape point
    int playerPos; //posisi player, bakal keupdate terus
    int enemyPos; //posisi enemy, bakal keupdate terus
    int energy; //energynya player, bakal keupdate terus
    int shortestDistance; //jarak terpendek dari posisi player ke escape point

    bool isDead;

    EscapeRoomGame(int level){
        isDead = false;
        if(level ==1){
                jumlahVertex = 5;
            }else if(level ==2){
                jumlahVertex = 7;
            }else if(level ==3){
                jumlahVertex = 10;
            }

        this -> jumlahVertex = jumlahVertex;
        this -> adjMatrix = vector(jumlahVertex, vector(jumlahVertex, 0));

        //buat graphnya
        for(int i = 0; i<jumlahVertex; i++){
            for(int j = 0; j<= i; j++){
                if(i == j){
                    adjMatrix[i][j] = 0;
                }else{
                    int p = rand() % 2;
                    if(p == 1){
                        int randomizedWeight = rand()%10 + 1;
                        adjMatrix[i][j] = randomizedWeight;
                        adjMatrix[j][i] = randomizedWeight;
                    }
                }
            }
        }

        //set posisi player secara random
        this -> playerPos = rand()%jumlahVertex;

        cout << "Ini player pos = " << playerPos << endl;
    }


    void printGraph(){
        for(int i = 0; i<jumlahVertex; i++){
            for(int j = 0; j<jumlahVertex; j++){
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    int dijkstra(int startVertex, int endVertex){

        vector<int> distance(this->jumlahVertex, INT_MAX);
        vector<bool> visited(this->jumlahVertex, false);

        distance[startVertex] = 0;

        for (int count = 0; count < this->jumlahVertex - 1; count++)
        {
            int u = minDistance(distance, visited);

            visited[u] = true;

            for (int v = 0; v < this->jumlahVertex; v++)
            {
                if (!visited[v] && this->adjMatrix[u][v] && distance[u] != INT_MAX &&
                    distance[u] + this->adjMatrix[u][v] < distance[v])
                {
                    distance[v] = distance[u] + this->adjMatrix[u][v];
                }
            }
        }
        return distance[endVertex];
    }

    int minDistance(const vector<int> &distance, const vector<bool> &visited)
    {
        int minDistance = INT_MAX, minIndex;

        for (int v = 0; v < this->jumlahVertex; v++)
        {
            if (!visited[v] && distance[v] <= minDistance)
            {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    //mencari node yang berhubungan dengan node player/node enemy
    vector<vector<int>> findAdjacent(int pos){
        vector<vector<int>> adjacent(2);

        for(int i = 0; i< jumlahVertex; i++){
            if(adjMatrix[pos][i] != 0){
                adjacent[0].push_back(adjMatrix[pos][i]); // weight
                adjacent[1].push_back(i); //room
            }
        }
        return adjacent;
    }


    //set jumlah vertex dan energy sesuai level
    //energy = ratio * distance dr posisi player awal ke escape point

vector<int> findPath(int startVertice, int endVertice) {
        // error dicek
        if (startVertice < 0 || startVertice>=this->jumlahVertex) {
            cout << "Verticenya invalid";
            return vector<int>(0,0);
        }

        // tampungan data
        // visited, queue
        vector<bool> visited(this->jumlahVertex, false);
        vector<int> distance(jumlahVertex, INT_MAX);
        queue<int> bfsQueue;
        vector<vector<int>> path;
        // untuk startig point
        visited[startVertice] = true;
        bfsQueue.push(startVertice);

        while (!bfsQueue.empty()) {

            int currVertice = bfsQueue.front();
            
            bfsQueue.pop();

            for (int i = 0; i < this->jumlahVertex; i++) {
                if(this->adjMatrix[currVertice][i] > 0 && !visited[i]) {
                   visited[i] = true;
                   distance[i] = distance[currVertice]+1;
                   path[i] = path[currVertice];
                   path[i].push_back(i);
                   bfsQueue.push(i);
                }
            }
        }
        return path[endVertice];
    }

    vector<int> BFS(int startVertice) {
        // error dicek
        if (startVertice < 0 || startVertice>=this->jumlahVertex) {
            cout << "Verticenya invalid";
            return vector<int>(0,0);
        }

        // tampungan data
        // visited, queue
        vector<bool> visited(this->jumlahVertex, false);
        vector<int> distance(jumlahVertex, INT_MAX);
        queue<int> bfsQueue;

        // untuk startig point
        visited[startVertice] = true;
        bfsQueue.push(startVertice);

        while (!bfsQueue.empty()) {

            int currVertice = bfsQueue.front();
            
            bfsQueue.pop();

            for (int i = 0; i < this->jumlahVertex; i++) {
                if(this->adjMatrix[currVertice][i] > 0 && !visited[i]) {
                   visited[i] = true;
                   distance[i] = distance[currVertice]+1;
                   bfsQueue.push(i);
                }
            }
        }
        return distance;
    }

    int BFS(int startVertice, int endVertice) {
        // error dicek
        if (startVertice < 0 || startVertice>=this->jumlahVertex) {
            cout << "Verticenya invalid";
            return -1;
        }

        // tampungan data
        // visited, queue
        vector<bool> visited(this->jumlahVertex, false);
        vector<int> distance(jumlahVertex, INT_MAX);
        queue<int> bfsQueue;

        // untuk startig point
        visited[startVertice] = true;
        bfsQueue.push(startVertice);

        while (!bfsQueue.empty()) {
            int currVertice = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < this->jumlahVertex; i++) {
                if(this->adjMatrix[currVertice][i] > 0 && !visited[i]) {
                   visited[i] = true;
                   distance[i] = distance[currVertice]+1;
                   bfsQueue.push(i);
                }
            }
        }
        return distance[endVertice];
    }

    bool isWin(){
        return (playerPos == escapePoint);
    }

    void set(){
        //set posisi escape point terjauh dari posisi player
        vector<int> distance = BFS(playerPos);

        int maxDistance = 0;
        int maxIndex = 0;

        for(int i = 0; i < jumlahVertex; i++){
            if(distance[i] > maxDistance){
                maxDistance = distance[i];
                maxIndex = i;
            }
        }

        this -> escapePoint = maxIndex;

        cout << "Escape point = " << escapePoint << endl;
        this -> shortestDistance = dijkstra(playerPos, escapePoint);

        //set posisi enemy di sebelah escape point
        for(int i = 0; i<jumlahVertex; i++){
           if(adjMatrix[escapePoint][i]!= 0){
            enemyPos = i;
            break;
           }
        }
    }

        //apa yg bakal terjadi setiap kali player pergi ke posisi lain?
    void move(int choice){
        //cek apakah energy player cukup, semisal energy player kurang dari semua jalur yg dapat dikunjungi, game end
        if(energy >= adjMatrix[playerPos][choice]){
            //update posisi player
            this -> playerPos = choice;
        }

        //posisi enemy terupdate, bergerak mendekati player
        vector<int> pathEnemy = findPath(playerPos, enemyPos);
    
        auto z = pathEnemy.end();
        advance(z, -1);

        for(auto z = pathEnemy.begin(); z != pathEnemy.end(); z++){
            cout << *z << " ";
        }
        cout << endl;

        enemyPos = *z;

        if(enemyPos == playerPos){
            cout << "Game over! Kidnapper menemukanmu!";
            isDead = true;
        }
    }

    void run(){

        printGraph();
        set();

        do{
        
        int jarakEnemy = BFS(playerPos, enemyPos);
        int jarakEscape = BFS(playerPos, escapePoint);

        cout <<"You wake up in room #" << playerPos << " the escape point is at room " << escapePoint << " you are " << jarakEnemy << " room away from the kidnapper, you see room " << endl;

        vector<vector<int>> adjacent = findAdjacent(playerPos);
        for(int i = 0; i< adjacent[0].size(); i++){
            cout << adjacent[1][i] << ", with energy cost " << adjacent[0][i] << endl;
        }

        int choice;
        bool exist = false;

        do{
            cout << "Which room you want to go to? ";
            cin>>choice;
            for(int i = 0; i< adjacent[0].size(); i++){
                if(adjacent[1][i] == choice){
                    exist = true;
                    break;
                }
            }
        }while(!exist);

        move(choice);

        if(isDead){
            
        }

        }
        while(!isWin());
        
        
    }
};

int main(){

    cout << "You have been abducted and placed in a basement with many rooms, you need to walk a certain distance before reaching to the next room and it takes a certain amount of your energy. Find your way out before you run out of energy!" << endl << endl;

    int level;
    do{
        cout << "Select your level: \n1. Easy\n2. Medium\n3. Hard\nChoose a level (1/2/3): ";
        cin >> level;
    }while (level != 1 && level != 2 && level != 3);
        
    EscapeRoomGame e(level);

    e.run();

    return 0;
}