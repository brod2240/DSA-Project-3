#include <vector>
#include <string>
using namespace std;

class MinHeap {
    private:
    int currSize;
    pair<int,string> arr[20];
    public:
    MinHeap()
    {
        /*currSize = size;
        int start;
        if(adjArtists.size() < 20)
            start = (adjArtists.size() / 2) - 1;
        else
            start = 9;

        for(int i = 0;i < adjArtists.size();i++)
            arr[i] = adjArtists[i];
        for(int i = start;i >= 0;i--)
            heapifyDown(i);*/
    }
    void swap(int element1,int element2)
    {
        pair<int,string> temp = arr[element1];
        arr[element1] = arr[element2];
        arr[element2] = temp;
    }
     void push(pair<int,string> artist)
    {
        if(currSize == 20)
            return;
        currSize++;
        int index = currSize - 1;
        arr[index] = artist;
        int parent = (index - 1) / 2;
        while(index != 0 && arr[parent].first > arr[index].first)
        {
            swap(index,parent);
            index = (index - 1) / 2;
            parent = (index - 1) / 2;
        }
    }
    void heapifyDown(int index)
    {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if(leftChild < currSize && arr[leftChild].first < arr[smallest].first)
            smallest = leftChild;
        if(rightChild < currSize && arr[rightChild].first < arr[smallest].first)
            smallest = rightChild;
        if(smallest != index)
        {
            swap(index,smallest);
            heapifyDown(smallest);
        }
    }
    void pop()
    {
        arr[0] = arr[currSize-1];
        currSize--;
        heapifyDown(0);
    }
    pair<int,string> top()
    {
        return arr[0];
    }  
};