// solving the 8 puzzle problems using uninformed search strategy
// used breadth first search technique
#include <bits/stdc++.h>
using namespace std;
#define N 3
set<vector<vector<int>>> visitedSet;
// state space tree nodes
struct Node
{
    // storing the parent configuration
    Node *parent;
    // stores matrix
    int mat[N][N];
    // stores blank tile coordinates
    int x, y;

    int level;
};

bool isGoalNode(int curr[N][N], int final[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (curr[i][j] != final[i][j])
                return false;
        }
    }
    return true;
}
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

void solve(int initial[N][N], int x, int y,
           int final[N][N])
{

    // create a root node and calculate its cost
    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    vector<vector<int>> current(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            current[i][j] = root->mat[i][j];

    queue<Node *> pq;
    pq.push(root);
    visitedSet.insert(current);

    while (!pq.empty())
    {
        // find a successor of the current node
        Node *min = pq.front();
        pq.pop();
        // if goal node is found
        if (isGoalNode(min->mat, final))
        {
            // print the path from root to destination;
            printPath(min);
            return;
        }

        // do for each child of min
        // max 4 children for a node

        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                // create a child node and calculate
                // its cost

                Node *child = newNode(min->mat, min->x,
                                      min->y, min->x + row[i],
                                      min->y + col[i],
                                      min->level + 1, min);

                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++)
                        current[i][j] = child->mat[i][j];

                // if the visited node is found , then simply continue
                if (visitedSet.find(current) != visitedSet.end())
                    continue;
                pq.push(child);
                visitedSet.insert(current);
            }
        }
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
        }
    }
    cout << "\n";

    solve(initial, x, y, final);
    cout << "The miminum number of moves for the algorithm is :" << steps << "\n";
    return 0;
}
