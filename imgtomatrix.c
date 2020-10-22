#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image_write.h"

int main()
{
    int width, height, channels;
    unsigned char *img = stbi_load("black.png", &width, &height, &channels, 0);
    if(img == NULL)
    {
        printf("Error loading the image...\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n",width,height,channels);
    
    size_t img_size = width * height * channels;
    unsigned char *color_img = malloc(img_size);
    if(color_img == NULL)
    {
        printf("Unable to loacte memory for colored image...\n");
        exit(1);
    }

    for(unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {
        //Y
        *pg = (uint8_t)fmin(0.299 * *p +0.587 * *(p+1) + 0.114 * *(p+2), 255.0);
        //Cb
        *(pg + 1) = (uint8_t)fmin(-0.168 * *p - 0.331 * *(p+1) + 0.500 * *(p+2), 255.0);
        //Cr
        *(pg + 2) = (uint8_t)fmin(0.500 * *p - 0.418 * *(p+1) - 0.081 * *(p+2), 255.0);
        if(channels == 4)
        {
            *(pg+3) = *(p+3);
        }
    }
    int count = 0, i, j;
    for(j = 0 ; j < height ; j++)
    {
        for(i = 0 ; i < width ; i++){
            printf("%c ", img[j * width + i] ? '0' : '1' );
            if(img[j * width + i]==1)
            count++;
        }
            
        printf("\n");
    }
    printf("%d", count);
    // stbi_write_jpg("fire_ycbcr(3).jpg", width, height, channels, color_img, 100);

    stbi_image_free(img);
    free(color_img);
    return 0;
}
