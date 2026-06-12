#ifndef LSP_H
#define LSP_H

enum LSP_Type
{
	TSP,  // Data for a symmetric traveling salesman problem
	ATSP, // Data for an asymmetric traveling salesman problem
	SOP,  // Data for a sequential ordering problem
	HCP,  // Hamiltonian cycle problem data
	CVRP, // Capacitated vehicle routing problem data
	TOUR  // A collection of tours
};

enum LSP_Edge_Weight_Type
{
	EXPLICIT, //Weights are listed explicitly in the corresponding section
	EUC_2D,   // Weights are Euclidean distances in 2-D
	EUC_3D,   // Weights are Euclidean distances in 3-D
	MAX_2D,   // Weights are maximum distances in 2-D
	MAX_3D,   // Weights are maximum distances in 3-D
	MAN_2D,   // Weights are Manhattan distances in 2-D
	MAN_3D,   // Weights are Manhattan distances in 3-D
	CEIL_2D,  // Weights are Euclidean distances in 2-D rounded up
	GEO,      // Weights are geographical distances
	ATT,      // Special distance function for problems att48 and att532
	XRAY1,    // Special distance function for crystallography problems (Version 1)
	XRAY2,    // Special distance function for crystallography problems (Version 2)
	SPECIAL   // There is a special distance function documented elsewhere
};

enum LSP_Edge_Weight_Format
{
	FUNCTION,       // Weights are given by a function (see above)
	FULL_MATRIX,    // Weights are given by a full matrix
	UPPER_ROW,      // Upper triangular matrix (row-wise without diagonal entries)
	LOWER_ROW,      // Lower triangular matrix (row-wise without diagonal entries)
	UPPER_DIAG_ROW, // Upper triangular matrix (row-wise including diagonal entries)
	LOWER_DIAG_ROW, // Lower triangular matrix (row-wise including diagonal entries)
	UPPER_COL,      // Upper triangular matrix (column-wise without diagonal entries)
	LOWER_COL,      // Lower triangular matrix (column-wise without diagonal entries)
	UPPER_DIAG_COL, // Upper triangular matrix (column-wise including diagonal entries)
	LOWER_DIAG_COL  // Lower triangular matrix (column-wise including diagonal entries)
};

enum LSP_Edge_Data_Format
{
	EDGE_LIST, // The graph is given by an edge list
	ADJ_LIST   // The graph is given as an adjacency list
};

enum LSP_Node_Coord_Type
{
	TWOD_COORDS,   // Nodes are specified by coordinates in 2-D
	THREED_COORDS, // Nodes are specified by coordinates in 3-D
	NO_COORDS      // The nodes do not have associated coordinates
};

enum LSP_Display_Data_Type
{
	COORD DISPLAY, // Display is generated from the node coordinates
	TWOD DISPLAY,  // Explicit coordinates in 2-D are given
	NO DISPLAY     // No graphical display is possible
};

struct LSP_File
{
	char* name;
	enum LSP_Type type;
	char* comment;
	unsigned int dimension;
	unsigned int capacity;
};

#endif // LSP_H
