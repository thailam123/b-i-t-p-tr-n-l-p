#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char buf[256];
    int pos = 0;
    char computer_name[64];
    printf(" nhap ten may tinh: ");
    scanf("%s", computer_name);

    strcpy(buf, computer_name);
    pos += strlen(computer_name);
    buf[pos] = 0;
    pos++;

    int num_drives;
    printf("Nhap so o dia: ");
    scanf("%d", & num_drives);
    getchar();
    char drive_letter;
    unsigned short drive_size;

    for (int i = 0; i < num_drives; i++)
    {
        printf("Nhap ky tu: ");
        scanf("%c",&drive_letter );
        buf[pos]=drive_letter;
        pos++;

        printf("Nhap kich thuoc: ");
        scanf("%hd",&drive_size);
        getchar();

        memcpy(buf,&drive_size,sizeof(drive_size));
        pos+=sizeof(drive_size);
    }
    printf("Buffer size: %d\n",pos);

    

    close(client)
    return 0;
}
