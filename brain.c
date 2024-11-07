#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char buffer[1024];
  if (argc < 3)
  {
    printf("proper argument not given\n");
    return 0;
  }
  FILE *fp, *fp1, *fp2;
  char *filename = malloc(13 * sizeof(char));
  strcpy(filename, argv[2]);
  strcat(filename, "_eb.txt");
  if ((fp = fopen(filename, "rb")) == NULL)
  {
    perror("error opening eb file through brain");
    exit(1);
  }
  strcpy(filename, argv[2]);
  strcat(filename, "_lb.txt");
  if ((fp1 = fopen(filename, "rb")) == NULL)
  {
    perror("error opening lb file through brain");
    exit(1);
  }
  strcpy(filename, argv[2]);
  strcat(filename, "_mb.txt");
  if ((fp2 = fopen(filename, "wb+")) == NULL)
  {
    perror("error opening mb file through brain");
    exit(1);
  }
  fseek(fp, 0, SEEK_END);
  fseek(fp1, 0, SEEK_END);
  fseek(fp2, 0, SEEK_END);
  int ebnew, ebold, lbnew, lbold, mbnew, mbold;
  ebnew = ftell(fp);
  ebold = ftell(fp);
  lbnew = ftell(fp1);
  lbold = ftell(fp1);
  while (1)
  {
    fseek(fp, 0, SEEK_END);
    ebnew = ftell(fp);
    fseek(fp1, 0, SEEK_END);
    lbnew = ftell(fp1);
    int ebdiff = ebnew - ebold;
    int lbdiff = lbnew - lbold;
    if (ebdiff > 0)
    {
      // data received
      fseek(fp, -ebdiff, SEEK_END);
      int n = fread(buffer, 1, ebdiff, fp);
      buffer[n] = '\0';
      printf("Message received: %s\n", buffer);
      printf("--------------\n");
      ebold = ebnew;
    }
    if (lbdiff > 0)
    {
      // msg to be sent
      fseek(fp1, -lbdiff, SEEK_END);
      int n = fread(&buffer, 1, lbdiff, fp1);
      buffer[n] = '\0';
      fseek(fp1, 0, SEEK_END);
      fseek(fp2, 0, SEEK_END);
      fwrite(buffer, 1, n - 1, fp2);
      fseek(fp2, 0, SEEK_END);
      lbold = lbnew;
    }
  }
  return 0;
}
