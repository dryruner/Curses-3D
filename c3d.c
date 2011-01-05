/* Ncurses 3D library				*/
/* Coded by ircsurfer33(at)gmail(dot)com	*/
/*						*/
/* Dependencies:				*/
/* Ncurses					*/

#include "c3d.h"

#define TRUE 1
#define FALSE 0

#define VERTGRAPHIC "X"
#define LINEGRAPHIC "O"

#define DEBUG FALSE


/* Render a line! Connect those dots! */
void renderLine(float *x1, float *y1, float *x2, float *y2)
{
	float slope=0;
	float line_x=0, line_y=0;
	float xcrd=0, ycrd=0;
	
	if(abs((*y2-*y1)) <= abs((*x2-*x1))){
	
		slope = (*y2-*y1)/(*x2-*x1);
		
		if(*x2 > *x1){
			for(line_x=*x1; line_x < *x2; line_x+=1){
				ycrd = (slope*(line_x-*x1)+*y1)*-1;

				mvprintw(ceil(ycrd)+SCRYMID, line_x+SCRXMID, LINEGRAPHIC);
			}
		}
		else
		{
			for(line_x=*x1; line_x > *x2; line_x-=1){
				ycrd = (slope*(line_x-*x1)+*y1)*-1;

				mvprintw(ceil(ycrd)+SCRYMID, line_x+SCRXMID, LINEGRAPHIC);
			}
		}
	}
	else
	{
		slope = (*x2-*x1)/(*y2-*y1);
		
		if(*y2 > *y1){
			for(line_y=*y1; line_y < *y2; line_y+=1){
				xcrd = (slope*(line_y-*y1)+*x1);
			
				mvprintw(line_y+SCRYMID, ceil(xcrd)+SCRXMID, LINEGRAPHIC);
			}
			
		}
		else
		{
			for(line_y=*y1; line_y > *y2; line_y-=1){
				xcrd = (slope*(line_y-*y1)+*x1);
			
				mvprintw(line_y+SCRYMID, ceil(xcrd)+SCRXMID, LINEGRAPHIC);
			}
			
		}
	}
	
}


/* Convert 3D points to 2D points */
struct POINT * _3dTo2dprojection(struct VERTEX *cam, struct VERTEX *verts, int total_vertices, int *total_points)
{
	if(cam == NULL || verts == NULL || total_vertices < 1)
		return NULL;

	struct POINT *newpoints = (struct POINT *)malloc(sizeof(struct POINT)*total_vertices);
	
	int cur_vert=0;
	
	for(cur_vert = 0; cur_vert < total_vertices; cur_vert+=1){
		
		if(verts[cur_vert].z > 0){
			newpoints[cur_vert].x = ((verts[cur_vert].x+cam->x) * cam->z)/verts[cur_vert].z;
			newpoints[cur_vert].y = ((verts[cur_vert].y+cam->y) * cam->z)/verts[cur_vert].z;
			
			*total_points += 1;
		}
	}
	
	
	
	return 	newpoints;
}


int renderVertices(struct POINT *points, int total_points)
{
	int cur_point=0;
	
	if(points == NULL || total_points < 1)
		return -1;
	
	for(cur_point = 0; cur_point < total_points; cur_point+=1){
		
		mvprintw(points[cur_point].y+SCRYMID, points[cur_point].x+SCRXMID, VERTGRAPHIC);
	}
	
	return 0;
}


