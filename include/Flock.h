#ifndef FLOCK_H_
#define FLOCK_H_

#include <cstddef>
#include <vector>
#include <string_view>
#include <ngl/AbstractVAO.h>
#include <memory>
#include "Boid.h"
class Flock
{
public:
  Flock(size_t _numParticles);
  size_t getNumParticles() const;
  void update();
  void render() const;

private:
  std::vector<Particle> m_particles;
  std::unique_ptr<ngl::AbstractVAO> m_vao;
 
};

#endif