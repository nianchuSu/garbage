#include <wiringPi.h>
#include <softPwm.h>

void open_sg(int pin)
{
    pinMode(pin, OUTPUT);   // 定义针脚为输出针脚
    softPwmCreate(pin, 0, 200); // 模拟pwm
    softPwmWrite(pin, 15);  // 转动?
    delay(1000);
    softPwmStop(pin);
}

void stop_sg(int pin)
{
    pinMode(pin, OUTPUT);
    softPwmCreate(pin, 0 , 200);
    softPwmWrite(pin, 5);
    delay(1000);
    softPwmStop(pin);
}