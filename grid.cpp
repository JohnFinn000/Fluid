/*
 * =====================================================================================
 *
 *       Filename:  grid.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2013 05:30:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "grid.h"

#undef COLOR


Particle::Particle() :
    x_velocity( 0 ),
    y_velocity( 0 ),
    density( 1 ),
    R( 0 ),
    G( 0 ),
    B( 1 ) {

}

Grid::Grid() {
    size = 500;
    viscousity = VISCOUSITY;
    particle_grid = new Particle*[size];
    for( int i = 0; i < size; ++i ) {
        particle_grid[i] = new Particle[size];
        //for( int k = 0; k < size; ++k ) {
        //    particle_grid[i][k].density = 1;
        //    particle_grid[i][k].R = 0;
        //    particle_grid[i][k].G = 0;
        //    particle_grid[i][k].B = 1;
        //}
    }


}

Grid::Grid( int size, double viscousity ) {
    this->size = size;
    this->viscousity = viscousity;
    particle_grid = new Particle*[size];
    for( int i = 0; i < size; ++i ) {
        particle_grid[i] = new Particle[size];
    }
}

void Grid::push( int x, int y, float x_v, float y_v ) {
    if( x < size && y < size && x >= 0 && y >= 0 ) {
        particle_grid[x][y].x_velocity += x_v;
        particle_grid[x][y].y_velocity += y_v;
    }
}

void Grid::drop( int x, int y, float density ) {
    if( x < size && y < size && x >= 0 && y >= 0 ) {
        particle_grid[x][y].density += density;
    }
}

void Grid::ink( int x, int y, float R, float G, float B ) {
    if( x < size && y < size && x >= 0 && y >= 0 ) {
        particle_grid[x][y].R = R;
        particle_grid[x][y].G = G;
        particle_grid[x][y].B = B;
    }
}

void Grid::iterate( float time ) {

    new_grid = new Particle*[size];
    for( int i = 0; i < size; ++i ) {
        new_grid[i] = new Particle[size];
    }

    for( int i = 0; i < size; ++i ) {
        for( int k = 0; k < size; ++k ) {

            Particle *p = &particle_grid[i][k];

            //if( p->x_velocity != 0 || p->y_velocity != 0 ) { 
                float move_x = (p->x_velocity * time);
                float move_y = (p->y_velocity * time);

                double temp_x;
                double temp_y;
                double new_x = i + move_x;
                double new_y = k + move_y;

                int x;
                int y;

                float x_ratio[2];
                float y_ratio[2];

                x_ratio[1] = modf( new_x, &temp_x );
                x = (int) temp_x;
                x_ratio[0] = 1 - x_ratio[1];
                y_ratio[1] = modf( new_y, &temp_y );
                y = (int) temp_y;
                y_ratio[0] = 1 - y_ratio[1];


                /*
                *-----------*
                |       |   |
                |       |   |
                |       |   |
                |-------X---|
                |       |   |
                *-----------*
                */

                float ratios[2][2];
                ratios[0][0] = x_ratio[0] * y_ratio[0]; // maybe use heirustics for this instead
                ratios[0][1] = x_ratio[0] * y_ratio[1];
                ratios[1][0] = x_ratio[1] * y_ratio[0];
                ratios[1][1] = x_ratio[1] * y_ratio[1];

                if( x < (size-1) && y < (size-1) && x > 0 && y > 0 ) {
                    new_grid[x][y].x_velocity += p->x_velocity * ratios[0][0];
                    new_grid[x][y].y_velocity += p->y_velocity * ratios[0][0];
                    new_grid[x][y].density    += p->density    * ratios[0][0];
#ifdef COLOR
                    new_grid[x][y].R          += p->R    * ratios[0][0];
                    new_grid[x][y].G          += p->G    * ratios[0][0];
                    new_grid[x][y].B          += p->B    * ratios[0][0];
#endif
     
                    //if( (x+1) < size ) {
                        new_grid[x+1][y].x_velocity += p->x_velocity * ratios[1][0];
                        new_grid[x+1][y].y_velocity += p->y_velocity * ratios[1][0];
                        new_grid[x+1][y].density    += p->density    * ratios[1][0];
#ifdef COLOR
                        new_grid[x+1][y].R          += p->R    * ratios[1][0];
                        new_grid[x+1][y].G          += p->G    * ratios[1][0];
                        new_grid[x+1][y].B          += p->B    * ratios[1][0];
#endif

                        //if( (y+1) < size ) {
                            new_grid[x][y+1].x_velocity += p->x_velocity * ratios[0][1]; // duplicated below
                            new_grid[x][y+1].y_velocity += p->y_velocity * ratios[0][1];
                            new_grid[x][y+1].density    += p->density    * ratios[0][1];
#ifdef COLOR
                            new_grid[x][y+1].R          += p->R    * ratios[0][1];
                            new_grid[x][y+1].G          += p->G    * ratios[0][1];
                            new_grid[x][y+1].B          += p->B    * ratios[0][1];
#endif

                            new_grid[x+1][y+1].x_velocity += p->x_velocity * ratios[1][1];
                            new_grid[x+1][y+1].y_velocity += p->y_velocity * ratios[1][1];
                            new_grid[x+1][y+1].density    += p->density    * ratios[1][1];
#ifdef COLOR
                            new_grid[x+1][y+1].R          += p->R    * ratios[1][1];
                            new_grid[x+1][y+1].G          += p->G    * ratios[1][1];
                            new_grid[x+1][y+1].B          += p->B    * ratios[1][1];
#endif
                        //}
                    /*} else {
                        if( (y+1) < size ) {
                            new_grid[x][y+1].x_velocity += p->x_velocity * ratios[0][1]; // duplicated above
                            new_grid[x][y+1].y_velocity += p->y_velocity * ratios[0][1];
                            new_grid[x][y+1].density    += p->density    * ratios[0][1];
                            new_grid[x][y+1].R          += p->R    * ratios[0][1];
                            new_grid[x][y+1].G          += p->G    * ratios[0][1];
                            new_grid[x][y+1].B          += p->B    * ratios[0][1];
                        }
                    }*/
                    
                    
                }
            //} else { // This particle did not move
            //    new_grid[i][k].x_velocity = 0;
            //    new_grid[i][k].y_velocity = 0;
            //    new_grid[i][k].density    += p->density;
