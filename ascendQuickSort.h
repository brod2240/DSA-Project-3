#include <vector>
#include <string>

using namespace std;

void swapA(vector<pair<string,double>> &vec,int index1,int index2) // swap two elements of vector.
{
    pair<string,double> temp = vec[index1];
    vec[index1] = vec[index2];
    vec[index2] = temp;
}
int partitionA(vector<pair<string,double>> &vec,int low,int high) // Partition function swaps elements until j > high, then swap i+1 and high before returning i+1 (the partition index).
{
    int pivot = vec[high].second; 
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) // Find a smaller element with j, if the element is found swap with i,
    {   
        if (vec[j].second < pivot)
        {
            i++; 
            swapA(vec,i,j);
        }
    }
    swapA(vec,i+1, high);
    return (i + 1);
}

void ascendQuickSort(vector<pair<string,double>> &vec,int low,int high) // Recursive quicksort function.
{
    if(low < high)
    {
        int j = partitionA(vec,low,high);
        ascendQuickSort(vec,low,j-1);
        ascendQuickSort(vec,j+1,high);
    }
}