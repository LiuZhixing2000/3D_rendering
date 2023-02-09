#pragma once
#include <vector>
#pragma once
#include <string>

/**
 * @brief seprate strings by backspaces
 * 
 * @param origin 
 * @return std::vector<std::string> 
 */
std::vector<std::string> seperate_string(std::string origin);

/**
 * @brief transfer numbers illustrated by string(seprated by backspaces) to doubles
 * 
 * @param origin 
 * @return std::vector<double> 
 */
std::vector<double> string2Doubles(std::string origin);