//
//  server_main.c
//
//
//  Created by Espen Næss on 18.06.14.
//  Copyright (c) 2014 Espen Næss. All rights reserved.
//

#include "server_main.h"
#include <string.h>
#include <netdb.h>

int main(int argc, const char * argv[])
{
    run_server();
    return 0;
}

void run_server(void) { // SERVERKODE
    int ny_socket, status_get_addr, status_sock, ja;
    char buffer[1024];
    char recv_meld[1024];

    struct addrinfo hint;
    struct addrinfo *server_info;

    struct sockaddr_storage server_lagring;
    socklen_t addr_str;

    memset(&hint, 0, sizeof(hint));

    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    //hint.ai_flags = AI_PASSIVE;

    if ((status_get_addr = getaddrinfo("192.168.0.14", "7864", &hint, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo feilet med feilmelding: %s\n", gai_strerror(status_get_addr));
    }

    status_sock = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

    printf("status: %i", status_sock);

    if (setsockopt(status_sock, SOL_SOCKET, SO_REUSEADDR, &ja, sizeof(ja)) == -1) {
        perror("setsockopt feilet");
    }

    bind(status_sock, server_info->ai_addr, server_info->ai_addrlen);
    if ((listen(status_sock, 5)) == 0) {
        printf("Nå lytter den\n");
    } else {
        printf("Nå feilet lyttinga");
    }

    addr_str = sizeof(server_lagring);
    ny_socket = accept(status_sock, (struct sockaddr *)&server_lagring, &addr_str);

    strcpy(buffer, "Heisann du der!");
    send(ny_socket, buffer, sizeof(buffer), 0);
    printf("buffer: %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
    printf("buffer: %s\n", buffer);

    recv(ny_socket, &recv_meld, 1024, 0);
    printf("MOTATT: %s\n", recv_meld);

    shutdown(ny_socket, 2);
    shutdown(status_sock, 2);
}
