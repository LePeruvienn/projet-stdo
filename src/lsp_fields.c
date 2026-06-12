#include "lsp_fields.h"
#include "lsp_fields_enums.h"
#include "logger.h"

#include <string.h>

LSP_Type parse_LSP_Type(const char* field)
{
	if      (strcmp(field, LSP_TYPE_TSP_STR ) == 0) { return e_TSP  ;}
	else if (strcmp(field, LSP_TYPE_ATSP_STR) == 0) { return e_ATSP ;}
	else if (strcmp(field, LSP_TYPE_SOP_STR ) == 0) { return e_SOP  ;}
	else if (strcmp(field, LSP_TYPE_HCP_STR ) == 0) { return e_HCP  ;}
	else if (strcmp(field, LSP_TYPE_CVRP_STR) == 0) { return e_CVRP ;}
	else if (strcmp(field, LSP_TYPE_TOUR_STR) == 0) { return e_TOUR ;}
	else
	{
		LOG_ERROR("Could not find .LSP field enum for : %s", field);
		return e_TYPE_UNDEFINED; // or LSP_FIELD_UNDEFINED
	}
}

LSP_Edge_Weight_Type parse_LSP_Edge_Weight_Type(const char* field)
{
	if      (strcmp(field, LSP_EDGE_WEIGHT_TYPE_EXPLICIT_STR) == 0) { return e_EXPLICIT ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_EUC_2D_STR  ) == 0) { return e_EUC_2D   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_EUC_3D_STR  ) == 0) { return e_EUC_3D   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_MAX_2D_STR  ) == 0) { return e_MAX_2D   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_MAX_3D_STR  ) == 0) { return e_MAX_3D   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_MAN_2D_STR  ) == 0) { return e_MAN_2D   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_MAN_3D_STR  ) == 0) { return e_MAN_3D   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_CEIL_2D_STR ) == 0) { return e_CEIL_2D  ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_GEO_STR     ) == 0) { return e_GEO      ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_ATT_STR     ) == 0) { return e_ATT      ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_XRAY1_STR   ) == 0) { return e_XRAY1    ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_XRAY2_STR   ) == 0) { return e_XRAY2    ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_TYPE_SPECIAL_STR ) == 0) { return e_SPECIAL  ;}
	else
	{
		LOG_ERROR("Could not find .LSP field enum for : %s", field);
		return e_EDGE_WEIGHT_TYPE_UNDEFINED; // or LSP_FIELD_UNDEFINED
	}
}

LSP_Edge_Weight_Format parse_LSP_Edge_Weight_Format(const char* field)
{
	LOG_ERROR("Could not find .LSP field enum for : %s", field);

	return e_EDGE_WEIGHT_FORMAT_UNDEFINED; // or LSP_FIELD_UNDEFINED
}

LSP_Edge_Data_Format parse_LSP_Edge_Data_Format(const char* field)
{
	LOG_ERROR("Could not find .LSP field enum for : %s", field);

	return e_EDGE_DATA_FORMAT_UNDEFINED; // or LSP_FIELD_UNDEFINED
}

LSP_Node_Coord_Type parse_LSP_Node_Coord_Type(const char* field)
{
	LOG_ERROR("Could not find .LSP field enum for : %s", field);

	return e_NODE_COORD_TYPE_UNDEFINED; // or LSP_FIELD_UNDEFINED
}

LSP_Display_Data_Type parse_LSP_Display_Data_Type(const char* field)
{
	LOG_ERROR("Could not find .LSP field enum for : %s", field);

	return e_DISPLAY_DATA_TYPE_UNDEFINED; // or LSP_FIELD_UNDEFINED
}
