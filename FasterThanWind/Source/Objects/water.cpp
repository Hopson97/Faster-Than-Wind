#include "water.h"

Water::Water()
{
    for( int i = -3; i < 9 ; i++ ) {
        for ( int j = 1.7 ; j < 3.7 ; j++) {
            waterShapes.emplace_back( WaterSqaure( {
                                                        (float) i * 200,
                                                        (float) j * 200
                                                    } ) );
        }
    }
}

void Water::update(const float dt)
{
    for ( auto& w : waterShapes ) {
        w.update(dt);
    }
}

void Water::draw(sf::RenderWindow& window)
{
    for ( auto& waterShape : waterShapes ) {
        window.draw( waterShape.getSquare() );
    }
}
