#include "main.hpp"
#include "./utils/operations.hpp"
#include "./utils/database.hpp"
#include "./utils/sd.hpp"
#include "pico/stdlib.h"
#include "tusb.h"
#include <cstdlib>
#include <cctype>
#include <string>
#include <iostream>



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


Message* parse_message(const char buffer[]) {

    char* operation_str = (char*) malloc((MAX_OPERATION_LENGHT+1)*sizeof(char)); // 2 bytes for the operation +1 for null terminator
    char* query = (char*) malloc((MAX_QUERY_LENGHT+1)*sizeof(char)); // N bytes for the query +1 for null terminator
    int operation = 0;

    strncpy(operation_str, buffer, MAX_OPERATION_LENGHT); // copy the first 2 bytes of the buffer to the operation string
    operation = std::stoi(operation_str, nullptr, 10); // convert the operation string to an integer
    
    strncpy(query, buffer+MAX_OPERATION_LENGHT, MAX_QUERY_LENGHT); // copy the rest of the buffer to the query string

    Message* message = new Message(operation, query);

    free(operation_str);
    free(query);

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
    
    case OP_DEBUG_DB:
        printf("Operation: Debug DB\n");
        //debug_db();
        break;

    case OP_TEST:
        printf("Operation: Test\n");
        test_sd_card();
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

    Message* message = parse_message(buffer);
    // message->print();

    call_operation(message);

    free(message);

    return true;
}


int main() {
    stdio_init_all();
    while (!tud_cdc_connected()) { 
        sleep_ms(100);
    }

    // if(!init_sd()){
    //     printf("Failed to initialize SD card\n");
    //     return 1;
    // }
    
    printf("Hello, Vacuus is Online and listening!\n");

    char buffer[MAX_MESSAGE_LENGHT];
    while (1) {
        if (tud_cdc_available()) {
            // all logic of the program will be here, so that when a message is received,
            // it will be processed withouth continuing to listen for other messages

            uint32_t count = tud_cdc_read(buffer, sizeof(buffer)-1); // -1 to leave space for null terminator placed next line
            buffer[count] = '\0'; // Null-terminate the string
            
            // clear the input buffer as exceeding characters could be read in the next message
            while (tud_cdc_available()) {
                tud_cdc_read_flush();
            }

            bool status = handle_uart_message(buffer, count);

            if(!status){
                printf("[ FORMAT ERROR ] Error processing message: %s\n", buffer);
            }
        }
        sleep_ms(100);
    }
    
    return 0;
}