#include <vector>
#include <string>
using namespace std;

void swap(vector<pair<string,double>> &vec,int index1,int index2) // swap two elements of vector.
{
    pair<string,double> temp = vec[index1];
    vec[index1] = vec[index2];
    vec[index2] = temp;
}
int partition(vector<pair<string,double>> &vec,int low,int high) // Partition function swaps elements until j > high, then swap i+1 and high before returning i+1 (the partition index).
{
    int pivot = vec[high].second; 
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) // Find a smaller element with j, if the element is found swap with i,
    {   
        if (vec[j].second < pivot)
        {
            i++; 
            swap(vec,i,j);
        }
    }
    swap(vec,i+1, high);
    return (i + 1);
}

void QuickSort(vector<pair<string,double>> &vec,int low,int high) // Recursive quicksort function.
{
    if(low < high)
    {
        int j = partition(vec,low,high);
        QuickSort(vec,low,j-1);
        QuickSort(vec,j+1,high);
    }
}