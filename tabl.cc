#pragma once

#include "stdafx.h"

constexpr auto TABLETOP_MAX_X = 4;
constexpr auto TABLETOP_MAX_Y = 4;

//0,0 is south west corner https://i.imgur.com/pm2XVHx.png
//Tabletop is never used, but it is here if required
class Tabletop
{
private:
    const uint8_t x_len = TABLETOP_MAX_X;
    const uint8_t y_len = TABLETOP_MAX_Y;
public:
};