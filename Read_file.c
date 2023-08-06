#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "C:\\Users\\arian\\Documents\\UoM_Electronic_Engineering\\Third_Year\\Second_Semester\\Computer_Architecture\\Cache_Coursework\\test_file.trc"


int main (void) {
    FILE *fp;
    char access_type;
    int memory_address;
	fp = fopen(FILE_NAME, "r");
  if(fp==NULL)
    {
       printf("Error opening trace file: %s\n", FILE_NAME);
       exit (EXIT_FAILURE);
    }

    int i=0;
    int external_memory_read_count=0;
    int external_memory_write_count=0;
    while (fscanf(fp, "%c %x\n\r", &access_type, &memory_address)==2)
    {
        i++;
        if(access_type=='R')
        external_memory_read_count++;
        else if(access_type=='W')
        external_memory_write_count++;
    }

    printf ("Read count is: %d, Write count is: %d", external_memory_read_count, external_memory_write_count);

    fclose(fp);
    fscanf(fp, "%c %x\n\r", &access_type, &memory_address);
    return 0;
}