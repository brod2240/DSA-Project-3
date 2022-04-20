#include <vector>
#include <string>

using namespace std;

class MaxHeap { // Implementation of a max heap.
    private:
        int currSize = 0;
        pair<string,double> arr[20];
    public:
        // Checks if heap is empty.
        bool empty()
        {
            return (currSize == 0);
        }

        // Returns size of heap.
        int size()
        {
            return currSize;
        }

        // swaps two elements.
        void swap(int element1,int element2)
        {
            pair<string,double> temp = arr[element1];
            arr[element1] = arr[element2];
            arr[element2] = temp;
        }

        // Push a new artist into heap.
         void push(pair<string,int> artist)
        {
            if(currSize == 20)
                return;
            currSize++;
            int index = currSize - 1;
            arr[index] = artist;
            int parent = (index - 1) / 2;
            // Heapify up to correct spot in the array.
            while(index != 0 && arr[parent].second < arr[index].second)
            {
                swap(index,parent);
                index = (index - 1) / 2;
                parent = (index - 1) / 2;
            }
        }

        // Recursive Heapify down function used when artist is deleted off heap.
        void heapifyDown(int index)
        {
            int smallest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            if(leftChild < currSize && arr[leftChild].second > arr[smallest].second)
                smallest = leftChild;
            if(rightChild < currSize && arr[rightChild].second > arr[smallest].second)
                smallest = rightChild;
            if(smallest != index)
            {
                swap(index,smallest);
                heapifyDown(smallest);
            }
        }

        // Delete artist from top of heap, replace with last element in heap, and call heapify down.
        void pop()
        {
            if(!empty())
            {
                arr[0] = arr[currSize-1];
                currSize--;
                heapifyDown(0);
            }
        }

        // returns top element of heap.
        pair<string,double> top()
        {
            if(!empty())
                return arr[0];
            return make_pair("",0);
        }
};