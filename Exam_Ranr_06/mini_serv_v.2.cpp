#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int id[64 * 1024];
int max = 0, next_id = 0;
fd_set active, readyRead, readyWrite;
char bufRead[42*4096], str[42*4096], bufWrite[42*4097];
void fatal_error()
{
    write(2, "Fatal error\n", 12);
    exit(1);
}
void send_all(int es) {
    for (int i = 0; i <= max; i++)
        if (FD_ISSET(i, &readyWrite) && i != es)
            send(i, bufWrite, strlen(bufWrite), 0);
}
int main(int ac, char **av) {
    if (ac != 2) {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }
    int port = atoi(av[1]);
    (void) port;

    bzero(&id, sizeof(id));
    FD_ZERO(&active);

    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0)
        fatal_error();

    max = serverSock;
    FD_SET(serverSock, &active);

    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = (1 << 24) | 127;
    addr.sin_port = (port >> 8) | (port << 8);

    if ((bind(serverSock, (const struct sockaddr *)&addr, sizeof(addr))) < 0)
        fatal_error();
    if (listen(serverSock, 128) < 0)
        fatal_error();

    while (1) {
        readyRead = readyWrite = active;
        if (select(max + 1, &readyRead, &readyWrite, NULL, NULL) < 0)
            continue ;

        for (int s = 0; s <= max; s++) {

            if (FD_ISSET(s, &readyRead) && s == serverSock) {
                int clientSock = accept(serverSock, (struct sockaddr *)&addr, &addr_len);
                if (clientSock < 0)
                continue ;

                max = (clientSock > max) ? clientSock : max;
                id[clientSock] = next_id++;
                FD_SET(clientSock, &active);

                sprintf(bufWrite, "server: client %d just arrived\n", id[clientSock]);
                send_all(clientSock);
                break ;
            }

            if (FD_ISSET(s, &readyRead) && s != serverSock) {

                int res = recv(s, bufRead, 42*4096, 0);

                if (res <= 0) {
                    sprintf(bufWrite, "server: client %d just left\n", id[s]);
                    send_all(s);
                    FD_CLR(s, &active);
                    close(s);
                    break ;
                }
                else {
                    for (int i = 0, j = 0; i < res; i++, j++) {
                        str[j] = bufRead[i];
                        if (str[j] == '\n') {
                            str[j] = '\0';
                            sprintf(bufWrite, "client %d: %s\n", id[s], str);
                            send_all(s);
                            j = -1;
                        }
                    }
                }
            }
        }
    }
}
