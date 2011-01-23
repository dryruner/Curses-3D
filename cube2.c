/* Render cube! */

#include "c3d.h"

int main(void)
{ 
	char keyboard;
	
	struct VERTEX vert[8];
	struct FACE p[12];
	struct VERTEX cam;
	
	cam.x = 0;
	cam.y = 0;
	cam.z = 10;
	
	vert[0].x = -2.0;	vert[0].y = 2.0;	vert[0].z = 1.0;
	vert[1].x = 2.0;	vert[1].y = 2.0;	vert[1].z = 1.0;
	vert[2].x = -2.0;	vert[2].y = 2.0;	vert[2].z = 2.0;
	vert[3].x = 2.0;	vert[3].y = 2.0;	vert[3].z = 2.0;
	vert[4].x = -2.0;	vert[4].y = -2.0;	vert[4].z = 1.0;
	vert[5].x = 2.0;	vert[5].y = -2.0;	vert[5].z = 1.0;
	vert[6].x = -2.0;	vert[6].y = -2.0;	vert[6].z = 2.0;
	vert[7].x = 2.0;	vert[7].y = -2.0;	vert[7].z = 2.0;
	
	p[0].a = 0; p[0].b = 1; p[0].c = 5;
	p[1].a = 0; p[1].b = 4; p[1].c = 5;
	p[2].a = 1; p[2].b = 3; p[2].c = 5;
	

	while(!controller(getchar(), &cam)){
		renderModel(&vert[0], 8, &p[0], 3, &cam, 0, 1);
	}
	
	return 0; 
}
