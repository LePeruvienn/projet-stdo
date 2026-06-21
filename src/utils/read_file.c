#include "utils/read_file.h"
#include "utils/logger.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char* read_file_bin(const char* path, size_t* out_size)
{
	FILE* file = fopen(path, "rb");

	if (file == NULL)
	{
		LOG_ERROR("Cannot read binary file, path is NULL");
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read binary file, fseek failed");
		return NULL;
	}

	size_t size = ftell(file);

	if (size <= 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read binary file, size is less or equal to 0");
		return NULL;
	}

	rewind(file);

	unsigned char* buf = malloc((size_t)size);
	if (buf == NULL)
	{
		fclose(file);
		LOG_ERROR("Cannot read binary file, failed to allocate buffer");
		return NULL;
	}

	size_t read_size = fread(buf, 1, (size_t)size, file);

	fclose(file);

	if (read_size != (size_t)size)
	{
		free(buf);
		LOG_ERROR("Failed read all binary file conten, read size and file size mismatch");
		return NULL;
	}

	*out_size = size;

	return buf;
}

char* read_file_txt(const char* path)
{
	FILE* file = fopen(path, "rb");

	if (file == NULL)
	{
		LOG_ERROR("Cannot read text file, path is NULL");
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read text file, fseek failed");
		return NULL;
	}

	size_t size = ftell(file);

	if (size <= 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read text file, size is less or equal to 0");
		return NULL;
	}

	rewind(file);

	char* buf = malloc((size_t)size + 1);
	if (buf == NULL)
	{
		fclose(file);
		LOG_ERROR("Cannot read text file, malloc failed");
		return NULL;
	}

	size_t read_size = fread(buf, 1, (size_t)size, file);

	fclose(file);

	if (read_size != (size_t)size)
	{
		free(buf);
		LOG_ERROR("Failed read all text file conten, read size and file size mismatch");
		return NULL;
	}

	buf[size] = '\0';

	return buf;
}

