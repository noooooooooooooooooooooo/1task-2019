#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int fd = open(argv[1], O_RDWR, 0666);
	int fd1 = open(argv[2], O_RDWR, 0666);
	if (fd == -1){
		printf("Can't find first file\n");
		return -1;
	}
	if (fd1 == -1){
        printf("Can't find second file\n");
        return -1;
    }
	if(argc < 3){
		printf("Enter two file's names\n");
		return -1;
	}
	char buff[256] = {0};
	char elements[128][256] = {0};
	int rd = read(fd, buff, 256);
	int k = 0, t = 0;
	char size[128] = {0};
	for(int i = 0; i <= rd; i++) {
		if(buff[i] == ' ' || i == rd) {		
			for(int j = t; j < i; j++) {
				elements[k][j - t] = buff[j];
				size[k] = i - t;
			}
			k++;
			t = i + 1;
		}
	}
	for(int i = 0; i < k; i++) {
		if(elements[i][0] - '0' <= 9) {
			if(atoi(elements[i])%15 == 0 && elements[i] != 0) {
				write(fd1, "bizzbuzz", 8);
				write(fd1, " ", 1);
			}
			else if(atoi(elements[i])%5 == 0 && elements[i] != 0) {
				write(fd1, "buzz", 4);
				write(fd1, " ", 1);
			}
			else if(atoi(elements[i])%3 == 0 && elements[i] != 0) {
				write(fd1, "bizz", 4);
				write(fd1, " ", 1);
			}
			else {
				write(fd1, elements[i], size[i]);
				write(fd1, " ", 1);
			}
		}
		else {
				write(fd1, elements[i], size[i]);
				write(fd1, " ", 1);
		}
	}
	close(fd);
	close(fd1);
}
