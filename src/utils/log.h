#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =-=-=-=-= Logging =-=-=-=-=
enum TextColor
{
    TEXT_COLOR_BLACK,
    TEXT_COLOR_RED,
    TEXT_COLOR_GREEN,
    TEXT_COLOR_YELLOW,
    TEXT_COLOR_BLUE,
    TEXT_COLOR_MAGENTA,
    TEXT_COLOR_CYAN,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_COUNT
};

template<typename ...Args>

void log(char* prefix, char* msg, TextColor textColor, Args... args)
{
    static char* textColorTable[TEXT_COLOR_COUNT] =
    {
        "\x1b[30m",
        "\x1b[31m",
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[34m",
        "\x1b[35m",
        "\x1b[36m",
        "\x1b[37m",
    };

    char formatBuffer[8192] = {};
    char textBuffer[8192] = {};
    sprintf(formatBuffer, "%s %s\033[0m %s", textColorTable[textColor], prefix, msg);
    sprintf(textBuffer, formatBuffer, args...);
    puts(textBuffer);
}

#define log_warn(msg, ...) log("[Warn]", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define log_error(msg, ...) log("[Error]", msg, TEXT_COLOR_RED, ##__VA_ARGS__);
#define log_trace(msg, ...) log("[Trace]", msg, TEXT_COLOR_BLUE, ##__VA_ARGS__);