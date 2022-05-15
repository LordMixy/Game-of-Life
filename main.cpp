#include <SFML/Graphics.hpp>

#include "./lib/WindowInfo.hpp"
#include "./lib/Universe.hpp"
#include "./lib/Cell.hpp"

CellBase Cell::CELL_BASE = CellBase {
    sf::Color::Black, // vita
    sf::Color::White, // morte
    10                // miracoli
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

    Universe uny = Universe(programInfo, Cell::CELL_BASE.size).generate_random(2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        uny.life();

        window.clear(programInfo.background_color);
        window.draw(uny);
        window.display();
    }

    return 0;
}