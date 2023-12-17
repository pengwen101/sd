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
    int worstDistance;

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
                        worstDistance += randomizedWeight;
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

    // set jumlah vertex dan energy sesuai level
    // energy = ratio * distance dr posisi player awal ke escape point

    vector<int> findPath(int startVertice, int endVertice)
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
                    distance[i] = distance[currVertice] + 1;
                    path[i] = path[currVertice];
                    path[i].push_back(i);
                    bfsQueue.push(i);
                }
            }
        }
        return path[endVertice];
    }

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
        return distance[endVertice];
    }

    bool isWin()
    {
        return (playerPos == escapePoint);
    }

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

        for (auto z = distance.begin(); z != distance.end(); z++)
        {
            cout << *z << " ";
        }

        cout << endl;

        this->escapePoint = maxIndex;

        this->shortestDistance = dijkstra(playerPos, escapePoint);
        this->energy = shortestDistance * 2;
        this->initialEnergy = energy;

        // set posisi enemy di sebelah escape point
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
    void movePlayer(int choice)
    {
            // update posisi player
            energy = energy - adjMatrix[playerPos][choice];
            this->playerPos = choice;
            // cout << "Energy yang tersisa : " << energy << endl;
    }

    void moveEnemy()
    {
        // posisi enemy terupdate, bergerak mendekati player
        vector<int> pathEnemy = findPath(enemyPos, playerPos);

        auto z = pathEnemy.begin();
        advance(z, 1);

        cout << "Kidnapper Path: ";

        for (; z != pathEnemy.end(); z++)
        {
            cout << *z << " ";
        }
        cout << endl;

        enemyPos = *z;
    }

    bool isDead()
    {
        if (enemyPos == playerPos)
        {
            cout << "Game over! Kidnapper menemukanmu!";
            return true;
        }
        if (energy <= 0)
        {
            cout << "Game over! Energy habis!";
            return true;
        }
        return false;
    }

    // asdjhasdhalda
    int calculateScore()
    {
        int traveledDistance = initialEnergy - energy;
        int offset = initialEnergy / 5;
        int score1 = abs(traveledDistance - shortestDistance);
        if (score1 > offset * 5)
        {
            return 1;
        }
        else if (score1 > offset * 4)
        {
            return 2;
        }
        else if (score1 > offset * 3)
        {
            return 3;
        }
        else if (score1 > offset * 2)
        {
            return 4;
        }
        else if (score1 > offset)
        {
            return 5;
        }
        return 0;
    }

    void run()
    {

        printGraph();
        set();
        int count = 1;

        do
        {
            cout << endl;
            cout << "Energi Sekarang : " << energy << endl;
            int jarakEnemy = BFS(playerPos, enemyPos);
            int jarakEscape = BFS(playerPos, escapePoint);

            cout << "You are at room #" << playerPos << " the escape point is at room " << escapePoint << " you are " << jarakEnemy << " room away from the kidnapper, and " << jarakEscape << " away from escape point, you see room " << endl;

            vector<vector<int>> adjacent = findAdjacent(playerPos);
            for (int i = 0; i < adjacent[0].size(); i++)
            {
                cout << adjacent[1][i] << ", with energy cost " << adjacent[0][i] << endl;
            }

            int choice;
            bool exist = false;
            if (count % 2 == 0)
                {
                    moveEnemy();
                }

            do
            {
                cout << endl;
                cout << "Which room you want to go to? ";
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
            count++;

            if (isDead())
            {
                exit(0);
            }

        } while (!isWin());
        cout << "Hore menang!" << endl;
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