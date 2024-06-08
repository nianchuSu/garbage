#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "wiringSerial.h"

char uart_getc(int fd)
{
	char c;
	if(read(fd,&c,1) != 1){
		return -1;
	}
	return c;
}


int uart_Open (const char *device, const int baud)	// 重写打开
{
	struct termios options ;
	speed_t myBaud ;	// 波特率
	int     status, fd ;

	switch (baud)		// 常用波特率9600	115200
	{
		case    9600:	myBaud =    B9600 ; break ;
		case  115200:	myBaud =  B115200 ; break ;

		default:
						return -2 ;
	}

	if ((fd = open (device, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1)	// 打开文件/万物皆文件
		return -1 ;

	fcntl (fd, F_SETFL, O_RDWR) ;

	// Get and modify current options:

	tcgetattr (fd, &options) ;

	cfmakeraw   (&options) ;
	cfsetispeed (&options, myBaud) ;
	cfsetospeed (&options, myBaud) ;

	options.c_cflag |= (CLOCAL | CREAD) ;	// 这几行是参数
	options.c_cflag &= ~PARENB ;	// 奇偶校验位
	options.c_cflag &= ~CSTOPB ;	// 停止位
	options.c_cflag &= ~CSIZE ;		// 数据长度?
	options.c_cflag |= CS8 ;		// 数据位
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;
	options.c_oflag &= ~OPOST ;		// 

	options.c_cc [VMIN]  =   0 ;
	options.c_cc [VTIME] = 100 ;	// Ten seconds (100 deciseconds)

	tcsetattr (fd, TCSANOW, &options) ;

	ioctl (fd, TIOCMGET, &status);

	status |= TIOCM_DTR ;
	status |= TIOCM_RTS ;

	ioctl (fd, TIOCMSET, &status);

	usleep (10000) ;	// 10mS

	return fd ;	// 返回句柄
}

void uart_Puts (const int fd, const unsigned char *s, int len)	// 发送字符串
{ 
	int ret;
	ret = write (fd, s, len);
	if (ret < 0)
		printf("Serial Puts Error\n");
}



int uart_Getstr (const int fd,unsigned char *buf, int len)	// 接收数据?
{
	int n_read;
	n_read = read(fd,buf,len);
	return n_read;
}
