#include "gluit.h"

extern int init_cyl();
extern void inittex();
float ang;
int mainwin, viewer;
void display(){}
void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	ViewerReshape(viewer);
}

GLuint cyl;

void grid()
{
	glPushAttrib (GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_1D);
	glBegin (GL_LINES);
	for (int i = -5; i <= 5; i++) {
		glVertex3i (-5,0,i); glVertex3i(5,0,i);
		glVertex3i (i,0,-5); glVertex3i(i,0,5);
	}
	glEnd();
	glPopAttrib();
}

void content()
{
	glClear (GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glColor3f(1,1,1);
	grid();

	glDepthMask (GL_FALSE);
	float yellow[] = {1,1,0,1};
//	glMaterialfv (GL_FRONT,GL_DIFFUSE, yellow);
	glColor3f (1,1,0);
	glPushMatrix();
	glTranslatef (2,0,0);
	glRotatef (90,-1,0,0);
	glRotatef (ang, 0,1,0);
	glScalef (1.5,1.5,5);
	glCallList (cyl);
	glPopMatrix();

	float cyan[] = {0,1,1,1};
	//glMaterialfv (GL_FRONT,GL_DIFFUSE, cyan);
	glColor3f(0,1,1);
	glPushMatrix();
	glTranslatef (-2,0,0);
	glRotatef (90,-1,0,0);
	glRotatef (ang, 0,-1,0);
	glScalef (1.5,1.5,5);
	glCallList (cyl);
	glPopMatrix();

	glDepthMask (GL_TRUE);
	glutSwapBuffers();
}
void init()
{
	glClearColor (.4,.4,.4,1);

	glEnable (GL_DEPTH_TEST);
	cyl = init_cyl();
	inittex();
	glEnable (GL_BLEND);
//	glEnable (GL_LIGHTING); glEnable (GL_LIGHT0);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable (GL_CULL_FACE);
	glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, 1);
}

void idle()
{
	static float delta = 0.3;
	ang += delta;
	if (ang > 70 || ang < -70)
		delta *= -1;
	ViewerRedisplay(viewer);
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize (400,400);
	mainwin = glutCreateWindow ("torches");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	viewer = ViewerNew (mainwin, 0,0,400,400, content);
	init();
	glutIdleFunc(idle);
	ViewerExtent (viewer, 10);
	//glDisable (GL_CULL_FACE);

	glutMainLoop();
}
