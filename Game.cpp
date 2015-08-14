#include "Game.h"

#include <gl/glew.h>
#include "Graphic/Window/Window.h"
#include <iostream>
#include <sstream>
#include "Graphic/Render/TextureManager.h"
#include "Graphic/Render/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Registry.h"


Game::Game()
{
  try
  {
    REGISTRY;
    Initialized = true;
  }
  catch (const char *e)
  {
    std::cout << e << std::endl;
    return;
  }
}

Game::~Game()
{

}


template< typename T >
std::string ToString( const T& val )
{
  std::stringstream iss;
  iss << val;
  return iss.str();
}

static void perspective(GLdouble fovY,  GLdouble aspect,  GLdouble zNear,  GLdouble zFar)
{
  const GLdouble PI = 3.1415926535897932384626433832795;

  GLdouble fW, fH;

  fH = tan(fovY / 180.0 * PI) * zNear / 2.0;

  fW = fH * aspect;

  glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

int Game::Run()
{
  if (!Initialized)
  {
    system("pause");
    return -1;
  }

  {
    glm::uvec2 size(600, 600);

    double tps = 10.0;

    PCamera cam = std::make_shared<Camera>();
    cam->UpdateProjection();

    glShadeModel( GL_SMOOTH );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      
    glClearDepth( 1.0f );              // ��������� ������� ������ �������
    glEnable( GL_DEPTH_TEST );            // ��������� ���� �������
    glDepthFunc( GL_LEQUAL );            // ��� ����� �������
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );      // ��������� � ���������� �����������

    glViewport( 0, 0, size.x, size.y );          // ����� ������� ������� ������

    glMatrixMode( GL_PROJECTION );            // ����� ������� ��������
    glLoadIdentity();              // ����� ������� ��������

    // ���������� ����������� �������������� �������� ��� ����
    //perspective( 45.0f, (GLfloat)size.x/(GLfloat)size.y, 0.1f, 100.0f );
    glLoadMatrixf(glm::value_ptr(cam->GetProject()));

    glMatrixMode( GL_MODELVIEW );            // ����� ������� ���� ������
    glLoadIdentity();              // ����� ������� ���� ������

    while(!REGISTRY.GetWindow().WindowShouldClose())
    {
      if(REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
      {
        cam->MoveX(-0.1f);
      }
      if(REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
      {
        cam->MoveX(0.1f);
      }
      if(REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
      {
        cam->MoveZ(0.1f);
      }
      if(REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_UP))
      {
        cam->MoveZ(-0.1f);
      }
      if(REGISTRY.GetWindow().GetKeyboard().IsKeyPress(GLFW_KEY_MINUS))
      {
        tps = glm::clamp(tps - 1.0, 1.0, 20.0);
      }
      if(REGISTRY.GetWindow().GetKeyboard().IsKeyPress(GLFW_KEY_EQUAL))
      {
        tps = glm::clamp(tps + 1.0, 1.0, 20.0);
      }
      float ay = REGISTRY.GetWindow().GetMouse().IsMoveX() / 30.0f;
      float ax = REGISTRY.GetWindow().GetMouse().IsMoveY() / 30.0f;

      cam->RotateX(ax);
      cam->RotateY(ay);

      cam->Update();


      //map.Draw();

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // ������� ������
      // � ������ �������
      glLoadIdentity();                               // ����� ���������

      //glLoadMatrixf(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(-1.5f,0.0f, 0.0f)) * cam->GetView()));
      glLoadMatrixf(glm::value_ptr(cam->GetView()));
      
      glTranslatef(-1.5f,0.0f,-6.0f);                 // ����� ����� � ������ ������
      glBegin(GL_TRIANGLES);                          // ������ ��������� ��������
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ���� ������������ (��������)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f(-1.0f,-1.0f, 1.0f);                  // ����� �����
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f( 1.0f,-1.0f, 1.0f);                  // ������ �����
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ���� ������������ (������)
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f( 1.0f,-1.0f, 1.0f);                  // ���� ������������ (������)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f( 1.0f,-1.0f, -1.0f);                 // ����� ������������ (������)
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ��� ������������ (�����)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f( 1.0f,-1.0f, -1.0f);                 // ���� ������������ (�����)
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f(-1.0f,-1.0f, -1.0f);                 // ����� ������������ (�����)
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ���� ������������ (����)
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f(-1.0f,-1.0f,-1.0f);                  // ���� ������������ (����)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f(-1.0f,-1.0f, 1.0f);                  // ����� ������������ (����)
      glEnd(); 

      glLoadMatrixf(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3( 5.5f,0.0f, 0.0f)) * cam->GetView()));

      glTranslatef(-1.5f,0.0f,-6.0f);                 // ����� ����� � ������ ������
      glBegin(GL_TRIANGLES);                          // ������ ��������� ��������
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ���� ������������ (��������)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f(-1.0f,-1.0f, 1.0f);                  // ����� �����
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f( 1.0f,-1.0f, 1.0f);                  // ������ �����
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ���� ������������ (������)
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f( 1.0f,-1.0f, 1.0f);                  // ���� ������������ (������)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f( 1.0f,-1.0f, -1.0f);                 // ����� ������������ (������)
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ��� ������������ (�����)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f( 1.0f,-1.0f, -1.0f);                 // ���� ������������ (�����)
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f(-1.0f,-1.0f, -1.0f);                 // ����� ������������ (�����)
      glColor3f(1.0f,0.0f,0.0f);                      // �������
      glVertex3f( 0.0f, 1.0f, 0.0f);                  // ���� ������������ (����)
      glColor3f(0.0f,0.0f,1.0f);                      // �����
      glVertex3f(-1.0f,-1.0f,-1.0f);                  // ���� ������������ (����)
      glColor3f(0.0f,1.0f,0.0f);                      // ��������
      glVertex3f(-1.0f,-1.0f, 1.0f);                  // ����� ������������ (����)
      glEnd(); 

      REGISTRY.GetWindow().SwapBuffers();
      REGISTRY.GetWindow().GetMouse().Update();
      Window::WindowSystemPollEvents();
    }
  }

  return 0;
}
