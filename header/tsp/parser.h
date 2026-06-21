#ifndef TSP_PARSER_H
#define TSP_PARSER_H

#include "tsp/file.h"

#include <stdio.h>

// from: https://www.delftstack.com/howto/c/trim-string-in-c/
void trim_str(char* str);

TSP_File TSP_parse_file(const char* filepath);

int TSP_parse_line(const char* line, char* field, char* input);

void TSP_parse_section_to_file(FILE* str, TSP_File lsp_file, const char* field);
void TSP_parse_field_to_file(TSP_File lsp_file, const char* field, const char* input);

#endif // TSP_PARSER_H
