// Program to print path from root node to destination node
// for N*N -1 puzzle algorithm using A start search algorithm
// The solution assumes that instance of puzzle is solvable
#include <bits/stdc++.h>
using namespace std;
#define N 3
set<vector<vector<int>>> visitedSet;
int final[N][N];
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

// heuristics used for this hill climb algorithm is
int calculateCost(int initial[N][N], int final[N][N])
{

    map<int, pair<int, int>> map2;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {

            map2[final[i][j]] = {i, j};
        }

    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
            {
                int element = initial[i][j];
                auto index = map2.find(element);
                count = count + abs(i - index->second.first) + abs(j - index->second.second);
            }
    // cout << "Manhattan distance :" << (-1) * count << "\n";
    return (-1) * count;
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

// f(n) = h(n) + g(n)
struct heuristicComp
{
    bool operator()(const Node *lhs, const Node *rhs) const
    {
        return (lhs->cost) < (rhs->cost);
    }
};

// Function to solve N*N - 1 puzzle algorithm using
//. x and y are blank tile coordinates
// in initial state
void print(int mat[N][N])
{

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
    cout << "\n";
}
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{

    // create a root node and calculate its cost
    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    Node *currentState = root;

    vector<vector<int>> current(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            current[i][j] = root->mat[i][j];
        }
    }
    visitedSet.insert(current);

    int iterations = 100;
    while (iterations--)
    {
        // cout << "Hello\n";
        if (isGoalNode(currentState->mat))
        {
            // print the path from root to destination;
            printPath(currentState);
            return;
        }
        Node *neighbour = NULL;
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(currentState->x + row[i], currentState->y + col[i]))
            {
                // extract all the child one by one
                Node *child = newNode(currentState->mat, currentState->x,
                                      currentState->y, currentState->x + row[i],
                                      currentState->y + col[i],
                                      currentState->level + 1, currentState);
                // print(child->mat);
                //  check if the current configuration is already visited;
                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++)
                        current[i][j] = child->mat[i][j];

                if (visitedSet.find(current) != visitedSet.end())
                    continue;
                if (neighbour == NULL)
                    neighbour = child;
                else if (calculateCost(child->mat, final) > calculateCost(neighbour->mat, final))
                    neighbour = child;
            }
        }
        if (neighbour == NULL)
            break;
        // now the neighbour will contain the child configuration which is most favourable
        // so make it visited and update currentState

        if (calculateCost(currentState->mat, final) > calculateCost(neighbour->mat, final))
        {
            cout << "No such optimal neighbour is found \n";
            break;
        }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                current[i][j] = neighbour->mat[i][j];

        visitedSet.insert(current);
        currentState = neighbour;

        // int cost = calculateCost(neighbour->mat, final);
        // cout << "Cost taken :" << cost << "\n";
    }
}

// Driver code
int main()
{

    int initial[N][N];
    int x, y;

    // Initial configuration of the puzzle
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
