// Muhammed Saad Anaikar | 110096621 
//Harish Kumravel | 110122049 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT_MAIN 8080
#define PORT_MIRROR 8081
#define MAX_BUFFER_SIZE 1024

char *userDir="/home/saad";


void sendTar(int client_socket){

    FILE *file = fopen("temp.tar.gz", "rb");
    if (file == NULL) {
        perror("Error opening file");
    }

    char buffer[MAX_BUFFER_SIZE];
    size_t bytesRead;
    while (1) {
        bytesRead = fread(buffer, 1, sizeof(buffer), file);
        if(bytesRead<=0){
            char bu[1024]="-1";
            send(client_socket, bu, strlen(bu), 0);
            break;
        }
        if (send(client_socket, buffer, bytesRead, 0) == -1) {
            perror("Error sending file content");
        }
    }

    fclose(file);
}


// Process getfn command
void processGetFnCommand(int client_socket, char *filename) {
    // Search for the file
    int fileFound = 0;

    char cmd[512]; 

    snprintf(cmd,sizeof(cmd),"find ~ -type f -name %s",filename);

    FILE* tree = popen(cmd,"r");

    char file[512]; 

    

    if( !tree ){
        char response[MAX_BUFFER_SIZE] = "File Not found";
        send(client_socket, response, strlen(response), 0);
    }else{
        fgets(file,sizeof(file),tree);
    }

    fclose(tree);


    if(strlen(file)==0){
        char response[MAX_BUFFER_SIZE] = "File Not found";
        send(client_socket, response, strlen(response), 0);
        return ;
    }

    char cmd2[512] = "stat -c '%n %s %y %a' ";

    strcat(cmd2,file); 

    FILE* tree2 = popen(cmd2,"r");

    char out[512];

    if( !tree2 ){
        char response[MAX_BUFFER_SIZE] = "File not found";
        send(client_socket, response, strlen(response), 0);
    }else{
        fgets(out,sizeof(out),tree2);
        fileFound = 1;  
    }

    char *p = strtok(out," ");
    int i=0;
    char *arr[6];

    while(p != NULL){
        arr[i++]=p;
        p = strtok(NULL," ");
    }

    char response[MAX_BUFFER_SIZE];

    if (fileFound) {
        snprintf(response, sizeof(response),
                    "Filename: %s\nSize: %s bytes\nDate Created: %s\nFile Permissions: %s",
                    filename, arr[1] , arr[2], arr[5]);
                    send(client_socket, response, strlen(response), 0);
                      
    } else {
        char response[MAX_BUFFER_SIZE] = "File not found";
        send(client_socket, response, strlen(response), 0);
    }

}

// Process getfz command
void processGetFzCommand(int client_socket, int size1, int size2) {
    remove("temp.tar.gz");
    char cmd[512]; 

    snprintf(cmd,sizeof(cmd),"find -type f -size +%dc -size -%dc -exec tar -rf  temp.tar.gz {} +",size1,size2);

    popen(cmd,"r");

    FILE* tree = popen(cmd,"r");

    if( !tree ){
        char response[MAX_BUFFER_SIZE] = "File Not found";
        send(client_socket, response, strlen(response), 0);
    }

    fclose(tree);

    sendTar(client_socket);


}


void processGetFtCommand(int client_socket, char *command) {
    
    remove("temp.tar.gz");

    // Parse extensions from the command
    

    char *p = strtok(command, " ");
    int i = 0;
    char *arr[4];

    while (p != NULL && i < 4) {
        arr[i++] = p;
        printf("%s\n", arr[i - 1]);
        printf("%d\n",i);  // Print the value just stored
        p = strtok(NULL, " ");

    }

    char cmd[512];
    if(i==1){
        char *ext1=arr[0];
        //char cmd[512];
        snprintf(cmd,sizeof(cmd),"find -type f \\( -iname \"*.%s\"  \\) -exec tar -rf  temp.tar.gz {} +",ext1);
    }
    else if(i==2){
        char *ext1=arr[0];
    char *ext2=arr[1];
        //char cmd[512];
        snprintf(cmd,sizeof(cmd),"find -type f \\( -iname \"*.%s\" -o -iname \"*.%s\"  \\) -exec tar -rf  temp.tar.gz {} +",ext1,ext2);
    }
    else if(i==3){
        char *ext1=arr[0];
    char *ext2=arr[1];
    char *ext3=arr[2];
         // char cmd[512];
              snprintf(cmd,sizeof(cmd),"find -type f \\( -iname \"*.%s\" -o -iname \"*.%s\" -o -iname \"*.%s\" \\) -exec tar -rf  temp.tar.gz {} +",ext1,ext2,ext3);

    }
    else{
        printf("error 1-3 only allowed");
        return;
    }

    // Execute the command
    FILE *tree = popen(cmd, "r");

    if (!tree) {
        char response[MAX_BUFFER_SIZE] = "File Not found";
        send(client_socket, response, strlen(response), 0);
    } 


    // Close the file stream
    fclose(tree);

    sendTar(client_socket);

}




