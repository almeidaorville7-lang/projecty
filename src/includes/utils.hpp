/**
 * @file utils.hpp
 * @brief Contains utility functions for the project.
 */

#pragma once

#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

using std::format;

/**
 * @brief Clears the terminal using an ANSI escape code.
 */
inline void clearScreen()
{
    std::cout << "\033c";
}

/**
 * @brief Displays a message followed by a newline.
 * @param message The message to display.
 */
inline void println(const std::string &message)
{
    std::cout << message << std::endl;
}

/**
 * @brief Displays text centered within a specified width.
 * @param text The text to center.
 * @param width The total width to center the text within (defaults to 50).
 */
inline void printctr(const std::string &text, int width = 50)
{
    if (width < 0)
    {
        width = 0;
    }
    println(std::format("{:^{}}", text, width));
}

/**
 * @brief Displays a header centered between horizontal dividers.
 * @param text The header title to display.
 * @param width The total width of the header divider (defaults to 50).
 * @param dividerChar The character to use for the divider (defaults to '=').
 */
inline void printHeader(const std::string &text, int width = 50, char dividerChar = '=')
{
    if (width < 0)
    {
        width = 0;
    }
    // Create a string of the specified width filled with the divider character
    std::string divider(width, dividerChar);
    println(divider);
    printctr(text, width);
    println(divider);
}

/**
 * @brief Reads a valid integer from the user.
 * @param prompt The message to display when asking for input.
 * @returns An integer entered by the user.
 */
inline int readInt(const std::string &prompt)
{
    std::string input;

    while (true)
    {
        std::cout << prompt << std::flush;
        if (!std::getline(std::cin, input))
        {
            return -1;
        }

        try
        {
            std::size_t position = 0;
            int number = std::stoi(input, &position);

            // validates that no unexpected characters remain after parsing an integer from input
            if (input.find_first_not_of(" \t\r\n", position) != std::string::npos)
            {
                println("Please enter a valid integer.");
                continue;
            }

            return number;
        }
        catch (const std::out_of_range &)
        {
            println("Input out of range.");
        }
        catch (const std::invalid_argument &)
        {
            println("Invalid input.");
        }
    }
}

/**
 * @brief Reads a valid positive integer from the user.
 * @param prompt The message to display when asking for input.
 * @returns A positive integer entered by the user.
 */
inline int getPositiveInt(const std::string &prompt)
{
    while (true)
    {
        int number = readInt(prompt);

        if (number <= 0)
        {
            println("Please enter a positive integer.");
            continue;
        }

        return number;
    }
}

/**
 * @brief Reads a non-empty string from the user.
 * @param prompt The message to display when asking for input.
 * @returns A non-empty string entered by the user.
 */
inline std::string readString(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt << std::flush;
        std::string input;
        if (!std::getline(std::cin, input))
        {
            return "";
        }

        if (!input.empty())
        {
            return input;
        }

        println("Input cannot be empty. Please enter a valid string.");
    }
}
