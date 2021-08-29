#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char const *argv[]) {
    int   serv_sd, clnt_sd;
    FILE *fp;
    char  buf[ BUF_SIZE ];
    int   read_cnt;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t          clnt_adr_sz;

    if (2 != argc) {
        printf("wrong!");
        exit(1);
    }

    printf("%d", htons(atoi(argv[ 1 ])));

    fp                       = fopen("../ch7/file_server.c", "rb");
    serv_adr.sin_family      = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port        = htons(atoi(argv[ 1 ]));

    if (-1 == bind(serv_sd, (struct sockaddr *) &serv_adr, sizeof(serv_adr))) {
        printf("error!");
        exit(1);
    }
    listen(serv_sd, 5);

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd     = accept(serv_sd, (struct sockaddr *) &clnt_adr, &clnt_adr_sz);

    while (1) {
        //从文件流中读取数据，buffer为接收数据的地址，size为一个单元的大小，count为单元个数，stream为文件流
        //返回实际读取的单元个数
        read_cnt = fread((void *) buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE) {
            write(clnt_sd, buf, read_cnt);
            break;
        }
        write(clnt_sd, buf, BUF_SIZE);
    }

    shutdown(clnt_sd, SHUT_WR);
    read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client: %s \n", buf);

    fclose(fp);
    close(clnt_sd);
    close(serv_sd);

    return 0;
}
