#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  FILE *fp, *fp1;
  size_t BUFLEN = 1024;
  int pid[3];
  char ids[4][7];
  char ports[4][5];
  char *filename = malloc(13 * sizeof(char));
  int i = 0;
  if (argc < 2)
  {
    printf("Config File not given\n");
    return 1;
  }
  if ((fp = fopen(argv[1], "rb")) == NULL)
  {
    printf("Error opening config file\n");
    return 1;
  }
  while (i < 4)
  {
    sprintf(ids[i], "000000");
    fread(&ids[i], 1, 6, fp);
    ids[i][6] = '\0';
    sprintf(ports[i], "0000");
    fread(&ports[i], 4, 1, fp);
    ports[i][4] = '\0';
    i++;
  }
  fflush(fp);
  ids[0][0] = 'u'; // just making sure everything is intact after checking
  if (filename == NULL)
  {
    perror("Malloc Error");
    exit(1);
  }
  strcpy(filename, ids[0]);
  strcat(filename, "_eb.txt");
  fp = fopen(filename, "w");
  fflush(fp);
  strcpy(filename, ids[0]);
  strcat(filename, "_mb.txt");
  fp = fopen(filename, "w");
  fflush(fp);
  strcpy(filename, ids[0]);
  strcat(filename, "_lb.txt");
  fp = fopen(filename, "w");

  char *brain[] = {"./brain", ports[0], ids[0], NULL};
  char *ear[] = {"./ear", ports[0], ids[0], NULL};
  char *mouth[] = {"./mouth", ports[0], ids[0], NULL};
  if ((pid[0] = fork()) == 0)
  {
    execv(brain[0], brain);
  }
  if ((pid[1] = fork()) == 0)
  {
    execv(ear[0], ear);
  }
  if ((pid[2] = fork()) == 0)
  {
    execv(mouth[0], mouth);
  }
  while (1)
  {
    printf("Enter the sr. no. to send msg and any other key to stop\n");
    for (i = 1; i < 4; i++)
    {
      printf("%d.\t %s\n", i, ids[i]);
    }
    char tmpbuff[10];
    int userInput;
    fgets(tmpbuff, 10, stdin);
    int n = sscanf(tmpbuff, "%d", &userInput);
    if (n == 1 && userInput > 0 && userInput < 4)
    {
      char temp[BUFLEN - 13];
      char buffer[BUFLEN];
      printf("Enter Msg to send\n");
      fgets(temp, BUFLEN - 13, stdin);
      strcpy(buffer, ports[userInput]);
      strcat(buffer, ids[0]);
      // strcat(buffer, ":");
      strcat(buffer, temp);
      fseek(fp, 0, SEEK_END);
      fwrite(&buffer, 1, strlen(buffer) - 1, fp);
      fseek(fp, 0, SEEK_END);
    }
    else
    {
      fseek(fp, 0, SEEK_END);
      printf("UI Closed\n");
      fflush(fp);
      break;
    }
  }
  return 0;
}