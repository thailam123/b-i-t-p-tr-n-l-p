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

    char buf[256];
    int ret = recv(client, buf, sizeof(buf), 0);
    buf[ret] = 0;

    printf("%d bytes received\n", ret);

    int pos = 0;
    char computer_name[64];
    strcpy(computer_name, buf);
    pos = strlen(computer_name) + 1;
    int num_drives = (ret - pos) / 3;

    for (int i = 0; i < num_drives; i++)
    {
        char drive_letter = buf[pos];
        pos++;
        unsigned short drive_size;
        memcpy(&drive_size, buf + pos, sizeof(drive_size));
        pos += sizeof(drive_size);

        printf("%c - ")
    }
}
