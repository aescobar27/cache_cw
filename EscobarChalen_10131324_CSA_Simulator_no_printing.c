//This program was written by: Ariana Escobar Chalen 
//Student ID: 10131324
//This is a cache simulator program, it simulates the operation of a fully associative
//cache memory for two different algorithms: cross-correlation and bubble sort

#include <stdio.h>
#include <stdlib.h>

    int n=0;        //variable for the number of cache blocks
    int words=0;    //variable for the number of cache words
    int shift=0;    //variable for the number of bits to be shifted
    int mode=0;

int main (int argc, char *argv[]) {
    
    FILE *fp;
    char access_type;
    int memory_address;

    //The number of arguments must be 3
    if (argc != 3) {
       printf( "usage: check filename\n");
       exit(EXIT_FAILURE);
    }

//Loop to run te two different Algorithms
for (int i=1; i<3; i++)
{
    //Loop to run different modes
    for (int a=1; a<9; a++)
    {
     switch (a) {
            case 1:;
                mode=1;
                n=256;
                words= 2;
                shift=1;             
                break;
            case 2:;
                mode=2;
                n=128;
                words= 4;
                shift=2;  
                break;
            case 3:;
                mode=3;
                n=64;
                words= 8;
                shift=3;  
                break;
            case 4:;
                mode=4;
                n=32;
                words= 16;
                shift=4;  
                break;
            case 5:;
                mode=5;
                n=16;
                words= 32;
                shift=5;  
                break;
            case 6:;
                mode=6;
                n=8;
                words=64;
                shift=6;  
                break;
            case 7:;
                mode=7;
                n=4;
                words= 128;
                shift=7;  
                break;
            case 8:;
                mode=8;
                n=2;
                words= 256;
                shift=8;  
                break;
            
            default:;
                n=0;
                words=0;
                shift=0;  
                break;
        }

    //Open file
	fp = fopen(argv[i], "r");
 
     if(fp==NULL)
    {
       printf("Error opening trace file: %s\n", argv[i]);
       exit (EXIT_FAILURE);
    }

    //Least Recently Used counter
     void increment_LRU(int arr[])
    {
        int l;
        for (l = 0; l < n; l++)
            arr[l]++;     
    }

    int y=0;
    int read_count=0;
    int write_count=0;
    int counter_tag_bits_not_in_cache=0; //variable to determine if the tag bits are not in cache
    int mm_tag_bits=0;
    int block_offset=0;
    int in_cache;      //variable to determine if the tag bits are in cache 
    int index;         //Least Recently Used index for array
    int biggest; 

    unsigned read_cache_hit=0; //NRCH
    unsigned read_cache_miss=0; //NRCM
    unsigned write_cache_hit=0; //NWCH
    unsigned write_cache_miss=0; //NWCM
    unsigned NRA=0;
    unsigned NRA_new=0; //NRA
    unsigned NWA=0;
    unsigned NWA_new=0; //NWA


    //Cache Memory Tag bits initialisation
    int cache_tag_bits_2[n];
    for (int j=0; j<n; j++){
            cache_tag_bits_2[j]=-1;
        }

    //Array with valid bits initialisation
    int valid_bit[n];
    for (int j=0; j<n; j++){
             valid_bit[j]=0;
        }

    //Array with dirty bits initialisation
    int dirty_bit_2[n];
    for (int j=0; j<n; j++){
             dirty_bit_2[j]=0;
        }

    //Array with LRU initialisation
    int LRU_2[n];  
    for (int j=0; j<n; j++){
             LRU_2[j]=0;
        }
    

    //Store the memory address and access type
    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        y++;
        index=-1;
        
        increment_LRU(LRU_2);   //LRU++
        biggest=-1; 


        //Determine which cache memory has the LRU counter and store the value in 'index'
        for (int i = 0; i < n; i++) {
            if ( LRU_2[i] > biggest) 
                {
                    biggest = LRU_2[i];
                    index = i;
                 }         
        }


        mm_tag_bits = memory_address >> shift;  //Determine main memory tag bits
        in_cache=-1;
        counter_tag_bits_not_in_cache=0;

        //Loop to determine if the main memory tag bits are in cache
        for (int x=0; x < n; x++)
                {  
                    //if main memory tag bits are in cache copy the array index in "in_cache"
                    if (mm_tag_bits == cache_tag_bits_2[x])
                    {in_cache=x;
                    }
                    //when the tag bit are not in cache, the counter will be equal to the number of blocks in cache
                    else 
                    {counter_tag_bits_not_in_cache++;}
                }
        //If access type is a READ
        if(access_type=='R')
        {
            read_count++;
                    
                    //If main memory tag bits are in cache
                    if (in_cache != -1)
                    {
                        if (valid_bit[in_cache]==1)
                        {
                            read_cache_hit++;
                            LRU_2[in_cache]=0;
                        }
                        else 
                        {
                            read_cache_miss++;
                            LRU_2[index]=0;
                            valid_bit[index]=1;
                            cache_tag_bits_2[index]=mm_tag_bits;
                            NRA++;
                            NRA_new=NRA*words;
                            }
                    }
                    //If main memory tag bits are not in cache
                    else if (counter_tag_bits_not_in_cache==n)
                     {
                        read_cache_miss++;
                        NRA++;
                        NRA_new=NRA*words;

                        //If dirty bit is one, copy the value to the main memory first
                       if (dirty_bit_2[index]==1){
                                dirty_bit_2[index]=0;
                                NWA++;
                                NWA_new=NWA*words;
                            }
                        LRU_2[index]=0;
                        cache_tag_bits_2[index]=mm_tag_bits;
                        valid_bit[index]=1;
                    }
    
        }

        //If access type is a WRITE
        else if(access_type=='W')
        {
            write_count++;
            //If main memory tag bits are in cache
            if (in_cache != -1)
                    {
                        if (valid_bit[in_cache]==1)
                        {
                            write_cache_hit++;
                            LRU_2[in_cache]=0;
                            dirty_bit_2[in_cache]=1;

                        }
                        else 
                        {
                            write_cache_miss++;
                            LRU_2[index]=0;
                            valid_bit[index]=1;
                            dirty_bit_2[index]=1;
                            cache_tag_bits_2[index]=mm_tag_bits;
                            NRA++;
                            NRA_new=NRA*words;
                            }
                    }
            //If main memory tag bits are not in cache
            else if (counter_tag_bits_not_in_cache==n)
                     {
                        write_cache_miss++;
                        NRA++;
                        NRA_new=NRA*words;
                        
                        //If dirty bit is one, copy the value to the main memory first
                       if (dirty_bit_2[index]==1){
                                NWA++;
                                NWA_new=NWA*words;
                            }
                        LRU_2[index]=0;
                        cache_tag_bits_2[index]=mm_tag_bits;
                        valid_bit[index]=1;
                        dirty_bit_2[index]=1;
                        }
                    

        }
        
        }
    //Print outcomes
    printf ("%s, %d, %u, %u, %u, %u, %u, %u\n", argv[i], mode, NRA_new, NWA_new, read_cache_hit, read_cache_miss, write_cache_hit, write_cache_miss);

    //Close the file
    fclose(fp);
    }
}
    return 0;

}