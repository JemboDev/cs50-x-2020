// https://cs50.harvard.edu/x/2020/psets/4/recover/
// Program that recovers JPEGs from a forensic image (12.05.20)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

// We'll be reading blocks of 512 bytes one-by-one
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Getting some memo for 512b chunks
    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);

    char jpg_name[sizeof("###.jpg")];
    int jpg_counter = 0;
    FILE *jpg = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xFF &&
            buffer[1] == 0xD8 &&
            buffer[2] == 0xFF &&
            (buffer[3] & 0xF0) == 0xE0)
        {
            if (jpg_counter != 0)
            {
                fclose(jpg);
            }

            sprintf(jpg_name, "%03i.jpg", jpg_counter);

            jpg = fopen(jpg_name, "w");

            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, jpg);

            jpg_counter++;
        }
        else if (jpg_counter != 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, jpg);
        }
    }

    fclose(jpg);
    fclose(card);
    free(buffer);
}