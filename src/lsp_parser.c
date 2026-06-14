#include "lsp_parser.h"
#include "lsp_fields.h"
#include "lsp_file.h"
#include "lsp_section.h"
#include "lsp_section_unstream.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_SIZE 256
#define MAX_FIELD_SIZE 128
#define MAX_INPUT_SIZE 128

#define SEPARATOR ':'
#define SPACE_CHAR ' '
#define TAB_CHAR '\t'
#define END_LINE '\n'
#define RETURN_LINE '\r'
#define END_STR '\0'

// from: https://www.delftstack.com/howto/c/trim-string-in-c/
void trim_str(char* str)
{
	char *start = str + strspn(str, " \t\n\r");  // Points to the first non-whitespace character
	char *end = str + strlen(str) - 1;  // Points to the last character of the string

	while (end > start &&
			(*end == SPACE_CHAR || *end == TAB_CHAR || *end == END_LINE || *end == RETURN_LINE))
	{
		--end;  // Move the end pointer backward while it points to whitespace
	}

	*(end + 1) = '\0';  // Place the null terminator after the last non-whitespace character

	// Move the trimmed string to the start of the buffer
	if (start > str)
	{
		memmove(str, start, end - start + 2);  // +2 to include the last character and null terminator
	}
}

int LSP_parse_line(const char* line, char* field, char* input)
{
	size_t field_size = 0;
	size_t input_size = 0;

	bool read_field = true;

	for (size_t i = 0; line[i] != END_STR && line[i] != END_LINE && line[i] != RETURN_LINE; ++i)
	{
		char c = line[i];

		// Start reading input after SEPARATOR char
		if(c == SEPARATOR && read_field)
		{
			read_field = false;
			continue;
		}

		// Reading field
		if(read_field)
		{
			// Check for max buffer size
			if (field_size >= MAX_FIELD_SIZE - 1)
			{
				LOG_ERROR("Field size is bigger than max size (%d). Stop reading line.", MAX_FIELD_SIZE);
				return 1;
			}
			// Add char to buffer
			field[field_size++] = c;
		}
		// Reading input
		else
		{
			// Check for max buffer size
			if (input_size >= MAX_INPUT_SIZE - 1)
			{
				LOG_ERROR("Input size is bigger than max size (%d). Stop reading line.", MAX_INPUT_SIZE);
				return 2;
			}
			// Add char to buffer
			input[input_size++] = c;
		}
	}

	field[field_size] = END_STR;
	input[input_size] = END_STR;

	trim_str(field);
	trim_str(input);

	return 0;
}

LSP_File LSP_parse_file(const char* filepath)
{
	FILE* str = fopen(filepath, "r");

	if (str == NULL)
	{
		LOG_ERROR("Failed to open .lsp file");
		return NULL;
	}

	LSP_File lsp_file = LSP_File_create();

	char line[MAX_LINE_SIZE];

	for(size_t i = 0; fgets(line, sizeof(line), str) != NULL; ++i)
	{
		char field[MAX_FIELD_SIZE] = {0};
		char input[MAX_INPUT_SIZE] = {0};

		if (LSP_parse_line(line, field, input) != 0)
		{
			LOG_ERROR("Failed to parse line %zu, continue with next line.", i);
			continue;
		}

		bool is_section = (input[0] == END_STR);

		if (is_section)
		{
			LOG("%zu > Section : %s", i, field);
 			LSP_parse_section_to_file(str, lsp_file, field);
		}
		else
		{
			LOG("%zu > %s : %s", i, field, input);
			LSP_parse_field_to_file(lsp_file, field, input);
		}
	}

	fclose(str);

	return lsp_file;
}

void LSP_parse_field_to_file(LSP_File lsp_file, const char* field, const char* input)
{
	if (strcmp(field, LSP_NAME_STR) == 0)
	{
		strncpy(lsp_file->NAME, input, LSP_NAME_MAX_SIZE);
	}
	else if(strcmp(field, LSP_TYPE_STR) == 0)
	{
		lsp_file->TYPE = parse_LSP_Type(input);
	}
	else if(strcmp(field, LSP_COMMENT_STR) == 0)
	{
		strncpy(lsp_file->COMMENT, input, LSP_COMMENT_MAX_SIZE);
	}
	else if(strcmp(field, LSP_DIMENSION_STR) == 0)
	{
		long long n = atoll(input);
		lsp_file->DIMENSION = n;
		// LOG("atoi parsed input %s -> %lld", input, n);
	}
	else if(strcmp(field, LSP_CAPACITY_STR) == 0)
	{
		long long n = atoll(input);
		lsp_file->CAPACITY = n;
		// LOG("atoi parsed input %s -> %lld", input, n);
	}
	else if(strcmp(field, LSP_EDGE_WEIGHT_TYPE_STR) == 0)
	{
		lsp_file->EDGE_WEIGHT_TYPE = parse_LSP_Edge_Weight_Type(input);
	}
	else if(strcmp(field, LSP_EDGE_WEIGHT_FORMAT_STR) == 0)
	{
		lsp_file->EDGE_WEIGHT_FORMAT = parse_LSP_Edge_Weight_Format(input);
	}
	else if(strcmp(field, LSP_EDGE_DATA_FORMAT_STR) == 0)
	{
		lsp_file->EDGE_DATA_FORMAT = parse_LSP_Edge_Data_Format(input);
	}
	else if(strcmp(field, LSP_NODE_COORD_TYPE_STR) == 0)
	{
		lsp_file->NODE_COORD_TYPE = parse_LSP_Node_Coord_Type(input);
	}
	else if(strcmp(field, LSP_DISPLAY_DATA_TYPE_STR) == 0)
	{
		lsp_file->DISPLAY_DATA_TYPE = parse_LSP_Display_Data_Type(input);
	}
	else
	{
		LOG_ERROR("Couldnt match any field with : %s", field);
	}
}

void LSP_parse_section_to_file(FILE* str, LSP_File lsp_file, const char* field)
{
	LSP_Section_Type type = parse_LSP_Section_Type(field);

	switch(type)
	{
		case e_NODE_COORD_SECTION:
			LSP_Node_Coord_Section_unstream(str, lsp_file);
			break;

		case e_DEPOT_SECTION:
			break;

		case e_DEMAND_SECTION:
			break;

		case e_EDGE_DATA_SECTION:
			break;

		case e_FIXED_EDGES_SECTION:
			break;

		case e_DISPLAY_DATA_SECTION:
			break;

		case e_TOUR_SECTION:
			break;

		case e_EDGE_WEIGHT_SECTION:
			break;

		case e_SECTION_TYPE_UNDEFINED:
			LOG_ERROR("Trying to parse a Undefined LSP Section type.");
			break;
	}
}
