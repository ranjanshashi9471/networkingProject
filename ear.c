#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 1024
// #define LISTENPORT 1234

int main(int argc, char *argv[])
{
  unsigned int LISTENPORT = atoi(argv[1]);
  printf("Listen Port is %d\n", LISTENPORT);
  int sockfd, len, n;
  char buffer[BUFLEN];
  struct sockaddr_in receiverAddr, senderAddr;
  FILE *fp;
  char *filename = malloc(13 * sizeof(char));
  strcpy(filename, argv[2]);
  strcat(filename, "_eb.txt");
  if ((fp = fopen(filename, "rb+")) == NULL)
  {
    perror("Opening File eb failed\n");
    exit(1);
  }

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket system call failed");
    exit(EXIT_FAILURE);
  }

  memset(&receiverAddr, 0, sizeof(receiverAddr));
  memset(&senderAddr, 0, sizeof(senderAddr));

  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_addr.s_addr = INADDR_ANY;
  receiverAddr.sin_port = htons(LISTENPORT);

  if (bind(sockfd, (const struct sockaddr *)&receiverAddr,
           sizeof(receiverAddr)) < 0)
  {
    perror("bind syscall failed");
    exit(EXIT_FAILURE);
  }
  len = sizeof(senderAddr);
  /* blocking subroutines or blocking syscalls
   *   scanf("%d", &n); */
  while (1)
  {
    printf("waiting for data to be received: \n");
    n = recvfrom(sockfd, (char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *)&senderAddr, &len);
    buffer[n] = '\0';
    fseek(fp, 0, SEEK_END);
    fwrite(buffer, 1, strlen(buffer), fp);
    fseek(fp, 0, SEEK_END);
  }
  return 0;
}

/*
 *
 * these are just source codes
 * urecv.c
 * usend.c
 * systeminternal.c
 *
 * these are the programs [executables]
 * urecv
 * usend
 * systeminternal
 *
 * $./urecv
 *
 *
 *  * */
