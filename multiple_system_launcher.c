#include <stdio.h>
#include <stdlib.h>
int main()
{
  system("gnome-terminal --title=utoob1 -- ./launcher config1");
  system("gnome-terminal --title=utoob2 -- ./launcher config2");
  system("gnome-terminal --title=utoob3 -- ./launcher config3");
  system("gnome-terminal --title=utoob4 -- ./launcher config4");
  return 0;
}
