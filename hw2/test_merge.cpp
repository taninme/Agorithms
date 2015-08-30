//Ferdous Ahmed
//Assignments # 2
//Date - 09/19/2013

#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;

const int INTEGER_N = 163;

void print(int *input) // this prints the input
{
    for ( int i = 0; i < INTEGER_N; i++ )
        cout << input[i] << " ";
    cout << endl;
}

void insertionsort(int* input)
{
    for (int i=1;i<INTEGER_N;i++)
    {
        for (int j=i;j>0;j--)
        {
            if (input[j]<input[j-1])
            {
                int tmp = input[j];
                input[j] = input[j-1];
                input[j-1] = tmp;
            } else
                break;
        }


    }
}

void merge(int* input, int p, int r)
{
    int mid = floor((p + r) / 2);
    int i1 = 0;
    int i2 = p;
    int i3 = mid + 1;

    // this Temp array
    int temp[r-p+1];

    // Merge is sorted to form two arrays
    while ( i2 <= mid && i3 <= r )
        if ( input[i2] < input[i3] )
            temp[i1++] = input[i2++];
        else
            temp[i1++] = input[i3++];

    // Merge the rest of the elements in left array
    while ( i2 <= mid )
        temp[i1++] = input[i2++];

    // Merge the rest of the elements in right array
    while ( i3 <= r )
        temp[i1++] = input[i3++];

    // Move from temp array to master array
    for ( int i = p; i <= r; i++ )
        input[i] = temp[i-p];
}

void merge_sort(int* input, int p, int r)
{
    if ( p < r )
    {
        int mid = floor((p + r) / 2);
        merge_sort(input, p, mid);
        merge_sort(input, mid + 1, r);
        merge(input, p, r);
    }
}

int main()
{
    //int input[INPUT_SIZE] = {500, 700, 800, 100, 300, 200, 900, 400, 1000, 600};
    int num,i,j,k;
    cout<<"Enter J and K"<<endl;
    cin>>num>>j>>k; // Enter n number of integer = num, j is the starting number at leftside and k is the number right most
    int input[num];

    clock_t tstart, tend, ttotal0, ttotal1, ttotal2 ;

    tstart=clock();

    for(int c=0;c<10000;c++)
    {
        for(i=0;i<num;i=i+2)
    {
        input[i] = i+1;
        input[i+1] = num - i;
    }
    }
    tend=clock();
    ttotal0 = tend - tstart;
    cout<<"Copy time :"<<ttotal0<<endl;
    cout << "Input: ";
    print(input);
    tstart=clock();

    for(int c=0;c<10000;c++)
    {
        for(i=0;i<num;i=i+2)
    {
        input[i] = i+1;
        input[i+1] = num - i;
    }
        merge_sort(input, j, k);
    }
    tend=clock();
    ttotal1 = (tend - tstart)-ttotal0;
    cout<<"Mergesort time :"<<ttotal1<<endl;

    for(int c=0;c<10000;c++)
    {
        for(i=0;i<num;i=i+2)
    {
        input[i] = i+1;
        input[i+1] = num - i;
    }
        insertionsort(input);
    }
    tend=clock();
    ttotal2 = (tend - tstart)- ttotal0;
    cout<<"Insertionsort time :"<<ttotal2<<endl;
    merge_sort(input, j, k);
    insertionsort(input);
    cout << "Output: ";
    print(input);
    return 0;
}

