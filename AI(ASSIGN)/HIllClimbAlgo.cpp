// Program to print path from root node to destination node
// for N*N -1 puzzle algorithm using A start search algorithm
// The solution assumes that instance of puzzle is solvable
#include <bits/stdc++.h>
using namespace std;
#define N 3
map<int, pair<int, int>> mp1, mp2;
// state space tree nodes
struct Node
{
    // storing the parent configuration
    Node *parent;
    // stores matrix
    int mat[N][N];
    // stores blank tile coordinates
    int x, y;
    // stores the number of misplaced tiles
    int cost;
    // stores the number of moves so far
    int level;
};

// Function to print the configuration of a state
int printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << "\n";
    }
}

// bottom, left, top, right
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Function to allocate a new node
Node *newNode(int mat[N][N], int x, int y, int newX,
              int newY, int level, Node *parent)
{
    Node *node = new Node;

    // set pointer for path to root
    node->parent = parent;

    // copy data from parent node to current node
    memcpy(node->mat, mat, sizeof node->mat);

    // move tile by 1 position
    swap(node->mat[x][y], node->mat[newX][newY]);

    // set number of misplaced tiles
    node->cost = INT_MAX;

    // set number of moves so far
    node->level = level;

    // update new blank tile coordinates
    node->x = newX;
    node->y = newY;

    return node;
}

// Function to calculate the number of misplaced tiles i.e manhattan distance
// ie. number of non-blank tiles not in their goal position
int calculateCost(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            mp2[initial[i][j]] = {i, j};
        }

    for (auto itr : mp1)
    {
        // mp1 stores the x,y coordinate of final configuration
        int x1 = itr.second.first;
        int y1 = itr.second.second;
        auto itr2 = mp2.find(itr.first);
        int x2 = itr2->second.first;
        int y2 = itr2->second.second;

        if (itr2->first)
            count += abs(x2 - x1) + abs(y2 - y1);
    }
    return count;
}

// Function to check if (x, y) is a valid matrix coordinate
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// print path from root node to destination node
int steps = 0;
void printPath(Node *root)
{
    if (root == NULL)
        return;
    steps++;
    printPath(root->parent);
    printMatrix(root->mat);

    printf("\n");
}

// Function to solve N*N - 1 puzzle algorithm using
// x and y are blank tile coordinates
// in initial state
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{
    // Create a  queue to store live nodes of
    // search tree;
    cout << "Hello\n";


    // create a root node and calculate its cost
    Node *current = newNode(initial, x, y, x, y, 0, NULL);
    int limit=20;
    
    cout << "Hello2\n";
    while (limit--)
    {
       

        // if current is an answer node
        if (current->cost == 0)
        {
            printPath(current);
            return;
        }
        Node *curr_neighbour = NULL;
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(current->x + row[i], current->y + col[i]))
            {
                
                Node *child = newNode(current->mat, current->x,
                                      current->y, current->x + row[i],
                                      current->y + col[i],
                                      current->level + 1, current);
                child->cost = calculateCost(child->mat, final);
                if (curr_neighbour == NULL)
                    curr_neighbour = child;
                else if (calculateCost(child->mat, final) > calculateCost(curr_neighbour->mat, final))
                    curr_neighbour = child;
                // Add child to list of live nodes
            }
        }
            

    

        pq.push(curr_neighbour);
    }
}

// Driver code
int main()
{

    int initial[N][N];
    int x, y;

    cout << "Enter the initial configuration \n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> initial[i][j];
            if (initial[i][j] == 0)
                x = i, y = j;
        }
    }
    int final[N][N];
    cout << "Enter the final configuration \n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> final[i][j];
            mp1[final[i][j]] = {i, j};
        }
    }
    cout << "\n";

    solve(initial, x, y, final);
    cout << "The micurrentum number of moves for the algorithm is :" << steps << "\n";
    return 0;
}
