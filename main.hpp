#include "pico/stdlib.h"

/**
 * @brief Validates the given input string against a custom regular expression.
 *
 * This function checks if the provided input string matches a predefined custom
 * regular expression pattern. It returns true if the input matches the pattern,
 * and false otherwise.
 *
 * @param input The input string to be validated.
 * @return true if the input matches the custom regular expression, false otherwise.
 */
bool validate_regex_custom(const char* input);

bool handle_uart_message(const char buffer[], const uint32_t count);