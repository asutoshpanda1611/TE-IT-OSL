#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#define FIFO_PIPE "xyz"

int main() {
    int fd, i, c = 0, w = 0, l = 0;
    char str[100];

    fd = open(FIFO_PIPE, O_RDONLY);  
    read(fd, str, sizeof(str));      
    
    for(i = 0; str[i] != '\0'; i++) {  
        if(str[i] == ' ' || str[i] == '\n')  
            w++;
        if(str[i] == '\n')  
            l++;
        c++;  
    }
    
    printf("\n No of characters = %d", c);   // Print character count
    printf("\n No of lines = %d", l + 1);    // Print line count (add 1 for the last line)
    printf("\n No of words = %d \n", w);     // Print word count

    close(fd);  // Close the pipe
    return 0;
}
