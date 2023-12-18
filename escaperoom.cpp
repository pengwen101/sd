#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

class EscapeRoomGame
{
public:
    int jumlahVertex;
    vector<vector<int>> adjMatrix;
    int escapePoint;      // escape point
    int playerPos;        // posisi player, bakal keupdate terus
    int enemyPos;         // posisi enemy, bakal keupdate terus
    int energy;           // energynya player, bakal keupdate terus
    int shortestDistance; // jarak terpendek dari posisi player ke escape point
    int initialEnergy;

    int counter = 1;

    EscapeRoomGame()
    {
        jumlahVertex = 30;

        this->jumlahVertex = jumlahVertex;
        this->adjMatrix = vector(jumlahVertex, vector(jumlahVertex, 0));

        // buat graphnya
        for (int i = 0; i < jumlahVertex; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                if (i == j)
                {
                    adjMatrix[i][j] = 0;
                }
                else
                {
                    int p = rand() % 7;
                    if (p == 1)
                    {
                        int randomizedWeight = rand() % 10 + 1;
                        adjMatrix[i][j] = randomizedWeight;
                        adjMatrix[j][i] = randomizedWeight;
                    }
                }
            }
        }

        // set posisi player secara random
        this->playerPos = rand() % jumlahVertex;
    }

    void printGraph()
    {
        for (int i = 0; i < jumlahVertex; i++)
        {
            for (int j = 0; j < jumlahVertex; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }


    //valiant gilchrist c14220157
    int dijkstra(int startVertex, int endVertex)
    {
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

    //valiant gilchrist c14220157
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


    // mencari node yang berhubungan dengan node player/node enemy
    //laura wijaya c14220192
    vector<vector<int>> findAdjacent(int pos)
    {
        vector<vector<int>> adjacent(2);

        for (int i = 0; i < jumlahVertex; i++)
        {
            if (adjMatrix[pos][i] != 0)
            {
                adjacent[0].push_back(adjMatrix[pos][i]); // weight
                adjacent[1].push_back(i);                 // room
            }
        }
        return adjacent;
    }

    //amelia wibisono c14220160
    vector<int> findPath(int startVertice, int endVertice)
    {
        // error dicek
        if (startVertice < 0 || startVertice >= this->jumlahVertex)
        {
            cout << "Verticenya invalid";
            return vector<int>(0, 0);
        }

        // tampungan data
        vector<bool> visited(this->jumlahVertex, false);
        queue<int> bfsQueue;
        vector<vector<int>> path(jumlahVertex);
        path[startVertice] = {startVertice};
        // untuk startig point
        visited[startVertice] = true;
        bfsQueue.push(startVertice);

        while (!bfsQueue.empty())
        {

            int currVertice = bfsQueue.front();

            bfsQueue.pop();

            for (int i = 0; i < this->jumlahVertex; i++)
            {
                if (this->adjMatrix[currVertice][i] > 0 && !visited[i])
                {
                    visited[i] = true;
                    path[i] = path[currVertice];
                    path[i].push_back(i);
                    bfsQueue.push(i);
                }
            }
        }
        return path[endVertice];
    }

    //amelia wibisono c14220160
    vector<int> BFS(int startVertice)
    {
        // error dicek
        if (startVertice < 0 || startVertice >= this->jumlahVertex)
        {
            cout << "Verticenya invalid";
            return vector<int>(0, 0);
        }

        // tampungan data
        // visited, queue
        vector<bool> visited(this->jumlahVertex, false);
        vector<int> distance(jumlahVertex, 0);
        queue<int> bfsQueue;

        // untuk startig point
        visited[startVertice] = true;
        bfsQueue.push(startVertice);

        while (!bfsQueue.empty())
        {
            int currVertice = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < this->jumlahVertex; i++)
            {
                if (this->adjMatrix[currVertice][i] > 0 && !visited[i])
                {
                    visited[i] = true;
                    distance[i] = distance[currVertice] + 1;
                    bfsQueue.push(i);
                }
            }
        }
        return distance;
    }


    //amelia wibisono c14220160
    int BFS(int startVertice, int endVertice)
    {
        // error dicek
        if (startVertice < 0 || startVertice >= this->jumlahVertex)
        {
            cout << "Verticenya invalid";
            return -1;
        }

        // tampungan data
        // visited, queue
        vector<bool> visited(this->jumlahVertex, false);
        vector<int> distance(jumlahVertex, 0);
        queue<int> bfsQueue;

        // untuk starting point
        visited[startVertice] = true;
        bfsQueue.push(startVertice);

        while (!bfsQueue.empty())
        {
            int currVertice = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < this->jumlahVertex; i++)
            {
                if (this->adjMatrix[currVertice][i] > 0 && !visited[i])
                {
                    visited[i] = true;
                    distance[i] = distance[currVertice] + 1;
                    bfsQueue.push(i);
                }
            }
        }
        return distance[endVertice];
    }

    bool isWin()
    {
        return (playerPos == escapePoint);
    }

    //laura wijaya c14220192
    void set()
    {
        // set posisi escape point terjauh dari posisi player
        vector<int> distance = BFS(playerPos);

        int maxDistance = 0;
        int maxIndex = 0;

        for (int i = 0; i < jumlahVertex; i++)
        {
            if (distance[i] > maxDistance)
            {
                maxDistance = distance[i];
                maxIndex = i;
            }
        }

        this->escapePoint = maxIndex;
        this->shortestDistance = dijkstra(playerPos, escapePoint);
        this->energy = shortestDistance * 2;
        this->initialEnergy = energy;

        // set posisi enemy terjauh kedua dari posisi player
        int maxDistances = 0;
        int maxIndeks = 0;
        for (int i = 0; i < jumlahVertex; i++)
        {
            if (distance[i] > maxDistances && i != escapePoint)
            {
                maxDistances = distance[i];
                maxIndeks = i;
            }
        }
        this->enemyPos = maxIndeks;
    }

    // apa yg bakal terjadi setiap kali player pergi ke posisi lain?
    //tania c14220181
    void movePlayer(int choice)
    {
            // update posisi player
            energy = energy - adjMatrix[playerPos][choice];
            this->playerPos = choice;
    }

    //tania c14220181
    void moveEnemy()
    {
        // posisi enemy terupdate, bergerak mendekati player
        vector<int> pathEnemy = findPath(enemyPos, playerPos);

        auto z = pathEnemy.begin();

        if(counter%2==0){
            cout << "\nTHE KIDNAPPER IS MOVING TOWARDS YOU!\n";
            enemyPos = *z;
        }

        cout << "PATH FROM THE KIDNAPPER TO YOU: ";

        for (; z != pathEnemy.end(); z++)
        {
            cout << *z << " ";
        }
        cout << endl<<endl;

    }

    bool isDead()
    {
        if (enemyPos == playerPos)
        {
            cout << "GAME OVER! YOU'VE BEEN CAUGHT BY THE KIDNAPPER!";
            return true;
        }
        if (energy <= 0)
        {
            cout << "GAME OVER! YOUR RAN OUT OF ENERGY TO CONTINUE THE ESCAPE!";
            return true;
        }
        return false;
    }

    //
    int calculateScore()
    {
        //energy = sisa energi yang dimiliki oleh player
        //nilai terbaik didapatkan saat initial energy - travelled distance = shortest distance
        // initial energy - travelled distance = energy
        //maka, skor terbaik didapat ketika energy = shortest distance,
        //namun di game ini sulit mendapatkan skor tsb sehingga 0.2*shortest distance cukup utk mendapat nilai terbaik

        if (energy > 0.2*shortestDistance){
            return 5;
        }

        if (energy > 0.15*shortestDistance){
            return 4;
        }

        if (energy > 0.1*shortestDistance){
            return 3;
        }

        if (energy > 0.05*shortestDistance){
            return 2;
        }

        if (energy > 0.0*shortestDistance){
            return 1;
        }
        
        return 0;
    }

    void run()
    {
        set();

        do
        {
            cout << endl;
            cout << "-----------------------------------------------------"<<endl;
           
            cout << "ENERGY LEFT : " << energy << endl <<endl;
        
            cout << "YOU ARE AT ROOM #" << playerPos << " THE ESCAPE POINT IS AT ROOM #" << escapePoint << " THE KIDNAPPER IS AT ROOM #" << enemyPos <<endl;

            int jarakEnemy = BFS(playerPos, enemyPos);
            int jarakEscape = BFS(playerPos, escapePoint);

            cout << "\nYOU ARE " << jarakEnemy << " ROOM AWAY FROM THE KIDNAPPER, AND " << jarakEscape << " ROOM AWAY FROM ESCAPE POINT\n";
            int choice;
            bool exist = false;

            moveEnemy();

            cout << "YOU SEE ROOM " << endl;
            vector<vector<int>> adjacent = findAdjacent(playerPos);
            for (int i = 0; i < adjacent[0].size(); i++)
            {
                cout << adjacent[1][i] << ", WITH ENERGY COST " << adjacent[0][i] << endl;
            }

            do
            {
                cout << endl;
                cout << "WHICH ROOM YOU WANT TO GO TO? ";
                cin >> choice;
                
                for (int i = 0; i < adjacent[0].size(); i++)
                {
                    if (adjacent[1][i] == choice)
                    {
                        exist = true;
                        break;
                    }
                }
            } while (!exist);


            movePlayer(choice);
            counter++;
        

            if (isDead())
            {
                exit(0);
            }

        } while (!isWin());
        cout << "YOU ESCAPED! CONGRATULATIONS YOU GET TO LIVE!\nYOUR SCORE: " << endl;
        for (int i = 0; i < calculateScore(); i++)
        {
            cout << "* ";
        }
        
    }
};

int main()
{
    cout << "You have been abducted and placed in a basement with many rooms, you need to walk a certain distance before reaching to the next room and it takes a certain amount of your energy. Find your way out before you run out of energy!" << endl
         << endl;

    EscapeRoomGame e;

    e.run();

    return 0;
}