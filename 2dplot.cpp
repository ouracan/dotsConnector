#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION

#endif


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>



const int WINDOWS_WIDTH = 640;
const int WINDOWS_HEIGHT = 480;

struct Vertex
{
  GLfloat x,y,z;
  GLfloat r, g, b, a;
};

struct Data
{
  GLfloat x,y,z;
};

void drawPoint(Vertex v1, GLfloat size){
  glPointSize(size);
  glBegin(GL_POINTS);

  glColor4f(v1.r, v1.g, v1.b, v1.a);
  glVertex3f(v1.x, v1.y, v1.z);
  
  glEnd();
}

void drawPointsDemo(int width, int height){
  GLfloat size = 5.0f;
  for(GLfloat x = 0.0f; x<=1.0f; x+= 0.2f, size+= 5)
    {
    Vertex v1 = {x, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    drawPoint(v1, size);
  }
}


void drawLineSegment(Vertex v1, Vertex v2, GLfloat width){
  glLineWidth(width);
  glBegin(GL_LINES);
  glColor4f(v1.r,v1.g,v1.b, v1.a);
  glVertex3f(v1.x, v1.y, v1.z);

  glColor4f(v2.r,v2.g,v2.b, v2.a);
  glVertex3f(v2.x, v2.y, v2.z);
  glEnd();
}


//draw the grid without the central axis

void drawGrid(GLfloat width, GLfloat height, GLfloat interval, GLfloat line_thickness){

 
  //horizontal lines
  for(float i =-height; i<height; i+=interval){
    if(i>=-0.05f&&i<=0.05f){
    Vertex v1 = {-width, i, 0.0f,1.0f,1.0f,1.0f,0.0f};
    Vertex v2 = {width, i, 0.0f,1.0f,1.0f,1.0f,0.0f};
    drawLineSegment(v1,v2,line_thickness);
    }else{
      Vertex v1 = {-width, i, 0.0f,1.0f,1.0f,1.0f,0.5f};
    Vertex v2 = {width, i, 0.0f,1.0f,1.0f,1.0f,0.5f};
    drawLineSegment(v1,v2,line_thickness);
    }

  }
  //vertical lines
  for(float i=-width; i<width; i+=interval){
    if(i>=-0.05f&&i<=0.05f){
    Vertex v1 = {i, -height, 0.0f,1.0f,1.0f,1.0f,0.0f};
    Vertex v2 = {i, height, 0.0f,1.0f,1.0f,1.0f,0.0f};
    drawLineSegment(v1,v2,line_thickness);
    }else{
      Vertex v1 = {i, -height, 0.0f,1.0f,1.0f,1.0f,0.5f};
    Vertex v2 = {i, height, 0.0f,1.0f,1.0f,1.0f,0.5f};
    drawLineSegment(v1,v2,line_thickness);
    }
  }
  
}


void drawAxis(void){
  
  //draw the x and y axis with the drawLineSegment function
  Vertex v1 = {-10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
  Vertex v2 = {10.f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
  drawLineSegment(v1,v2, 2.0f);
  Vertex v3 = {0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
  Vertex v4 = {0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
  drawLineSegment (v3,v4,2.0f);

}




void drawTriangle (Vertex v1, Vertex v2, Vertex v3){
  glBegin(GL_TRIANGLES);

  glColor4f(v1.r, v1.g, v1.b, v1.a);
  glVertex3f(v1.x,v1.y,v1.z);
  glColor4f(v2.r,v2.g,v2.b,v2.a);
  glVertex3f(v2.x,v2.y,v2.z);
  glColor4f(v3.r,v3.g,v3.b,v3.a);
  glVertex3f(v3.x,v3.y,v3.z);
  glEnd();
}

void drawTriagnleDemo (){
  Vertex v1 = {0.0f, 0.8f, 0.0f, 1.0f, 0.0f,0.0f,0.6f};
  Vertex v2 = {-1.0f, -0.8f, 0.0f, 0.0f,1.0f,0.0f,0.6f};
  Vertex v3 = {1.0f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 0.6f};
  drawTriangle(v1,v2,v3);
}

void drawLineDemo(){

  //draw a simple grid
  drawGrid(5.0f,1.0f,0.1f,0.1f);

  //draw a triangle
  drawTriagnleDemo();  

  //define the vertices and colors of the line segment
  Vertex v1 = {-5.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.7f};
  Vertex v2 = {5.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.7f};
  Vertex v3 = {0.0f,1.0f,0.0f,1.0f,0.0f,0.0f,0.7f};
  Vertex v4 = {0.0f,-1.0f,0.0f,1.0f,0.0f,0.0f,0.7f};

  //draw the line segments
  drawLineSegment(v1,v2,10.f);
  drawLineSegment(v3,v4,10.f);

  
}




//Define a generic 2D data plotting function called "draw2DscatterPlot" with the input data stream and number of points as the input

void draw2DscatterPlot(const Data *data, int num_points){

  //draw the data points one by one with the drawPoint function
  for (int i =0 ; i<num_points; i++){
    GLfloat x = data[i].x;
    GLfloat y = data[i].y;
    Vertex v ={x,y,0.0f,1.0f,1.0f,1.0f,0.5f};
    drawPoint(v,8.0f);
  }
}




//create a similar function called dotsConnect to connect the dots together with the line segments, so the curve and the points and displayed together

void dotsConnect(const Data *data, int num_points){
  for(int i =0; i<num_points-1;i++){
    GLfloat x1 = data[i].x;
    GLfloat y1 = data[i].y;
    GLfloat x2 = data[i+1].x;
    GLfloat y2 = data[i+1].y;
    Vertex v1={x1, y1, 0.0f,0.0f,1.0f,1.0f,0.5f};
    Vertex v2 = {x2, y2, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f};
    drawLineSegment(v1,v2,4.0f);
  }
}


//integrate everything into a full demo by creating the grid, generate the simulated data points using a cosine function and connect the points with lines

void linePlotDemo(float phase_shift){

  GLfloat range = 10.0f;
  const int num_points = 200;
  Data *data =(Data*)malloc(sizeof(Data)*num_points);
  for(int i = 0; i < num_points; i++)
    {
      data[i].x = ((GLfloat) i /num_points) * range-range/2.0f;
      data[i].y = 0.8f*cosf(data[i].x*3.14f+phase_shift);
    }
  draw2DscatterPlot(data,num_points);
  dotsConnect(data,num_points);
  free(data);
}


void drawString(char *string)
{

    glDisable( GL_LIGHTING );
    glColor4f(1.0f, 0.0f, 0.0f,0.9f);

    glRasterPos2f(0.9f, 0.9f);
    //void *font = GLUT_BITMAP_HELVETICA_18;
    void *font =GLUT_BITMAP_TIMES_ROMAN_24;
    for (char* c=string; *c != '\0'; c++) 
    {
        glutBitmapCharacter(font, *c); 
    }
}



int main(void)
{
  GLFWwindow* window;
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, "Primitive Drawings", NULL, NULL);

  if(!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  //Enable anti-aliasing and smoothing

  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Define loop which terminates when the window is closed.
  //and Set up viewport using the size of the window and clear color buffer

  float phase_shift = 0.0f;

  
  while(!glfwWindowShouldClose(window))
    {
      float ratio;
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      ratio = (float)width / (float)height;
      glViewport(0,0,width,height);
      glClear(GL_COLOR_BUFFER_BIT);

      //set up orthographic projection

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //call drawPointsDemo function

      //drawPointsDemo(width, height);

      //call drawLineDemo function



      //draw
      drawAxis();

      //draw grid
      drawGrid(10.0f, 1.0f, 0.1f,0.1f);

      //drawLineDemo();
      phase_shift+=0.02f;
      linePlotDemo(phase_shift);
      
      //draw strings
      drawString("Cosine wave function with phase shift");


      


      

      //swap the front and back buffers of the window and process event queue
      //such as IO to avoid lock-up

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  //release the memory and termiante the GLFW library

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
