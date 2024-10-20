#include "main.hpp"
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

#define MAX_QUERY_LENGHT 255
#define MAX_OPERATION_LENGHT 2
#define MAX_MESSAGE_LENGHT MAX_QUERY_LENGHT + MAX_OPERATION_LENGHT +1 // +1 for null terminator


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



bool validate_regex_custom(const char* input) {

    // Check if the string is exactly 255 characters long
    if (strlen(input) > MAX_MESSAGE_LENGHT) {
        return false;
    }

    // Check if the first character is a digit
    for(int i=0; i<MAX_OPERATION_LENGHT; i++){
        if (input[i] < '0' || input[i] > '9') {
            return false;
        }
    }
    // The rest of the characters can be anything, which is already
    // ensured by the length check

    return true;
}


Message* parse_message(const char buffer[], const uint32_t count) {

    char* operation_str = (char*) malloc(MAX_OPERATION_LENGHT*sizeof(char)); // 2 bytes for the operation
    strncpy(operation_str, buffer, MAX_OPERATION_LENGHT); // copy the first 2 bytes of the buffer to the operation string
    int operation = std::stoi(operation_str, nullptr, 10); // convert the operation string to an integer

    char* query = (char*) malloc(MAX_QUERY_LENGHT*sizeof(char));

    query = (char*) &buffer[MAX_OPERATION_LENGHT];

    Message* message = new Message(operation, query);

    return message;
}


void call_operation(Message* message) {
    switch (message->operation)
    {
    case 0:
        printf("Operation not supported\n");
        break;

    case OP_GET_BY_ID:
        printf("Operation: Get by ID\n");
        break;
    
    case OP_GET_BY_USERNAME:
        printf("Operation: Get by Username\n");
        break;
    
    case OP_GET_BY_WEBISTE_MATCH:
        printf("Operation: Get by Website Match\n");
        break;
    
    default:
        printf("Unknown operation\n");
        break;
    }
}


bool handle_uart_message(const char buffer[], const uint32_t count) {
    // buffer[count] = '\0'; // Null-terminate the string

    if (!validate_regex_custom(buffer)) {
        printf("Invalid message: %s\n", buffer);
        return false;
    }

    Message* message = parse_message(buffer, count);
    message->print();

    call_operation(message);

    free(message);

    return true;
}


int main() {
    stdio_init_all();
    while (!tud_cdc_connected()) { 
        sleep_ms(100);
    }
    
    printf("Hello, Vacuus is Online and listening!\n");

    char buffer[MAX_MESSAGE_LENGHT];
    while (1) {
        if (tud_cdc_available()) {
            // all logic of the program will be here, so that when a message is received,
            // it will be processed withouth continuing to listen for other messages

            uint32_t count = tud_cdc_read(buffer, sizeof(buffer));
            buffer[count] = '\0'; // Null-terminate the string
            bool status = handle_uart_message(buffer, count);

            if(!status){
                printf("[ FORMAT ERROR ] Error processing message: %s\n", buffer);
            }
        }
        sleep_ms(100);
    }
    
    return 0;
}