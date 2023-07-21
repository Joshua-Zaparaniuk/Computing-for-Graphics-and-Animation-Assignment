#ifndef FLOCK_H_
#define FLOCK_H_

#include <cstddef>
#include <vector>
#include <list>
#include <string_view>
#include <ngl/AbstractVAO.h>
#include <memory>
#include "Boid.h"

class Flock : public Boid
{
public:
  Flock(size_t _numParticles);
  size_t getNumParticles() const;
  void update();
  void render() const;

  double dist(const ngl::Vec3 &_a, const ngl::Vec3 &_b);

  ngl::Vec3 alignment(Boid &_boid);
  ngl::Vec3 cohesion(Boid &_boid);
  ngl::Vec3 separation(Boid &_boid);

  void add_boids(const int &_num_boids);

  void edges(Boid &_boid);
  void clear_boids();

  void set_boid_size(const int &_size);
  void set_threshold(const double &_threshold);
  void set_force(const double &_force);
  void set_speed_loss(const double &_speed_loss);
  void set_delta_time(const double &_delta_time);

  void set_alignment_state(const bool &_align);
  void set_cohesion_state(const bool &_cohesive);
  void set_separation_state(const bool &_separate);

  void set_cohesion_factor(const double &_factor);
  void set_alignment_factor(const double &_factor);
  void set_separation_factor(const double &_factor);

  void set_tank_pos_x(const float &_posX);
  void set_tank_pos_y(const float &_posY);
  void set_tank_pos_z(const float &_posZ);

  void set_tank_rad_x(const float &_radX);
  void set_tank_rad_y(const float &_radY);
  void set_tank_rad_z(const float &_radZ);

  void set_emit_dir_x(const float &_emitDirX);
  void set_emit_dir_y(const float &_emitDirY);
  void set_emit_dir_z(const float &_emitDirZ);

  void set_gravity(const float &_gravity);

  Boid &get_boid(const int &_id);

private:
  std::vector<Boid> m_boids;

  int m_boid_size = 5;
  double m_threshold = 1.0f;
  double m_force = 5.0f;
  double m_speed_loss = 0.2f;
  double m_dt = 0.03f;

  bool m_alignment = true;
  bool m_cohesion = true;
  bool m_separation = true;

  double m_cohesion_inf = 0.3f;
  double m_alignment_inf = 0.1f;
  double m_separation_inf = 2.3f;

  ngl::Vec3 m_tank_pos = {0.0f, 0.0f, 0.0f};
  ngl::Vec3 m_tank_radius = {6.0f, 6.0f, 6.0f};

  ngl::Vec3 m_emit_direction = {2.0, 2.0f, 4.0f};
  ngl::Vec3 m_gravity = {0.0f, -5.5f, 0.0f};

  std::unique_ptr<ngl::AbstractVAO> m_vao;
 
};

#endif
