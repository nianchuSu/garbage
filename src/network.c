#include "network.h"

int net_init(const char *ipaddr, const char *port)
{
    int sock_fd = -1;             // 操作标识符
    struct sockaddr_in sock_addr; // define the IP address and its port information structure(定义IP地址及其端口信息结构体)
    int ret = -1;

    memset(&sock_addr, 0, sizeof(struct sockaddr_in)); // Data clearing(数据清空)

    // 1.create a TCP protocol socket(创建一个TCP协议的套接字)
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    { // check whether the creation is successful(判断是否创建成功)
        perror("socket");
        return -1;
    }

    sock_addr.sin_family = AF_INET;         // Address family(地址族)
    sock_addr.sin_port = htons(atoi(port)); // Port, and X86 small-endian to (big-endian) network byte order(端口,并且X86小端字节序转(大端)网络字节序)
                                            //	sock_addr.sin_addr.s_addr = inet_aton("127.0.0.1");		// Struct nested struct,ip address string translation network format(结构体嵌套结构体,ip地址字符串转换网络格式)
    inet_aton(ipaddr, &sock_addr.sin_addr); // Struct nested struct,ip address string translation network format(结构体嵌套结构体,ip地址字符串转换网络格式)

    // 2.bind the IP address and port number(绑定IP地址及其端口)
    ret = bind(sock_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr_in));
    if (-1 == ret)
    {
        perror("bind");
        return -1;
    }

    // 3.network monitoring(网络监听)
    ret = listen(sock_fd, 1); // Monitor ten(监听十个)
    if (-1 == ret)
    {
        perror("listen");
        return -1;
    }

    return sock_fd;
}