#ifdef COLOR
                new_grid[i][k].R          += p->R;
                new_grid[i][k].G          += p->G;
                new_grid[i][k].B          += p->B;
#endif
            //}
        }
    }

    refresh_borders();

    diffuse();

    for( int i = 0; i < size; ++i ) {
        delete[] particle_grid[i];
    }
    delete[] particle_grid;
    
    particle_grid = new_grid;

}

inline void Grid::refresh_borders() {
    for( int i = 0; i < size; ++i ) {
        new_grid[i][0].density = 1;
        new_grid[i][0].x_velocity = 0;
        new_grid[i][0].y_velocity = 0;
    }
    for( int i = 1; i < size-1; ++i ) {
        new_grid[0][i].density = 1;
        new_grid[0][i].x_velocity = 0;
        new_grid[0][i].y_velocity = 0;
    }
    for( int i = 1; i < size-1; ++i ) {
        new_grid[size-1][i].density = 1;
        new_grid[size-1][i].x_velocity = 0;
        new_grid[size-1][i].y_velocity = 0;
    }
    for( int i = 0; i < size; ++i ) {
        new_grid[i][size-1].density = 1;
        new_grid[i][size-1].x_velocity = 0;
        new_grid[i][size-1].y_velocity = 0;
    }
}

inline void Grid::diffuse() {

    for( int i = 1; i < (size-1); ++i ) {
        for( int k = 1; k < (size-1); ++k ) {

            double var = .0000001;
            float x_force = viscousity * (new_grid[i][k].density - new_grid[i+1][k].density);
            new_grid[i][k].x_velocity   += x_force / (new_grid[i][k].density >= var ? new_grid[i][k].density : var );
            new_grid[i+1][k].x_velocity += x_force / (new_grid[i+1][k].density >= var ? new_grid[i+1][k].density : var );

            float y_force = viscousity * (new_grid[i][k].density - new_grid[i][k+1].density);
            new_grid[i][k].y_velocity   += y_force / (new_grid[i][k].density >= var ? new_grid[i][k].density : var);
            new_grid[i][k+1].y_velocity += y_force / (new_grid[i][k+1].density >= var ? new_grid[i][k+1].density : var);

        }
    }

}

void Grid::display() {
    for( int i = 0; i < size; ++i ) {
        for( int k = 0; k < size; ++k ) {
            printf("(%f,%f,%f) ", particle_grid[k][i].x_velocity, particle_grid[k][i].y_velocity, particle_grid[k][i].density );
        }
        printf("\n");
    }
}














