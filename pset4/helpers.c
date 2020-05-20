#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each col
        for (int j = 0; j < width; j++)
        {
            // Calculate average pixel value
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Change all pixel values to calculated average pixel value
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each col / 2
        for (int j = 0; j < width / 2; j++)
        {
            // Store current pixel into temporary BYTEs
            BYTE tempR = image[i][j].rgbtRed;
            BYTE tempG = image[i][j].rgbtGreen;
            BYTE tempB = image[i][j].rgbtBlue;

            // Go to pixel at opposite side of row
            // Assign current pixel with opposite pixel
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            // Assign temporary BYTEs to opposite pixel (puts original pixel to opposite)
            image[i][width - 1 - j].rgbtRed = tempR;
            image[i][width - 1 - j].rgbtGreen = tempG;
            image[i][width - 1 - j].rgbtBlue = tempB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int redSum, greenSum, blueSum;
    float counter;
    RGBTRIPLE temp[height][width];

    // Create copy of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each row
        for (int j = 0; j < width; j++)
        {
            redSum = 0;
            greenSum = 0;
            blueSum = 0;
            counter = 0.0;

            // Goes through adjacent pixels and adds to RGB sum
            // n = row, m= col
            for (int n = -1; n <= 1; n++)
            {
                // Checks for out-of-bounds (at top and bottom rows)
                if (n + i < 0 || n + i > height - 1)
                {
                    continue;
                }

                for (int m = -1; m <= 1; m++)
                {
                    // Checks for out-of-bounds (at left and right edges)
                    if (j + m < 0 || j + m > width - 1)
                    {
                        continue;
                    }

                    redSum += temp[i + n][j + m].rgbtRed;
                    greenSum += temp[i + n][j + m].rgbtGreen;
                    blueSum += temp[i + n][j + m].rgbtBlue;
                    counter++;
                }
            }

            // Calculates box blur average per pixel and applies to image
            image[i][j].rgbtRed = round(redSum / counter);
            image[i][j].rgbtGreen = round(greenSum / counter);
            image[i][j].rgbtBlue = round(blueSum / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float redGx, greenGx, blueGx;
    float redGy, greenGy, blueGy;
    int sobelRed, sobelGreen, sobelBlue;
    RGBTRIPLE temp[height][width];

    // Create copy of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each col
        for (int j = 0; j < width; j++)
        {
            redGx = 0.0;
            greenGx = 0.0;
            blueGx = 0.0;

            redGy = 0.0;
            greenGy = 0.0;
            blueGy = 0.0;

            sobelRed = 0;
            sobelGreen = 0;
            sobelBlue = 0;

            // Applies Gx and Gy kernels
            for (int n = -1; n <=  1; n++)
            {
                //Check for out-of-bounds (at top and bottom rows)
                if (i + n < 0 || i + n > height - 1)
                {
                    continue;
                }

                for (int m = -1; m <= 1; m++)
                {
                    //Check for out-of-bounds (at left and right cols)
                    if (j + m < 0 || j + m > width - 1)
                    {
                        continue;
                    }

                    if (n == -1)
                    {
                        // Top-Left
                        if (m == -1)
                        {
                            redGx += (-1 * temp[i + n][j + m].rgbtRed);
                            greenGx += (-1 * temp[i + n][j + m].rgbtGreen);
                            blueGx += (-1 * temp[i + n][j + m].rgbtBlue);

                            redGy += (-1 * temp[i + n][j + m].rgbtRed);
                            greenGy += (-1 * temp[i + n][j + m].rgbtGreen);
                            blueGy += (-1 * temp[i + n][j + m].rgbtBlue);
                        }
                        // Top-Center
                        else if (m == 0)
                        {
                            redGy += (-2 * temp[i + n][j + m].rgbtRed);
                            greenGy += (-2 * temp[i + n][j + m].rgbtGreen);
                            blueGy += (-2 * temp[i + n][j + m].rgbtBlue);
                        }
                        // Top-Right
                        else
                        {
                            redGx += temp[i + n][j + m].rgbtRed;
                            greenGx += temp[i + n][j + m].rgbtGreen;
                            blueGx += temp[i + n][j + m].rgbtBlue;

                            redGy += (-1 * temp[i + n][j + m].rgbtRed);
                            greenGy += (-1 * temp[i + n][j + m].rgbtGreen);
                            blueGy += (-1 * temp[i + n][j + m].rgbtBlue);
                        }
                    }
                    else if (n == 0)
                    {
                        // Center-Left
                        if (m == -1)
                        {
                            redGx += (-2 * temp[i + n][j + m].rgbtRed);
                            greenGx += (-2 * temp[i + n][j + m].rgbtGreen);
                            blueGx += (-2 * temp[i + n][j + m].rgbtBlue);
                        }
                        // Center
                        else if (m == 0)
                        {
                            // Do nothing
                        }
                        // Center-Right
                        else
                        {
                            redGx += (2 * temp[i + n][j + m].rgbtRed);
                            greenGx += (2 * temp[i + n][j + m].rgbtGreen);
                            blueGx += (2 * temp[i + n][j + m].rgbtBlue);
                        }
                    }
                    else
                    {
                        // Bottom-Left
                        if (m == -1)
                        {
                            redGx += (-1 * temp[i + n][j + m].rgbtRed);
                            greenGx += (-1 * temp[i + n][j + m].rgbtGreen);
                            blueGx += (-1 * temp[i + n][j + m].rgbtBlue);

                            redGy += temp[i + n][j + m].rgbtRed;
                            greenGy += temp[i + n][j + m].rgbtGreen;
                            blueGy += temp[i + n][j + m].rgbtBlue;
                        }
                        // Bottom-Center
                        else if (m == 0)
                        {
                            redGy += (2 * temp[i + n][j + m].rgbtRed);
                            greenGy += (2 * temp[i + n][j + m].rgbtGreen);
                            blueGy += (2 * temp[i + n][j + m].rgbtBlue);
                        }
                        // Bottom-Right
                        else
                        {
                            redGx += temp[i + n][j + m].rgbtRed;
                            greenGx += temp[i + n][j + m].rgbtGreen;
                            blueGx += temp[i + n][j + m].rgbtBlue;

                            redGy += temp[i + n][j + m].rgbtRed;
                            greenGy += temp[i + n][j + m].rgbtGreen;
                            blueGy += temp[i + n][j + m].rgbtBlue;
                        }
                    }
                }
            }

            // Apply Sobel filter algorithm
            // sqrt(Gx^2 + Gy^2)
            sobelRed = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));
            sobelGreen = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));
            sobelBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));

            if (sobelRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sobelRed;
            }

            if (sobelGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sobelGreen;
            }

            if (sobelBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sobelBlue;
            }
        }
    }
    return;
}
