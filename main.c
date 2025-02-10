#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include <string.h>

// Function to copy file contents from source to destination
int copy_command(int fd1, int fd2)
{
    struct stat status;     // Structure to store file status
    char buffer[1024];      // Buffer to read and write data
    int bytes_read, bytes_written; // Variables to store bytes read and written
    
    while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0) // Read data from source file
    {
        bytes_written = write(fd2, buffer, bytes_read); // Write data to destination file
        if (bytes_written != bytes_read) // Check for write errors
        {
            printf("Error writing to file\n");
            return 0;
        }
        printf("Data read -> %d bytes\n", bytes_read);
        printf("Data write -> %d bytes\n", bytes_written);
        
        fstat(fd1, &status); // Get file status (permissions, size, etc.)
        int ret = fchmod(fd2, status.st_mode); // Copy file permissions to destination
        if (ret == -1) // Check for errors in changing permissions
        {
            printf("Error changing permission\n");
            return 0;
        }
    }
    // Close file descriptors after operation
    close(fd1);
    close(fd2);  
    return 0; 
}

int main(int argc, char *argv[])
{
    // Validate command-line arguments
    if (argc == 3 || argc == 4)
    {
        if (argc == 3)   // If only source and destination arguments are provided
        {
            for (int i = 0; i < argc; i++)
            {
                if (strcmp(argv[1], "-p") == 0) // Ensure that the second argument is not "-p"
                {
                    printf("Usage: ./a.out <source> <destination>\n");
                    return 0;
                }
            }
        }
        if (argc == 4) // If permission flag (-p) is provided
        {
            for (int i = 0; i < argc; i++)
            {
                if (strcmp(argv[1], "-p") != 0)
                {
                    printf("Usage: ./a.out -p <source> <destination>\n");
                    return 0;
                }
            }
        }
    }
    else
    {
        printf("Insufficient arguments\n");
        return 0;
    }

    // Open source file for reading
    int fd1 = open(argv[argc - 2], O_RDONLY);
    if (fd1 == -1)
    {
        if (errno == EACCES)
        {
            printf("Required permissions denied\n");
            return 0;
        }
        if (errno == ENOENT)
        {
            printf("File does not exist\n");
            return 0;
        }
    }

    // Open destination file for writing
    int fd2 = open(argv[argc - 1], O_WRONLY);
    if (fd2 == -1)
    {
        if (errno == EACCES)
        {
            printf("Required permissions denied\n");
            return 0;
        }
        if (errno == ENOENT)
        {
            printf("File %s does not exist\n", argv[argc - 1]);
            printf("Creating file %s with required permissions\n", argv[argc - 1]);
            fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644); // Create file if it doesn't exist
            copy_command(fd1, fd2);
            return 0;
        }  
    }
    
    // If destination file exists, ask user for confirmation to overwrite
    printf("File %s contains data\n", argv[argc - 1]);
    printf("Do you want to overwrite the data and permission? \n");
    printf("Yes(y) / No(n)\n");
    
    char choice;
    scanf("%c", &choice);
    if (choice == 'y')
    {
        fd2 = open(argv[argc - 1], O_WRONLY | O_TRUNC, 0644); // Truncate file before writing
        copy_command(fd1, fd2);
    }
    else if (choice == 'n')
    {
        close(fd1);
        close(fd2);
        return 0;
    }     
}
