// https://lab.cs50.io/cs50/labs/2020/x/mario/more/
// Mario (more comfortable) (04.04.20)

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // getting user's input as height
    int height;
    
    do
    {
        height = get_int("Height: ");
    } 
    while (height < 1 || height > 8);
    // drawing the tower
    for (int i = 1; i <= height; i++) // floors
    {
        for (int j = 0; j < height - i; j++) // spaces
        {
            printf(" ");
        }
        for (int k = 0; k < i; k++) // hashes (left)
        {
            printf("#");
        }

        printf("  ");

        for (int l = 0; l < i; l++) // hashes (right)
        {
            printf("#");
        }

        printf("\n");
    }
}
