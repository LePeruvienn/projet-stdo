#ifndef LSP_FIELDS_ENUMS_H
#define LSP_FIELDS_ENUMS_H

/*
 * MACROS: type -> char*
 */

#define LSP_FIELD_UNDEFINED 0
#define LSP_FIELD_UNDEFINED_STR "UNDEFINED"

#define LSP_TYPE_TSP_STR "TSP"
#define LSP_TYPE_ATSP_STR "ATSP"
#define LSP_TYPE_SOP_STR "SOP"
#define LSP_TYPE_HCP_STR "HCP"
#define LSP_TYPE_CVRP_STR "CVRP"
#define LSP_TYPE_TOUR_STR "TOUR"

#define LSP_EDGE_WEIGHT_TYPE_EXPLICIT_STR "EXPLICIT"
#define LSP_EDGE_WEIGHT_TYPE_EUC_2D_STR "EUC_2D"
#define LSP_EDGE_WEIGHT_TYPE_EUC_3D_STR "EUC_3D"
#define LSP_EDGE_WEIGHT_TYPE_MAX_2D_STR "MAX_2D"
#define LSP_EDGE_WEIGHT_TYPE_MAX_3D_STR "MAX_3D"
#define LSP_EDGE_WEIGHT_TYPE_MAN_2D_STR "MAN_2D"
#define LSP_EDGE_WEIGHT_TYPE_MAN_3D_STR "MAN_3D"
#define LSP_EDGE_WEIGHT_TYPE_CEIL_2D_STR "CEIL_2D"
#define LSP_EDGE_WEIGHT_TYPE_GEO_STR "GEO"
#define LSP_EDGE_WEIGHT_TYPE_ATT_STR "ATT"
#define LSP_EDGE_WEIGHT_TYPE_XRAY1_STR "XRAY1"
#define LSP_EDGE_WEIGHT_TYPE_XRAY2_STR "XRAY2"
#define LSP_EDGE_WEIGHT_TYPE_SPECIAL_STR "SPECIAL"


#define LSP_EDGE_WEIGHT_FORMAT_FUNCTION "FUNCTION"
#define LSP_EDGE_WEIGHT_FORMAT_FULL_MATRIX "FULL_MATRIX"
#define LSP_EDGE_WEIGHT_FORMAT_UPPER_ROW "UPPER_ROW"
#define LSP_EDGE_WEIGHT_FORMAT_LOWER_ROW "LOWER_ROW"
#define LSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_ROW "UPPER_DIAG_ROW"
#define LSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_ROW "LOWER_DIAG_ROW"
#define LSP_EDGE_WEIGHT_FORMAT_UPPER_COL "UPPER_COL"
#define LSP_EDGE_WEIGHT_FORMAT_LOWER_COL "LOWER_COL"
#define LSP_EDGE_WEIGHT_FORMAT_UPPER_DIAG_COL "UPPER_DIAG_COL"
#define LSP_EDGE_WEIGHT_FORMAT_LOWER_DIAG_COL "LOWER_DIAG_COL"

#define LSP_EDGE_DATA_FORMAT_EDGE_LIST "EDGE_LIST"
#define LSP_EDGE_DATA_FORMAT_ADJ_LIST "ADJ_LIST"

#define LSP_NODE_COORD_TYPE_TWOD_COORDS "TWOD_COORDS"
#define LSP_NODE_COORD_TYPE_THREED_COORDS "THREED_COORDS"
#define LSP_NODE_COORD_TYPE_NO_COORDS "NO_COORDS"

#define LSP_DISPLAY_DATA_TYPE_COORD_DISPLAY "COORD_DISPLAY"
#define LSP_DISPLAY_DATA_TYPE_TWOD_DISPLAY "TWOD_DISPLAY"
#define LSP_DISPLAY_DATA_TYPE_NO_DISPLAY "NO_DISPLAY"

/*
 * TYPE DEF : enum -> type
 */

typedef enum LSP_Type LSP_Type;
typedef enum LSP_Edge_Weight_Type LSP_Edge_Weight_Type;
typedef enum LSP_Edge_Weight_Format LSP_Edge_Weight_Format;
typedef enum LSP_Edge_Data_Format LSP_Edge_Data_Format;
typedef enum LSP_Node_Coord_Type LSP_Node_Coord_Type;
typedef enum LSP_Display_Data_Type LSP_Display_Data_Type;


