# Client-Server File Handling Application with Mirror Server

This repository contains a simple client-server application for handling file-related commands. The application allows clients to interact with a main server and optionally switch to a mirror server for load balancing or fault tolerance.

## Features

- **getfn Command:** Retrieve information about a specific file, including its name, size, creation date, and permissions.

- **getfz Command:** Retrieve files within a specified size range and receive them as a compressed tar archive.

- **getft Command:** Retrieve files with specified file extensions and receive them as a compressed tar archive.

- **getfdb Command:** Retrieve files created on or before a specified date and receive them as a compressed tar archive.

- **getfda Command:** Retrieve files created on or after a specified date and receive them as a compressed tar archive.

- **quitc Command:** Gracefully terminate the client.

## Mirror Server

- The mirror server acts as a secondary server to handle client requests.
- Clients can switch between the main server and the mirror server.

## Usage

1. **Server Setup:**
   - Compile and run the main server on the desired port (default: 8080).
   - Compile and run the mirror server on a different port (default: 8081).

2. **Client Setup:**
   - Compile and run the client, which connects to the main or mirror server based on the server's response.

3. **Commands:**
   - Use commands like `getfn`, `getfz`, `getft`, `getfdb`, `getfda`, and `quitc` to interact with the server.

## Configuration

- Adjust server ports, user directories, and other settings in the code as needed.

## Contributing

If you'd like to contribute to the project, please follow the standard GitHub Fork & Pull Request workflow.

## Acknowledgments

- This project was developed by Harish Kumaravel.
- Special thanks to Dr. Prashanth C. Ranga.

