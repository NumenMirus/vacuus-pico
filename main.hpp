#include "pico/stdlib.h"
#include "tusb.h"
#include <cstdlib>
#include <cctype>
#include <string>

#define OP_ERROR -1
#define OP_GET_BY_ID 1
#define OP_GET_BY_USERNAME 2
#define OP_GET_BY_WEBISTE_MATCH 3
#define OP_DELETE_BY_ID 4
#define OP_DELETE_BY_USERNAME 5
#define OP_DELETE_BY_WEBSITE_MATCH 6
#define OP_ADD_CREDENTIALS 7
#define OP_UPDATE_CREDENTIALS 8

#define OP_DEBUG_DB 99
#define OP_TEST 98

#define MAX_QUERY_LENGHT 10 +1 // +1 for null terminator
#define MAX_OPERATION_LENGHT 2
#define MAX_MESSAGE_LENGHT MAX_QUERY_LENGHT + MAX_OPERATION_LENGHT 

typedef class Message {

    public:
        uint8_t operation;
        char query[MAX_QUERY_LENGHT];

        // constructor
        Message(uint8_t operation, const char* query) {
            this->operation = operation;
            strcpy(this->query, query);
        }

        // default constructor
        Message() {
            this->operation = 0;
            this->query[0] = '\0';
        }

        // copy constructor
        Message(const Message& other) {
            this->operation = other.operation;
            strcpy(this->query, other.query);
        }

        void print() {
            printf("Operation: %d\n", this->operation);
            printf("Query: %s\n", this->query);
        }

} Message;

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

/**
 * @brief Parses a message from the given buffer.
 * 
 * This function takes a character buffer, and parses it into a 
 * Message object. The buffer should contain a valid message format that this 
 * function can interpret.
 * 
 * @param buffer A constant character array containing the message to be parsed.
 * @return A pointer to a Message object parsed from the buffer.
 */
Message* parse_message(const char buffer[]);

/**
 * @brief Handles a UART message.
 *
 * This function processes a message received via UART. It takes a buffer
 * containing the message and the count of bytes in the buffer.
 *
 * @param buffer A constant character array containing the UART message.
 * @param count The number of bytes in the buffer.
 * @return A boolean value indicating the success or failure of the message handling.
 */
bool handle_uart_message(const char buffer[], const uint32_t count);

/**
 * @brief Executes the specified operation based on the provided message.
 * 
 * This function processes the given message and performs the corresponding
 * operation. The exact behavior depends on the content of the message.
 * 
 * @param message A pointer to a Message object that contains the details
 *                of the operation to be performed.
 */
void call_operation(Message* message);

