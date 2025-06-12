// TODO implementation
#include "iconFactory.h"

Icon IconFactory::createIcon(const std::vector<std::string>& asciiArt, Color color) {
    Icon icon;
    for (const auto& line : asciiArt) {
        std::vector<Cell> row;
        for (char ch : line) {
            row.emplace_back(color, std::string(1, ch));
        }
        icon.push_back(row);
    }
    return icon;
}
                    