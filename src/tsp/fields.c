#include "tsp/fields.h"
#include "tsp/fields_enums.h"
#include "utils/logger.h"

#include <string.h>

TSP_Type parse_TSP_Type(const char* field)
{
	if      (strcmp(field, TSP_TYPE_TSP_STR ) == 0) { return e_TSP  ;}
	else if (strcmp(field, TSP_TYPE_ATSP_STR) == 0) { return e_ATSP ;}
	else if (strcmp(field, TSP_TYPE_SOP_STR ) == 0) { return e_SOP  ;}
	else if (strcmp(field, TSP_TYPE_HCP_STR ) == 0) { return e_HCP  ;}
	else if (strcmp(field, TSP_TYPE_CVRP_STR) == 0) { return e_CVRP ;}
	else if (strcmp(field, TSP_TYPE_TOUR_STR) == 0) { return e_TOUR ;}
	else
	{
		LOG_ERROR("Could not find .TSP field enum for : %s", field);
		return e_TYPE_UNDEFINED; // or TSP_FIELD_UNDEFINED
	}
}

TSP_Edge_Weight_Type parse_TSP_Edge_Weight_Type(const char* field)
{
	if      (strcmp(field, TSP_EDGE_WEIGHT_TYPE_EXPLICIT_STR) == 0) { return e_EXPLICIT ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_EUC_2D_STR  ) == 0) { return e_EUC_2D   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_EUC_3D_STR  ) == 0) { return e_EUC_3D   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_MAX_2D_STR  ) == 0) { return e_MAX_2D   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_MAX_3D_STR  ) == 0) { return e_MAX_3D   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_MAN_2D_STR  ) == 0) { return e_MAN_2D   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_MAN_3D_STR  ) == 0) { return e_MAN_3D   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_CEIL_2D_STR ) == 0) { return e_CEIL_2D  ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_GEO_STR     ) == 0) { return e_GEO      ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_ATT_STR     ) == 0) { return e_ATT      ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_XRAY1_STR   ) == 0) { return e_XRAY1    ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_XRAY2_STR   ) == 0) { return e_XRAY2    ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_TYPE_SPECIAL_STR ) == 0) { return e_SPECIAL  ;}
	else
	{
		LOG_ERROR("Could not find .TSP field enum for : %s", field);
		return e_EDGE_WEIGHT_TYPE_UNDEFINED; // or TSP_FIELD_UNDEFINED
	}
}

TSP_Edge_Weight_Format parse_TSP_Edge_Weight_Format(const char* field)
{
	if      (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_FUNCTION      ) == 0) { return e_FUNCTION      ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_FULL_MATRIX   ) == 0) { return e_FULL_MATRIX   ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_UPPER_ROW     ) == 0) { return e_UPPER_ROW     ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_LOWER_ROW     ) == 0) { return e_LOWER_ROW     ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_ROW) == 0) { return e_UPPER_DIAG_ROW;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_ROW) == 0) { return e_LOWER_DIAG_ROW;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_UPPER_COL     ) == 0) { return e_UPPER_COL     ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_LOWER_COL     ) == 0) { return e_LOWER_COL     ;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_COL) == 0) { return e_UPPER_DIAG_COL;}
	else if (strcmp(field, TSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_COL) == 0) { return e_LOWER_DIAG_COL;}
	else
	{
		LOG_ERROR("Could not find .TSP field enum for : %s", field);
		return e_EDGE_WEIGHT_FORMAT_UNDEFINED; // or TSP_FIELD_UNDEFINED
	}
}

TSP_Edge_Data_Format parse_TSP_Edge_Data_Format(const char* field)
{
	if      (strcmp(field, TSP_EDGE_DATA_FORMAT_EDGE_LIST) == 0) { return e_EDGE_LIST ;}
	else if (strcmp(field, TSP_EDGE_DATA_FORMAT_ADJ_LIST ) == 0) { return e_ADJ_LIST  ;}
	else
	{
		LOG_ERROR("Could not find .TSP field enum for : %s", field);
		return e_EDGE_DATA_FORMAT_UNDEFINED; // or TSP_FIELD_UNDEFINED
	}
}

TSP_Node_Coord_Type parse_TSP_Node_Coord_Type(const char* field)
{
	if      (strcmp(field, TSP_NODE_COORD_TYPE_TWOD_COORDS  ) == 0) { return e_TWOD_COORDS   ;}
	else if (strcmp(field, TSP_NODE_COORD_TYPE_THREED_COORDS) == 0) { return e_THREED_COORDS ;}
	else if (strcmp(field, TSP_NODE_COORD_TYPE_NO_COORDS    ) == 0) { return e_NO_COORDS     ;}
	else
	{
		LOG_ERROR("Could not find .TSP field enum for : %s", field);
		return e_NODE_COORD_TYPE_UNDEFINED; // or TSP_FIELD_UNDEFINED
	}
}

TSP_Display_Data_Type parse_TSP_Display_Data_Type(const char* field)
{
	if      (strcmp(field, TSP_DISPLAY_DATA_TYPE_COORD_DISPLAY) == 0) { return e_COORD_DISPLAY ;}
	else if (strcmp(field, TSP_DISPLAY_DATA_TYPE_TWOD_DISPLAY ) == 0) { return e_TWOD_DISPLAY  ;}
	else if (strcmp(field, TSP_DISPLAY_DATA_TYPE_NO_DISPLAY   ) == 0) { return e_NO_DISPLAY    ;}
	else
	{
		LOG_ERROR("Could not find .TSP field enum for : %s", field);
		return e_DISPLAY_DATA_TYPE_UNDEFINED; // or TSP_FIELD_UNDEFINED
	}
}

