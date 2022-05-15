#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

enum CELL_STATE {
    ALIVE = 1,
    DEAD = 0, // poverina :(
};

struct CellBase {
    sf::Color aliveColor;
    sf::Color deadColor;
    int size;
};

class Cell {
    private:
        CELL_STATE state;
        sf::RectangleShape shape;

        void changeColorState() {
            shape.setFillColor(
                this->state == CELL_STATE::ALIVE ? 
                    Cell::CELL_BASE.aliveColor : Cell::CELL_BASE.deadColor
            );
        }
    public:
        static CellBase CELL_BASE;

        Cell(CELL_STATE state, sf::Vector2f position) {
            this->state = state;

            float size = (float) Cell::CELL_BASE.size;
            
            shape = sf::RectangleShape(sf::Vector2f(size, size));
            shape.setPosition(position);
            
            shape.setOutlineThickness(size / 20.0f);
            shape.setOutlineColor(sf::Color(220, 220, 220));

            this->changeColorState();
        }

        sf::RectangleShape getShape() const {
            return this->shape;
        }

        CELL_STATE getState() const {
            return this->state;
        }

        void changeState() {
            this->state = this->state == CELL_STATE::ALIVE ? 
                CELL_STATE::DEAD : CELL_STATE::ALIVE;

            this->changeColorState();
        }
};

#endif