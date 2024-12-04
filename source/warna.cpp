#include "warna.h"
#include <string>

// Foreground (Text) Colors
const std::string Color::RED = "\033[31m";
const std::string Color::GREEN = "\033[32m";
const std::string Color::YELLOW = "\033[33m";
const std::string Color::BLUE = "\033[34m";
const std::string Color::MAGENTA = "\033[35m";
const std::string Color::CYAN = "\033[36m";
const std::string Color::WHITE = "\033[37m";
const std::string Color::GRAY = "\033[90m";

// Background Colors
const std::string Color::BG_RED = "\033[41m";
const std::string Color::BG_GREEN = "\033[42m";
const std::string Color::BG_YELLOW = "\033[43m";
const std::string Color::BG_BLUE = "\033[44m";
const std::string Color::BG_MAGENTA = "\033[45m";
const std::string Color::BG_CYAN = "\033[46m";
const std::string Color::BG_WHITE = "\033[47m";

// Text Effects
const std::string Color::BOLD = "\033[1m";
const std::string Color::UNDERLINE = "\033[4m";
const std::string Color::RESET = "\033[0m";
