// Muhammed Saad Anaikar | 110096621 
//Harish Kumravel | 110122049 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 8080
#define PORT_MIRROR 8081
#define MAX_BUFFER_SIZE 1024


void processGetFnCommand(int client_socket, char *command) {
    // Extract filename from the command
    char filename[MAX_BUFFER_SIZE];
    if (sscanf(command, "getfn %s", filename) != 1) {
        fprintf(stderr, "Invalid command syntax. Usage: getfn filename\n");
        return;
    }

    // Send the command to the server
    send(client_socket, command, strlen(command), 0);

    // Read the response from the server
    char buffer[MAX_BUFFER_SIZE] = {0};
    read(client_socket, buffer, MAX_BUFFER_SIZE);

    if (strncmp(buffer, "File not found", sizeof("File not found") - 1) == 0) {
        printf("File not found\n");
    } else {
        printf("Server response:\n%s\n", buffer);
    }
}

void processQuitCommand(int client_socket, char *command) {
    // Send the quit command to the server
    send(client_socket, command, strlen(command), 0);

    // Close the socket and terminate the client process
    printf("Terminating the client process.\n");
    close(client_socket);
    exit(EXIT_SUCCESS);
}

void processGetFzCommand(int client_socket, char *command) {

    mkdir("f23project",0777);
    
    // Send the getfz command to the server
    

    int size1, size2;
    if (sscanf(command, "getfz %d %d", &size1, &size2) != 2 || size1 < 0 || size2 < 0 || size1 > size2) {
        fprintf(stderr, "Invalid command syntax. Usage: getfz size1 size2 (where size1 <= size2 and both are non-negative)\n");
        return;
    }

    remove("f23project/received_file.tar.gz");

    send(client_socket, command, strlen(command), 0);

    // Receive file content

    open("f23project/received_file.tar.gz",O_CREAT,0777);
    
    FILE *file = fopen("f23project/received_file.tar.gz", "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = recv(client_socket, buffer, sizeof(buffer), 0)) == 1024) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);

    // Check if the server sent "No file found"
    if (strncmp(buffer, "No file found", sizeof("No file found") - 1) == 0) {
        printf("No files found in the specified size range.\n");
    } else {
        printf("Received tar archive from server. Saved as Received_file.tar.gz.\n");
    }
}

void processGetFtCommand(int client_socket, char *command) {

    mkdir("f23project",0777);

    if (strcmp(command,"getft")==0) {
        fprintf(stderr, "Invalid command syntax. Usage: getft [ext1] [ext2] [ext3]\n");
        return;
    }

    remove("f23project/received_file.tar.gz");

    send(client_socket, command, strlen(command), 0);

    // Receive file content

    open("f23project/received_file.tar.gz",O_CREAT,0777);

    // Receive file content
    FILE *file = fopen("f23project/received_file.tar.gz", "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = recv(client_socket, buffer, sizeof(buffer), 0)) == 1024) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);

    // Check if the server sent "No file found"
    if (strncmp(buffer, "No file found", sizeof("No file found") - 1) == 0) {
        printf("No files found in the specified size range.\n");
    } else {
        printf("Received tar archive from server. Saved as Received_file.tar.gz.\n");
    }
}





void processGetFdbCommand(int client_socket, char *command) {

    mkdir("f23project",0777);

    // Extract date from the command
    char date[MAX_BUFFER_SIZE];
    if (sscanf(command, "getfdb %s", date) != 1) {
        fprintf(stderr, "Invalid command syntax. Usage: getfdb date (e.g., 2023-01-01)\n");
        return;
    }

    remove("f23project/received_file.tar.gz");

    send(client_socket, command, strlen(command), 0);

    // Receive file content

    open("f23project/received_file.tar.gz",O_CREAT,0777);

    // Receive file content
    FILE *file = fopen("f23project/received_file.tar.gz", "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = recv(client_socket, buffer, sizeof(buffer), 0)) == 1024) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);

    // Check if the server sent "No file found"
    if (strncmp(buffer, "No file found", sizeof("No file found") - 1) == 0) {
        printf("No files found in the specified size range.\n");
    } else {
        printf("Received tar archive from server. Saved as Received_file.tar.gz.\n");
    }
}

void processGetFdaCommand(int client_socket, char *command) {

    mkdir("f23project",0777);

    // Extract date from the command
    char date[MAX_BUFFER_SIZE];
    if (sscanf(command, "getfda %s", date) != 1) {
        fprintf(stderr, "Invalid command syntax. Usage: getfda date (e.g., 2023-01-01)\n");
        return;
    }

    remove("f23project/received_file.tar.gz");

    send(client_socket, command, strlen(command), 0);

    // Receive file content

    open("f23project/received_file.tar.gz",O_CREAT,0777);

    // Receive file content
    FILE *file = fopen("f23project/received_file.tar.gz", "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = recv(client_socket, buffer, sizeof(buffer), 0)) == 1024) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);

    // Check if the server sent "No file found"
    if (strncmp(buffer, "No file found", sizeof("No file found") - 1) == 0) {
        printf("No files found in the specified size range.\n");
    } else {
        printf("Received tar archive from server. Saved as Received_file.tar.gz.\n");
    }
}


int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char msg_from_clinet[MAX_BUFFER_SIZE] = {0};

    remove("f23project");
    mkdir("f23project",0777);
    


    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char status[MAX_BUFFER_SIZE]={0};
    read(client_socket,status, MAX_BUFFER_SIZE);
    printf("Server: %s\n", status);


    if (strncmp(status, "server", sizeof("server") - 1) == 0) {
            
    }else if(strncmp(status, "mirror", sizeof("mirror") - 1) == 0){
        
        if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_MIRROR);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    }

    while(1){

        char buffer[MAX_BUFFER_SIZE] = {0};
        // Get user input
        printf("Enter a command: ");
        // Get user input

        fgets(buffer, MAX_BUFFER_SIZE, stdin);

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';


        // Process commands
        if (strncmp(buffer, "getfn", sizeof("getfn") - 1) == 0) {
            processGetFnCommand(client_socket, buffer);
        } else if (strncmp(buffer, "quitc", sizeof("quitc") - 1) == 0) {
            processQuitCommand(client_socket, buffer);
        } else if (strncmp(buffer, "getfz", sizeof("getfz") - 1) == 0) {
            processGetFzCommand(client_socket, buffer);
        } else if (strncmp(buffer, "getft", sizeof("getft") - 1) == 0) {
            processGetFtCommand(client_socket, buffer);
        } else if (strncmp(buffer, "getfdb", sizeof("getfdb") - 1) == 0) {
            processGetFdbCommand(client_socket, buffer);
        } else if (strncmp(buffer, "getfda", sizeof("getfda") - 1) == 0) {
            processGetFdaCommand(client_socket, buffer);
        } else {
            printf("Unknown command. Supported commands: getfn, quitc, getfz, getft, getfdb, getfda, getTar\n");
        }

    }
    

    

    close(client_socket);

    return 0;
}