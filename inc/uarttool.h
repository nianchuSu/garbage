#ifndef __UARTTOOL__H
#define __UARTTOOL__H

int uart_Open (const char *device, const int baud);	// 重写打开

void uart_Puts (const int fd, const unsigned char *s, int len);	// 发送字符串

int uart_Getstr (const int fd,unsigned char *buf, int len);	// 写入?

char uart_getc();

#define URAT "/dev/ttyS5"
#define BAUD 115200

#endif