# DSA-Project-3
This is the code and documentation for Team 65's Final DSA Project using Spotify's API

Proposal
Problem and Motivation
Music is an ever-present thing in our lives. Songs can be tied to people's personal identities, and particular moments in life. One of the most popular streaming services to listen to music is Spotify. Whether you can afford the premium service or not, you are given the opportunity to listen to music that is most impactful to you with a plethora of genres at your disposal to explore. However, while this application has many perks, it lacks a good song recommendation algorithm.
Even though songs are impactful, they can get tiring to listen to over time. People are then in search of new ones that can ignite their emotions once again just as the old ones did. But finding a new song means looking at the artists, finding what genre they sing, then actively searching for other artists in that genre, then listening to songs to decide whether it is worthy enough to be added to a playlist. Completing this process takes a lot of time and effort, and that can be avoided if Spotify uses their data to create an algorithm that recommends songs to listeners based on the songs and artists in their playlists.
Features Implemented
The main feature implemented in this program is a search, where the user can search for an artist and the program will generate a list of related artists that the user may like. The search can be split into different categories:
Search for Artist: When this option is selected, you will be able to search the name of an artist you frequently listen to and the program will produce a list of other artists that fit into the same genre as the one searched for.
Least Niche: Choosing this option will return the top ten most popular artists that relate to the artist you input.
Most Niche: This option works vice versa to the least niche where it will return a list of the least popular artists that relate to the one you inputted.
Description of Data
The team traversed through Spotify’s API to collect the information of 100,000 artists stored in their program. Information such as their name, their URIs (a series of numbers and letters that act as identification), their popularity rank, the genres their music falls into, albums they’ve produced, their top tracks, and their related artists were taken and stored into a set. After obtaining that information, for each of the artists, the team used the commonalities in genre and rank in popularity to determine and store up to 20 artists who have a relation to that artist. Using the popularity rank, genre, and related artists we managed to create an adjacency list that links the artists with each of their related artists with the weight between each connection based on the sum of the number of genres they have in common and the average of their popularities.

API/Algorithms/Languages/Tools/Libraries
Languages
 Python
C++
Tools/IDE
 Pycharm
Visual Studio Code
Clion
Libraries
 CSV, Spotipy,  Queue, Fstream, Sstream, Limits,  Map,  Set,  Vector, String, Iostream, Iomanip
API
  Spotify API (Spotipy)
Algorithms Implemented
Collecting the data involved traversal, specifically a breadth first search traversal, implemented using a stack and a queue.
There were two general steps in this project: Gathering data through an API using python and then using that data to create our program using C++. There were three main processes in collecting the data:
1.      Traversal to collect the artists
2.      Creating a function to calculate weight
3.      Determine the related artists to each artist
4. 	Exporting to a CSV for the C++ 
Distribution of Responsibility and Roles
Brianna created the breadth first traversal used to collect the name of the artists in the API. Maya looked through the information of each artist to gather commonalities in genre and rank in popularity and calculate the weight of each edge. Dany implemented functions within the Spotify API to gather up to 20 artists that fall into the same relation as the artist we stored. Due to the large amount of data required for this project, the team split up using the functions above to gather the data. For the C++, ideas on what data structures would best be suited to complete this project (working on this sentence) involved collaboration between all members of the group. Then once that was decided, the implementation was split between the team, while the main cpp file was coded by the group as a whole.



Analysis
Changes and Rationale
There were some changes made after the proposal but, fundamentally, the project still achieved the same goal. Originally, we had planned to display the information we collected more visually, i.e. in a diagram representing the graph data structure we created storing the artists. This way, the user would be able to see it all on a grander scale; however, due to time constraints and underestimating how difficult it would be to learn a new language and adapt our code to it, doing this in a different language was just not feasible. 
As a result, we decided to take the idea of the user selecting an artist to know more about their related artists and apply that to text-based visualization. This way, when the user types in the name of the artist when prompted, they will be able to choose whether they want to see the popular related artist or the more underground related artists, and the program will display the top 20 artists with respect to the user decision. Even though text-based visualization was not intended, it still achieves the same goal which was to deliver related artists in a more readable fashion.
Other changes we made were narrowing down the options to search (like geography and genre) down to strictly by popularity. In the future, we may be able to implement the others but, due to time constraints, it would be another layer to add to the already complex organization we had. As well, in order to incorporate genre, we added it to the weight of the edges so searching for related artists by genre is built in. 
Lastly, in order for the player to play music, the Python library (Spotipy)  requires the user to be able to share the connected devices with us or for the program to be implemented on a website. Being able to do this seems like a task we are not able to perform due to the security risks associated with getting the user’s Spotify information and being able to play from their devices.


Time Complexity

Python

bfs(name)
O(A) where A is 441. 441 is derived by creating an exponential equation to determine the number of related artists each artist could possibly have before the commonalities in genre stray away. That number was divided by the total number of datapoints each member had to collect which was then divided by the number of genres each member would collect data for. For each genre, the bfs would run with a time complexity of  O(A).

