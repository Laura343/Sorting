#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

void merge(std::vector<int>& v,int start,int middle,int end);

std::mutex mtx;
void sort(std::vector<int>& v,int start,int end)
{
    if((end-start)<=1)
      return;
    
    std::thread t1([&](){
        sort(v,start,start+(end-start)/2);
    });
    std::thread t2([&](){
        sort(v,start+(end-start)/2,end);
    }); 

    t1.join();
    t2.join();

    merge(v,start,start+(end-start)/2,end);   
}

void merge(std::vector<int>& v,int start,int middle,int end)
{
    std::vector<int> tmp;
    int i=start,j=middle;
    while(i<middle && j<end)
    {
        if(v[i]>=v[j])
        {
            tmp.push_back(v[j]);
            j++;
        }
        else
        {
            tmp.push_back(v[i]);
            i++;
        }
    }
    
    if(i<middle)
    {
        for(int k=middle-1;k>=i;k--)
        {
            v[--end]=v[k];
        }
    }
    i=start;
    for(int x:tmp)
    {
        v[i++]=x;
    }
}

int main()
{
    std::vector<int> arr={1,3,7,24,4,2,7,3,3,72,4,124};

    sort(arr,0,arr.size());
    for(int x:arr)
    {
        std::cout<<x<<" ";
    }
    std::cout<<std::endl;

    return 0;
}