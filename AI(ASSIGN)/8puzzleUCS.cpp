// Program to print path from root node to destination node
// for N puzzle algorithm (using BFS )
#include <bits/stdc++.h>
using namespace std;
#define N 3
int final[N][N];
set<Node *> visited;
// state space tree nodes
struct Node
{
    // storing the parent configuration
    Node *parent;
    // stores matrix
    int mat[N][N];
    // stores blank tile coordinates
    int x, y;

    // stores the number of moves so far
    int level;
};
// Function to print N x N matrix
int printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << "\n";
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

    // set number of moves so far
    node->level = level;

    // update new blank tile coordinates
    node->x = newX;
    node->y = newY;

    return node;
}

// Function to check if (x, y) is a valid matrix coordinate
int isSafe(int x, int y)
{

    return (x >= 0 && x < N && y >= 0 && y < N);
}
// print path from root node to destination node
void printPath(Node *root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);

    printf("\n");
}

bool isGoalNode(int mat[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            if (mat[i][j] != final[i][j])
                return false;
    }
    return true;
}
// solve function to solve the problem
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{

    queue<Node *> pq;
    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    pq.push(root);
    visited.insert(root);

    while (!pq.empty())
    {

        Node *currentState = pq.front();
        pq.pop();
        // if currentState is an answer node
        if (isGoalNode(currentState->mat))
        {
            // print the path from root to destination;
            printPath(currentState);
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            Node *child = newNode(currentState->mat, currentState->x,
                                  currentState->y, currentState->x + row[i],
                                  currentState->y + col[i],
                                  currentState->level + 1, currentState);
            if (visited.find(child) == visited.end() && isSafe(currentState->x + row[i], currentState->y + col[i]))
            {
                visited.insert(child);
                pq.push(child);
            }
        }
    }
}
// Driver code
int main()
{
    int initial[N][N];
    int x, y;
    cout << "Enter the initial configuration of the 3 puzzle \n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> initial[i][j];
            if (initial[i][j] == 0)
                x = i, y = j; // store the blank space
        }
    }

    cout << "Enter the final configuration \n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> final[i][j];
        }
    }
    solve(initial, x, y, final);
    return 0;
}
