#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	char buff[20];
	int fd = open("sampl.txt",O_RDONLY);
	read(fd,buff,19);
	printf("%s",buff);
}
