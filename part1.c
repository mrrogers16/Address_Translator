#include <stdio.h>
#include <stdlib.h>

// Constants
#define PAGE_SIZE 128 // Page size in bytes
#define OFFSET_BITS 7 // Number of bits used for the offset (log2(PAGE_SIZE))
#define PAGE_BITS 5   // Number of bits used for the page number (log2(Virtual Memory Size) - log2(Page Size))

FILE *open_file_rb(char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening %s\n", filename);
        return NULL;
    }
    return file;
}

FILE *open_file_wb(char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening %s\n", filename);
        return NULL;
    }
    return file;
}

int main(int argc, char *argv[])
{

    FILE *input;
    FILE *output;
    unsigned long virtual_addr, physical_addr;
    int page_num, frame_num, offset;

    if (argc <= 2)
    {
        fprintf(stderr, "ERROR: Usage %s infile outfile\n", argv[0]);
        return 1;
    }

    input = open_file_rb(argv[1]);
    output = open_file_wb(argv[2]);

    if (input == NULL)
    {
        fprintf(stderr, "ERROR: Opening %s", argv[1]);
        return 1;
    }
    else if (output == NULL)
    {
        fprintf(stderr, "ERROR: Opening %s", argv[2]);
        return 1;
    }

    int pagetable[32] = {2, 4, 1, 7, 3, 5, 6};

    while(fread(&virtual_addr, sizeof(unsigned long), 1, input))
    {
        page_num = virtual_addr >> OFFSET_BITS;

        offset = virtual_addr & ((1 << OFFSET_BITS) - 1);

        frame_num = pagetable[page_num];

        physical_addr = (frame_num << OFFSET_BITS) | offset;

        if (fwrite(&physical_addr, sizeof(unsigned long), 1, output) != 1)
        {
            fprintf(stderr, "Error writing to %s\n", argv[2]);
            fclose(input);
            fclose(output);
            return 1;
        }
    }
    fclose(input);
    fclose(output);

    return 0;
}