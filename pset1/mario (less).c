// https://lab.cs50.io/cs50/labs/2020/x/mario/less/
// Mario (less comfortable) (04.04.20)

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
        for (int k = 0; k < height - i; k++) // spaces
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++) // hashes
        {
            printf("#");
        }
        printf("\n");
    }
}
