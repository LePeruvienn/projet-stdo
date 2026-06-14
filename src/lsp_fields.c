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
	if      (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_FUNCTION      ) == 0) { return e_FUNCTION      ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_FULL_MATRIX   ) == 0) { return e_FULL_MATRIX   ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_UPPER_ROW     ) == 0) { return e_UPPER_ROW     ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_LOWER_ROW     ) == 0) { return e_LOWER_ROW     ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_ROW) == 0) { return e_UPPER_DIAG_ROW;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_ROW) == 0) { return e_LOWER_DIAG_ROW;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_UPPER_COL     ) == 0) { return e_UPPER_COL     ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_LOWER_COL     ) == 0) { return e_LOWER_COL     ;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_COL) == 0) { return e_UPPER_DIAG_COL;}
	else if (strcmp(field, LSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_COL) == 0) { return e_LOWER_DIAG_COL;}
	else
	{
		LOG_ERROR("Could not find .LSP field enum for : %s", field);
		return e_EDGE_WEIGHT_FORMAT_UNDEFINED; // or LSP_FIELD_UNDEFINED
	}
}

LSP_Edge_Data_Format parse_LSP_Edge_Data_Format(const char* field)
{
	if      (strcmp(field, LSP_EDGE_DATA_FORMAT_EDGE_LIST) == 0) { return e_EDGE_LIST ;}
	else if (strcmp(field, LSP_EDGE_DATA_FORMAT_ADJ_LIST ) == 0) { return e_ADJ_LIST  ;}
	else
	{
		LOG_ERROR("Could not find .LSP field enum for : %s", field);
		return e_EDGE_DATA_FORMAT_UNDEFINED; // or LSP_FIELD_UNDEFINED
	}
}

LSP_Node_Coord_Type parse_LSP_Node_Coord_Type(const char* field)
{
	if      (strcmp(field, LSP_NODE_COORD_TYPE_TWOD_COORDS  ) == 0) { return e_TWOD_COORDS   ;}
	else if (strcmp(field, LSP_NODE_COORD_TYPE_THREED_COORDS) == 0) { return e_THREED_COORDS ;}
	else if (strcmp(field, LSP_NODE_COORD_TYPE_NO_COORDS    ) == 0) { return e_NO_COORDS     ;}
	else
	{
		LOG_ERROR("Could not find .LSP field enum for : %s", field);
		return e_NODE_COORD_TYPE_UNDEFINED; // or LSP_FIELD_UNDEFINED
	}
}

LSP_Display_Data_Type parse_LSP_Display_Data_Type(const char* field)
{
	if      (strcmp(field, LSP_DISPLAY_DATA_TYPE_COORD_DISPLAY) == 0) { return e_COORD_DISPLAY ;}
	else if (strcmp(field, LSP_DISPLAY_DATA_TYPE_TWOD_DISPLAY ) == 0) { return e_TWOD_DISPLAY  ;}
	else if (strcmp(field, LSP_DISPLAY_DATA_TYPE_NO_DISPLAY   ) == 0) { return e_NO_DISPLAY    ;}
	else
	{
		LOG_ERROR("Could not find .LSP field enum for : %s", field);
		return e_DISPLAY_DATA_TYPE_UNDEFINED; // or LSP_FIELD_UNDEFINED
	}
}

