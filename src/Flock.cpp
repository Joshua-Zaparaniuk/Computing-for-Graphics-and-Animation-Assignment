#include "Flock.h"
#include <ngl/Random.h>
#include <iostream>
#include <string_view>
#include <fstream>
#include <sstream>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>

ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f)
{
  float phi = ngl::Random::randomPositiveNumber(static_cast<float>(M_PI * 2.0f));
  float costheta = ngl::Random::randomNumber();
  float u = ngl::Random::randomPositiveNumber();
  float theta = acos(costheta);
  float r = _radius * std::cbrt(u);
  return ngl::Vec3(r * sin(theta) * cos(phi),
                   r * sin(theta) * sin(phi),
                   r * cos(theta));
}

Flock::Flock(size_t _numParticles)
{
  m_boids.resize(_numParticles);
  ngl::Vec3 emitDir(0, 10.0f, 0);
  for (auto &p : m_particles)
  {
    p.direction = emitDir * ngl::Random::randomPositiveNumber() + randomVectorOnSphere() * 10;
    p.direction.m_y = std::abs(p.direction.m_y);
    p.colour = ngl::Random::getRandomColour3();
  }

  m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);

}

size_t Flock::getNumParticles() const
{
  return m_boids.size();
}

void Flock::update()
{
  float _dt = 0.01f;
  ngl::Vec3 gravity(0, -9.81f, 0);
  for (auto &p : m_particles)
  {
    p.direction += gravity * _dt * 0.5f;
    p.position += p.direction * _dt;
    p.scale += 0.001f;
    if (p.position.m_y <= 0.0f)
    {
      p.position.set(0, 0, 0);
      p.direction = ngl::Vec3{0, 10, 0} * ngl::Random::randomPositiveNumber() + randomVectorOnSphere() * 10;
      p.direction.m_y = std::abs(p.direction.m_y);
      p.colour = ngl::Random::getRandomColour3();
    }
  }
}

void Flock::render() const
{
  glPointSize(4);

  m_vao->bind();
  m_vao->setData(ngl::SimpleVAO::VertexData(m_particles.size()*sizeof(Particle),m_particles[0].position.m_x ));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),3);

  m_vao->setNumIndices(m_particles.size());
  m_vao->draw();

  m_vao->unbind();
}

void Flock::dist(const ngl::Vec3 &_a, const ngl::Vec3 &_b)
{
  return std::sqrt(std::pow(_a.x - _b.x, 2) + std::pow(_a.y - _b.y, 2) +
        std::pow(_a.z - _b.z, 2));
}

void Flock::alignment(Boid &_boid)
{
  
}

void Flock::cohesion(Boid &_boid)
{

}

void Flock::separation(Boid &_boid)
{

}

Boid &Flock::get_boid(const int &_id)
{
  return m_boids[_id];
}

void Flock::find_neighbours(const &Boid)
{
  for (auto &p: m_boids)
  {
    if ( dist(p.get_position(), Boid.get_position()) <= m_treshold)
    {
      Boid.set_neighbour(p.get_id());
    }
    else
    {
      Boid.remove_neighbour(p.get_id())
    }
  }
}
