#include "../include/GLDraw.hpp"
#include <algorithm>

GLfloat angle;
GLDraw *GLDraw::instance = nullptr; // or maybe = NULL



//virtual methods

void GLDraw::reshape(int w, int h) 
{
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);

}

void GLDraw::idle()
{
 	//glutPostRedisplay();	
}


void GLDraw::display(void)  
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
 	glClear(GL_COLOR_BUFFER_BIT);
 		 
  glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
  glLoadIdentity();               // Reset the model-view matrix

glPushMatrix();
	glTranslatef(-9.9f, 3.0f, -10.0f);
	for( int i = 0; i<100; i++)
	{
		glRectf(0.0f, 0.0f, 0.1f, (specL[i]+specR[i])*8.0 );
		glTranslatef(0.2f, 0.0f, 0.0f);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.9f, 1.0f, -10.0f);
	for( int i = 100; i<200; i++)
	{
		
		glRectf(0.0f, 0.0f, 0.1f, (specL[i]+specR[i])*8.0 );
		glTranslatef(0.2f, 0.0f, 0.0f);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.9f, -1.0f, -10.0f);
	for( int i = 200; i<300; i++)
	{
		
		glRectf(0.0f, 0.0f, 0.1f, (specL[i]+specR[i])*8.0 );
		glTranslatef(0.2f, 0.0f, 0.0f);
	}
	glPopMatrix();	
	glPushMatrix(); 
	glTranslatef(-9.9f, -3.0f, -10.0f);
	for( int i = 300; i<400; i++)
	{
		
		glRectf(0.0f, 0.0f, 0.1f, (specL[i]+specR[i])*8.0 );
		glTranslatef(0.2f, 0.0f, 0.0f);
	}
	glPopMatrix();	
	glPushMatrix(); 
	glTranslatef(-9.9f, -5.0f, -10.0f);
	for( int i = 400; i<500; i++)
	{
		
		glRectf(0.0f, 0.0f, 0.1f, (specL[i]+specR[i])*8.0 );
		glTranslatef(0.2f, 0.0f, 0.0f);
	}
	glPopMatrix();	


}


void GLDraw::init()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);  
	//	if(isPiano)
		//	Piano obj;
}



void GLDraw::setInstance()
{
	std::cout << 	"GLDraw::setInstance() \n";
	instance = this;
}


// static
void GLDraw::displayWrapper()
{
	instance -> displayFramework();
}

void GLDraw::reshapeWrapper( int w, int h)
{
	instance -> reshape( w, h );
}

void GLDraw::runWrapper( )
{
	instance -> run( );
}

void GLDraw::displayFramework()
{
	glutPostRedisplay();
	display();
	glutSwapBuffers( );
}

 
void GLDraw::start( int argc, char *argv[] )
{

		setInstance();
		// Initialize GLUT
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(110,110);
    glutCreateWindow("simple");
    glutDisplayFunc(displayWrapper);
		glutReshapeFunc(reshapeWrapper);
		 
		init();					
		//glutIdleFunc(runWrapper);

}

void GLDraw::drawCircle(float radius)
{
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
		for (int j=0; j < 360; j++)
	 	{
			float degInRad = j*DEG2RAD;
	    glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
	  }
	glEnd(); 

}

void GLDraw::drawTriangle(float size)
{
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(size, 0.0f);
		glVertex2f(size/2.0, ( sqrt(3) * size) / 2.0 );
	glEnd();
}

void GLDraw::getData( const std::pair < std::vector <float>, std::vector <float> > pair )
{
	specL = pair. first;
	specR = pair. second;
} 

void GLDraw::getNotes( const std::list <bool> bools )
{
	int i = 0;
	for( auto it = bools. begin(); it != bools. end(); ++it)
	{
		keys[i] = (*it);
		i++;
	}
}

