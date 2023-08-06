#include <stdio.h>
#include <stdlib.h>

//#define FILE_NAME "C:\\Users\\arian\\Documents\\UoM_Electronic_Engineering\\Third_Year\\Second_Semester\\Computer_Architecture\\Cache_Coursework\\test_file.trc"
 void increment_LRU(int arr[])
    {
 
        int i;
        for (i = 0; i < 4; i++)
            arr[i]++;     // this alters values in array in main
 
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

    int i=0;
    int external_memory_read_count=0;
    int external_memory_write_count=0;
    int valid_bit=0;
    int read_cache_hit=0;
    int read_cache_miss=0;
    int write_cache_hit=0;
    int write_cache_miss=0;

    int LRU[256]={0};

     
    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        i++;
        int cache[256]={0};
        int valid_bit[256]={0};
        int dirty_bit[256]={0};
        int main_memory[65536]={0};
        int biggest=0;
        int index=0;
        int tag_bits=0;
        int block_offset=0;

        int LRU[256] = {0};
        increment_LRU(LRU);

        if(access_type=='R')
        {
            external_memory_read_count++;
        
        tag_bits = memory_address >> 1;
        block_offset = memory_address & 0x0001;
                for (int x; x < 256; x++)
                {
                    if (tag_bits == cache[x])
                    {
                        read_cache_hit++;
                        LRU[x]=0;
                        
                    }
                    else {
                        read_cache_miss++;
                        biggest = LRU[0];
                            for (i = 0; i < 256; i++) {
                            if ( LRU[i] > biggest) {
                                biggest = LRU[i];
                                index = i;
                                 }
                        if (dirty_bit[index]==1){
                            main_memory[index]=cache[index];
                            LRU[index]=0;
                            cache[index]=tag_bits;
                            valid_bit[index]=1;
                        }
                        else {
                            LRU[index]=0;
                            cache[index]=tag_bits;
                            valid_bit[index]=1;
                        }
                       
            
                    }
                }

        }
        }
        else if(access_type=='W')
        {
            external_memory_write_count++;
        
        }
        }



   

    printf ("Read count is: %d, Write count is: %d", external_memory_read_count, external_memory_write_count);
    printf ("Read Hit count is: %d, Read Miss count is: %d", read_cache_hit, read_cache_miss);

    fclose(fp);
    fscanf(fp, "%c %x\n\r", &access_type, &memory_address);
    return 0;

}