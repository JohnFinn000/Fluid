/*
 * =====================================================================================
 *
 *       Filename:  grid.h
 *
 *    Description:  grid for fluid dynamic simulator
 *
 *        Version:  1.0
 *        Created:  04/05/2013 01:05:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

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
    Particle **particle_grid;

    Grid();

    void push( int x, int y, float x_v, float y_v );
    void drop( int x, int y, float density );
    void ink(  int x, int y, float R, float G, float B );
    void iterate( float time );
    void refresh_borders();
    void diffuse();

    void display();

};