void GLDraw::drawSierpinski(int depth, float size, float modifier)
{

	glPushMatrix();
	if ( depth > 0 )
	{
		drawTriangle(size/3.0);
		drawSierpinski(depth-1, size/3.0, modifier);

		glTranslatef(size/3.0, 0.0f, modifier);
		drawTriangle(size/3.0);
		drawSierpinski(depth-1, size/3.0, modifier);

		glTranslatef(size/3.0, 0.0f, modifier);
		drawTriangle(size/3.0);
		drawSierpinski(depth-1, size/3.0, modifier);

    glTranslatef( -size + 0.5 * size, (sqrt(3) * size/3.0) / 2.0, modifier); 
		drawTriangle(size/3.0);	
		drawSierpinski(depth-1, size/3.0, modifier);

    glTranslatef( size/3.0, 0.0f, modifier); 
		drawTriangle(size/3.0);	
		drawSierpinski(depth-1, size/3.0, modifier);

    glTranslatef( -0.5 * size/3.0, (sqrt(3) * size/3.0) / 2.0, modifier); 
		drawTriangle(size/3.0);	
		drawSierpinski(depth-1, size/3.0, modifier);



		depth--;
	}

	glPopMatrix();

}

void GLDraw::drawPiano()
{
	int i;
	int octaves = 10;
	glPushMatrix();
	glTranslatef(-9.0f, 0.0f, -10.0f);
	for( int j = 0 ; j < octaves; j++ )
	{
		int sc = j*12;
		glColor3f(1.0f, 1.0f, 1.0f);
		drawWhite(j, keys[sc]);
		drawWhite(j, keys[sc+2]);
		drawWhite(j, keys[sc+4]);
		drawWhite(j, keys[sc+5]);
		drawWhite(j, keys[sc+7]);
		drawWhite(j, keys[sc+9]);
		drawWhite(j, keys[sc+11]);

		glTranslatef(-1.75f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawBlack(j, keys[sc+1]);
		drawBlack(j, keys[sc+3]);
		glTranslatef(0.25f, 0.0f, 0.0f);
		drawBlack(j, keys[sc+6]);
		drawBlack(j, keys[sc+8]);
		drawBlack(j, keys[sc+10]);
		glTranslatef(0.25f, 0.0f, 0.0f);
	}
	glPopMatrix();

}

void GLDraw::drawWhite(int octave, bool isPressed)
{
		if( isPressed )
			glColor3f(0.4f,0.5f,0.1f);
		glRectf(0.0f,0.0f, 0.2f, 1.0f);
		glTranslatef(0.25f, 0.0f, 0.0f);
		
		glColor3f(1.0f,1.0f,1.0f);
		
}

void GLDraw::drawBlack(int octave, bool isPressed)
{
		if( isPressed )
			glColor3f(0.4f,0.5f,0.1f);
		glRectf(0.15f,0.3f, 0.3f, 1.0f);
		glTranslatef(0.25f, 0.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 0.0f);

}

/*
 	//glutPostRedisplay();
	float size = 5.2;
	auto maxIteratorR = std::max_element(&specR[0], &specR[sampleSize]);
	float maxVVV = *maxIteratorR;
 	//glClearColor( 1.0-maxVVV*1.4, maxVVV*0.6, 1.0-maxVVV, 1.0 );
 	glClear(GL_COLOR_BUFFER_BIT);
 		 
  glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
  glLoadIdentity();               // Reset the model-view matrix
 
	glPushMatrix();
	glTranslatef(-3.0, 0.0, -10.0); // first to 3.0
	for( int i = 0; i < sampleSize;  i ++)
	{
		drawCircle(size*specL[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 0.0, -10.0); // first to 3.0
	for( int i = 0; i < sampleSize;  i ++)
	{
		drawCircle(size*specR[i]);
	}
	glPopMatrix();

	//glPushMatrix();
	glTranslatef(-3.0, 0.0, -10.0);
	//drawTriangle(size+0.8f);
	drawSierpinski(4, 6.0, maxVVV );
	//glPopMatrix();
*/





