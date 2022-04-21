#include <map>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include "descendQuickSort.h"
#include "ascendQuickSort.h"
#include <iostream>
#include <iomanip> 
#include <queue>

//creating adjacency list using quick sort
using namespace std;

// Adjacency list, represented by a map with a string as key and vector of pairs to represent the adjacent nodes.
class AdjacencyListAlt {
 private: 
      map<string,vector<pair<string,double>>> graph;
      set<string> popSet;
      set<string> nicheSet;
 public: 
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
         // Insert each node into the undirected graph.
        graph[from].push_back(make_pair(to,weight));
        graph[to].push_back(make_pair(from,weight));
     }

     // BFS used to find most niche related artists.
    bool BFS(vector<pair<string,double>> &vec,set<string> &s,int constraint,string name)
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
                    // Use two sets to avoid duplicates in the list, use a max heap to keep the most popular at the top
                    if(s.find(artist.first) == s.end() && popSet.find(artist.first) == popSet.end())
                    {
                        s.insert(artist.first);
                        nicheSet.insert(artist.first);
                        q.push(artist.first);
                        if(vec.size() < 20)
                            vec.push_back(artist);
                    }
                }
            }

            if(nicheSet.size() == 1000)
                nicheSet.clear();
            if(s.size() >= 20)
                return true;
            
        }
        return false;
    }
    // BFS used to find most popular related artists.
    bool BFS(vector<pair<string,double>> &vec,set<string> &s,int constraint,string name,bool pop)
    {
        queue<string> q;
        q.push(name);
        s.insert(name);
        while(!q.empty())  // Use queue to traverse through graph.
        {
            string artistName = q.front();
            q.pop();
            for(pair<string,double> artist : graph[artistName]) // OR USE SORT()
            {
                if(artist.second > constraint)
                {
                    // Use two sets to avoid duplicates in the list, use a max heap to keep the most popular at the top.
                    if(s.find(artist.first) == s.end() && nicheSet.find(artist.first) == nicheSet.end())
                    {
                        s.insert(artist.first);
                        popSet.insert(artist.first);
                        q.push(artist.first);
                        if(vec.size() < 20)
                            vec.push_back(artist);
                    }
                }
            }

            if(popSet.size() == 1000)
                popSet.clear();
            if(s.size() >= 20)
                return true;
            
        }
        return false;
    }

    void search() // Finds direct related artists regardless of popularity or niche level.
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

     void mostNiche()
     {
        string name;
        cout << "ENTER ARTIST NAME:" << endl;
         auto start = chrono::steady_clock::now();
        cin.get();
        getline(cin,name);
         // First checks if artist is in graph. If the artist is found, it will be passed through a BFS traversal.
        if(graph.find(name) != graph.end())
        {
            set<string> s;
            int constraint = 50;
            vector<pair<string,double>> vec;
            bool flag = false;
            // In the case that the constraint is too high to find 20 artists we decrement by 10 and repeat the BFS.
            while(!flag && constraint > 0)
            {
                flag = BFS(vec,s,constraint,name);
                constraint -= 10;
            }
            // Send our vector through quicksort to sort out artist in ascending level of weight.
            ascendQuickSort(vec,0,vec.size()-1);
            print("NICHE",name,vec);
        }
        else
            cout << "This artist cannot be found" << endl;
         auto end = chrono::steady_clock::now();
         cout << "Elapsed time in seconds: "
              << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
              << " nanoseconds" <<endl;
     }

     void mostPop()
     {
        string name;
        cout << "ENTER ARTIST NAME:" << endl;
         auto start = chrono::steady_clock::now();
        cin.get();
        getline(cin,name);
         // First checks if artist is in graph. If the artist is found, it will be passed through a BFS traversal.
        if(graph.find(name) != graph.end())
        {
            vector<pair<string,double>> vec;
            set<string> s;
            int constraint = 50;
            BFS(vec,s,constraint,name,true);
            // Send vector through quicksort to sort out artist in ascending level of weight.
            descendQuickSort(vec,0,vec.size()-1);
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