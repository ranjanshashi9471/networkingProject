#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 1024

int getSubStr(unsigned char *destn, unsigned char *source, unsigned int start, unsigned int count)
{
  unsigned int i = 0;
  while (i < count)
  {
    destn[i] = source[start];
    i++;
    start++;
  }
  destn[i] = '\0';
  printf("Substring is %s\n", destn);
  return i + 1;
}

int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = malloc(13 * sizeof(char));
  strcpy(filename, argv[2]);
  strcat(filename, "_mb.txt");
  if ((fp = fopen(filename, "rb")) == NULL)
  {
    printf("Error opening bm file\n");
    exit(1);
  }
  int sockfd, userInput;
  char buffer[BUFLEN];
  char *messageStr =
      "a very important Good Morning message with 100s of emojis!!!";
  struct sockaddr_in receiverAddr;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  int new, old;
  new = ftell(fp);
  old = ftell(fp);
  while (1)
  {
    fseek(fp, 0, SEEK_END);
    new = ftell(fp);
    int diff = new - old;
    if (diff > 0)
    {
      fseek(fp, -diff, SEEK_END);
      int n = fread(buffer, 1, diff, fp);
      buffer[n] = '\0';
      char *tmpport = malloc(4 * sizeof(char));
      getSubStr(tmpport, buffer, 0, 4);
      tmpport[4] = '\0';

      unsigned int REMOTEPORT;
      n = sscanf(tmpport, "%d", &REMOTEPORT);
      if (n == 1)
      {
        memset(&receiverAddr, 0, sizeof(receiverAddr));
        receiverAddr.sin_family = AF_INET;
        receiverAddr.sin_port = htons(REMOTEPORT);
        receiverAddr.sin_addr.s_addr = INADDR_ANY;
        sendto(sockfd, (const char *)&buffer[4], strlen(buffer) - 5, 0, (const struct sockaddr *)&receiverAddr, sizeof(receiverAddr));
        printf("message sent.....\n");
      }
      else
      {
        printf("Message Sending Aborted and Mouth is stopped\n");
        close(sockfd);
        return 0;
      }
      old = new;
    }
  }
}