const char* LSP_Type_to_str(LSP_Type type)
{
	switch (type)
	{
		case e_TSP  : return LSP_TYPE_TSP_STR ;
		case e_ATSP : return LSP_TYPE_ATSP_STR;
		case e_SOP  : return LSP_TYPE_SOP_STR ;
		case e_HCP  : return LSP_TYPE_HCP_STR ;
		case e_CVRP : return LSP_TYPE_CVRP_STR;
		case e_TOUR : return LSP_TYPE_TOUR_STR;

		case e_TYPE_UNDEFINED : return LSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for TYPE enum : %d", type);
	return LSP_FIELD_UNDEFINED_STR;
}

const char* LSP_Edge_Weight_Type_to_str(LSP_Edge_Weight_Type type)
{
	switch (type)
	{
		case e_EXPLICIT : return LSP_EDGE_WEIGHT_TYPE_EXPLICIT_STR;
		case e_EUC_2D   : return LSP_EDGE_WEIGHT_TYPE_EUC_2D_STR  ;
		case e_EUC_3D   : return LSP_EDGE_WEIGHT_TYPE_EUC_3D_STR  ;
		case e_MAX_2D   : return LSP_EDGE_WEIGHT_TYPE_MAX_2D_STR  ;
		case e_MAX_3D   : return LSP_EDGE_WEIGHT_TYPE_MAX_3D_STR  ;
		case e_MAN_2D   : return LSP_EDGE_WEIGHT_TYPE_MAN_2D_STR  ;
		case e_MAN_3D   : return LSP_EDGE_WEIGHT_TYPE_MAN_3D_STR  ;
		case e_CEIL_2D  : return LSP_EDGE_WEIGHT_TYPE_CEIL_2D_STR ;
		case e_GEO      : return LSP_EDGE_WEIGHT_TYPE_GEO_STR     ;
		case e_ATT      : return LSP_EDGE_WEIGHT_TYPE_ATT_STR     ;
		case e_XRAY1    : return LSP_EDGE_WEIGHT_TYPE_XRAY1_STR   ;
		case e_XRAY2    : return LSP_EDGE_WEIGHT_TYPE_XRAY2_STR   ;
		case e_SPECIAL  : return LSP_EDGE_WEIGHT_TYPE_SPECIAL_STR ;

		case e_EDGE_WEIGHT_TYPE_UNDEFINED: return LSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for EDGE_WEIGHT_TYPE enum : %d", type);
	return LSP_FIELD_UNDEFINED_STR;
}

const char* LSP_Edge_Weight_Format_to_str(LSP_Edge_Weight_Format format)
{
	switch (format)
	{
		case e_FUNCTION       : return LSP_EDGE_WEIGHT_FORMAT_FUNCTION      ;
		case e_FULL_MATRIX    : return LSP_EDGE_WEIGHT_FORMAT_FULL_MATRIX   ;
		case e_UPPER_ROW      : return LSP_EDGE_WEIGHT_FORMAT_UPPER_ROW     ;
		case e_LOWER_ROW      : return LSP_EDGE_WEIGHT_FORMAT_LOWER_ROW     ;
		case e_UPPER_DIAG_ROW : return LSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_ROW;
		case e_LOWER_DIAG_ROW : return LSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_ROW;
		case e_UPPER_COL      : return LSP_EDGE_WEIGHT_FORMAT_UPPER_COL     ;
		case e_LOWER_COL      : return LSP_EDGE_WEIGHT_FORMAT_LOWER_COL     ;
		case e_UPPER_DIAG_COL : return LSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_COL;
		case e_LOWER_DIAG_COL : return LSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_COL;

		case e_EDGE_WEIGHT_FORMAT_UNDEFINED: return LSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for EDGE_WEIGHT_FORMAT enum : %d", format);
	return LSP_FIELD_UNDEFINED_STR;
}

const char* LSP_Edge_Data_Format_to_str(LSP_Edge_Data_Format format)
{
	switch (format)
	{
		case e_EDGE_LIST : return LSP_EDGE_DATA_FORMAT_EDGE_LIST;
		case e_ADJ_LIST  : return LSP_EDGE_DATA_FORMAT_ADJ_LIST ;

		case e_EDGE_DATA_FORMAT_UNDEFINED: return LSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for EDGE_DATA_FORMAT enum : %d", format);
	return LSP_FIELD_UNDEFINED_STR;
}

const char* LSP_Node_Coord_Type_to_str(LSP_Node_Coord_Type type)
{
	switch (type)
	{
		case e_TWOD_COORDS   : return LSP_NODE_COORD_TYPE_TWOD_COORDS  ;
		case e_THREED_COORDS : return LSP_NODE_COORD_TYPE_THREED_COORDS;
		case e_NO_COORDS     : return LSP_NODE_COORD_TYPE_NO_COORDS    ;

		case e_NODE_COORD_TYPE_UNDEFINED: return LSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for NODE_COORD_TYPE enum : %d", type);
	return LSP_FIELD_UNDEFINED_STR;
}

const char* LSP_Display_Data_Type_to_str(LSP_Display_Data_Type type)
{
	switch (type)
	{
		case e_COORD_DISPLAY : return LSP_DISPLAY_DATA_TYPE_COORD_DISPLAY;
		case e_TWOD_DISPLAY  : return LSP_DISPLAY_DATA_TYPE_TWOD_DISPLAY ;
		case e_NO_DISPLAY    : return LSP_DISPLAY_DATA_TYPE_NO_DISPLAY  ;

		case e_DISPLAY_DATA_TYPE_UNDEFINED: return LSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for DISPLAY_DATA_TYPE enum : %d", type);
	return LSP_FIELD_UNDEFINED_STR;
}

