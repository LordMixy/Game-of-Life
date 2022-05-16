#include <SFML/Graphics.hpp>

#include "./lib/WindowInfo.hpp"
#include "./lib/Universe.hpp"
#include "./lib/Cell.hpp"

CellBase Cell::CELL_BASE = CellBase {
    sf::Color::Black, // vita
    sf::Color::White, // morte
    20                // miracoli
};

int main() {
    const WindowInfo programInfo = WindowInfo {
        (std::string) "Game of Life",
        700,
        500,
        sf::Color::White
    };

    sf::RenderWindow window(
        sf::VideoMode(programInfo.width, programInfo.height), programInfo.title
    );
    window.setFramerateLimit(5);

    Universe uny = Universe(programInfo, Cell::CELL_BASE.size).generate_empty();

    std::cout << uny.getRows() << std::endl;
    std::cout << uny.getColumns() << std::endl;

    bool life = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                case sf::Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x / Cell::CELL_BASE.size;
                        int y = event.mouseButton.y / Cell::CELL_BASE.size;
                        uny.setCell(sf::Vector2i(y, x), CELL_STATE::ALIVE);
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        life = !life;
                        std::cout << "LIFE: " << life << std::endl;
                    }
                }
            }
        }

        if (life) {
            uny.life();
        }

        window.clear(programInfo.background_color);
        window.draw(uny);
        window.display();
    }

    return 0;
}
