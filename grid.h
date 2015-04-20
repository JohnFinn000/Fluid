/*
 * =====================================================================================
 *
 *       Filename:  grid.h
 *
 *    Description:  grid for fluid dynamic simulator
 *
 * =====================================================================================
 */

#ifndef __GRID_H__
#define __GRID_H__

#define VISCOUSITY .001

class Particle {
private:
public:
    float x_velocity;
    float y_velocity;
    float density;
    float R;
    float G;
    float B;

    Particle();

};

class Grid {
private:
    Particle **new_grid;
public:
    int size;
    double viscousity;
    Particle **particle_grid;

    float max_density;
    float min_density;
    float average_density; 

    Grid();
    Grid( int size, double viscousity );

    void push( int x, int y, float x_v, float y_v );
    void drop( int x, int y, float density );
    void ink(  int x, int y, float R, float G, float B );
    void iterate( float time );
    void refresh_borders();
    void diffuse();

    void display();

};

#endif

