#include <stdio.h>
#include <stdlib.h>

//#define FILE_NAME "C:\\Users\\arian\\Documents\\UoM_Electronic_Engineering\\Third_Year\\Second_Semester\\Computer_Architecture\\Cache_Coursework\\test_file.trc"
 void increment_LRU(int arr[])
    {
 
        int l;
        for (l = 0; l < 256; l++)
            arr[l]++;     // this alters values in array in main
 
    }

int main (int argc, char *argv[]) {
    FILE *fp;
    char access_type;
    int memory_address;

    printf ("There are:%d arguments\n", argc);
    for (int i=0; i!=argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    if (argc != 2) {
       printf( "usage: check filename\n");
       exit(EXIT_FAILURE);
    }

	fp = fopen(argv[1], "r");
 
     if(fp==NULL)
    {
       printf("Error opening trace file: %s\n", argv[1]);
       exit (EXIT_FAILURE);
    }

    int y=0;
    int read_count=0;
    int write_count=0;
    int read_cache_hit=0;
    int read_cache_miss=0;
    int write_cache_hit=0;
    int write_cache_miss=0;
    int counter_tag_bits_not_in_cache;
    int mm_tag_bits=0;
    int block_offset=0;

    int NRA=0;
    int NWA=0;

    //MODE 1
    int cache_tag_bits[256]={0};
    int valid_bit[256]={0};
    int dirty_bit[256]={0};
    int LRU[256] = {0};  
    int biggest=LRU[0]; 


    for (int j=0; j<256; j++){
            cache_tag_bits[j]=-1;
        }

    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        y++;
        int index=-1;
        
        increment_LRU(LRU);
        
        for (int i = 0; i < 256; i++) {
            if ( LRU[i] > biggest) 
                {
                    biggest = LRU[i];
                    index = i;
                 }         
        }

        //printf("the index is: %d\n", index);

        mm_tag_bits = memory_address >> 1;
        block_offset = memory_address & 0x0001;
        int in_cache=-1;
        counter_tag_bits_not_in_cache=0;

        //printf("Tag bits: %d\n", mm_tag_bits);
        
        for (int x=0; x < 256; x++)
                {  
                    if (mm_tag_bits == cache_tag_bits[x])
                    {in_cache=x;
                    //printf("in cache: %d\n", in_cache);
                    break;}
                    else 
                    {counter_tag_bits_not_in_cache++;}
                }
    //printf("Counter: %d, In cache: %d\n", counter_tag_bits_not_in_cache, in_cache);
        if(access_type=='R')
        {
            read_count++;

                    if (in_cache != -1)
                    {
                        if (valid_bit[in_cache]==1)
                        {
                            read_cache_hit++;
                            LRU[in_cache]=0;
                            
                        }
                        else 
                        {
                            read_cache_miss++;
                            LRU[in_cache]=0;
                            cache_tag_bits[in_cache]=mm_tag_bits;
                            NRA++;
                            }
                    }

                    else if (counter_tag_bits_not_in_cache==256)
                     {
                        read_cache_miss++;
                        NRA++;

                       if (dirty_bit[index]==1){
                                LRU[index]=0;
                                cache_tag_bits[index]=mm_tag_bits;
                                valid_bit[index]=1;
                                dirty_bit[index]=0;
                            }
                        else if (dirty_bit[index]==0) {
                            LRU[index]=0;
                            cache_tag_bits[index]=mm_tag_bits;
                            valid_bit[index]=1;
                        }
                    }
    
        }
        else if(access_type=='W')
        {
            write_count++;

            if (in_cache != -1)
                    {
                        if (valid_bit[in_cache]==1)
                        {
                            write_cache_hit++;
                            LRU[in_cache]=0;
                            dirty_bit[in_cache]=1;
                        }
                        else 
                        {
                            write_cache_miss++;
                            LRU[in_cache]=0;
                            dirty_bit[in_cache]=1;
                            cache_tag_bits[in_cache]=mm_tag_bits;
                            }
                    }

                    else if (counter_tag_bits_not_in_cache==256)
                     {
                        write_cache_miss++;

                       if (dirty_bit[index]==1){
                                LRU[index]=0;
                                cache_tag_bits[index]=mm_tag_bits;
                                valid_bit[index]=1;
                                dirty_bit[index]=1;
                                NWA++;
                            }
                        else if (dirty_bit[index]==0) {
                            LRU[index]=0;
                            cache_tag_bits[index]=mm_tag_bits;
                            valid_bit[index]=1;
                            dirty_bit[index]=1;
                        }
                    }

        }
         //printf ("Write Hit count is: %d, Write Miss count is: %d\n", write_cache_hit, write_cache_miss);
        }



   
    printf ("MODE 1\n");
    printf ("Read count is: %d, Write count is: %d\n", read_count, write_count);
    printf ("External Read count is: %d, External Write count is: %d\n", NRA, NWA);
    printf ("Read Hit count is: %d, Read Miss count is: %d\n", read_cache_hit, read_cache_miss);
    printf ("Write Hit count is: %d, Write Miss count is: %d\n", write_cache_hit, write_cache_miss);


    //MODE 2
    y=0;
    read_count=0;
    write_count=0;
    read_cache_hit=0;
    read_cache_miss=0;
    write_cache_hit=0;
    write_cache_miss=0;
    counter_tag_bits_not_in_cache;
    mm_tag_bits=0;
    block_offset=0;

    NRA=0;
    NWA=0;

    
    int cache_tag_bits_2[128]={0};
    int valid_bit_2[128]={0};
    int dirty_bit_2[128]={0};
    int LRU_2[128] = {0};  
    int biggest_2=LRU_2[0]; 


    for (int j=0; j<128; j++){
            cache_tag_bits_2[j]=-1;
        }

    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        y++;
        int index=-1;
        
        increment_LRU(LRU_2);
        
        for (int i = 0; i < 128; i++) {
            if ( LRU_2[i] > biggest_2) 
                {
                    biggest_2 = LRU_2[i];
                    index = i;
                 }         
        }

        //printf("the index is: %d\n", index);

        mm_tag_bits = memory_address >> 2;
        block_offset = memory_address & 0x0003;
        int in_cache=-1;
        counter_tag_bits_not_in_cache=0;

        //printf("Tag bits: %d\n", mm_tag_bits);
        
        for (int x=0; x < 128; x++)
                {  
                    if (mm_tag_bits == cache_tag_bits_2[x])
                    {in_cache=x;
                    //printf("in cache: %d\n", in_cache);
                    break;}
                    else 
                    {counter_tag_bits_not_in_cache++;}
                }
    //printf("Counter: %d, In cache: %d\n", counter_tag_bits_not_in_cache, in_cache);
        if(access_type=='R')
        {
            read_count++;

                    if (in_cache != -1)
                    {
                        if (valid_bit_2[in_cache]==1)
                        {
                            read_cache_hit++;
                            LRU_2[in_cache]=0;
                            
                        }
                        else 
                        {
                            read_cache_miss++;
                            LRU_2[in_cache]=0;
                            cache_tag_bits_2[in_cache]=mm_tag_bits;
                            NRA++;
                            }
                    }

                    else if (counter_tag_bits_not_in_cache==128)
                     {
                        read_cache_miss++;
                        NRA++;

                       if (dirty_bit_2[index]==1){
                                LRU_2[index]=0;
                                cache_tag_bits_2[index]=mm_tag_bits;
                                valid_bit_2[index]=1;
                                dirty_bit_2[index]=0;
                            }
                        else if (dirty_bit_2[index]==0) {
                            LRU_2[index]=0;
                            cache_tag_bits_2[index]=mm_tag_bits;
                            valid_bit_2[index]=1;
                        }
                    }
    
        }
        else if(access_type=='W')
        {
            write_count++;

            if (in_cache != -1)
                    {
                        if (valid_bit_2[in_cache]==1)
                        {
                            write_cache_hit++;
                            LRU_2[in_cache]=0;
                            dirty_bit_2[in_cache]=1;
                        }
                        else 
                        {
                            write_cache_miss++;
                            LRU_2[in_cache]=0;
                            dirty_bit_2[in_cache]=1;
                            cache_tag_bits_2[in_cache]=mm_tag_bits;
                            }
                    }

                    else if (counter_tag_bits_not_in_cache==128)
                     {
                        write_cache_miss++;

                       if (dirty_bit_2[index]==1){
                                LRU_2[index]=0;
                                cache_tag_bits_2[index]=mm_tag_bits;
                                valid_bit_2[index]=1;
                                dirty_bit_2[index]=1;
                                NWA++;
                            }
                        else if (dirty_bit_2[index]==0) {
                            LRU_2[index]=0;
                            cache_tag_bits_2[index]=mm_tag_bits;
                            valid_bit_2[index]=1;
                            dirty_bit_2[index]=1;
                        }
                    }

        }
         //printf ("Write Hit count is: %d, Write Miss count is: %d\n", write_cache_hit, write_cache_miss);
        }



   
    printf ("MODE 2\n");
    printf ("Read count is: %d, Write count is: %d\n", read_count, write_count);
    printf ("External Read count is: %d, External Write count is: %d\n", NRA, NWA);
    printf ("Read Hit count is: %d, Read Miss count is: %d\n", read_cache_hit, read_cache_miss);
    printf ("Write Hit count is: %d, Write Miss count is: %d\n", write_cache_hit, write_cache_miss);

    fclose(fp);
    return 0;

}