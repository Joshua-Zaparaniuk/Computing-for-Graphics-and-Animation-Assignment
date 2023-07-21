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

void Flock::add_boids(const int &_num_boids)
{
  for(int i=0; i<_num_boids; ++i)
  {
    Boid b;
    m_boids.push_back(b);
  }
}

void Flock::edges(Boid &_boid)
{
  ngl::Vec3 new_dir = _boid.get_direction();
  ngl::Vec3 new_pos = _boid.get_position();

  if(_boid.get_position()[0]>(m_tank_radius.m_x + m_tank_pos.m_x) )
  {
    new_dir[0] *= -1*m_speed_loss;
    new_pos.m_x = (m_tank_radius.m_x + m_tank_pos.m_x) - ( _boid.get_position().m_x
                                                          - (m_tank_radius.m_x + m_tank_pos.m_x));
  }
  if ( _boid.get_position()[0]<(-1*(m_tank_radius.m_x + m_tank_pos.m_x)) )
  {
    new_dir[0] *= -1*m_speed_loss;
    new_pos.m_x = (m_tank_radius.m_x + m_tank_pos.m_x) + ( -1*(m_tank_radius.m_x + m_tank_pos.m_x) -
                                        _boid.get_position().m_x);
  }
  if(_boid.get_position()[1]>(m_tank_radius.m_y + m_tank_pos.m_y) )
  {
    new_dir[1] *= -1*m_speed_loss;
    new_pos.m_y = (m_tank_radius.m_y + m_tank_pos.m_y) - ( _boid.get_position().m_y
                                                          - (m_tank_radius.m_y + m_tank_pos.m_y));
  }
  if ( _boid.get_position()[1]<(-1*(m_tank_radius.m_y + m_tank_pos.m_y)) )
  {
    new_dir[1] *= -1*m_speed_loss;
    new_pos.m_y = (m_tank_radius.m_y + m_tank_pos.m_y) + ( -1*(m_tank_radius.m_y + m_tank_pos.m_y) -
                                                          _boid.get_position().m_y);
  }
  if(_boid.get_position()[2]>(m_tank_radius.m_z + m_tank_pos.m_z) )
  {
    new_dir[2] *= -1*m_speed_loss;
    new_pos.m_z = (m_tank_radius.m_z + m_tank_pos.m_z) - ( _boid.get_position().m_z
                                                          - (m_tank_radius.m_z + m_tank_pos.m_z));
  }
  if ( _boid.get_position()[2]<(-1*(m_tank_radius.m_z + m_tank_pos.m_z)) )
  {
    new_dir[2] *= -1*m_speed_loss;
    new_pos.m_z = (m_tank_radius.m_z + m_tank_pos.m_z) + ( -1*(m_tank_radius.m_z + m_tank_pos.m_z) -
                                                          _boid.get_position().m_z);
  }
    _boid.set_direction(new_dir);
    _boid.set_position(new_pos);
}

size_t Flock::getNumParticles() const
{
  return m_boids.size();
}

void Flock::update()
{
  for (auto &boid : m_boids)
  {
    ngl::Vec3 aligned = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 cohesive = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 separated = {0.0f, 0.0f, 0.0f};

    if (m_alignment)
    {
      aligned = alignment(boid) * m_alignment_inf;
    }
    if (m_cohesion)
    {
      cohesive = cohesion(boid) * m_cohesion_inf;
    }
    if (m_separation)
    {
       separated = separation(boid) * m_separation_inf;
    }

    boid.set_acceleration(separated + cohesive + aligned);
    boid.get_position() += boid.get_direction() * m_dt;
    boid.get_direction() += (boid.get_acceleration()) + m_gravity * m_dt * 0.2f;
    edges(boid);
    boid.set_acceleration({0.0f,0.0f,0.0f});

  }
}

void Flock::render() const
{
  glPointSize(m_boid_size);

  if (m_boids.empty())
    return;

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

void Flock::clear_boids()
{
  m_boids.erase(m_boids.begin(), m_boids.end());
}

Boid &Flock::get_boid(const int &_id)
{
  return m_boids[_id];
}


// ------------------------------------- GETTER AND SETTER METHODS --------------------------------------
void Flock::set_boid_size(const int &_size)
{
  m_boid_size = _size;
}

void Flock::set_threshold(const double &_threshold)
{
  m_threshold = _threshold;
}

void Flock::set_force(const double &_force)
{
  m_force = _force;
}

void Flock::set_speed_loss(const double &_speed_loss)
{
  m_speed_loss = _speed_loss;
}

void Flock::set_delta_time(const double &_delta_time)
{
  m_dt = _delta_time;
}

void Flock::set_alignment_state(const bool &_align)
{
  m_alignment = _align;
}

void Flock::set_cohesion_state(const bool &_cohesive)
{
  m_cohesion = _cohesive;
}

void Flock::set_separation_state(const bool &_separate)
{
  m_separation = _separate;
}

void Flock::set_cohesion_factor(const double &_factor)
{
  m_cohesion_inf = _factor;
}

void Flock::set_alignment_factor(const double &_factor)
{
  m_alignment_inf = _factor;
}

void Flock::set_separation_factor(const double &_factor)
{
  m_separation_inf = _factor;
}

void Flock::set_tank_pos_x(const float &_posX)
{
  m_tank_pos.m_x = _posX;
}

void Flock::set_tank_pos_y(const float &_posY)
{
  m_tank_pos.m_y = _posY;
}

void Flock::set_tank_pos_z(const float &_posZ)
{
  m_tank_pos.m_z = _posZ;
}

void Flock::set_tank_rad_x(const float &_radX)
{
  m_tank_radius.m_x = _radX;
}

void Flock::set_tank_rad_y(const float &_radY)
{
    m_tank_radius.m_y = _radY;
}

void Flock::set_tank_rad_z(const float &_radZ)
{
    m_tank_radius.m_z = _radZ;
}

void Flock::set_emit_dir_x(const float &_emitDirX)
{
    m_emit_direction.m_x = _emitDirX;
}

void Flock::set_emit_dir_y(const float &_emitDirY)
{
    m_emit_direction.m_y = _emitDirY;
}

void Flock::set_emit_dir_z(const float &_emitDirZ)
{
    m_emit_direction.m_z = _emitDirZ;
}

void Flock::set_gravity(const float &_gravity)
{
    m_gravity.m_y = _gravity;
}