get_artist(name)
O(1) as this function involves taking from a dictionary in Python. Getting values from a dictionary requires O(1) time.

print_artist()
O(1)
Calls the function len() which in worst-case is O(1) for the four containers and was used for debugging purposes

makeDictionary()
O(N (S + R)) where N is the names in artistName set, S is item in the spotify dictionary and R is the number of related artists given an artist uri
The outer for loop will iterate N amount of times for the number of items in the set. Withing the for loop, would be a time complexity of O(S + R). Using .get() or a [] on a dictionary in Python is O(S), in worst case, where S is the number of items in the dictionary. As well, we are iterating through an array of related artists which would be a time complexity of O(R)

makePairs()
O(K * V) where k is the number of keys and V is the number of values belonging to the key
The function has a nested for loop where the outer for loop loops through the keys in a sorted dictionary which would be O(K). The inner for loop loops through the values that belong to the key in the dictionary which would be O(V)

createTupleForCSV()
O(N * G) where N is the number of tuples in the pairArtistRelated list and G is the number of genres the artist has
The outer for loop iterates through the list of tuples which would be O(N). Within the for loop, there is a for loop that iterates through the genres G times, i.e. the number of genre the artist has hence it would be O(G)

createCSV()
O(N) where N is the number of tuples in the finalCSVPair that the csv writer has to write to a file. As for the CSV writer function in Python, that is O(1) which is disregarded as O(N) is the more dominant time complexity.

main()
The complexity involves combining the complexities of all the functions called in main:
            O(A + N(S + R) + K*V + N*G + N), where any constant complexity is disregarded.
            
C++


void insert(string from, string to, double weight)
O(logV * E + logV)
The first part has uses .find() which has a O(logV) worst case time complexity where V is the number of vertices. If the vertex is found, it goes through a for loop through its edges which would be O(E) time complexity where E is the number of edges. The next part is using [] with a map which is O(V) time complexity
bool BFS(MinHeap &heap,set<string> &s,int constraint,string name)
O(Vlogv + E) In the worst case of having to traverse the entire adjacency list the worst case time complexity will be O(V + E), but because find() function is called twice on each node that passes the constraint test and is pushed into the heap which performs heapify up,, this will become O(V(3logV) + E) -> O(VlogV + E).
bool BFS(MaxHeap &heap,set<string> &s,int constraint,string name)
O(Vlogv + E) In the worst case of having to traverse the entire adjacency list the worst case time complexity will be O(V + E), but because find() function of nicheSet and s is called twice on each node that passes the constraint test and is pushed into the heap which performs heapify up,, this will become O(V(3logV) + E) -> O(VlogV + E).
  
void search()
O(V) Where V is the total number of vertices in the graph. The first part calls the find() function of the map STL, which will take in the worst case O(V). Afterwards a traversal through the found vertex’s adjacent nodes is done which will always be equal to or less than O(V).
  
void mostNiche()
O(logV
  
void mostPop()


void print(string type, string name,vector<pair<string,double>> artistList)
O(p) where p is the length or number of artists in the vector artistList.
  
bool empty()


int size()


void swap(int element1, int element2)
O(1) 
Swaps elements in constant time complexity
  
void push(pair<string,int> artist)
O(logn) where n is the number of elements in the heap
Inserts the artists in the heap and then performs heapifyUp to put the artist in the correct space in the heap which takes O(logn) 
  
void heapifyDown(int index)
O(logn) where n is the number of elements in the heap
When performing pop() calls heapify down to maintain heap property, requires going down the height of the heao which would be O(logn)
  
void pop()
O(logn) where n is the number of elements in the heap
Calls heapifyDown() which has mentioned above is O(logn) complexity
  
pair<string,double> top()
O(1)
Returns the top element of the heap which calls the array using [] which is O(1)
void swap(vector<pair<string,double>> &vec,int index1,int index2)
O(1), as you are getting a value from a vector where the indices are known.
  
int partition(vector<pair<string,double>> &vec,int low,int high)
O(h) where h is the difference between the parameters (high-1) and low. You go through a for loop with a condition of j being the value of low, not being able to exceed (high - 1) iterations.
  
void QuickSort(vector<pair<string,double>> &vec,int low,int high)
O(s^2 + h) where h is the time complexity of the partition function called in this function and s is the number of elements smaller than the pivot. Because s is guaranteed to be larger than h, this can be reduced to O(s^2)
int main()


void printMenu()
O(1), all you are doing is using cout to print out the menu in constant time.
bool BFS(vector<pair<string,double>> &vec,set<string> &s,int constraint,string name)
O(Vlogv + E) In the worst case of having to traverse the entire adjacency list the worst case time complexity will be O(V + E), but because find() function is called twice on each node that passes the constraint test, this will become O(V(2logV) + E) -> O(VlogV + E).


 
