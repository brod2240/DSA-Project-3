#include <vector>
#include <string>

using namespace std;

void swapD(vector<pair<string,double>> &vec,int index1,int index2) // swap two elements of vector.
{
    pair<string,double> temp = vec[index1];
    vec[index1] = vec[index2];
    vec[index2] = temp;
}
int partitionD(vector<pair<string,double>> &vec,int low,int high) // Partition function swaps elements until j > high, then swap i+1 and high before returning i+1 (the partition index).
{
    int pivot = vec[high].second; 
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) // Find a smaller element with j, if the element is found swap with i,
    {   
        if (vec[j].second > pivot)
        {
            i++; 
            swapD(vec,i,j);
        }
    }
    swapD(vec,i+1, high);
    return (i + 1);
}

void descendQuickSort(vector<pair<string,double>> &vec,int low,int high) // Recursive quicksort function.
{
    if(low < high)
    {
        int j = partitionD(vec,low,high);
        descendQuickSort(vec,low,j-1);
        descendQuickSort(vec,j+1,high);
    }
}