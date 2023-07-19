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
  for (auto &p : m_boids)
  {
    p.get_direction() = m_emit_direction * ngl::Random::randomPositiveNumber() + randomVectorOnSphere() * 10;
    p.get_direction().m_y = std::abs(p.get_direction().m_y);
  }

  m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);

}

void Flock::edge_detection(Boid &_boid)
{
  ngl::Vec3 new_dir = _boid.get_direction();
  if(_boid.get_position()[0]>=(m_tank_radius.m_x) ||
       _boid.get_position()[0]<=(-1*m_tank_radius.m_x) )
    {
        new_dir[0] *= -1*m_speed_loss;
    }
  if(_boid.get_position()[1]>=(m_tank_radius.m_y) ||
       _boid.get_position()[1]<=(-1*m_tank_radius.m_y) )
    {
        new_dir[1] *= -1*m_speed_loss;
    }
  if(_boid.get_position()[2]>=(m_tank_radius.m_z) ||
       _boid.get_position()[2]<=(-1*m_tank_radius.m_z) )
    {
        new_dir[2] *= -1*m_speed_loss;
    }
    _boid.set_direction(new_dir);
}

size_t Flock::getNumParticles() const
{
  return m_boids.size();
}

void Flock::update()
{
  float _dt = 0.03f;
  ngl::Vec3 gravity(0, -1.0f, 0);
  for (auto &boid : m_boids)
  {
    ngl::Vec3 aligned = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 cohesive = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 separated = {0.0f, 0.0f, 0.0f};

    if (m_alignment)
    {
      aligned = alignment(boid);
    }
    if (m_cohesion)
    {
      cohesive = cohesion(boid);
    }
    if (m_separation)
    {
       separated = separation(boid);
    }

    boid.set_acceleration(separated + cohesive + aligned);
    edge_detection(boid);
    boid.get_position() += boid.get_direction() * _dt;
    boid.get_direction() += (boid.get_acceleration()) + gravity * _dt * 0.2f;
    boid.set_acceleration({0.0f,0.0f,0.0f});

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
    avg_dir.clamp(m_force);
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
    avg_dir.clamp(m_force);
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
    avg_dir.clamp(m_force);
  }
  return avg_dir;
}

Boid &Flock::get_boid(const int &_id)
{
  return m_boids[_id];
}

