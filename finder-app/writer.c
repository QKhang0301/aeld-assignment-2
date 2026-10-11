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

int main(int argc, char* argv[]){
    /* Init variables */
    int fd = 0;
    int fail_in_opening_file = -1;
    char* writefile = NULL;
    char* file_dir = NULL; 
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
    // Check the value again
    if (writefile == NULL || writefile == NULL){
        printf("The input is invalid, pls check again\n");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: invalid value of writefile/writestr\n");
        return RET_ERROR;
    }
    /*Logging*/
    syslog(LOG_DEBUG, "LSP Assisgnment - Writer - The file need to be written: %s", writefile);
    syslog(LOG_DEBUG, "LSP Assisgnment - Writer - The string written to file: %s", writestr);    
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
    }
    
    if(close(fd) == -1){
        perror("Error returned:");
        syslog(LOG_ERR, "LSP Assisgnment - Writer - ERROR: Cannot close the file\n");
    } else {
        ret_val = RET_SUCCESS;
    }
    
    return ret_val;
}
