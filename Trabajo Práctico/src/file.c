#include "file.h"

#define DELIMS " \n"

bool writeFile(char * key, char * value);
bool readFile(char * key, char * response);
bool deleteFile(char * key);

void cmmdExecution(int client_socket, char* buffer) {

    char *command = strtok(buffer, DELIMS);
    char *key = strtok(NULL, DELIMS);
    char *value = strtok(NULL, DELIMS);

    if (strcmp(command, "SET") == 0 && key && value) {
        
                
        if (!writeFile(key, value)) {
            
            write(client_socket, "ERROR\n", 6);
                       
        } else {
        
            write(client_socket, "OK\n", 3);
            
        }
        
    } else if (strcmp(command, "GET") == 0 && key) {
        
        char response[RESPONSE_SIZE] = {0};
        if (!readFile(key, response)) {
        
            write(client_socket, "NOTFOUND\n", 9);
            
        } else {

            write(client_socket, "OK\n", 3);
            write(client_socket, response, strlen(response));
            write(client_socket, "\n", 1);
	            
        }

        
    } else if (strcmp(command, "DEL") == 0 && key) {
     
        deleteFile(key);
        
        write(client_socket, "OK\n", 3);

    } else {
        
        write(client_socket, "ERROR: Invalid command\n", 23);
        
    }
    
}

bool writeFile(char * key, char * value) {

    int file = open(key, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (file < 0) {
            
        perror("ERROR opening file");
        return false;
                      
    } else {
        
         write(file, value, strlen(value));
         close(file);
         return true;
            
    }

}

bool readFile(char * key, char * response) {

    int file = open(key, O_RDONLY);
    if (file < 0) {
        
        return false;
            
    } else {
	
	read(file, response, RESPONSE_SIZE);
        close(file);

        return true;
	            
    }

}

bool deleteFile(char * key) {

    return (remove(key) == 0);

}


