//QuickSort

#include<iostream>
#include<time.h>


const int INTEGER_N = 200;

using namespace std;

int Partition (int a[],int start, int over, int pivotIndex)

{
    int pivot = a[pivotIndex];

    do
    {
        while(a[start]<pivot)
            start ++;
        while(a[over]>pivot)
            over --;
        if(start<over && a[start] != a[over])
        {
            swap(a[start],a[over]);
        }
        else
            return over;

    }
        while(start<over);
            return over;

}

void quicksort(int a[], int start , int over)
{
    if(start<over)
    {
        int pivot =(start+over)/2;
        int pivot_new = Partition(a,start,over,pivot);
        quicksort(a,start,pivot_new -1);
        quicksort(a,pivot_new + 1, over);
    }
}

void print(int *input) // this prints the input
{
    for ( int i = 0; i < INTEGER_N; i++ )
        cout << input[i] << " ";
    cout << endl;
}
int main()
{

    int i,st,ov;
    cout<<"Enter Staring and End Value :";
    cin>>st>>ov;
    clock_t tstart, tend, ttotal0;
    int input[INTEGER_N];

    tstart=clock();

        for(i=0;i<INTEGER_N;i++)
    {
        input[i] = i+1;
    }

    quicksort(input,st,ov);

    tend=clock();
    ttotal0 = tend - tstart;
    cout<<ttotal0;
    //print(input);
    //tstart=clock();
}
