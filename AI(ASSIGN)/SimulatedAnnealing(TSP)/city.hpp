

#ifndef CITY_HPP
#define CTTY_HPP

#include <cmath>
#include <string>
class City
{
public:
    int m_x;
    int m_y;

public:
    City()
    {

        m_x = rand() % 200;
        m_y = rand() % 200;
    }

    City(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    int getX()
    {
        return m_x;
    }

    int getY()
    {
        return m_y;
    }

    double distanceTo(City city)
    {
        int xDistance = fabs(getX() - city.getX());
        int yDistance = fabs(getY() - city.getY());
        double distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));
        return distance;
    }

    std::string toString()
    {
        return std::to_string(getX()) + ", " + std::to_string(getY());
    }
};

#endif