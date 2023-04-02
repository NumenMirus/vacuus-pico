#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 256
#define MAX_WEBSITE_LENGTH 100

typedef struct{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char website[MAX_WEBSITE_LENGTH];
} Credentials;

bool set_credentials_username(char* username, Credentials* creds){
    if(strlen(username) < MAX_USERNAME_LENGTH) {
        strcpy(creds->username, username);
        return true;
    }else{
        printf("Wrong username length");
        return false;
    }
}

bool set_credentials_website(char* website, Credentials* creds){
    if(strlen(website) < MAX_WEBSITE_LENGTH) {
        strcpy(creds->website, website);
        return true;
    }else{
        printf("Wrong website length");
        return false;
    }
}

bool set_credentials_password(char* password, Credentials* creds){
    if(strlen(password) < MAX_PASSWORD_LENGTH) {
        strcpy(creds->password, password);
        return true;
    }else{
        printf("Wrong password length");
        return false;
    }
}

void debug_credentials(const Credentials* creds){
    printf("----[CREDS DEBUG]----\n"
           "Website: %s\n"
           "Username: %s\n"
           "Password: %s\n",
           creds->website, creds->username, creds->password);
}

// parse csv file in Credentials array
Credentials* read_credentials_into_array(FILE* file){
    int size = 0;
    int i = 0;
    fscanf(file, "%d\n", &size);

    Credentials* creds = malloc(size*sizeof(Credentials));

    while(!feof(file)){
        char* line = NULL;
        fscanf(file, "%[^|]|%[^|]|%[^\n]\n", creds[i].website, creds[i].username, creds[i].password);
        i++;
    }

    return creds;
}

int write_credentials(const Credentials* creds, FILE* file){
    return fprintf(file, "%s|%s|%s", creds->website, creds->username, creds->password);
}

void print_file(){
    printf("----[FILE DEBUG]----\n");
    FILE* file = fopen("db.csv", "r");
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
    }
    free(line);
    fclose(file);
}

Credentials search_credentials(const char* website, const Credentials* creds, int size){
    for(int i = 0; i < size; i++){
        if(strcmp(creds[i].website, website) == 0){
            return creds[i];
        }
    }
    return (Credentials){"", "", ""};
}

Credentials search_credentials_with_regex(const char* regex, const Credentials* creds, int size){
    for(int i = 0; i < size; i++){
        if(strstr(creds[i].website, regex) != NULL){
            return creds[i];
        }
    }
    return (Credentials){"", "", ""};
}

void blink_led(int n){
    if (cyw43_arch_init()){
        printf("Wi-Fi init failed");
        return;
    }
    for(int i = 0; i < n; i++){
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(100);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(100);
    }
}

int main() {
    stdio_init_all();

    blink_led(10);

    /*
    const char* filename = "db.csv";
    FILE* file = fopen(filename, "r");
    Credentials* creds = read_credentials_into_array(file);

    int i = 0;
    char* website = malloc(MAX_WEBSITE_LENGTH);
    while(i < 10){
        printf("Enter website: ");
        scanf("%s", website);

        Credentials c = search_credentials(website, creds, 34);
        if(strcmp(c.website, "") == 0){
            printf("Website not found\n");
            i++;
            continue;
        }

        printf("Username: %s\nPassword: %s\n", c.username, c.password);
        i++;
    }

    free(website);
    free(creds);
    fclose(file);
    */
    return 0;
}