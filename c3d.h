/* Ncurses 3D library				*/
/* Coded by ircsurfer33(at)gmail(dot)com	*/
/*						*/
/* Dependencies:				*/
/* Ncurses					*/

#include <ncurses.h>
#include <stdlib.h>
#include <math.h>

#define SCRXMID COLS/2
#define SCRYMID LINES/2

#define VERTGRAPHIC "X"


struct POINT
{
	float x;
	float y;
};
	
struct VERTEX
{
	float x;
	float y;
	float z;
};
	
struct FACE
{
	int a;
	int b;
	int c;
};

/* Rendering prototypes */
int renderModel(struct VERTEX *vertex_data, int numberOfVertices, struct FACE *face_data, int numberOfFaces, struct VERTEX *camera, float degrees, int method);
int renderPolygons(struct FACE *face, struct POINT *curpoint, int total_polygons);
void renderLine(float *x1, float *y1, float *x2, float *y2);
int renderVertices(struct POINT *points, int total_points);

/* Point conversion/manipulation crap */
struct POINT * _3dTo2dprojection(struct VERTEX *cam, struct VERTEX *verts, int total_vertices, int *total_points);
int rotate(struct VERTEX *vert_array, int total_verts, float degrees);

/* Controller, moves the camera around */
int controller(char input, struct VERTEX *cam);
