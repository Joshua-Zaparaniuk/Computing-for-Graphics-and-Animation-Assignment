#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Flock.h"
#include "WindowParams.h"
// this must be included after NGL includes else we get a clash with gl libs
#include <QOpenGLWidget>
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QOpenGLWidget
{
    Q_OBJECT
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for our NGL drawing class
  /// @param [in] parent the parent window to the class
  //----------------------------------------------------------------------------------------------------------------------
  NGLScene(QWidget *_parent);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor must close down ngl and release OpenGL resources
  //----------------------------------------------------------------------------------------------------------------------
  ~NGLScene() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the initialize class is called once when the window is created and we have a valid GL context
  /// use this to setup any default GL stuff
  //----------------------------------------------------------------------------------------------------------------------
  void initializeGL() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------------------------------------------------
  void paintGL() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we resize the window
  //----------------------------------------------------------------------------------------------------------------------
  void resizeGL(int _w, int _h) override;

  public slots:

  void clear_boids();
  void add_boids(const int &_num_boids);

  void set_alignment(const bool &state);
  void set_cohesion(const bool &state);
  void set_separation(const bool &state);

  void set_boid_size(const int &_size);
  void set_threshold(const double &_threshold);
  void set_force(const double &_force);
  void set_speed_loss(const double &_speed_loss);
  void set_delta_time(const double &_delta_time);

  void set_cohesion_factor(const double &_factor);
  void set_alignment_factor(const double &_factor);
  void set_separation_factor(const double &_factor);

  void set_tank_pos_x(const double &_posX);
  void set_tank_pos_y(const double &_posY);
  void set_tank_pos_z(const double &_posZ);

  void set_tank_rad_x(const double &_radX);
  void set_tank_rad_y(const double &_radY);
  void set_tank_rad_z(const double &_radZ);

  void set_emit_dir_x(const double &_emitDirX);
  void set_emit_dir_y(const double &_emitDirY);
  void set_emit_dir_z(const double &_emitDirZ);

  void set_gravity(const double &_gravity);

  void set_defaults();

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Qt Event called when a key is pressed
  /// @param [in] _event the Qt event to query for size etc
  //----------------------------------------------------------------------------------------------------------------------
  void keyPressEvent(QKeyEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseMoveEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mousePressEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent(QMouseEvent *_event) override;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse wheel is moved
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void wheelEvent(QWheelEvent *_event) override;
  void timerEvent(QTimerEvent *_event) override;
  /// @brief windows parameters for mouse control etc.
  WinParams m_win;
  /// position for our model
  ngl::Vec3 m_modelPos;
  ngl::Mat4 m_view;
  ngl::Mat4 m_project;
  std::unique_ptr<Flock> m_emitter;
};

#endif
