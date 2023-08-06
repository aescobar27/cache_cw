#include <stdio.h>
#include <stdlib.h>

//#define FILE_NAME "C:\\Users\\arian\\Documents\\UoM_Electronic_Engineering\\Third_Year\\Second_Semester\\Computer_Architecture\\Cache_Coursework\\test_file.trc"


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
    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        i++;
        int tag_bits = memory_address >> 1;
        printf("Tag bits: %d\n", tag_bits);
        
        if(access_type=='R')
        {external_memory_read_count++;
        //printf ("Read address is %x\n", memory_address);
        }

        else if(access_type=='W')
        {  external_memory_write_count++;
        //printf ("Write address is %x\n", memory_address);
        }
       
    }

    printf ("Read count is: %d, Write count is: %d", external_memory_read_count, external_memory_write_count);

    fclose(fp);
    fscanf(fp, "%c %x\n\r", &access_type, &memory_address);
    return 0;
}