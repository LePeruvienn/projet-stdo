#ifndef LSP_PARSER_H
#define LSP_PARSER_H

#include "LSP/file.h"

#include <stdio.h>

// from: https://www.delftstack.com/howto/c/trim-string-in-c/
void trim_str(char* str);

LSP_File LSP_parse_file(const char* filepath);

int LSP_parse_line(const char* line, char* field, char* input);

void LSP_parse_section_to_file(FILE* str, LSP_File lsp_file, const char* field);
void LSP_parse_field_to_file(LSP_File lsp_file, const char* field, const char* input);

#endif // LSP_PARSER_H
