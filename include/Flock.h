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

  void alignment(Boid &_boid);
  void cohesion(Boid &_boid);
  void separation(Boid &_boid);

  void find_neighbours(Boid &_boid);
  Boid &get_boid(const int &_id);

private:
  std::vector<Boid> m_boids;
  float m_threshold;
  std::unique_ptr<ngl::AbstractVAO> m_vao;
 
};

#endif