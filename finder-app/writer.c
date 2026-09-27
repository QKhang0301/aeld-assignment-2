#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define RET_ERROR (1) 
#define RET_SUCCESS (0) 

int main(int argc, char* argv[]){
    /* Init variables */
    int fd = 0;
    int fail_in_opening_file = -1;
    char* writefile = NULL;
    char* writestr = NULL;
    int valid_number_of_arg = 3;
    /* Check the validity of input */
    if (argc != valid_number_of_arg){
        printf("The number of input arguments is invalid, it must be %d\n", valid_number_of_arg);
        return RET_ERROR;
    }
    // Get the value
    writefile = argv[1];
    writestr = argv[2];
    // Check the value again
    if (writefile == NULL || writefile == NULL){
        printf("The input is invalid, pls check again\n");
        return RET_ERROR;
    }
    //Print the info
    printf("Info\n");
    printf("The file you want to write: %s\n", writefile);
    printf("The string you want to write: %s\n", writestr); 
    //Open the file with read & write operation*/
    fd = open(writefile, O_CREAT | O_RDWR | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
    //Check for success opening
    if (fd == fail_in_opening_file){
        perror("Perror returned:");    
        return RET_ERROR;
    }
    
    
    //write to the file
    size_t len = strlen(writestr);
    ssize_t nr = write(fd, writestr, len);
    if(nr == -1){ //fail to write
        perror("Error returned");
        return RET_ERROR;
    } else if (nr != len){
        printf("Something wrong when writing\n");
        return RET_ERROR;
    }
     
}
