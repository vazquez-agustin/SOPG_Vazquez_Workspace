#include "server.h"
#include "file.h"

void handle_client(int client_socket) {

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    int read_size = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (read_size < 0) {
    
        perror("ERROR reading socket");
        exit(EXIT_FAILURE);
        
    }

    buffer[read_size] = '\0';
    
    cmmdExecution(client_socket, buffer);
    
    close(client_socket);
    
}

// Configure the server socket
int setTCPServerSocket(int port) {
    
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
    
        perror("ERROR creating socket");
        exit(EXIT_FAILURE);
        
    }
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
	
    // Open port with bind()
    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
    
        perror("bind");
        exit(EXIT_FAILURE);
        
    }
	
    // Set socket in listening mode
    if (listen(server_socket, 5) < 0) {
    
        perror("listen");
        exit(EXIT_FAILURE);
        
    }

    return server_socket;
    
}


// main() function
int main() {

    struct sockaddr_in clientAddr;
    socklen_t client_len = sizeof(clientAddr);

    int server_socket = setTCPServerSocket(PORT);
    printf("Server listening in port %d\n", PORT);

    while (1) {
    
        int client_socket = accept(server_socket, (struct sockaddr*)&clientAddr, &client_len);
        if (client_socket < 0) {
        
            perror("ERROR in accept");
            continue;
            
        }

        printf("Client conected\n");
        handle_client(client_socket);
        
    }

    close(server_socket);
    return 0;
    
}


