#ifndef COLORS_H
#define COLORS_H

// Foreground colors
#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define BLU     "\x1B[34m"
#define MAG     "\x1B[35m"
#define CYN     "\x1B[36m"
#define WHT     "\x1B[37m"

// Background colors
#define BG_RED     "\x1B[41m"
#define BG_GRN     "\x1B[42m"
#define BG_YEL     "\x1B[43m"
#define BG_BLU     "\x1B[44m"
#define BG_MAG     "\x1B[45m"
#define BG_CYN     "\x1B[46m"
#define BG_WHT     "\x1B[47m"

// Text attributes
#define BOLD       "\x1B[1m"
#define ITALIC     "\x1B[3m"
#define UNDERLINE  "\x1B[4m"
#define BLINK      "\x1B[5m"
#define REVERSE    "\x1B[7m"

// Reset all attributes
#define RESET      "\x1B[0m"

#define COLOR_PRINT(color, text) color text RESET
#define COLOR_PRINTF(color, fmt, ...) printf(color fmt RESET, ##__VA_ARGS__)

void print_colored(const char* color, const char* text);
void print_error(const char* message);
void print_success(const char* message);
void print_warning(const char* message);
void print_info(const char* message);


#ifdef COLORS_IMPLEMENTATION

#include <stdio.h>

void print_colored(const char* color, const char* text) {
    printf("%s%s%s", color, text, RESET);
}

void print_error(const char* message) {
    print_colored(RED, message);
}

void print_success(const char* message) {
    print_colored(GRN, message);
}

void print_warning(const char* message) {
    print_colored(YEL, message);
}

void print_info(const char* message) {
    print_colored(BLU, message);
}

#endif
#endif // COLORS_H