/* Render polygons */
int renderPolygons(struct FACE *face, struct POINT *curpoint, int total_polygons)
{
	int cur_poly=0;
	
	if(face == NULL || curpoint == NULL || total_polygons < 1)
		return -1;
	
	
	for(cur_poly = 0; cur_poly < total_polygons; cur_poly+=1){
		#if DEBUG == TRUE
			mvprintw(cur_poly, 0,"X1:%f Y1:%f X2:%f Y2:%f X3:%f Y3:%f",
			curpoint[face[cur_poly].a].x, 
			curpoint[face[cur_poly].a].y,
			curpoint[face[cur_poly].b].x,
			curpoint[face[cur_poly].b].y,
			curpoint[face[cur_poly].c].x,
			curpoint[face[cur_poly].c].y);
		#endif
	
		renderLine(&curpoint[face[cur_poly].a].x, &curpoint[face[cur_poly].a].y, &curpoint[face[cur_poly].b].x, &curpoint[face[cur_poly].b].y);
		renderLine(&curpoint[face[cur_poly].b].x, &curpoint[face[cur_poly].b].y, &curpoint[face[cur_poly].c].x, &curpoint[face[cur_poly].c].y);
		renderLine(&curpoint[face[cur_poly].c].x, &curpoint[face[cur_poly].c].y, &curpoint[face[cur_poly].a].x, &curpoint[face[cur_poly].a].y);
	}
	
	return 0;
}

/* This isn't working... */
int rotate(struct VERTEX *vert_array, int total_verts, float degrees)
{
	if(vert_array == NULL || total_verts < 0)
		return -1;
		
	double radians = degrees*(3.1415/180);
	float new_x, new_z;
	int cur_vert;
	
	for(cur_vert = 0; cur_vert < total_verts; cur_vert+=1){
		new_z = (vert_array[cur_vert].z * cos(radians))-(vert_array[cur_vert].x*sin(radians));
		new_x = (vert_array[cur_vert].z * sin(radians))-(vert_array[cur_vert].x*cos(radians));
		
		
		vert_array[cur_vert].x = new_x;
		vert_array[cur_vert].z = new_z;
	}
	
	return 0;
}
	
int renderModel(struct VERTEX *vertexData, int numberOfVertices, struct FACE *face_data, int numberOfFaces, struct VERTEX *camera, float degrees, int method)
{
	/* Checking stuffs */
	if(vertexData == NULL || face_data == NULL || camera == NULL){
		printf("Vertex, Face or Camera data missing.\n");
		return -1;
	}
	
	if(numberOfVertices < 1 || numberOfFaces < 1){
		printf("Not enough Vertices or Faces\n");
		 return -1;
	}
	
	/* I dont want to add this to the POINT struct, because it will make a ton of redundant copies. */
	int numberOfPoints = 0;
	
	/* Initialize the terminal screen for use */
	initscr();
	clear();
	
	/* Do the needed rotations */
	//rotate(vertexData, numberOfVertices, degrees);
	
	/* Calculate 3D to 2D projections */
	struct POINT *convertedPoints = _3dTo2dprojection(camera, vertexData, numberOfVertices, &numberOfPoints);
	
	/* Render the polygons/vertices/both */
	switch(method){	
		case 0:
			renderPolygons(face_data, convertedPoints, numberOfFaces);
			break;
		
		case 1:
			renderVertices(convertedPoints, numberOfPoints);
			break;
		
		case 2:
			renderPolygons(face_data, convertedPoints, numberOfFaces);
			renderVertices(convertedPoints, numberOfPoints);
			break;
		
		default:
			//invalid rendering method!
			mvprintw(SCRYMID, SCRXMID, ">No such method<"); 
			break;
	}
	
	/* Free mem */
	free(convertedPoints);
	
	/* See what we did */
	refresh();
	
	/* End our session */
	endwin();
	return 0;
}

/* Every thing is backwards in ncurses.... */
int controller(char input, struct VERTEX *cam)
{
	int quit = FALSE;
	
	switch(input)
	{
		case 'w':
			cam->y -= 1;
			break;
		case 's':
			cam->y += 1;
			break;
		case 'a':
			cam->x += 1;
			break;
		case 'd':
			cam->x -= 1;
			break;
		case ' ':
			cam->z -= 1;
			break;
			
		case 'q':
			quit = TRUE;
			break;
			
		default:
			break;
	}

	return quit;	
}
