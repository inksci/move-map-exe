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


float				x_move	= 548;
float				y_move	= 149;
float x_target=509;
float y_target=442;
using namespace std; ofstream	outfile;

/* mouse click */
int	mouse_left_down		= 0;
int	mouse_left_clicked	= 0;
int	mouse_right_down	= 0;
int	mouse_right_clicked	= 0;
int	mouse_x;
int	mouse_y;



// reading a text file  
   #include <iostream>  
   #include <fstream>  
   #include <stdlib.h> 

void run_as_load();


//切割字符串
#include <sstream>
#include <string>
#include <iostream>

void myDisplay( void );

void MouseClick( int button, int state, int x, int y )
{
	outfile << button << ", " << state << ", " << x << ", " << y << endl;
	switch ( button )
	{
	case GLUT_LEFT_BUTTON:
		if ( state == GLUT_DOWN )
		{
			//mouse_left_down = 1;
			mouse_x		= x;
			mouse_y		= y;
			x_move=x;
			y_move=600-y;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if ( state == GLUT_DOWN )
		{
			//mouse_right_down	= 1;
			mouse_x			= x;
			mouse_y			= y;
			x_target=x;
			y_target=600-y;
		}
		break;
	default:
		break;
	}
}


void processNormalKeys( unsigned char key, int x, int y )
{
	if ( key == 27 ) /*按ESC退出 */
	{
		outfile.close();
		exit( 0 );
	}

	switch ( key )
	{
	case 'w':
		run_as_load();
		;
		break;

	default:
		;
		break;
	}
}

void run_as_load(){
	string str_data="";

	// read data from file
	// move x,y by data
	char buffer[256];  
       ifstream in("data_run.txt");  
       if (! in.is_open())  
       { cout << "Error opening file"; exit (1); }  
       while (!in.eof() )  
       {  
           in.getline (buffer,100);  
           //cout << buffer << endl;  
		   str_data=buffer;
		   //cout << str_data.c_str() << endl;

		   int x1=atoi(str_data.substr(3,3).c_str());
		   int y1=atoi(str_data.substr(7,3).c_str());
		   int x2=atoi(str_data.substr(11,3).c_str());
		   int y2=atoi(str_data.substr(15,3).c_str());
		   //int direction=atoi(str_data.substr(21,1).c_str());
		   cout<<x1<<endl;
		   cout<<y1<<endl;
		   cout<<x2<<endl;
		   cout<<y2<<endl;
		   //cout<<direction<<endl;
		   x_target=x1;
		   y_target=y1;
		   x_move=x2;
		   y_move=y2;
		   //Sleep(50);
		   myDisplay();
       } 

	   
}
void processSpecialKeys( int key, int x, int y )
{
	// up down left right: 0 1 2 3
	int key_control=-1;
	switch ( key )
	{
	case GLUT_KEY_F1: red	= 1.0; green = 0.0; blue = 0.0; break;
	case GLUT_KEY_F2: red	= 0.0; green = 1.0; blue = 0.0; break;
	case GLUT_KEY_F3: red	= 0.0; green = 0.0; blue = 1.0; break;

	case GLUT_KEY_UP: y_move	= y_move + 1; key_control=0; break;
	case GLUT_KEY_DOWN: y_move	= y_move - 1; key_control=1; break;
	case GLUT_KEY_LEFT: x_move	= x_move - 1; key_control=2; break;
	case GLUT_KEY_RIGHT: x_move	= x_move + 1; key_control=3; break;
	}
	//outfile << "x_move: " << x_move << endl;
	//outfile << "y_move: " << y_move << endl;
	outfile<<"{ ("<<x_target<<","<<y_target<<","<<x_move<<","<<y_move<<"): "<<key_control<<" }"<<endl;

}


void draw_rectangle( float l, float t, float w, float h )
{
	glBegin( GL_POLYGON );
	/* 左下 左上 右上 右下 */
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
	/* 打开文件 */
	FILE* pfile = fopen( "map-1213.bmp", "rb" );
	if ( pfile == 0 )
		exit( 0 );
	/* 读取图像大小 */
	fseek( pfile, 0x0012, SEEK_SET );
	fread( &imagewidth, sizeof(imagewidth), 1, pfile );
	fread( &imageheight, sizeof(imageheight), 1, pfile );
	/* 计算像素数据长度 */
	pixellength = imagewidth * 3;
	while ( pixellength % 4 != 0 )
		pixellength++;
	pixellength *= imageheight;
	/* 读取像素数据 */
	pixeldata = (GLubyte *) malloc( pixellength );
	if ( pixeldata == 0 )
		exit( 0 );
	fseek( pfile, 54, SEEK_SET );
	fread( pixeldata, pixellength, 1, pfile );

	/* 关闭文件 */
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

	glColor3f( 1.0, 0.0, 0.0 );
	draw_rectangle( x_target, y_target, 10, 10 );

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
 * 假设窗口的宽度和高度分别是:m_winWidth, m_winHeight;
 * 设置窗口居中：
 */
	glutInitWindowPosition( (cx - m_winWidth) / 2, (cy - m_winHeight) / 2 );

	glutCreateWindow( "OpenGL-InkGrasp" );
	glutDisplayFunc( myDisplay );
	myInit();
	/* call the function to specify the window */
	setWindow( 0, 800, 0, 600 );
	/* call the function to specify the viewport */
	setViewport( 0, 800, 0, 600 );

	glutIdleFunc( myDisplay ); /* 空闲时调用的函数，即渲染时调用的函数，非常重要 */
	/* adding here the setting of keyboard processing */
	glutKeyboardFunc( processNormalKeys );
	glutSpecialFunc( processSpecialKeys );

	glutMouseFunc( MouseClick );
	glutMainLoop();
}