#include <gl/glut.h>

// cylinder of radius 0.5 and height 1
// ends at Z=0 and Z=1 
int init_cyl()
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	// default GLU cylinder: along z-axis [0,height]

	// default GLU disk: on XY plane
	//gluQuadricDrawStyle(qobj, GLU_LINE); /* all polygons wireframe */
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);  // DEFAULT
	gluQuadricOrientation (qobj, GLU_OUTSIDE);

	GLuint cyl = glGenLists (1);
	glNewList(cyl, GL_COMPILE);
    glPushMatrix();
		gluCylinder(qobj, 0.25, 1.5, 1.0, 15, 1);
#if 0
		glPushMatrix();
			glTranslatef(0.0, 0.0, 1.0);
			gluDisk(qobj, 0.0, 0.5, 20, 4);
		glPopMatrix();
		glPushMatrix();
			glRotatef(180., 1.0, 0.0, 0.0);
			gluDisk(qobj, 0.0, 0.5, 20, 4);
		glPopMatrix();
#endif
	glPopMatrix();
	glEndList();
	return cyl;
}
