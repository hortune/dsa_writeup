#include <iostream>
using namespace std;

 void max(int* arr, int left, int right, int res){
  int mid = (left+right)/2;
      int res1 = 0;
      int res2 = 0;
      if (left == right){
        res = arr[mid];
      }
      else{
        max(arr, left, mid, res1);
       max(arr, mid+1, right, res2);
       std::cout << res1 << ' ' << res2 << ' ' << std::endl;
       res = (res1 > res2 ? res1 : res2);
     }
   }      
int main()
{
  
  int array[ ]={1,2,3,4,5,6,7};
  int a=0;
  max(array,0,6,a);
}