#include<stdio.h>
 
int main() {
   int i, num, biggest, index;
  int a[10]={10, 5, 7, 1, 8, 20, 20, 20, 9, 5};
   //Consider first element as smallest
   biggest = a[0];
   for (i = 0; i < 10; i++) {
      if (a[i] > biggest) {
         biggest = a[i];
         index = i;
      }
   }
 
   // Print out the Result
   printf("\nBiggest Element : %d", biggest);
     printf("\nElement : %d", index);
 
   return (0);
}