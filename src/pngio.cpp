#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "png.h"

unsigned char *png_load(const char *path, int *width, int *height, int *channels)
{
	FILE *file = fopen(path, "rb");

	if (!file)
		return 0;

	size_t headerSize = 8;
	unsigned char header[8];
	headerSize = fread(header, 1, headerSize, file);

	if (png_sig_cmp(header, 0, headerSize))
	{
		fclose(file);
		return 0;
	}

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png)
	{
		fclose(file);
		return 0;
	}

	png_infop info = png_create_info_struct(png);

	if (!info)
	{
		png_destroy_read_struct(&png, NULL, NULL);
		fclose(file);
		return 0;
	}

	png_infop info_end = png_create_info_struct(png);

	if (!info_end)
	{
		png_destroy_read_struct(&png, &info, NULL);
		fclose(file);
		return 0;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		png_destroy_read_struct(&png, &info, &info_end);
		fclose(file);
		return 0;
	}

	png_init_io(png, file);
	png_set_sig_bytes(png, headerSize);
	png_read_png(png, info, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	int color = png_get_color_type(png, info);
	*width = png_get_image_width(png, info);
	*height = png_get_image_height(png, info);

	if (color != PNG_COLOR_TYPE_RGB && color != PNG_COLOR_TYPE_RGB_ALPHA)
	{
		png_destroy_read_struct(&png, &info, &info_end);
		fclose(file);
		return 0;
	}

	png_bytep *rows = png_get_rows(png, info);

	*channels = (color == PNG_COLOR_TYPE_RGB_ALPHA ? 4 : 3);

	unsigned char *image = new unsigned char[(*width) * (*height) * (*channels)];

	for (int y = 0; y < *height; y++)
		memcpy(image + y * (*width) * (*channels), rows[y], (*width) * (*channels));

	png_destroy_read_struct(&png, &info, &info_end);
	fclose(file);

	return image;
}

bool png_save(const char *filename, int width, int height, unsigned char *data)
{
	FILE *png_file = fopen(filename, "wb");

	if (!png_file)
		return false;

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		return false;

	png_infop info_ptr = png_create_info_struct(png_ptr);

	if (!info_ptr)
		return false;

	png_init_io(png_ptr, png_file);

	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	png_byte **row_ptrs = new png_byte*[height];

	for (int i = 0; i < height; i++)
		row_ptrs[i] = data + i * width * 4;

	png_set_rows(png_ptr, info_ptr, row_ptrs);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	png_destroy_write_struct(&png_ptr, &info_ptr);

	fclose(png_file);

	delete[] row_ptrs;

	return true;
}
