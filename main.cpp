/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main
 *
 *        Version:  1.0
 *        Created:  03/02/2014 10:49:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "grid.h"

int main() {

    Grid *grid = new Grid();
    for( int i = 0; i < 100; ++i ) {
        grid->push( 5, 5, 10, 10 );
        grid->iterate( .01 );
    }
}

