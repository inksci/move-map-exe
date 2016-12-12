#include <windows.h>
#include <iostream>
#include <math.h>
#include <GLU.h>
#include <glut.h>
#include <gl.h>
#include <stdlib.h>
#include <stdio.h>

#include <fstream>
static GLint	imagewidth;
static GLint	imageheight;
static GLint	pixellength;
static GLubyte	* pixeldata;

/* use a named constant to approximate pi */
const float pi = 3.14159265358979;


float	red	= 1.0, blue = 1.0, green = 1.0;


float				x_move	= 20.0;
float				y_move	= 20.0;
using namespace std; ofstream	outfile;

/* mouse click */
int	mouse_left_down		= 0;
int	mouse_left_clicked	= 0;
int	mouse_right_down	= 0;
int	mouse_right_clicked	= 0;
int	mouse_x;
int	mouse_y;
void MouseClick( int button, int state, int x, int y )
{
	outfile << button << ", " << state << ", " << x << ", " << y << endl;
	switch ( button )
	{
	case GLUT_LEFT_BUTTON:
		if ( state == GLUT_DOWN )
		{
			mouse_left_down = 1;
			mouse_x		= x;
			mouse_y		= y;
			;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if ( state == GLUT_DOWN )
		{
			mouse_right_down	= 1;
			mouse_x			= x;
			mouse_y			= y;
			;
		}
		break;
	default:
		break;
	}
}


void processNormalKeys( unsigned char key, int x, int y )
{
	if ( key == 27 ) /*��ESC�˳� */
	{
		outfile.close();
		exit( 0 );
	}

	switch ( key )
	{
	case 'w':
		;
		break;

	default:
		;
		break;
	}
}


void processSpecialKeys( int key, int x, int y )
{
	switch ( key )
	{
	case GLUT_KEY_F1: red	= 1.0; green = 0.0; blue = 0.0; break;
	case GLUT_KEY_F2: red	= 0.0; green = 1.0; blue = 0.0; break;
	case GLUT_KEY_F3: red	= 0.0; green = 0.0; blue = 1.0; break;

	case GLUT_KEY_UP: y_move	= y_move + 1; break;
	case GLUT_KEY_DOWN: y_move	= y_move - 1; break;
	case GLUT_KEY_LEFT: x_move	= x_move - 1; break;
	case GLUT_KEY_RIGHT: x_move	= x_move + 1; break;
	}
	outfile << "x_move: " << x_move << endl;
	outfile << "y_move: " << y_move << endl;

}


void draw_rectangle( float l, float t, float w, float h )
{
	glBegin( GL_POLYGON );
	/* ���� ���� ���� ���� */
	glVertex2f( l, t + h );
	glVertex2f( l, t );
	glVertex2f( l + w, t );
	glVertex2f( l + w, t + h );
	glEnd();
}


void draw_line()
{
	glVertex2f( 0, 0 );
	glVertex2f( 640, 480 );
}


void open_img()
{
	/* ���ļ� */
	FILE* pfile = fopen( "C:\\Users\\Administrator\\Pictures\\map-1212.bmp", "rb" );
	if ( pfile == 0 )
		exit( 0 );
	/* ��ȡͼ���С */
	fseek( pfile, 0x0012, SEEK_SET );
	fread( &imagewidth, sizeof(imagewidth), 1, pfile );
	fread( &imageheight, sizeof(imageheight), 1, pfile );
	/* �����������ݳ��� */
	pixellength = imagewidth * 3;
	while ( pixellength % 4 != 0 )
		pixellength++;
	pixellength *= imageheight;
	/* ��ȡ�������� */
	pixeldata = (GLubyte *) malloc( pixellength );
	if ( pixeldata == 0 )
		exit( 0 );
	fseek( pfile, 54, SEEK_SET );
	fread( pixeldata, pixellength, 1, pfile );

	/* �ر��ļ� */
	fclose( pfile );
}


/*
 * --------------- setWindow ---------------------
 * define our own function to specify the window, as explained later
 */
void setWindow( GLfloat left, GLfloat right, GLfloat bottom, GLfloat top )

{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( left, right, bottom, top );
}


/* ---------------- setViewport ------------------ */
void setViewport( int left, int right, int width, int height )
/* define our own function to specify the viewport, as explained later */
{
	GLfloat bottom	= 0.5;
	GLfloat top	= 1.5;
	glViewport( left, bottom, right - left, top - bottom );
}



void myDisplay( void ) /* plot the sinc function, using world coordinates */

{
	glClear( GL_COLOR_BUFFER_BIT );
	glDrawPixels( imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();


	glColor3f( 0.0, 1.0, 0.0 );
	draw_rectangle( x_move, y_move, 10, 10 );

	glFlush();
	glutSwapBuffers();
}


void myInit( void )

{
	glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glColor3f( 0.0f, 0.0f, 0.0f );
	glLineWidth( 1.0 );
}


void main( int argc, char** argv )

{
	outfile.open( "key-down.txt" );


	open_img();
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );

	int	m_winWidth	= 800;
	int	m_winHeight	= 600;
	glutInitWindowSize( m_winWidth, m_winHeight );
	int	cx	= glutGet( GLUT_SCREEN_WIDTH );
	int	cy	= glutGet( GLUT_SCREEN_HEIGHT );


/*
 * ���贰�ڵĿ�Ⱥ͸߶ȷֱ���:m_winWidth, m_winHeight;
 * ���ô��ھ��У�
 */
	glutInitWindowPosition( (cx - m_winWidth) / 2, (cy - m_winHeight) / 2 );

	glutCreateWindow( "OpenGL-InkGrasp" );
	glutDisplayFunc( myDisplay );
	myInit();
	/* call the function to specify the window */
	setWindow( 0, 640, 0, 480 );
	/* call the function to specify the viewport */
	setViewport( 0, 640, 0, 480 );

	glutIdleFunc( myDisplay ); /* ����ʱ���õĺ���������Ⱦʱ���õĺ������ǳ���Ҫ */
	/* adding here the setting of keyboard processing */
	glutKeyboardFunc( processNormalKeys );
	glutSpecialFunc( processSpecialKeys );

	glutMouseFunc( MouseClick );
	glutMainLoop();
}


