

int setTCPServerSocket (int port) {
    
    struct sockaddr_in serverAddr;
    
    // Socket creation (listener mode)
    server_socket = socket (AF_INET, SOCK_STREAM, 0);
    
    if (server_socket == -1) {
        
        perror("Error creating the socket");
        return -1; //SOCKET_ERROR
        
        
    }
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind ERROR");
        close(server_socket);
        return -1; //BIND_ERROR
    }
    
    
}
