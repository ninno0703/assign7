// TODO 
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller. 
#ifndef ICON_FACTORY_H
#define ICON_FACTORY_H
#include "icon.h"

class IconFactory {
public:
    static Icon createIcon(const std::vector<std::string>& asciiArt, Color color);
private:
    IconFactory() = default;
    ~IconFactory() = default;
};


#endif
