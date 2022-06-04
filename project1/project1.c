// Project#3 for Advanced C course @ Sejong University
// Solved by Abdiganiev Saidbek (21012865)
// Check the commit history at https://github.com/Laroikin/advanced-c-project

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct Contact
{
  // All char arrays have an additiona byte due to the way C handles strings (the size of string itself + the null terminator)
  char name[21];
  char phoneNumber[16];
  char birthDate[9];
} Contact;

void swap(Contact *A, Contact *B)
{
  // Simple swap using pointers
  Contact temp = *A;
  *A = *B;
  *B = temp;
}

void sort(Contact phoneBook[], int curr_pos)
{
  // Implementing a simple bubble sort algorithm to sort the contacts by the name field
  int swapped = 0;
  for (int i = 0; i < curr_pos - 1; i++)
  {
    swapped = 0;
    for (int j = 0; j < curr_pos - i - 1; j++)
    {
      if (strcmp(phoneBook[j].name, phoneBook[j + 1].name) > 0)
      {
        swap(&phoneBook[j], &phoneBook[j + 1]);
        swapped = 1;
      }
    }

    if (swapped == 0)
      break;
  }
}

void registration(Contact phoneBook[], int *curr_pos)
{
  //If current size is bigger or equal to max size, return 
  if (*curr_pos >= MAX_SIZE)
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
  printf("%s %s %s\n", phoneBook[*curr_pos].name, phoneBook[*curr_pos].phoneNumber, phoneBook[*curr_pos].birthDate);
  //Incrementing the current size
  *curr_pos = *curr_pos + 1;
  printf("<<%d>>\n", *curr_pos);
  //Sorting after adding to array
  sort(phoneBook, *curr_pos);
};

void showAll(Contact phoneBook[], int curr_pos)
{
  // Simply iterating through every element in array
  for (int i = 0; i < curr_pos; i++)
  {
    printf("%s %s %s \n", phoneBook[i].name, phoneBook[i].phoneNumber, phoneBook[i].birthDate);
  }
}

void delete (Contact phoneBook[], int *curr_pos)
{
  char nameToDelete[21];
  printf("Name:");
  scanf("%s", nameToDelete);

  int flag = 0;

  for (int i = 0; i < *curr_pos; i++)
  {
    if (strcmp(phoneBook[i].name, nameToDelete) == 0)
    {
      //Rewrite everything from the current position till the end
      while (i != *curr_pos - 1)
      {
        phoneBook[i] = phoneBook[i + 1];
        i++;
      }
      //Decrement the size
      *curr_pos = *curr_pos - 1;
      //Change the flag
      flag = 1;
      break;
    }
  }

  if (!flag)
  {
    //If not found, displays this message
    printf("NO MEMBER\n");
  }
}

int getMonth(Contact phoneBook)
{
  //Function which gets an integer of a month of the given element of the array
  char a = phoneBook.birthDate[5];
  char b = phoneBook.birthDate[4];
  int res = 10 * (b - '0') + (a - '0');
  return res;
}

void findByBirth(Contact phoneBook[], int curr_pos)
{
  printf("Birth:");
  int monthToFind;
  scanf("%d", &monthToFind);
  for (int i = 0; i < curr_pos; i++)
  {
    //Iterating through all elements in the array and displaying only matching entries
    int month = getMonth(phoneBook[i]);
    if (month == monthToFind)
    {
      printf("%s %s %s \n", phoneBook[i].name, phoneBook[i].phoneNumber, phoneBook[i].birthDate);
    }
  }
}

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

    case 2:
      showAll(phoneBook, curr_pos);
      break;

    case 3:
      delete (phoneBook, &curr_pos);
      break;

    case 4:
      findByBirth(phoneBook, curr_pos);
      break;

    default:
      break;
    }
  }
}