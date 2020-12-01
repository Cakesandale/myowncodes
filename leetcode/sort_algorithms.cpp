#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//每次把最大的数放到末尾
void Bubble_Sort(vector<int> &array){
    size_t N=array.size();
    for(int m=N-1;m>=0;m--){
        bool flag=false;
        for(int i=0;i<m;i++){
            if(array[i]>array[i+1]){
                swap(array[i],array[i+1]);
                flag=true;
            }
        }
        if(flag==false) break;
    }
}

//考虑A[n]的值，从右向左扫描有序数组A[0,n-1]，直到第一个小于等于A[n]的元素，将A[n]插在这个元素的后面。
//对于基本有序的数组，会体现出良好的性能
void Insertion_Sort1(vector<int> &array){
    size_t N=array.size();
    for(int m=1;m<N;m++){
        int temp=array[m];
        int i=m;
        for(;i>0 && array[i-1]<temp;i--)
            array[i]=array[i-1];
        array[i]=temp;
    }
}
void Insertion_Sort2(vector<int> &array){
    size_t N=array.size();
    for(int i=1;i<N;++i)
        for(int j=i;j>0;--j)
             if(array[j]<array[j-1]) swap(array[j],array[j-1]);
             else break;
             
     return;
}

//希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，
//每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。
void Shell_Sort(vector<int> &array){
    size_t N = array.size();
    for(int D=N/2;D>0;D/=2){
        for(int m=D;m<N;m++){//insert-sort
            int temp=array[m];
            int i=m;
            for(;i>=D && array[i-D]<temp;i-=D)
                array[i]=array[i-D];
            array[i]=temp;
        }
    }
}


//归并排序(ascending)
void merge(vector<int> &array, vector<int> &temp_array, int left,int mid,int right){
    int i=left,j=mid+1, k=0;
    while(i<=mid && j<=right){
        if(array[i]<=array[j]) temp_array[k++]=array[i++];
        else temp_array[k++]=array[j++];
    }
    while(i<=mid){
        temp_array[k++]=array[i++];
    }
    while(j<=right){
        temp_array[k++]=array[j++];
    }
    for(int i=0;i<k;i++){
        array[left+i]=temp_array[i];
    }
}
void sub_merge(vector<int> &array, vector<int> &temp_array, int left, int right){
    if(left<right){
        int mid=(left+right)/2;
        sub_merge(array, temp_array, left, mid);
        sub_merge(array, temp_array, mid+1, right);
        merge(array, temp_array, left, mid, right);
    }
}
void Merge_Sort(vector<int> &array){
    size_t N = array.size();
    vector<int> temp(N,0);
    sub_merge(array, temp, 0, N-1);
    
}

//quicksort 对小规模的数据（例如N不到100）可能还不如插入排序快
int median3(vector<int> &A, int Left, int Right){//优化部分：选主元，左中右的中位数
    int Center = ( Left + Right ) / 2; 
    if ( A[Left] > A[Center] ) 
        swap(A[Left], A[Center] ); 
    if ( A[Left] > A[Right] ) 
        swap(A[Left], A[Right] ); 
    if ( A[Center] > A[Right] ) 
        swap(A[Center], A[Right] ); 
    /* A[ Left ] <= A[ Center ] <= A[ Right ] */ 
    swap(A[Center], A[Right] ); /* 将pivot藏到右边 */ 
    /* 只需要考虑 A[ Left+1 ] … A[ Right–2 ] */
    return A[Right]; /* 返回 pivot */
}
void Quick_Sort(vector<int> &array, int left, int right){
    size_t N = array.size();
    if(N > 5){//大规模数据才用快排
        if(left>right) return;
        int pivot=median3(array, left ,right);
        int i=left,j=right-1;
        while(i<j){
            while(array[i]<pivot){i++;}
            while(array[j]>pivot){j--;}
            if(i<j)
                swap(array[i], array[j]);
            else
            {
                break;
            }
            
        }
        swap(array[i],array[right]);
        Quick_Sort(array, left, i-1);
        Quick_Sort(array,i+1,right);
    }
    else
    {
        Insertion_Sort1(array);
    }
    
}

//radix_sort
int maxbit(vector<int> &a, int N){
    // size_t N = a.size();
    int re=1;
    int m=10;
    for(int i=0;i<N;i++){
        int temp=a[i];
        int cnt=1;
        while(temp>0){
            temp = temp>>1;
            cnt++;
        }
        re = max(re, cnt);
    }
    return re;
}
void radix_sort_LSD(vector<int> &array){
    size_t N = array.size();
    // int mx = maxbit(array, N);
    int mx=3;
    // vector<int> cur(array);
    int k=1;
    for(int i=1;i<mx;i++){
        vector<vector<int> > temp(10,vector<int>());
        for(int x:array){
            int m=(x/k)%10;
            temp[m].push_back(x);
        }
        array.clear();
        for(vector<int> x:temp){
            array.insert(array.end(),x.begin(),x.end());
        }
        k *= 10;
    }
}


//main
int main(int arg, char *argv[]){
    int b[8]={3,1,4,5,21,12,8,7};
    vector<int> a(b,b+8);
    // Quick_Sort(a,0,7);
    radix_sort_LSD(a);
    for(auto x:a){
        cout<<x<<' ';
    }
    cout<<endl;
    return 0;
}