#include <map>
#include <vector>
#include <string>
#include "MinHeap.h"
#include "MaxHeap.h"
#include <iostream>
#include <iomanip> 
using namespace std;

class AdjacencyList { 

 private: 
  map<string,vector<pair<string,double>>> graph; // Graph represented as an adjacency list.
 public: 
 void insert(string from,string to,int weight)
 {
    graph[from].push_back(make_pair(to,weight));
    if(graph.find(to) == graph.end())
        graph[to] = {};
 }
 
void search(string name)
 {  
    if(graph.find(name) != graph.end())
    {
        vector<pair<int,string>> vec;
        for(pair<string,int> artist : graph[name]) // OR USE SORT()
            vec.push_back(make_pair(artist.second,artist.first));
        print("NICHE",name,vec);
    }
    else
        cout << "This artist cannot be found" << endl;
 }
 void mostNiche(string name)
 {
    if(graph.find(name) != graph.end())
    {
        MinHeap pq;
        vector<pair<int,string>> vec;
        for(pair<string,int> artist : graph[name]) // OR USE SORT()
            pq.push(make_pair(artist.second,artist.first));
        for(int i = 0; i < 10; i++)
        {
            vec.push_back(pq.top());
            pq.pop();
        }
        print("NICHE",name,vec);
    }
    else
        cout << "This artist cannot be found" << endl;
 }
 void mostPop(string name)
 {  
    if(graph.find(name) != graph.end())
    {
        MaxHeap pq;
        vector<pair<int,string>> vec;
        for(pair<string,int> artist : graph[name]) // OR USE SORT()
            pq.push(make_pair(artist.second,artist.first));
        for(int i = 0; i < 10; i++)
        {
            vec.push_back(pq.top());
            pq.pop();
        }
        print("POPULAR",name,vec);
    }
    else
        cout << "This artist cannot be found" << endl;
 }
 void print(string type, string name,vector<pair<int,string>> artistList) 
 {
   
    if(type == "REG")
        cout << right << setw(25) << "RELATED ARTISTS FOR" << name << endl;
    else
        cout << right << setw(25) << "TOP 10 MOST " << type << endl;
    cout << left << setw(20) << "ARTISTS FOR " << name << "|";
    cout << right << setw(23) << (type + "level") << endl;
    cout << "--------------------------------------------" << endl;
   for(pair<int,string> artist : artistList)
   {             
        cout << left << setw(20) << artist.second << "|";
        cout << right << setw(23) << artist.first << endl;
   }
 }
 void printTest(string type) 
 {
    string word = (type == "POPULAR") ? "Popularity":"Niche";
    word += " level";
    cout << right << setw(35) << "TOP 10 MOST " << type << endl;
    cout << left << setw(20) << "|from" << "|";
    cout << left << setw(23) << "to" << "|";
    cout << left << setw(23) << word << "|" << endl;
    cout << "---------------------------------------------------------------------" << endl;
   for(map<string,vector<pair<string,double>>>::iterator it = graph.begin();it != graph.end();it++)
   {        
        for(vector<pair<string,double>>::iterator it2 = it->second.begin();it2 != it->second.end();it2++) 
            {
                cout << left << setw(20) << it->first << "|";
                cout << left << setw(23) << it2->first << "|";
                cout << left << setw(23) << it2->second << "|" << endl;
            }
   }
 }
};  