/*
 * ENUM : field -> enum
 */

enum LSP_Type
{
	e_TYPE_UNDEFINED = 0, // VALUE CANNOT BE SET (Equivalent of NULL)

	e_TSP,  // Data for a symmetric traveling salesman problem
	e_ATSP, // Data for an asymmetric traveling salesman problem
	e_SOP,  // Data for a sequential ordering problem
	e_HCP,  // Hamiltonian cycle problem data
	e_CVRP, // Capacitated vehicle routing problem data
	e_TOUR  // A collection of tours
};

enum LSP_Edge_Weight_Type
{
	e_EDGE_WEIGHT_TYPE_UNDEFINED = 0, // VALUE CANNOT BE SET (Equivalent of NULL)

	e_EXPLICIT, // Weights are listed explicitly in the corresponding section
	e_EUC_2D,   // Weights are Euclidean distances in 2-D
	e_EUC_3D,   // Weights are Euclidean distances in 3-D
	e_MAX_2D,   // Weights are maximum distances in 2-D
	e_MAX_3D,   // Weights are maximum distances in 3-D
	e_MAN_2D,   // Weights are Manhattan distances in 2-D
	e_MAN_3D,   // Weights are Manhattan distances in 3-D
	e_CEIL_2D,  // Weights are Euclidean distances in 2-D rounded up
	e_GEO,      // Weights are geographical distances
	e_ATT,      // Special distance function for problems att48 and att532
	e_XRAY1,    // Special distance function for crystallography problems (Version 1)
	e_XRAY2,    // Special distance function for crystallography problems (Version 2)
	e_SPECIAL   // There is a special distance function documented elsewhere
};

enum LSP_Edge_Weight_Format
{
	e_EDGE_WEIGHT_FORMAT_UNDEFINED = LSP_FIELD_UNDEFINED, // VALUE CANNOT BE SET (Equivalent of NULL)

	e_FUNCTION,       // Weights are given by a function (see above)
	e_FULL_MATRIX,    // Weights are given by a full matrix
	e_UPPER_ROW,      // Upper triangular matrix (row-wise without diagonal entries)
	e_LOWER_ROW,      // Lower triangular matrix (row-wise without diagonal entries)
	e_UPPER_DIAG_ROW, // Upper triangular matrix (row-wise including diagonal entries)
	e_LOWER_DIAG_ROW, // Lower triangular matrix (row-wise including diagonal entries)
	e_UPPER_COL,      // Upper triangular matrix (column-wise without diagonal entries)
	e_LOWER_COL,      // Lower triangular matrix (column-wise without diagonal entries)
	e_UPPER_DIAG_COL, // Upper triangular matrix (column-wise including diagonal entries)
	e_LOWER_DIAG_COL  // Lower triangular matrix (column-wise including diagonal entries)
};

enum LSP_Edge_Data_Format
{
	e_EDGE_DATA_FORMAT_UNDEFINED = LSP_FIELD_UNDEFINED, // VALUE CANNOT BE SET (Equivalent of NULL)

	e_EDGE_LIST, // The graph is given by an edge list
	e_ADJ_LIST   // The graph is given as an adjacency list
};

enum LSP_Node_Coord_Type
{
	e_NODE_COORD_TYPE_UNDEFINED = LSP_FIELD_UNDEFINED, // VALUE CANNOT BE SET (Equivalent of NULL)

	e_TWOD_COORDS,   // Nodes are specified by coordinates in 2-D
	e_THREED_COORDS, // Nodes are specified by coordinates in 3-D
	e_NO_COORDS      // The nodes do not have associated coordinates
};

enum LSP_Display_Data_Type
{
	e_DISPLAY_DATA_TYPE_UNDEFINED = LSP_FIELD_UNDEFINED, // VALUE CANNOT BE SET (Equivalent of NULL)

	e_COORD_DISPLAY, // Display is generated from the node coordinates
	e_TWOD_DISPLAY,  // Explicit coordinates in 2-D are given
	e_NO_DISPLAY     // No graphical display is possible
};

#endif // LSP_FIELDS_ENUMS_H
