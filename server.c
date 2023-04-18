#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client = accept(listener,
                        (struct sockaddr *)&client_addr,
                        &client_addr_len);

    printf("Accepted socket %d from IP: %s:%d\n",
           client,
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));
    // bài làm
    // buf sau khi tách chuỗi
    char buf1[2048];

    // tách chuỗi ký tự lưu vào buf1
    const char s[6] = " \n";
    char *token;

    token = strtok(buf, s);

    while (token != NULL)
    {
        strcat(buf1, token);
        token = strtok(NULL, s);
    }
    // kết thúc bài làm
    fclose(f);
    close(client);
    close(listener);
}
