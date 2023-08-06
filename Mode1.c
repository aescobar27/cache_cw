#include <stdio.h>
#include <stdlib.h>




int main (int argc, char *argv[]) {
   //open file
    FILE *fp;
    char access_type;
    int memory_address;

    printf ("There are:%d arguments\n", argc);
    for (int x=0; x!=argc; x++)
    {
        printf("%s\n", argv[x]);
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

    //variables initialisation
    int i=0;
    int external_memory_read_count=0;
    int external_memory_write_count=0;
    int read_cache_miss=0;
    int read_cache_hit=0;
    int write_cache_miss=0;
    int write_cache_hit=0;
    int dirty_bit=0;
    int valid_bit=0;
    int least_recently_used;
    int MMtag_bits=0;

    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        i++;
    
        if(access_type=='R')
        {
            least_recently_used++;
            external_memory_read_count++;
            MMtag_bits = memory_address >> 1;
            printf("this is the address: %X\n", MMtag_bits);
        }
        

        else if(access_type=='W')
        external_memory_write_count++;
    }

    printf ("Read count is: %d, Write count is: %d", external_memory_read_count, external_memory_write_count);

    fclose(fp);
    fscanf(fp, "%c %x\n\r", &access_type, &memory_address);
    return 0;
}