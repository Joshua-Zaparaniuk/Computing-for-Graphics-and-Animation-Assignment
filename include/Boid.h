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
  
public:
  ngl::Vec3 &get_position();
  ngl::Vec3 &get_direction();
  float &get_scale();
  ngl::Vec3 &get_colour();

  int &get_lifetime();
  int &get_id();
  void remove_neighbour(const int &_id);
  std::list<int> &get_neighbours();

  void set_position(const ngl::Vec3 &position);
  void set_direction(const ngl::Vec3 &direction);
  void set_colour(const ngl::Vec3 &colour);
  void set_neighbour(const int &neighbour);
  void set_lifetime(const int &lifetime);
  void set_id(const int &id);

  ngl::Vec3 m_position={0.0f,0.0f,0.0f};

private:
  std::list<int> m_neighbours;
  ngl::Vec3 m_direction={0.0f,1.0f,0.0f};
  ngl::Vec3 m_colour={1.0f,0.0f,0.0f};
  float m_scale = 1.0f;
  int m_lifetime= 0;
  int m_id;
};

#endif