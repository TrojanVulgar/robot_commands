#include "robot.h"
#include "tabletop.h"
#include "helpers.h"

namespace ToyRobot
{
    //used as an interface to supply instructions as text, robot will perform
    bool Robot::command(std::string instruction)
    {
        std::istringstream iss(instruction);
        std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

        if (this->commandList.count(tokens[0]) > 0) //is the first token, a valid command?
        {
            //command is valid
            if (tokens[0] == "PLACE")
            { //check if there are valid arguments
                if (tokens.size() < 2)
                {
                    std::cout << "Error! Not enough arguments for 'PLACE'\n";
                    return false;
                }
                else
                {
                    try
                    {
                        uint8_t arg1 = std::stoi(split(tokens[1], ",")[0]);
                        uint8_t arg2 = std::stoi(split(tokens[1], ",")[1]);
                        std::string arg3 = split(tokens[1], ",")[2];
                        this->place(arg1, arg2, arg3);
                    }
                    catch (...)
                    {
                        return false;
                    }

                    return true;
                }
            }
            else if (tokens[0] == "MOVE")
            {
                this->move();
            }
            else if (tokens[0] == "LEFT" || tokens[0] == "RIGHT")
            {
                this->rotate(tokens[0]);
            }
            else if (tokens[0] == "REPORT")
            {
                this->printStatus();
            }

            return true;
        }
        else
            return false;
    }

    //checks if a given position is valid (used only by other methods)
    bool Robot::isValidPosition(uint8_t x, uint8_t y)
    {
        if (x < 0 || x > TABLETOP_MAX_X || y < 0 || y > TABLETOP_MAX_Y)
            return false;
        else
            return true;
    }

    //places robot, ignores invalid positions
    bool Robot::place(uint8_t x_place_pos, uint8_t y_place_pos, std::string facingDirection)
    {
        if (x_place_pos < 0 || x_place_pos > TABLETOP_MAX_X || y_place_pos < 0 || y_place_pos > TABLETOP_MAX_Y)
            return false;

        if (this->facingDirections.count(facingDirection) == 0) //check if given facing direction was valid
            return false;

        this->x_pos = x_place_pos;
        this->y_pos = y_place_pos;

        this->facingDirection = this->facingDirections[facingDirection];

        this->placed = true;
        return true;
    }

    //moves robot forward by one, ignored invalid movements
    bool Robot::move()
    {
        if (this->placed)
        {
            uint8_t sim_x = this->x_pos;
            uint8_t sim_y = this->y_pos;

            //simulate movement
            if (facingDirection == 0)
                sim_y += 1;
            else if (facingDirection == 1)
                sim_x += 1;
            else if (facingDirection == 2)
                sim_y -= 1;
            else if (facingDirection == 3)
                sim_x -= 1;

            if (isValidPosition(sim_x, sim_y))//if it was valid, set and return true
            {
                this->x_pos = sim_x;
                this->y_pos = sim_y;
                return true;
            }
            else //invalid move (would be out of bounds)
                return false;
        }
        else //not placed
            return false;
    }

    //rotates robot given a direction string
    bool Robot::rotate(std::string direction)
    {
        if (this->placed)
        {
            uint8_t sim_direction = this->facingDirection;

            if (direction == "LEFT")
                sim_direction = (sim_direction + 3) % 4; //rotate left
            else if (direction == "RIGHT")
                sim_direction = (sim_direction + 1) % 4; //rotate right
            else
                return false; //invalid input

            this->facingDirection = sim_direction;
            return true;
        }
        else //not placed
            return false;
    }

    void Robot::printStatus()
    {
        if (this->placed)
            std::cout << int(this->x_pos) << ',' << int(this->y_pos) << ',' << (this->reversedDirections[this->facingDirection]) << "\n";
        else
            std::cout << "Robot is not yet placed on the tabletop!\n";
    }
}