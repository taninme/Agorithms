#include<iostream>
#include<time.h>
#include<stdlib.h>

const int INTEGER_N = 163;

using namespace std;

int Partition (int a[],int start, int over)

{
    int i,j;
    i = start - 1;
    int x = a[over];

    for(j=start;j<(over -1);j++)
    {
        if(a[j]<x)
        {
          i = i+1;
          swap(a[i],a[j]);
        }
    }

    swap(a[i+1],a[over]);
    return i+1;
}


int Randomized_Partition(int a[], int start, int over)
{
    int i = start + rand() % (over - start + 1);
    swap(a[over],a[i]);
    return Partition(a,start,over);
}

void randomized_quicksort(int a[], int start , int over
{
    if(start<over)
    {
    int q = Randomized_Partition(a,start,over);
    randomized_quicksort(a,start,q-1);
    randomized_quicksort(a,q+1,over);
    }
}

void print(int *input) // this prints the the input and output
{
    for ( int i = 0; i < INTEGER_N; i++ )
        cout << input[i] << " ";
    cout << endl;
}
int main()
{

    int i,st,ov;
    int input[INTEGER_N];
    cout<<"Enter Staring and End Value :";
    cin>>st>>ov;
    clock_t tstart, tend, ttotal0;

    tstart=clock();
    randomized_quicksort(input,st,ov);
    tend=clock();

    ttotal0 = tend - tstart;
    cout<<ttotal0;


}




