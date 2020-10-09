// https://cs50.harvard.edu/x/2020/psets/4/filter/more/
// Program that applies filters (grayscale, reflect, blur, edges) to BMPs (07.05.20)

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k, l, kX, kY, gxRed, gxGreen, gxBlue, gyRed, gyGreen, gyBlue;
    float sobelRed, sobelGreen, sobelBlue;
    int kernelX[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}

    };
    int kernelY[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}

    };
    RGBTRIPLE img_copy[height][width];

    // Getting copy of the original image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            img_copy[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Resetting variables;
            kX = kY = gxRed = gxGreen = gxBlue = gyRed = gyGreen = gyBlue = 0;

            // Iterating through 3x3 piece of the picture
            for (k = i - 1; k <= i + 1; k++)
            {
                for (l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 || k > height - 1 ||
                        l < 0 || l > width - 1)
                    {
                        kY++;
                        continue;
                    }
                    else
                    {
                        gxRed += img_copy[k][l].rgbtRed * kernelX[kX][kY];
                        gxGreen += img_copy[k][l].rgbtGreen * kernelX[kX][kY];
                        gxBlue += img_copy[k][l].rgbtBlue * kernelX[kX][kY];

                        gyRed += img_copy[k][l].rgbtRed * kernelY[kX][kY];
                        gyGreen += img_copy[k][l].rgbtGreen * kernelY[kX][kY];
                        gyBlue += img_copy[k][l].rgbtBlue * kernelY[kX][kY];

                        kY++;
                    }
                }
                // Coordinates of the corresponding vals in kernel X and Y
                kY = 0;
                kX++;
            }
            sobelRed = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            sobelGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            sobelBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // Filtering original image
            image[i][j].rgbtRed = (sobelRed > 255) ? 255 : sobelRed;
            image[i][j].rgbtGreen = (sobelGreen > 255) ? 255 : sobelGreen;
            image[i][j].rgbtBlue = (sobelBlue > 255) ? 255 : sobelBlue;
        }
    }
}