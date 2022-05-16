#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>
#include <experimental/random>

#include "WindowInfo.hpp"
#include "Cell.hpp"

class Universe : public sf::Drawable, public sf::Transformable {
    private:
        int rows;
        int columns;
        int cellSize;
        int maxCells;

        std::vector<Cell> grid;
    public:
        Universe(const WindowInfo& info, int cellSize) {
            this->cellSize = cellSize;
            this->maxCells = maxCells;

            this->rows = info.height / cellSize;
            this->columns = info.width / cellSize;

            this->grid = std::vector<Cell>();
        }

        Universe generate_random(int _maxAliveRow = -1) {
            const int MAX_ALIVE = _maxAliveRow < 0 ? this->getColumns() : _maxAliveRow;

            int maxAliveRow = MAX_ALIVE;
            for (int row = 0; row < this->getRows(); row++) {
                for (int column = 0; column < this->getColumns(); column++) {
                    CELL_STATE state = maxAliveRow > 0 ? (
                        std::experimental::randint(0, 1) == 0 ? CELL_STATE::DEAD : CELL_STATE::ALIVE
                    ) : CELL_STATE::DEAD;

                    if (state == CELL_STATE::ALIVE)
                        maxAliveRow--;

                    Cell c = Cell (
                        state,
                        sf::Vector2f(column * this->cellSize, row * this->cellSize)
                    );

                    this->grid.push_back(c);
                }
                maxAliveRow = MAX_ALIVE;
            }

            return *this;
        }

        Universe generate() {
            for (int row = 0; row < this->getRows(); row++) {
                for (int column = 0; column < this->getColumns(); column++) {
                    int index = (row * this->getColumns()) + column;

                    CELL_STATE state = (index % 2 == 0 || index % 7 == 0) ?
                        CELL_STATE::ALIVE : CELL_STATE::DEAD;

                    Cell c = Cell(
                        state,
                        sf::Vector2f(column * this->cellSize, row * this->cellSize)
                    );

                    this->grid.push_back(c);
                }
            }
            return *this;
        }

        Universe generate_empty() {
            for (int row = 0; row < this->getRows(); row++) {
                for (int column = 0; column < this->getColumns(); column++) {
                    Cell c = Cell(
                        CELL_STATE::DEAD,
                        sf::Vector2f(column * this->cellSize, row * this->cellSize)
                    );
                    this->grid.push_back(c);
                }
            }
            return *this;
        }

        void setCell(sf::Vector2i point, CELL_STATE state) {
            this->getCell(point.x, point.y)->changeState();
        }

        int getRows() const {
            return this->rows;
        }

        int getColumns() const {
            return this->columns;
        }

        Cell *getCell(int row, int column) {
            int index = (row * this->getColumns()) + column;
            return &this->grid.at(index);
        }

        Cell getCellNOREFERENCE(int row, int column) {
            int index = (row * this->getColumns()) + column;
            return this->grid.at(index);
        }

        int getNumberOfNeighbours(int row, int column) {
            int neighbours = 0;

            int startRow = row == 0 ? row : row - 1;
            int startColumn = column == 0 ? column : column - 1;

            int endRow = row == this->getRows() - 1 ? row : row + 1;
            int endColumn = column == this->getColumns() - 1 ? column : column + 1;

            for (int i = startRow; i <= endRow; i++) {
                for (int j = startColumn; j <= endColumn; j++) {
                    if (i == row && j == column) continue;

                    if (this->getCell(i, j)->getState() == CELL_STATE::ALIVE) {
                        neighbours++;
                    }
                }
            }
            return neighbours;
        }


        void life() {
            auto resultGrid = std::vector<Cell>();

            for (int row = 0; row < this->getRows(); row++) {
                for (int column = 0; column < this->getColumns(); column++) {
                    Cell c = this->getCellNOREFERENCE(row, column);

                    int x = c.getShape().getPosition().x / 20;
                    int y = c.getShape().getPosition().y / 20;

                    int neighbours = getNumberOfNeighbours(row, column);
                    if (c.getState() == CELL_STATE::ALIVE) {
                        if (neighbours < 2 || neighbours > 3) {
                            c.changeState();
                        }
                    } else {
                        if (neighbours == 3) {
                            c.changeState();
                        }
                    }

                    resultGrid.push_back(c);
                }
            }

            this->grid = resultGrid;
        }

        void render(sf::RenderTarget &target) const {
            for (int i = 0; i < this->getRows() * this->getColumns(); i++) {
                target.draw(this->grid.at(i).getShape());
            }
        }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
            states.transform *= getTransform();
            this->render(target);
        }
};

#endif
