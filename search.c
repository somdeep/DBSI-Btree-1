#include <stdio.h>

int binary(int arr[],int start,int end,int target);
int main()
{
    
    printf("\nHello World");
    int arr[]={1,2,5,6};
    printf("%d\n",sizeof(arr)/sizeof(int) );
    int result=binary(arr,0,sizeof(arr)/sizeof(int)-1,5)+1;
    printf("\nResult : %d",result);
    return 0;

}



int binary(int arr[],int start,int end,int target)
{
    if(start>end)
        return end;


    int mid=(start+end)/2;


    if(arr[mid] == target)
        return mid;


    else if(target<arr[mid])
        return binary(arr,start,mid-1,target);
    else
        return binary(arr,mid+1,end,target);
        
    
        
}
