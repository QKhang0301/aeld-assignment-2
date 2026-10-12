#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

#define RET_ERROR (1) 
#define RET_SUCCESS (0) 

char* get_filename(char* file_path);

int main(int argc, char* argv[]){
    /* Init variables */
    int fd = 0;
    int fail_in_opening_file = -1;
    char* writefile = NULL;
    char* filename = NULL; 
    char* writestr = NULL;
    int valid_number_of_arg = 3;
    int ret_val = RET_ERROR;
    /* Open Log*/
    openlog(NULL, 0, LOG_USER);
    /* Check the validity of input */
    if (argc != valid_number_of_arg){
        printf("ERROR: Invalid number of argument\n");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Number of input arguments is invalid, it must be %d\n", valid_number_of_arg);
        return RET_ERROR;
    }
    // Get the value
    writefile = argv[1];
    writestr = argv[2];
    // Extract the filename
    filename = get_filename(writefile);
    // Check the value again
    if (writefile == NULL || writefile == NULL || filename == NULL){
        printf("The input is invalid, pls check again\n");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: invalid value of writefile/writestr\n");
        return RET_ERROR;
    }

    /*Logging*/
    syslog(LOG_DEBUG, "LSP Assisgnment - Writer - The file need to be written: %s\n", writefile);
    syslog(LOG_DEBUG, "LSP Assisgnment - Writer - The string written to file: %s\n", writestr);
    /* Printing to the terminal */
    printf("The file need to be written: %s\n", writefile);
    printf("The string written to file: %s\n", writestr);    
    //Open the file with read & write operation*/
    fd = open(writefile, O_CREAT | O_RDWR | O_TRUNC,
                        S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    //Check for success opening
    if (fd == fail_in_opening_file){
        perror("Perror returned:");    
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Cannot open the file\n");
        return RET_ERROR;
    }
    
    //write to the file
    size_t len = strlen(writestr);
    ssize_t nr = write(fd, writestr, len);
    if(nr == -1){ //fail to write
        perror("Error returned");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Cannot write the the file, Error returned: %d\n", errno);
    } else if (nr != len){
        printf("Something wrong when writing\n");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Cannot write the the file, maybe a partly write\n");
    } else {
        // Write successfully
        syslog(LOG_DEBUG, "Writing %s to file %s", writestr, filename);
    }
    
    if(close(fd) == -1){
        perror("Error returned:");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Cannot close the file\n");
    } else {
        ret_val = RET_SUCCESS;
    }
    
    return ret_val;
}

/* Extracting a file name from the input file path */
char* get_filename(char* file_path){
    char* filename = NULL;
    // Check if the file_path is NULL or blank
    if(file_path == NULL || file_path[0] == '\0'){
        printf("ERROR: Invalid file path\n");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Invalid file path\n");
        return NULL;
    }

    // Check whether the last character of the path is "/" -> it is directory
    size_t length = strlen(file_path);
    if (file_path[length - 1] == '/'){
        printf("ERROR: This is a directory, not a file\n");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: The path is a directory, not a file path\n");
        return NULL;
    }

    // Get the last "/" character position
    unsigned int index = length - 1;
    for(index = length - 1; index >= 0; index--){
        if (file_path[index] == '/'){
            filename = file_path + (index+1)*sizeof(file_path[0]);
            break;
        }
    }

    return filename;
}