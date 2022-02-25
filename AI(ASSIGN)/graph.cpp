#include <bits/stdc++.h>
using namespace std;
class Graph
{
   int nvertices, nedges;
   vector<vector<int>> adjList;

public:
   void initialise(int n, int e)
   {
      nvertices = n;
      nedges = e;
      adjList.resize(n + 1);
      for (int i = 0; i < e; i++)
      {
         int x, y;
         cin >> x >> y;
         adjList[x].push_back(y);
         adjList[y].push_back(x);
      }
   }
   int number_of_vertices()
   {
      return nvertices;
   }
   void printPath(vector<int> path)
   {
      cout << "Path:";
      int i;
      for (i = 0; i < path.size(); i++)
         cout << path[i] << " ";
      cout << "\n";
   }
   void printOrder(vector<int> order)
   {
      cout << "Order--\n";
      int i;
      for (i = 0; i < order.size() - 1; i++)
         cout << order[i] << " ";
      cout << order[i] << "\n";
   }
   // depth first search to find all the paths from a given node to a target node in the graph
   void dfs(int node, int targetNode, vector<bool> &visited, vector<int> &path, vector<vector<int>> &all_paths)
   {
      visited[node] = true;
      path.push_back(node);

      if (node == targetNode)
      {
         all_paths.push_back(path);
      }
      for (int curr_node : adjList[node])
      {
         if (visited[curr_node] == false)
         {
            dfs(curr_node, targetNode, visited, path, all_paths);
         }
      }

      path.pop_back();
      visited[node] = false;
   }
   void dls(int node, int targetNode, vector<bool> &visited, vector<int> &path, vector<vector<int>> &all_paths, int depthLimit)
   {
      if (depthLimit <= 0)
         return;
      visited[node] = true;
      path.push_back(node);

      if (node == targetNode)
      {
         all_paths.push_back(path);
      }
      for (int curr_node : adjList[node])
      {
         if (visited[curr_node] == false)
         {
            dls(curr_node, targetNode, visited, path, all_paths, depthLimit - 1);
         }
      }
            
      path.pop_back();
      visited[node] = false;

   }
      

   bool pathNotVisited(int node, vector<int> &path)
   {
      int size = path.size();
      for (int i = 0; i < size; i++)
      {
         if (path[i] == node)
            return false;
      }
      return true;
   }
   void bfs(int source, int targetNode)
   {

      queue<vector<int>> q;
      set<vector<int>> paths;
      vector<int> path;
      path.push_back(source);
      q.push(path);

      while (!q.empty())
      {
         path = q.front();
         q.pop();

         int last_node = path[path.size() - 1];
         if (last_node == targetNode)
         {
            //  printPath(path);
            paths.insert(path);
         }

         for (int node : adjList[last_node])
         {
            if (pathNotVisited(node, path))
            {
               vector<int> newPath(path);
               newPath.push_back(node);
               q.push(newPath);
            }
         }
      }
      int count = 0;
      for (auto x : paths)
      {
         cout << "Path " << ++count << ":";
         for (int node : x)
         {
            cout << node << " ";
         }
         cout << "\n";
      }
   }
};

class Operations
{
public:
   void depth_first_search(Graph &g, int source, int targetNode)
   {
      vector<vector<int>> all_paths;
      vector<int> path;
      vector<bool> visited(g.number_of_vertices() + 1, false);
      // call the dfs to search for all the possible paths from source to targetNode
      g.dfs(source, targetNode, visited, path, all_paths);

      // printing all the paths
      int count = 0;
      for (auto path : all_paths)
      {
         cout << "PATH " << ++count << ":";
         for (int node : path)
            cout << node << " ";
         cout << "\n";
      }
      cout << "\n";
   }

   void breadth_first_search(Graph &g, int source, int targetNode)
   {
      g.bfs(source, targetNode);
   }

   void depth_limited_search(Graph &g, int source, int targetNode, int depthLimit)
   {
      vector<vector<int>> all_paths;
      vector<int> path;
      vector<bool> visited(g.number_of_vertices() + 1, false);
      g.dls(source, targetNode, visited, path, all_paths, depthLimit);

      for (auto path : all_paths)
      {
         for (int node : path)
            cout << node << " ";
         cout << "\n";
      }
      cout << "\n";
   }

   void iterative_deepening_search(Graph &g, int source, int targetNode, int number_of_iterations)
   {

      vector<vector<int>> all_paths;
      vector<int> path;
      vector<bool> visited(g.number_of_vertices() + 1, false);
      for (int i = 1; i <= number_of_iterations; i++)
      {
         visited.clear();
         all_paths.clear();
         path.clear();

         g.dls(source, targetNode, visited, path, all_paths, i);

         for (auto path : all_paths)
         {
            cout << "Limit Required :" << i << "\n";
            for (int node : path)
               cout << node << " ";
            cout << "\n";
         }
         if (all_paths.size())
            break;
      }

      cout << "\n";
   }

   void iterative_breadth_first_search(Graph &g, int source, int targetNode)
   {

      vector<bool> visited(g.number_of_vertices() + 1, false);
      if (source == targetNode)
         return;
      vector<int> path, parent(g.number_of_vertices() + 1, -1);
      g.bfs(source, targetNode);

      int currnode = targetNode;
      while (currnode != -1 && currnode != source)
      {
         path.push_back(currnode);
         currnode = parent[currnode];
      }
      path.push_back(source);
      reverse(path.begin(), path.end());
      for (int node : path)
         cout << node << " ";
   }
};

int main()
{

   cout << "--------------------GRAPH SEARCH ALGORITHMS------------- \n";
   Graph g;
   Operations op;
   int nvertices, nedges, src, targetNode, depthLimit;

   cout << "Enter the number of vertices :";
   cin >> nvertices;
   cout << "Enter the number of edges:";
   cin >> nedges;

   g.initialise(nvertices, nedges);
   cout << "Src:";
   cin >> src;
   cout << "Target: ";
   cin >> targetNode;

   // now the graph initialization has been done , we now need to choose the algorithm
   //  or the search strategy which needs to be followed to peform the operations

   cout << "User have the following options:\n";
   cout << "1.Depth First Search\n";   // working fine
   cout << "2.Breadth First Search\n"; // working fine
   cout << "3.Depth limited search\n";
   cout << "4.Iterative Deepening Search\n";
   cout << "5.Iterative Breadth First Search\n";
   cout << "6.Exit\n";

   while (1)
   {
      cout << "Enter your choice:";
      int choice;
      cin >> choice;
      if (choice == 6)
         break;
      switch (choice)
      {
      case 1:
         op.depth_first_search(g, src, targetNode);
         break;
      case 2:
         op.breadth_first_search(g, src, targetNode);
         break;
      case 3:
         cout << "Enter the depth limit :";
         cin >> depthLimit;
         op.depth_limited_search(g, src, targetNode, depthLimit);
         break;
      case 4:
         int number_of_iterations;
         cin >> number_of_iterations;
         op.iterative_deepening_search(g, src, targetNode, number_of_iterations);
         break;
      case 5:
         op.iterative_breadth_first_search(g, src, targetNode);
         break;
      default:
         cout << "Please enter a valid choice  \n";
      }
   }

   return 0;
}
