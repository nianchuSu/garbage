#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "oled.h"
#include "font.h"

#include "myoled.h"

#define IIC "/dev/i2c-3"

static struct display_info disp;

int myoled_show(void *arg)
{
	unsigned char *buf = (unsigned char *)arg; // 强转数据类型
	oled_putstrto(&disp, 0, 4, "This garbage is:");
	disp.font = font2;
	printf("oled**buf[2]--%c\n",buf[2]);
	switch (buf[2])
	{
		case 0x41:
			oled_putstrto(&disp, 16, 32, "dry refuse");
			break;
		case 0x42:
			oled_putstrto(&disp, 16, 32, "wet garbage");
			break;
		case 0x43:
			oled_putstrto(&disp, 16, 32, "recyclables");
			break;
		case 0x44:
			oled_putstrto(&disp, 16, 32, "harmful waste");
			break;
		case 0x45:
			oled_putstrto(&disp, 16, 32, "Item recognition failure!!!");
			break;
	}
	disp.font = font2;
	oled_send_buffer(&disp);
	return 0;
}

int myoled_init(void)
{
	int i;
	disp.address = OLED_I2C_ADDR;
	disp.font = font2;

	i = oled_open(&disp, IIC);
	i = oled_init(&disp);

	return i;
}