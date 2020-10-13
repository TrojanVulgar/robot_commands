#pragma once

#include "stdafx.h"

namespace ToyRobot
{
    class Robot
    {
    private:
        bool placed = false;
        uint8_t x_pos = NULL;
        uint8_t y_pos = NULL;
        uint8_t facingDirection = NULL;

        const std::unordered_set<std::string> commandList = { "PLACE","MOVE","LEFT","RIGHT","REPORT" };

        std::unordered_map <std::string, int> facingDirections
            = { {"NORTH", 0}, {"EAST", 1},
                {"SOUTH", 2}, {"WEST", 3} };

        std::unordered_map <int, std::string> reversedDirections
            = { {0, "NORTH"}, {1, "EAST"},
                {2, "SOUTH"}, {3, "WEST"} };

        bool isValidPosition(uint8_t, uint8_t);
    public:
        Robot() //constructor
        {
        }

        bool command(std::string);
        bool place(uint8_t, uint8_t, std::string);
        bool move();
        bool rotate(std::string);
        void printStatus();
    };
}