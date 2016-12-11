#include <glut.h>
#include <gl.h>
#include<stdlib.h>

#include <fstream>


float angle = 0.0;
float red=1.0, blue=1.0, green=1.0;

float x_move=0.0;
float y_move=0.0;
using namespace std;	ofstream outfile;

// mouse click
int mouse_left_down=0;
int mouse_left_clicked=0;
int mouse_right_down=0;
int mouse_right_clicked=0;
int mouse_x;
int mouse_y;

float robot_x;
float robot_y;


void changeSize(int w, int h) 
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		0.0,0.0,-1.0,
		0.0f,1.0f,0.0f);


}


void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	float width=0.1;
	float height=0.1;
	glLoadIdentity();
glTranslatef(x_move,y_move,-6.0f);
	glBegin(GL_QUADS);				//绘制正方形
	glVertex3f(-1.0f,1.0f,0.0f);	//四边形左上

	glVertex3f(-1.0f+width,1.0f,0.0f);		//右上

	glVertex3f(-1.0f+width,1.0+height,0.0f);	//右下

	glVertex3f(-1.0f,1.0+height,0.0f);	//左下
glEnd();


// mouse event
if(mouse_left_down==1){
	if(mouse_left_clicked==0){
		mouse_left_clicked=1;

		// set value
		robot_x=1;
		robot_y=1;

glLoadIdentity();
glTranslatef(0.0f,0.0f,-6.0f);
glBegin(GL_TRIANGLES);
glVertex3f(0.0f,0.0f, 0.0f);
glVertex3f(1.0f,0.0f, 0.0f);
glVertex3f(0.0f,1.0f, 0.0f);
glEnd();
	}else{
		// update value
		//robot_x
		glLoadIdentity();
glTranslatef(0.0f,0.0f,-6.0f);
glBegin(GL_TRIANGLES);
glVertex3f(0.0f,0.0f, 0.0f);
glVertex3f(1.0f,0.0f, 0.0f);
glVertex3f(0.0f,1.0f, 0.0f);
glEnd();
	}

	

}
	/*
	glRotatef(angle,0.0,1.0,0.0);
	glTranslatef(x_move,0.0f,-6.0f);

	glColor3f(red,green,blue);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5,-0.5,0.0);
	glVertex3f(0.5,0.0,0.0);
	glVertex3f(0.0,0.5,0.0);
	glEnd();


	glBegin(GL_QUADS);				//绘制正方形
	glVertex3f(-1.0f,1.0f,0.0f);	//四边形左上

	glVertex3f(1.0f,1.0f,0.0f);		//右上

	glVertex3f(1.0f,-1.0f,0.0f);	//右下

	glVertex3f(-1.0f,-1.0f,0.0f);	//左下
	*/


glLoadIdentity();
glColor3f(1,green,blue);
glTranslatef(0.0f,0.0f,-6.0f);
glBegin(GL_TRIANGLES);
glVertex3f(0.0f,0.0f, 0.0f);
glVertex3f(1.0f,0.0f, 0.0f);
glVertex3f(0.0f,1.0f, 0.0f);
glEnd();

glLoadIdentity();
glTranslatef(0.2f,0.0f,-6.0f);
glBegin(GL_TRIANGLES);
glVertex3f(0.0f,0.0f, 0.0f);
glVertex3f(1.0f,0.0f, 0.0f);
glVertex3f(0.0f,1.0f, 0.0f);
glEnd();

	glPopMatrix();
	//angle++;
	glutSwapBuffers();
}

void MouseClick(int button, int state, int x, int y)  
{ 
/*
0, 0, 44, 51
0, 1, 44, 51
0, 0, 215, 62
0, 1, 215, 62
0, 0, 57, 150
0, 1, 57, 150
0, 0, 233, 171
0, 1, 233, 171
2, 0, 43, 42
2, 1, 43, 42
2, 0, 182, 45
2, 1, 182, 45
2, 0, 45, 153
2, 1, 45, 153
2, 0, 216, 165
2, 1, 216, 165*/
	outfile<<button<<", "<<state<<", "<<x<<", "<<y<<endl;
   switch (button) {  
      case GLUT_LEFT_BUTTON:  
         if (state == GLUT_DOWN) { 
			 mouse_left_down=1;
			 mouse_x=x;
				 mouse_y=y;
            ;
			
		 }
		 //glutIdleFunc(spinDisplay);  
         break;  
      case GLUT_MIDDLE_BUTTON:  
      case GLUT_RIGHT_BUTTON:  
         if (state == GLUT_DOWN) { 
			 mouse_right_down=1;
			 mouse_x=x;
				 mouse_y=y;
            ;
		 }
		 //glutIdleFunc(NULL);  
         break;  
      default:  
         break;  
   }  
}  
void processNormalKeys(unsigned char key, int x, int y) 
{
	
	if (key == 27){  //按ESC退出
		outfile.close();
		exit(0);
	}

	switch (key) {  
      case 'w':
		  angle++;
		  break;
		  
	  default:
		  ;
		  break;
	}
}

void processSpecialKeys(int key, int x, int y) 
{
	

	switch(key) 
	{
	case GLUT_KEY_F1 : red = 1.0; green = 0.0; blue = 0.0; break;
	case GLUT_KEY_F2 : red = 0.0; green = 1.0; blue = 0.0; break;
	case GLUT_KEY_F3 : red = 0.0; green = 0.0; blue = 1.0; break;

	case GLUT_KEY_UP : y_move=y_move+0.1; break;
	case GLUT_KEY_DOWN : y_move=y_move-0.1; break;
	case GLUT_KEY_LEFT : x_move=x_move-0.1; break;
	case GLUT_KEY_RIGHT : x_move=x_move+0.1; break;
	
	}
	outfile<<"x_move: "<<x_move<<endl;
	outfile<<"y_move: "<<y_move<<endl;
/*
x_move: -1.5
...
x_move: 2.5
--------------
y_move: -3.5
...
y_move: 0.5
*/
}

void main(int argc, char **argv) 
{
	outfile.open("key-down.txt");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Lighthouse 3D - GLUT Tutorial");
	glutDisplayFunc(renderScene);  //
	/*
	glutIdleFunc设置全局的回调函数，当没有窗口事件到达时，GLUT程序功能可以执行后台处理任务或连续动画。
	如果启用，这个idle function会被不断调用，直到有窗口事件发生。
	*/
	glutIdleFunc(renderScene); //空闲时调用的函数，即渲染时调用的函数
	glutReshapeFunc(changeSize);

	//adding here the setting of keyboard processing
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutMouseFunc(MouseClick);  
   //glutMotionFunc(MouseMotion);  

	glutMainLoop(); //进入循环，该语句后面的语句不会执行
}
