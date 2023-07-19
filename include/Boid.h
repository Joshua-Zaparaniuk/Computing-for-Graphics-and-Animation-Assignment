#ifndef BOID_H_
#define BOID_H_

#include <ngl/Vec3.h>
#include <list>

class Boid
{
public:
  Boid(const ngl::Vec3 position = {0.0f, 0.0f, 0.0f},
         const ngl::Vec3 colour = {0.0f, 0.0f, 0.0f},
         const ngl::Vec3 direction = {0.0f, 1.0f, 0.0f},
         const float scale = 1.0f, const int lifetime = 0);
  ~Boid();

  bool operator!=(Boid &_other) const;

public:
  ngl::Vec3 &get_position();
  ngl::Vec3 &get_direction();
  float &get_scale();
  ngl::Vec3 &get_colour();
  ngl::Vec3 &get_acceleration();

  int &get_lifetime();

  void set_position(const ngl::Vec3 &position);
  void set_direction(const ngl::Vec3 &direction);
  void set_colour(const ngl::Vec3 &colour);
  void set_acceleration(const ngl::Vec3 &acceleration);
  void set_lifetime(const int &lifetime);

  ngl::Vec3 m_position={0.0f,0.0f,0.0f};

private:
  ngl::Vec3 m_direction={0.0f,1.0f,0.0f};
  ngl::Vec3 m_colour={1.0f,0.0f,0.0f};
  ngl::Vec3 m_acceleration = {0.0f,0.0f,0.0f};
  float m_scale = 1.0f;
  int m_lifetime= 0;
  int m_id;
};

#endif