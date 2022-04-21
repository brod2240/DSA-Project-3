#include <vector>
#include <string>

using namespace std;

class MinHeap { // Implementation of a min heap.
    private:
        int currSize = 0;
        pair<string,double> arr[20]; // Max size of heap is 20.
    public:
        bool empty() // Checks if heap is empty.
        {
            return (currSize == 0);
        }
        int size() // Returns size of heap.
        {
            return currSize;
        }
        void swap(int element1,int element2) // swaps two elements.
        {
            pair<string,double> temp = arr[element1];
            arr[element1] = arr[element2];
            arr[element2] = temp;
        }
         void push(pair<string,double> artist) // Push a new artist into heap.
        {
            if(currSize == 20)
                return;
            currSize++;
            int index = currSize - 1;
            arr[index] = artist;
            int parent = (index - 1) / 2;
            while(index != 0 && arr[parent].second > arr[index].second) // Heapify up to correct spot in the array.
            {
                swap(index,parent);
                index = (index - 1) / 2;
                parent = (index - 1) / 2;
            }
        }
        void heapifyDown(int index) // Recursive Heapify down function used when artist is deleted off heap.
        {
            int smallest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            if(leftChild < currSize && arr[leftChild].second < arr[smallest].second)
                smallest = leftChild;
            if(rightChild < currSize && arr[rightChild].second < arr[smallest].second)
                smallest = rightChild;
            if(smallest != index)
            {
                swap(index,smallest);
                heapifyDown(smallest);
            }
        }
        void pop() // Delete artist from top of heap, replace with last element in heap, and call heapify down.
        {
            if(!empty())
            {
                arr[0] = arr[currSize-1];
                currSize--;
                heapifyDown(0);
            }

        }
        pair<string,double> top() // returns top element of heap.
        {
            if(!empty())
                return arr[0];
            return make_pair("",0);
        }
};