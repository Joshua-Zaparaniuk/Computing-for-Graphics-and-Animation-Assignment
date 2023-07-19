#include "Boid.h"


Boid::Boid(const ngl::Vec3 position,
         const ngl::Vec3 colour,
         const ngl::Vec3 direction,
         const float scale, const int lifetime) 
{
    m_position = position;
    m_colour = colour;
    m_direction = direction;
    m_scale = scale;
    m_lifetime = lifetime;
}

bool Boid::operator!=(Boid &_other) const
{
    return m_position!=_other.get_position();
}

ngl::Vec3 &Boid::get_position() 
{
    return m_position;
}

ngl::Vec3 &Boid::get_direction() 
{
    return m_direction;
}

ngl::Vec3 &Boid::get_colour() 
{
    return m_colour;
}

int &Boid::get_lifetime()
{
    return m_lifetime;
}

float &Boid::get_scale()
{
    return m_scale;
}

ngl::Vec3 &Boid::get_acceleration()
{
    return m_acceleration;
}

void Boid::set_position(const ngl::Vec3 &position)
{
    m_position = position;
}

void Boid::set_direction(const ngl::Vec3 &direction)
{
    m_direction = direction;
}

void Boid::set_acceleration(const ngl::Vec3 &acceleration)
{
    m_acceleration = acceleration;
}

void Boid::set_colour(const ngl::Vec3 &colour)
{
    m_colour = colour;
}


void Boid::set_lifetime(const int &lifetime)
{
    m_lifetime = lifetime;
}

Boid::~Boid()
{
}