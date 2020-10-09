// https://cs50.harvard.edu/x/2020/psets/4/filter/less/
// Program that applies filters (grayscale, sepia, reflect, blur) to BMPs (06.05.20)

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, avgGrey;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Determine what shade of grey to make the new pixel
            avgGrey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Setting each pixel to grey
            image[i][j].rgbtBlue = avgGrey;
            image[i][j].rgbtGreen = avgGrey;
            image[i][j].rgbtRed = avgGrey;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, sepiaRed, sepiaGreen, sepiaBlue;
    RGBTRIPLE pixel;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixel = image[i][j];

            // Getting sepia values for original colors
            sepiaRed = round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue);
            sepiaGreen = round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue);
            sepiaBlue = round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue);

            // Ensuring values are not overflowed and assigning
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, half;
    RGBTRIPLE temp_pixel;

    half = width / 2;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < half; j++)
        {
            temp_pixel = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp_pixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k, l, allRed, allGreen, allBlue;
    float counter;
    RGBTRIPLE img_copy[height][width];

    // Getting copy of the original image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            img_copy[i][j] = image[i][j];
        }
    }

    // Messy blur happens here
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Resetting variables for counting avgColor
            allRed = allGreen = allBlue = 0;
            counter = 0.0;

            // Iterating through 3x3 piece of the picture
            for (k = i - 1; k <= i + 1; k++)
            {
                for (l = j - 1; l <= j + 1; l++)
                {
                    // Checking for edge (pun intended) cases
                    if (k < 0 || k > height - 1 ||
                        l < 0 || l > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        allRed += img_copy[k][l].rgbtRed;
                        allGreen += img_copy[k][l].rgbtGreen;
                        allBlue += img_copy[k][l].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Bluring original image
            image[i][j].rgbtRed = round(allRed / counter);
            image[i][j].rgbtGreen = round(allGreen / counter);
            image[i][j].rgbtBlue = round(allBlue / counter);
        }
    }
}