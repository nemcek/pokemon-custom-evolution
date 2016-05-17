//
// Created by Martin on 14. 5. 2016.
//

#include "src/loaders/ImageLoader.hpp"

bool ImageLoader::LoadPNGImage(const char *file_name, png_image_t *png_image)
{
    png_byte header[8];

    FILE *fp = fopen(file_name, "rb");
    if (fp == 0)
    {
        perror(file_name);
        return false;
    }

    // read the header
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "error: %s is not a PNG.\n", file_name);
        fclose(fp);
        return false;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "error: png_create_read_struct returned 0.\n");
        fclose(fp);
        return false;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return false;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return false;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return false;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
                 NULL, NULL, NULL);

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = (int)png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);

    // Allocate the image as a big block, to be given to opengl
    png_byte *image;
    image = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for pointing to image for reading the png with libpng
    png_bytep * row_pointers = (png_bytep *)malloc(temp_height * sizeof(png_bytep));
    if (row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image);
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image
//    for (int i = 0; i < temp_height; i++)
//    {
//        row_pointers[temp_height - 1 - i] = image + i * rowbytes;
//    }
    for (int i = 0; i < (int)temp_height; i++)
        row_pointers[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

    // read the png into image through row_pointers
    png_read_image(png_ptr, row_pointers);

//    png_image = new png_image_t();
    png_image->row_pointers = row_pointers;
    png_image->width = (int)temp_width;
    png_image->height = (int)temp_height;
    png_image->bit_depth = bit_depth;
    png_image->color_type = color_type == PNG_COLOR_TYPE_RGB ? IMAGE_COLOR_TYPE::RGB : IMAGE_COLOR_TYPE::RGBA;

    // clean up
    fclose(fp);

    return true;
}
