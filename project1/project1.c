#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct Contact
{
  char name[20];
  char phoneNumber[15];
  char birthDate[8];
} Contact;

void registration(Contact phoneBook[], int *curr_pos)
{
  if (*curr_pos == MAX_SIZE)
  {
    printf("OVERFLOW\n");
    return;
  }
  printf("Name:");
  scanf("%s", phoneBook[*curr_pos].name);
  printf("Phone_number:");
  scanf("%s", phoneBook[*curr_pos].phoneNumber);
  printf("Birth:");
  scanf("%s", phoneBook[*curr_pos].birthDate);
  *curr_pos = *curr_pos + 1;
  printf("<<%d>>\n", *curr_pos);
  sort(phoneBook, curr_pos);
};

int main()
{
  Contact phoneBook[MAX_SIZE];
  int curr_pos = 0;

  int menu = 0;
  while (menu != 5)
  {
    printf("*****Menu*****\n");
    printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
    printf("Enter_the_menu_number:");
    scanf("%d", &menu);

    switch (menu)
    {
    case 1:
      registration(phoneBook, &curr_pos);
      break;

    default:
      break;
    }
  }
}