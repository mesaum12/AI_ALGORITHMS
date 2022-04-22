#include <bits/stdc++.h>
#include "8puzzle.h"

using namespace std;
vector<vector<int>> orderListCurrent;
vector<int> order;
class Graph
{
   int nvertices, nedges;
   vector<vector<int>> adjList;

public:
   vector<vector<pair<int, int>>> adjList2;
   void initialise(int n, int e, bool weighted = false)
   {

      nvertices = n;
      nedges = e;

      if (weighted)
      {
         adjList2.resize(n + 1);
         adjList.resize(n + 1);
         for (int i = 0; i < e; i++)
         {
            cout << "Enter the edges in the form <a b w>\n";
            int x, y, w;
            cin >> x >> y >> w;
            // assuming the graph is undirected
            adjList2[x].push_back({y, w});
            adjList2[y].push_back({x, w});
            adjList[x].push_back(y);
            adjList[y].push_back(x);
         }
      }
      else
      {
         adjList.resize(n + 1);
         for (int i = 0; i < e; i++)
         {
            cout << "Enter the edges in the from <a b>\n";
            int x, y;
            cin >> x >> y;
            // assuming the graph is undirected
            adjList[x].push_back(y);
            adjList[y].push_back(x);
         }
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
      cout << "Order:\n";
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
      order.push_back(node);
      if (node == targetNode)
      {
         orderListCurrent.push_back(order);
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
   map<int, int> mp;
   void dfs(int node, int targetNode, vector<bool> &visited, vector<int> &path, vector<vector<int>> &all_paths, int i)
   {
      visited[node] = true;
      path.push_back(node);
      order.push_back(node);
      if (node == targetNode)
      {
         orderListCurrent.push_back(order);
         all_paths.push_back(path);
      }
      for (int curr_node : adjList[node])
      {
         if (mp[node] < i && visited[curr_node] == false)
         {
            mp[node]++;
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
      order.push_back(node);
      if (node == targetNode)
      {
         printOrder(order);
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
      order.push_back(source);
      q.push(path);

      while (!q.empty())
      {
         path = q.front();
         q.pop();

         int last_node = path[path.size() - 1];
         if (last_node == targetNode)
         {
            //  printPath(path);
            printOrder(order);
            paths.insert(path);
         }

         for (int node : adjList[last_node])
         {
            if (pathNotVisited(node, path))
            {
               vector<int> newPath(path);
               newPath.push_back(node);
               order.push_back(node);
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
   int bfs(int source, int targetNode, int branch_factor)
   {
      queue<vector<int>> q;
      set<vector<int>> paths;
      vector<int> path;
      path.push_back(source);
      order.push_back(source);
      q.push(path);

      while (!q.empty())
      {
         path = q.front();
         q.pop();

         int last_node = path[path.size() - 1];
         if (last_node == targetNode)
         {
            //  printPath(path);
            printOrder(order);
            paths.insert(path);
         }

         int counter = 0;
         if (counter < branch_factor)
         {
            for (int node : adjList[last_node])
            {
               counter++;
               if (pathNotVisited(node, path))
               {
                  order.push_back(node);
                  vector<int> newPath(path);
                  newPath.push_back(node);
                  q.push(newPath);
               }
            }
         }
      }
      int count = 0;
      if (paths.size() == 0)
         return 0;
      for (auto x : paths)
      {
         cout << "Path " << ++count << ":";
         for (int node : x)
         {
            cout << node << " ";
         }
         cout << "\n";
      }
      return 1;
   }

   void bestFirstSearch(int source, int targetNode)
   {

      vector<bool> visited(nvertices + 1, false);
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
      pq.push({0, source});
      visited[source] = true;
      cout << "Source:" << source << "\n";
      vector<int> parent(100000, -1);
      while (!pq.empty())
      {

         auto current = pq.top();
         pq.pop();

         int node = current.second;
         int weight = current.first;

         if (node == targetNode)
         {
            int current = targetNode;
            cout << "Path:";
            while (current != -1)
            {
               cout << "HI";
               cout << current << " ";
               current = parent[current];
            }
            return;
         }

         for (pair<int, int> curr : adjList2[node])
         {
            int current_weight = curr.second;
            int current_node = curr.first;
            if (!visited[current_node])
            {
               pq.push({current_weight, current_node});
               parent[current_node] = node;
               visited[current_node] = true;
            }
         }
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
      count = 0;
      for (auto order : orderListCurrent)
      {
         cout << "ORDER" << ++count << ":";
         for (int node : order)
            cout << node << " ";
         cout << "\n";
      }
      cout << "\n";
      orderListCurrent.clear();
      order.clear();
   }
   void depth_first_search(Graph &g, int source, int targetNode, int i)
   {
      vector<vector<int>> all_paths;
      vector<int> path;
      vector<bool> visited(g.number_of_vertices() + 1, false);
      // call the dfs to search for all the possible paths from source to targetNode

      g.dfs(source, targetNode, visited, path, all_paths, i);

      // printing all the paths
      int count = 0;
      for (auto path : all_paths)
      {
         cout << "PATH " << ++count << ":";
         for (int node : path)
            cout << node << " ";
         cout << "\n";
      }
      count = 0;
      for (auto order : orderListCurrent)
      {
         cout << "ORDER" << ++count << ":";
         for (int node : order)
            cout << node << " ";
         cout << "\n";
      }
      cout << "\n";
      orderListCurrent.clear();
      order.clear();
   }
   void bestFirstSearch(Graph &g, int source, int targetNode)
   {
      // we need to perform bfs but use a priority queue instead of queue to reach the target node
      g.bestFirstSearch(source, targetNode);
      orderListCurrent.clear();
      order.clear();
   }
   void breadth_first_search(Graph &g, int source, int targetNode)
   {
      g.bfs(source, targetNode);
      orderListCurrent.clear();
      order.clear();
   }

   void depth_limited_search(Graph &g, int source, int targetNode, int depthLimit)
   {
      vector<vector<int>> all_paths;
      vector<int> path;
      vector<bool> visited(g.number_of_vertices() + 1, false);
      g.dls(source, targetNode, visited, path, all_paths, depthLimit);

      int count = 0;
      for (auto path : all_paths)
      {
         cout << "PATH " << ++count << ":";
         for (int node : path)
            cout << node << " ";
         cout << "\n";
      }
      count = 0;
      for (auto order : orderListCurrent)
      {
         cout << "ORDER " << ++count << ":";
         for (int node : order)
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
         if (all_paths.size() == 0)
            continue;

         for (auto path : all_paths)
         {
            cout << "Number of iterations required:" << i << "\n";
            for (int node : path)
               cout << node << " ";
            cout << "\n";
         }
         break;
      }

      cout << "\n";
   }

   void iterative_broadening_search(Graph &g, int source, int targetNode, int branch)
   {

      depth_first_search(g, source, targetNode, branch);
   }
};
Graph InputGraphDetailsWeighted()
{
   Graph g;
   int nvertices, nedges, src, targetNode;
   // take the input of the graph details
   cout << "Enter the number of vertices in the graph:";
   cin >> nvertices;
   cout << "Enter the number of edges in the graph:";
   cin >> nedges;
   // this graph needs to be weighted for processing of the best first search

   g.initialise(nvertices, nedges, true);

   cout << "Source Node:";
   cin >> src;
   cout << "Target Node:";
   cin >> targetNode;

   return g;
}
int nvertices, nedges, src, targetNode;
Graph InputGraphDetailsUnweighted()
{
   Graph g;

   // take the input of the graph details
   cout << "----------Enter the graph------------\n";
   cout << "Enter the number of vertices in the graph:";
   cin >> nvertices;
   cout << "Enter the number of edges in the graph:";
   cin >> nedges;
   // this graph needs to be weighted for processing of the best first search

   g.initialise(nvertices, nedges);

   cout << "Source Node:";
   cin >> src;
   cout << "Target Node:";
   cin >> targetNode;

   return g;
}
void printGraph(Graph g)
{

   vector<vector<pair<int, int>>> adjList = g.adjList2;
   for (int i = 1; i < adjList.size(); i++)
   {
      cout << i << " ";
      for (auto node : adjList[i])
      {
         cout << "{" << node.first << "," << node.second << "}"
              << " ";
      }
      cout << "\n";
   }
}

int main()
{

   cout << "--------------------+++++---GRAPH SEARCH ALGORITHMS---++++------------------------- \n";
   Graph g, g2;
   Operations op;
   // int nvertices, nedges, src, targetNode, depthLimit, number_of_iterations;
   int depthLimit, number_of_iterations;
   string str;
   int newGraph = 0;
   bool flag = true;
   // now the graph initialization has been done , we now need to choose the algorithm
   //  or the search strategy which needs to be followed to peform the operations

   while (1)
   {
      cout << "\n\n";
      cout << "Choose one of the following options:\n";
      cout << "1.Depth First Search\n";
      cout << "2.Breadth First Search\n";
      cout << "3.Depth Limited Search\n";
      cout << "4.Iterative Deepening Search\n";
      cout << "5.Iterative Broadening Search\n";
      cout << "6.Best first search\n";
      cout << "7.Exit\n";
      cout << "8.Eight puzzle\n";
      cout << "Enter your choice:";

      int choice, weighted;
      cin >> choice;
      if (choice == 7)
         break;

      if (flag && choice >= 1 && choice <= 6)
      {
         flag = false;

         cout << "Is the graph weighted or unweighted ?, enter 1 for weighted , otherwise 0:";
         cin >> weighted;
         if (weighted == 1)
            g = InputGraphDetailsWeighted();

         else
            g = InputGraphDetailsUnweighted();
      }
      switch (choice)
      {
      case 1:
         cout << "Enter 1 to change the graph:";
         cin >> newGraph;
         if (newGraph)
            g = InputGraphDetailsUnweighted();
         op.depth_first_search(g, src, targetNode);
         break;

      case 2:
         cout << "Enter 1 to change the graph:";
         cin >> newGraph;
         if (newGraph)
            g = InputGraphDetailsUnweighted();
         op.breadth_first_search(g, src, targetNode);
         break;

      case 3:
         cout << "Enter 1 to change the graph:";
         cin >> newGraph;
         if (newGraph)
            g = InputGraphDetailsUnweighted();

         cout << "Enter the depth limit:";
         cin >> depthLimit;
         op.depth_limited_search(g, src, targetNode, depthLimit);

         break;

      case 4:
         cout << "Enter 1 to change the graph:";
         cin >> newGraph;
         if (newGraph)
            g = InputGraphDetailsUnweighted();

         cout << "Enter the maximum number of iterations:";
         cin >> number_of_iterations;
         op.iterative_deepening_search(g, src, targetNode, number_of_iterations);
         break;
      case 5:
         cout << "Enter 1 to change the graph:";
         cin >> newGraph;
         if (newGraph)
            g = InputGraphDetailsUnweighted();

         cout << "Enter the maximum number of iterations:";
         cin >> number_of_iterations;
         op.iterative_broadening_search(g, src, targetNode, number_of_iterations);
         break;
      case 6:
         cout << "Enter 1 to change the graph:";
         cin >> newGraph;
         // if user tries to change the graph , only provide him the option of weighted
         if (newGraph)
            g = InputGraphDetailsWeighted();

         if (!weighted)
         {
            cout << "Need weighted graph, Renter the graph with weights to perform this algorithm:\n";
            g = InputGraphDetailsWeighted();
         }

         // printGraph(g);
         op.bestFirstSearch(g, src, targetNode);
         cout << "\n";
         break;

      case 8:
         cout << "-------8 puzzle problem using A* ----- \n";
         initConfiguration();
         break;

      default:
         cout << "Please enter a valid choice !!\n";
      }
   }
   return 0;
}
