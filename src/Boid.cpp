#include "Boid.h"


Boid::Boid(const ngl::Vec3 position,
         const ngl::Vec3 colour,
         const ngl::Vec3 direction = {0.0f, 1.0f, 0.0f},
         const float scale, const int lifetime) 
{
    m_position = position;
    m_colour = colour;
    m_direction = direction;
    m_scale = scale;
    m_lifetime = lifetime;
}

ngl::Vec3 Boid::get_position()
{
    return m_position;
}

ngl::Vec3 Boid::get_direction()
{
    return m_direction;
}

ngl::Vec3 Boid::get_colour()
{
    return m_colour;
}

std::list<int> Boid::get_neighbours()
{
    return this->m_neighbours;
}

int Boid::get_lifetime()
{
    return m_lifetime;
}

int Boid::get_id()
{
    return m_id;
}

int Boid::remove_neighbour(const int &_id)
{
    m_neighbours.remove_if(_id);
}

const &Boid::set_id(const int &id)
{
    m_id = id;
}

const &Boid::set_position(const ngl::Vec3 &position)
{
    >m_position = position;
}

const &Boid::set_direction(const ngl::Vec3 &direction)
{
    m_direction = direction;
}

const &Boid::set_colour(const ngl::Vec3 &colour)
{
    m_colour = colour;
}

const &Boid::set_neighbour(const int &neighbour)
{
    m_neighbours.push_back(neighbour);
}

const &Boid::set_lifetime(const int &lifetime)
{
    m_lifetime = lifetime;
}

Boid::~Boid()
{
}