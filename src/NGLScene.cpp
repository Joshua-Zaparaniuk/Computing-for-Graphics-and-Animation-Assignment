#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Mat4.h>
#include <ngl/Util.h>

NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{
}

NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_win.width = static_cast<int>(_w * devicePixelRatio());
  m_win.height = static_cast<int>(_h * devicePixelRatio());
}

const std::string_view ParticleShader="ParticleShader";

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  m_emitter = std::make_unique<Flock>(100);
  ngl::ShaderLib::use(ngl::nglColourShader);
  m_view = ngl::lookAt({10, 10, 10}, {0, 0, 0}, {0, 1, 0});
  m_project = ngl::perspective(45.0f, 1.0f, 0.01f, 100.0f);
  ngl::ShaderLib::setUniform("MVP", m_project * m_view);

  ngl::ShaderLib::loadShader(ParticleShader,"shaders/ParticleVertex.glsl","shaders/ParticleFragment.glsl");
  ngl::ShaderLib::use(ParticleShader);
  ngl::ShaderLib::setUniform("MVP", m_project * m_view);


  startTimer(10);
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_win.width, m_win.height);
  m_emitter->render();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape:
    QGuiApplication::exit(EXIT_SUCCESS);
    break;
  case Qt::Key_Space:
    m_win.spinXFace = 0;
    m_win.spinYFace = 0;
    m_modelPos.set(ngl::Vec3::zero());

    break;
  default:
    break;
  }
  // finally update the GLWindow and re-draw

  update();
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  m_emitter->update();
  update();
}

void NGLScene::add_boids(const int &_num_boids)
{
  m_emitter->add_boids(_num_boids);
}

void NGLScene::clear_boids()
{
  m_emitter->clear_boids();
}

void NGLScene::set_alignment(const bool &state)
{
  m_emitter->set_alignment_state(state);
}

void NGLScene::set_separation(const bool &state)
{
 m_emitter->set_separation_state(state);
}

void NGLScene::set_cohesion(const bool &state)
{
 m_emitter->set_cohesion_state(state);
}

void NGLScene::set_boid_size(const int &_size)
{
 m_emitter->set_boid_size(_size);
}
void NGLScene::set_threshold(const double &_threshold)
{
 m_emitter->set_threshold(_threshold);
}
void NGLScene::set_force(const double &_force)
{
 m_emitter->set_force(_force);
}
void NGLScene::set_speed_loss(const double &_speed_loss)
{
 m_emitter->set_speed_loss(_speed_loss);
}
void NGLScene::set_delta_time(const double &_delta_time)
{
 m_emitter->set_delta_time(_delta_time);
}

void NGLScene::set_cohesion_factor(const double &_factor)
{
 m_emitter->set_cohesion_factor(_factor);
}
void NGLScene::set_alignment_factor(const double &_factor)
{
 m_emitter->set_alignment_factor(_factor);
}
void NGLScene::set_separation_factor(const double &_factor)
{
 m_emitter->set_separation_factor(_factor);
}

void NGLScene::set_tank_pos_x(const double &_posX)
{
 m_emitter->set_tank_pos_x(_posX);
}
void NGLScene::set_tank_pos_y(const double &_posY)
{
 m_emitter->set_tank_pos_y(_posY);
}
void NGLScene::set_tank_pos_z(const double &_posZ)
{
 m_emitter->set_tank_pos_z(_posZ);
}

void NGLScene::set_tank_rad_x(const double &_radX)
{
 m_emitter->set_tank_rad_x(_radX);
}
void NGLScene::set_tank_rad_y(const double &_radY)
{
 m_emitter->set_tank_rad_y(_radY);
}
void NGLScene::set_tank_rad_z(const double &_radZ)
{
 m_emitter->set_tank_rad_z(_radZ);
}

void NGLScene::set_emit_dir_x(const double &_emitDirX)
{
 m_emitter->set_emit_dir_x(_emitDirX);
}
void NGLScene::set_emit_dir_y(const double &_emitDirY)
{
 m_emitter->set_emit_dir_y(_emitDirY);
}
void NGLScene::set_emit_dir_z(const double &_emitDirZ)
{
 m_emitter->set_emit_dir_z(_emitDirZ);
}

void NGLScene::set_gravity(const double &_gravity)
{
 m_emitter->set_gravity(_gravity);
}

void NGLScene::set_defaults()
{
 m_emitter->set_boid_size(5);
 m_emitter->set_threshold(1.0);
 m_emitter->set_force(5.0);
 m_emitter->set_speed_loss(0.2);
 m_emitter->set_delta_time(0.03);

 m_emitter->set_alignment_state(false);
 m_emitter->set_cohesion_state(false);
 m_emitter->set_separation_state(false);

 m_emitter->set_cohesion_factor(0.3);
 m_emitter->set_alignment_factor(0.1);
 m_emitter->set_separation_factor(2.3);

 m_emitter->set_tank_pos_x(0.0);
 m_emitter->set_tank_pos_y(0.0);
 m_emitter->set_tank_pos_z(0.0);

 m_emitter->set_tank_rad_x(6.0);
 m_emitter->set_tank_rad_y(6.0);
 m_emitter->set_tank_rad_z(6.0);

 m_emitter->set_emit_dir_x(2.0);
 m_emitter->set_emit_dir_y(2.0);
 m_emitter->set_emit_dir_z(4.0);

 m_emitter->set_gravity(-5.5);
}
