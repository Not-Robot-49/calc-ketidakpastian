#ifndef WARNA_H
#define WARNA_H

#include <string>

class Color {
public:
    // Foreground (Text) Colors
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string GRAY;

    // Background Colors
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    static const std::string BG_MAGENTA;
    static const std::string BG_CYAN;
    static const std::string BG_WHITE;

    // Text Effects
    static const std::string BOLD;
    static const std::string UNDERLINE;
    static const std::string RESET;
};

#endif // COLOR_H
