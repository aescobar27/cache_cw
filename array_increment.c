
    /*
     * C Program to Increment every Element of the Array by one & Print Incremented Array
     */
 
    #include <stdio.h>
    void incrementArray(int arr[])
    {
 
        int i;
        for (i = 0; i < 4; i++)
            arr[i]++;     // this alters values in array in main
 
    }
    void main()
    {
        int x;
        int LRU[4] = {0};
        for( x=0; x < 10; x++){
        int i;
        incrementArray(LRU);
        
        for (i = 0; i < 4; i++)
        
         {
             if (x==1)
             if(i==1){
            LRU[i]=0;
        }
             printf("%d\t", LRU[i]);   // Prints 2, 3, 4, 5

           }  
     }

    }
 
    