// Process getfdb command
void processGetFdbCommand(int client_socket, char *date) {
    // Search for files created on or before the specified date
    remove("temp.tar.gz");
    char cmd[512]; 

    snprintf(cmd,sizeof(cmd),"find -type f -newermt 12/01/2022 ! -newermt %s -exec tar -rf  temp.tar.gz {} +",date);

    popen(cmd,"r");

    FILE* tree = popen(cmd,"r");

    if( !tree ){
        char response[MAX_BUFFER_SIZE] = "File Not found";
        send(client_socket, response, strlen(response), 0);
    }

    fclose(tree);

    sendTar(client_socket);
}

// Process getfda command
void processGetFdaCommand(int client_socket, char *date) {
    // Search for files created on or after the specified date
    remove("temp.tar.gz");
    char cmd[512]; 

    snprintf(cmd,sizeof(cmd),"find -type f -newermt %s -exec tar -rf  temp.tar.gz {} +",date);

    popen(cmd,"r");

    FILE* tree = popen(cmd,"r");

    if( !tree ){
        char response[MAX_BUFFER_SIZE] = "File Not found";
        send(client_socket, response, strlen(response), 0);
    }

    fclose(tree);

    sendTar(client_socket);
}

// Process quitc command
void processQuitCommand(int client_socket) {
    // Close the connection
    close(client_socket);
}

// Map command to a constant value
int mapCommand(char *command) {
    if (strcmp(command, "getfn") == 0) {
        return 1;
    } else if (strcmp(command, "getfz") == 0) {
        return 2;
    } else if (strcmp(command, "getft") == 0) {
        return 3;
    } else if (strcmp(command, "getfdb") == 0) {
        return 4;
    } else if (strcmp(command, "getfda") == 0) {
        return 5;
    } else if (strcmp(command, "quitc") == 0) {
        return 6;
    } else {
        return -1;  // Unknown command
    }
}

// Main function to handle client requests

void pclientrequest(int client_socket) {

    // send(client_socket, message, strlen(message), 0);
    
    while (1) {

        // Receive command from the client
        char buffer[MAX_BUFFER_SIZE] = "";
        char command[MAX_BUFFER_SIZE] = "";
        char argument[MAX_BUFFER_SIZE] = "";

        recv(client_socket, buffer, sizeof(buffer), 0);

        // Extract command and argument
        sscanf(buffer, "%s %[^\n]", command, argument);
        // printf("Received Command: %s, Argument: %s\n", command, argument);
        // Map command name to its integer value
        int mappedCommand = mapCommand(command);


        switch (mappedCommand) {
            case 1: // getfn
                processGetFnCommand(client_socket, argument);
                break;

            case 2: // getfz
                int size1, size2;
                sscanf(argument, "%d %d", &size1, &size2);
                processGetFzCommand(client_socket, size1, size2);
                break;

            case 3: // getft
                processGetFtCommand(client_socket, argument);
                break;

            case 4: // getfdb
                processGetFdbCommand(client_socket, argument);
                break;

            case 5: // getfda
                processGetFdaCommand(client_socket, argument);
                break;

            case 6: // quitc
                processQuitCommand(client_socket); // Remove the extra argument
                break;

            default:
                // Unknown command
                // printf("Unknown command received from client.\n");
                break;
        }
    }
}


int main() {
    int mirror_socket, client_socket;
    struct sockaddr_in mirror_addr, client_addr;
    int addr_len = sizeof(mirror_addr);

    // Create socket for the mirror server
    if ((mirror_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating mirror socket");
        exit(EXIT_FAILURE);
    }

    // Set up mirror server address struct
    memset(&mirror_addr, 0, addr_len);
    mirror_addr.sin_family = AF_INET;
    mirror_addr.sin_port = htons(PORT_MIRROR);  // Use the correct PORT_MIRROR here
    mirror_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the mirror socket to an address
    if (bind(mirror_socket, (struct sockaddr *)&mirror_addr, sizeof(mirror_addr)) == -1) {
        perror("Error binding mirror socket");
        exit(EXIT_FAILURE);
    }

    // Listen for mirror connections
    if (listen(mirror_socket, 5) == -1) {
        perror("Error listening for mirror connections");
        exit(EXIT_FAILURE);
    }

    printf("Mirror server listening on port %d...\n", PORT_MIRROR);  // Corrected print statement

    // Accept connections for the mirror server
    while (1) {

        umask(0000);
        chdir(userDir);

        if ((client_socket = accept(mirror_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len)) == -1) {
            perror("Error accepting mirror connection");
            exit(EXIT_FAILURE);
        }

        // printf("Mirror Connection accepted from %s\n", inet_ntoa(client_addr.sin_addr));

        // Fork a new process to handle mirror client requests
        if (fork() == 0) {
            close(mirror_socket);  // Close the mirror server socket in the child process
            pclientrequest(client_socket);
            exit(EXIT_SUCCESS);  // Make sure the child process exits after handling the request
        } else {
            close(client_socket);  // Close the client socket in the parent process
        }
    }

    return 0;
}