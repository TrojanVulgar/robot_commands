#include "stdafx.h"
#include "helpers.h"

//python's "split" function, implemented in C++. returns a vector of split std::strings by a specified delimiter
std::vector<std::string> split(const std::string& in, const std::string& delim)
{
    using std::string;
    using std::vector;

    string::size_type start = in.find_first_not_of(delim), end = 0;

    vector<string> out;
    while (start != in.npos)
    {
        end = in.find_first_of(delim, start);
        if (end == in.npos)
        {
            out.push_back(in.substr(start));
            break;
        }
        else
        {
            out.push_back(in.substr(start, end - start));
        }
        start = in.find_first_not_of(delim, end);
    }
    return out;
}