const char* TSP_Type_to_str(TSP_Type type)
{
	switch (type)
	{
		case e_TSP  : return TSP_TYPE_TSP_STR ;
		case e_ATSP : return TSP_TYPE_ATSP_STR;
		case e_SOP  : return TSP_TYPE_SOP_STR ;
		case e_HCP  : return TSP_TYPE_HCP_STR ;
		case e_CVRP : return TSP_TYPE_CVRP_STR;
		case e_TOUR : return TSP_TYPE_TOUR_STR;

		case e_TYPE_UNDEFINED : return TSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for TYPE enum : %d", type);
	return TSP_FIELD_UNDEFINED_STR;
}

const char* TSP_Edge_Weight_Type_to_str(TSP_Edge_Weight_Type type)
{
	switch (type)
	{
		case e_EXPLICIT : return TSP_EDGE_WEIGHT_TYPE_EXPLICIT_STR;
		case e_EUC_2D   : return TSP_EDGE_WEIGHT_TYPE_EUC_2D_STR  ;
		case e_EUC_3D   : return TSP_EDGE_WEIGHT_TYPE_EUC_3D_STR  ;
		case e_MAX_2D   : return TSP_EDGE_WEIGHT_TYPE_MAX_2D_STR  ;
		case e_MAX_3D   : return TSP_EDGE_WEIGHT_TYPE_MAX_3D_STR  ;
		case e_MAN_2D   : return TSP_EDGE_WEIGHT_TYPE_MAN_2D_STR  ;
		case e_MAN_3D   : return TSP_EDGE_WEIGHT_TYPE_MAN_3D_STR  ;
		case e_CEIL_2D  : return TSP_EDGE_WEIGHT_TYPE_CEIL_2D_STR ;
		case e_GEO      : return TSP_EDGE_WEIGHT_TYPE_GEO_STR     ;
		case e_ATT      : return TSP_EDGE_WEIGHT_TYPE_ATT_STR     ;
		case e_XRAY1    : return TSP_EDGE_WEIGHT_TYPE_XRAY1_STR   ;
		case e_XRAY2    : return TSP_EDGE_WEIGHT_TYPE_XRAY2_STR   ;
		case e_SPECIAL  : return TSP_EDGE_WEIGHT_TYPE_SPECIAL_STR ;

		case e_EDGE_WEIGHT_TYPE_UNDEFINED: return TSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for EDGE_WEIGHT_TYPE enum : %d", type);
	return TSP_FIELD_UNDEFINED_STR;
}

const char* TSP_Edge_Weight_Format_to_str(TSP_Edge_Weight_Format format)
{
	switch (format)
	{
		case e_FUNCTION       : return TSP_EDGE_WEIGHT_FORMAT_FUNCTION      ;
		case e_FULL_MATRIX    : return TSP_EDGE_WEIGHT_FORMAT_FULL_MATRIX   ;
		case e_UPPER_ROW      : return TSP_EDGE_WEIGHT_FORMAT_UPPER_ROW     ;
		case e_LOWER_ROW      : return TSP_EDGE_WEIGHT_FORMAT_LOWER_ROW     ;
		case e_UPPER_DIAG_ROW : return TSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_ROW;
		case e_LOWER_DIAG_ROW : return TSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_ROW;
		case e_UPPER_COL      : return TSP_EDGE_WEIGHT_FORMAT_UPPER_COL     ;
		case e_LOWER_COL      : return TSP_EDGE_WEIGHT_FORMAT_LOWER_COL     ;
		case e_UPPER_DIAG_COL : return TSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_COL;
		case e_LOWER_DIAG_COL : return TSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_COL;

		case e_EDGE_WEIGHT_FORMAT_UNDEFINED: return TSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for EDGE_WEIGHT_FORMAT enum : %d", format);
	return TSP_FIELD_UNDEFINED_STR;
}

const char* TSP_Edge_Data_Format_to_str(TSP_Edge_Data_Format format)
{
	switch (format)
	{
		case e_EDGE_LIST : return TSP_EDGE_DATA_FORMAT_EDGE_LIST;
		case e_ADJ_LIST  : return TSP_EDGE_DATA_FORMAT_ADJ_LIST ;

		case e_EDGE_DATA_FORMAT_UNDEFINED: return TSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for EDGE_DATA_FORMAT enum : %d", format);
	return TSP_FIELD_UNDEFINED_STR;
}

const char* TSP_Node_Coord_Type_to_str(TSP_Node_Coord_Type type)
{
	switch (type)
	{
		case e_TWOD_COORDS   : return TSP_NODE_COORD_TYPE_TWOD_COORDS  ;
		case e_THREED_COORDS : return TSP_NODE_COORD_TYPE_THREED_COORDS;
		case e_NO_COORDS     : return TSP_NODE_COORD_TYPE_NO_COORDS    ;

		case e_NODE_COORD_TYPE_UNDEFINED: return TSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for NODE_COORD_TYPE enum : %d", type);
	return TSP_FIELD_UNDEFINED_STR;
}

const char* TSP_Display_Data_Type_to_str(TSP_Display_Data_Type type)
{
	switch (type)
	{
		case e_COORD_DISPLAY : return TSP_DISPLAY_DATA_TYPE_COORD_DISPLAY;
		case e_TWOD_DISPLAY  : return TSP_DISPLAY_DATA_TYPE_TWOD_DISPLAY ;
		case e_NO_DISPLAY    : return TSP_DISPLAY_DATA_TYPE_NO_DISPLAY  ;

		case e_DISPLAY_DATA_TYPE_UNDEFINED: return TSP_FIELD_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for DISPLAY_DATA_TYPE enum : %d", type);
	return TSP_FIELD_UNDEFINED_STR;
}

