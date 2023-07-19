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
  for (auto &p : m_boids)
  {
    p.get_direction() = emitDir * ngl::Random::randomPositiveNumber() + randomVectorOnSphere() * 10;
    p.get_direction().m_y = std::abs(p.get_direction().m_y);
    p.get_colour() = ngl::Random::getRandomColour3();
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
  for (auto &boid : m_boids)
  {
    ngl::Vec3 aligned = alignment(boid);
    ngl::Vec3 cohesive = cohesion(boid);
    ngl::Vec3 separated = separation(boid);
    boid.set_acceleration(separated + aligned + cohesive);
    boid.get_position() += boid.get_direction() * _dt;
    boid.get_direction() += (boid.get_acceleration()) * _dt * 0.2f;
    boid.set_acceleration({0.0f,0.0f,0.0f});

    /* if (boid.get_position().m_y <= 0.0f)
    {
      boid.get_position().set(0, 0, 0);
      boid.get_direction() = ngl::Vec3{0, 10, 0} * ngl::Random::randomPositiveNumber() + randomVectorOnSphere() * 10;
      boid.get_direction().m_y = std::abs(boid.get_direction().m_y);
    } */
  }
}

void Flock::render() const
{
  glPointSize(4);

  m_vao->bind();
  m_vao->setData(ngl::SimpleVAO::VertexData(m_boids.size()*sizeof(Boid), 
                 m_boids[0].m_position.m_x ));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Boid),0);
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Boid),3);

  m_vao->setNumIndices(m_boids.size());
  m_vao->draw();

  m_vao->unbind();
}

double Flock::dist(const ngl::Vec3 &_a, const ngl::Vec3 &_b)
{
  return std::sqrt(std::pow(_a.m_x - _b.m_x, 2) + std::pow(_a.m_y - _b.m_y, 2) +
        std::pow(_a.m_z - _b.m_z, 2));
}

ngl::Vec3 Flock::alignment(Boid &_boid)
{
  static ngl::Vec3 avg_dir;
  ngl::Real total=0;
  for (auto &other: m_boids)
  {
    double dist = this->dist(_boid.get_position(), other.get_position());
    if (other != _boid && dist < m_threshold)
    {
      avg_dir += other.get_direction();
      total += 1;
    }
  }
  if (total > 0)
  {
    avg_dir /= total;
    avg_dir -= _boid.get_direction();
  }
  return avg_dir;
}

ngl::Vec3 Flock::cohesion(Boid &_boid)
{
  static ngl::Vec3 avg_dir;
  ngl::Real total=0;
  for (auto &other: m_boids)
  {
    double dist = this->dist(_boid.get_position(), other.get_position());
    if (other != _boid && dist < m_threshold)
    {
      avg_dir += other.get_position();
      total += 1;
    }
  }
  if (total > 0)
  {
    avg_dir /= total;
    avg_dir -= _boid.get_position();
    avg_dir -= _boid.get_direction();
  }
  return avg_dir;
}

ngl::Vec3 Flock::separation(Boid &_boid)
{
  static ngl::Vec3 avg_dir;
  ngl::Real total=0;
  for (auto &other: m_boids)
  {
    double dist = this->dist(_boid.get_position(), other.get_position());
    if (other != _boid && dist < m_threshold)
    {
      ngl::Vec3 diff = _boid.get_position() - other.get_position();
      diff /= dist;
      avg_dir += diff;
      total += 1;
    }
  }
  if (total > 0)
  {
    avg_dir /= total;
    avg_dir -= _boid.get_direction();
  }
  return avg_dir;
}

Boid &Flock::get_boid(const int &_id)
{
  return m_boids[_id];
}

