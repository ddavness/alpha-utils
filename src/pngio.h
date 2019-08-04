#pragma once

#ifndef PNGIO
#define PNGIO
unsigned char *png_load(const char *path, int *width, int *height, int *channels);
bool png_save(const char *filename, int width, int height, unsigned char *data);

#endif