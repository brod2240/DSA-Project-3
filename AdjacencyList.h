#include <map>
#include <set>
#include <vector>
#include <string>
#include "MinHeap.h"
#include "MaxHeap.h"
#include <iostream>
#include <iomanip> 
#include <queue>
#include <chrono>

//creating an adjacency list using heaps
using namespace std;

// Adjacency list, represented by a map with a string as key and vector of pairs to represent the adjacent nodes.
class AdjacencyList {
 private: 
      map<string,vector<pair<string,double>>> graph;
      set<string> nicheSet;
      set<string> popSet;
 public:
    //given from and to artist and weight, inserts into adjacency list
    void insert(string from,string to,double weight)
    {
        // The code below checks for parallel edges and ignores them.
        if(graph.find(from) != graph.end())
        {
            for(pair<string,int> artist : graph[from])
            {
                if(artist.first.compare(to) == 0)
                   return;
            }
        }
        if(graph.find(to) != graph.end())
        {
            for(pair<string,int> artist : graph[to])
            {
                if(artist.first.compare(from) == 0)
                    return;
            }
        }
        graph[from].push_back(make_pair(to,weight)); // Insert each node into the undirected graph.
        graph[to].push_back(make_pair(from,weight));
     }

     // BFS used to find most niche related artists.
    bool BFS(MinHeap &heap,set<string> &s,int constraint,string name)
    {

        queue<string> q;
        q.push(name);
        s.insert(name);
        while(!q.empty()) // Use queue to traverse through graph.
        {
            string artistName = q.front();
            q.pop();
            for(pair<string,double> artist : graph[artistName])
            {
                if(artist.second < constraint)
                {
                    // Use two sets to avoid duplicates in the list, use a min heap to keep the most niche at the top
                    if(s.find(artist.first) == s.end() && popSet.find(artist.first) == popSet.end())
                    {
                        s.insert(artist.first);
                        nicheSet.insert(artist.first);
                        heap.push(artist);
                        q.push(artist.first);
                    }
                }
            }

            if(nicheSet.size() == 1000)
                nicheSet.clear();
            if(s.size() == 20)
                return true;
        }
        return false;
    }

    // BFS used to find most popular related artists.
    bool BFS(MaxHeap &heap,set<string> &s,int constraint,string name)
    {

        queue<string> q;
        q.push(name);
        s.insert(name);
        while(!q.empty())// Use queue to traverse through graph.
        {
            string artistName = q.front();
            q.pop();
            for(pair<string,double> artist : graph[artistName])
            {
                if(artist.second > constraint)
                {
                    // Use two sets to avoid duplicates in the list, use max heap to keep the most popular at the top
                    if(s.find(artist.first) == s.end() && nicheSet.find(artist.first) == nicheSet.end())
                    {
                        s.insert(artist.first);
                        popSet.insert(artist.first);
                        heap.push(artist);
                        q.push(artist.first);
                    }
                }
            }

            if(popSet.size() == 1000)
                popSet.clear();
            if(s.size() == 20)
                return true;
        }
        return false;
    }

    // Finds direct related artists regardless of popularity or niche level.
    void search()
     {
        string name;
        cout << "ENTER ARTIST NAME:" << endl;
        cin.get();
        getline(cin,name);
        if(graph.find(name) != graph.end())
        {
            vector<pair<string,double>> vec;
            for(pair<string,double> artist : graph[name])
                // Store adjacent nodes (related artists) in a vector and prints.
                vec.push_back(make_pair(artist.first,artist.second));
            print("REG",name,vec);
        }
        else
            cout << "THIS ARTIST CANNOT BE FOUND" << endl;
     }

     // Uses a BFS traversal and heap sort to find the most niche related artists.
     void mostNiche()
     {

        string name;
        cout << "ENTER ARTIST NAME:" << endl;
         auto start = chrono::steady_clock::now();
        cin.get();
         // First check if artist is in graph. If the artist is found, it will be passed through a BFS traversal.
        getline(cin,name);
        if(graph.find(name) != graph.end())
        {
            MinHeap pq;
            set<string> s;
            int constraint = 50;
            vector<pair<string,double>> vec;
            bool flag = BFS(pq,s,constraint,name);
            // In the case that the constraint is too high to find 20 artists we decrement by 10 and repeat the BFS.
            while(!flag && constraint > 0)
            {
                constraint -= 10;
                flag = BFS(pq,s,constraint,name);
            }
            while(!pq.empty()) // Empty heap into vector.
            {
                vec.push_back(pq.top());
                pq.pop();
            }
            print("NICHE",name,vec);
        }
        else
            cout << "This artist cannot be found" << endl;
         auto end = chrono::steady_clock::now();
         cout << "Elapsed time in seconds: "
              << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
              << " nanoseconds" <<endl;
     }

     // Uses a BFS traversal and heap sort to find the most popular related artists.
     void mostPop()
     {
        string name;
        cout << "ENTER ARTIST NAME:" << endl;
         auto start = chrono::steady_clock::now();
        cin.get();
        getline(cin,name);
         // First check artist is in graph. If the artist is found, it will be passed through a BFS traversal
        if(graph.find(name) != graph.end())
        {
            MaxHeap pq;
            set<string> s;
            int constraint = 50;
            vector<pair<string,double>> vec;
            BFS(pq,s,constraint,name);
            while(!pq.empty()) // Empty heap into vector.
            {
                pair<string,double> artist = pq.top();
                vec.push_back(artist);
                pq.pop();
            }
            print("POPULAR",name,vec);
        }
        else
            cout << "This artist cannot be found" << endl;
         auto end = chrono::steady_clock::now();
         cout << "Elapsed time in seconds: "
              << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
              << " nanoseconds" <<endl;
     }

     // Print function used to print artists and weights on a table.
     void print(string type, string name,vector<pair<string,double>> artistList)
     {

        if(type == "REG")
            cout << endl << right << setw(25) << "RELATED ARTISTS FOR " + name << endl;
        else
        {
             cout  << endl << "TOP 20 MOST " << type << " RELATED ARTIST FOR " << name << endl << endl;
            cout << left << setw(20) << "ARTIST NAME " << "|";
            cout << right << setw(23) << (type + " level") << endl;
        }

        cout << "--------------------------------------------" << endl;
       for(pair<string,double> artist : artistList)
       {
            cout << left << setw(20) << artist.first << "|";
            cout << right << setw(23) << artist.second << endl;
       }
     }
};  