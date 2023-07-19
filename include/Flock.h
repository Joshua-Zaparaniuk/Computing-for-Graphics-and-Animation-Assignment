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

  void edge_detection(Boid &_boid);

  Boid &get_boid(const int &_id);

private:
  std::vector<Boid> m_boids;
  const float m_threshold =25.0f;
  const float m_force = 12.0f;
  const float m_speed_loss = 0.2f;

  const bool m_alignment = true;
  const bool m_cohesion = true;
  const bool m_separation = true;

  ngl::Vec3 m_tank_radius = {10.0f, 10.0f, 10.0f};
  ngl::Vec3 m_emit_direction = {0.0, 10.0f, 0.0f};
  std::unique_ptr<ngl::AbstractVAO> m_vao;
 
};

#endif