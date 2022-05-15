#ifndef WINDOW_INFO_CPP
#define WINDOW_INFO_CPP

#include <iostream>
#include <SFML/Graphics.hpp>

struct WindowInfo {
    std::string title;

    int width;
    int height;

    sf::Color background_color;
};

#endif