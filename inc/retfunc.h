#ifndef __RETFUNC__H
#define __RETFUNC__H	// 头文件只定义一次

void py_init(void);

void py_finish(void);

char *par_retfunc(char *str);
// 拍照
#define SHOOT "wget http://127.0.0.1:8080/?action=snapshot -O /home/orangepi/smart/image/lj.jpg"
// #define SHOOT "wget http://127.0.0.1:8080/?action=snapshot -O ~/smart/image/lj.jpg"
#define GARBAGE_FILE "/home/orangepi/smart/image/lj.jpg"    // 图像绝对路径

#endif
