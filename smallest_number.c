#include<stdio.h>
 
int main() {
   int i, num, biggest;
  int a[10]={10, 5, 7, 1, 8, 20, 6, 8, 9, 28};
   //Consider first element as smallest
   biggest = a[0];
   for (i = 0; i < 10; i++) {
      if (a[i] > biggest) {
         biggest = a[i];
      }
   }
 
   // Print out the Result
   printf("\nBiggest Element : %d", biggest);
 
   return (0);
}