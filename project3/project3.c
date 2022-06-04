#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Contact
{
  // Swaping predefined variable size to pointers
  char *name;
  char *phoneNumber;
  char *birthDate;
} Contact;

char *getln()
{
  // Function to allocate exact amount of memory for each string in phoneBook
  char *str;

  char buf[101]; // Buffer

  scanf("%s", buf); // Read the string and store it in buffer

  str = (char *)malloc(strlen(buf) + 1);

  strcpy(str, buf);

  return str;
}

char *getlnf(char *passed_str)
{
  // Function to allocate exact amount of memory for each string in phoneBook from a string
  char *str;

  char buf[101]; // Buffer

  sscanf(passed_str, "%s", buf); // Read the string and store it in buffer

  str = (char *)malloc(strlen(buf) + 1);

  strcpy(str, buf);

  return str;
}

void swap(Contact *A, Contact *B)
{
  // Simple swap using pointers
  Contact temp = *A;
  *A = *B;
  *B = temp;
}

void sort(Contact *phoneBook, int curr_pos)
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

void registration(Contact **phoneBook, int *curr_pos, int size)
{
  if (*curr_pos >= size)
  {
    printf("OVERFLOW\n");
    return;
  }
  if (*curr_pos != 0)
  {
    // Reallocating memory
    *phoneBook = realloc(*phoneBook, (*curr_pos + 1) * sizeof(Contact));
  }
  printf("Name:");
  // I'm using this weird syntax to get an access to basically a pointer to a pointer to a pointer (I love low level programming!!!!!!!)
  (*phoneBook)[*curr_pos].name = getln();
  printf("Phone_number:");
  (*phoneBook)[*curr_pos].phoneNumber = getln();
  printf("Birth:");
  (*phoneBook)[*curr_pos].birthDate = getln();

  // Incrementing the current position
  *curr_pos = *curr_pos + 1;
  printf("<<%d>>\n", *curr_pos);
  // Sorting after adding to array
  sort(*phoneBook, *curr_pos);

  // This project took way much time than I expected (i hate pointers)
};

void showAll(Contact *phoneBook, int curr_pos)
{
  // Simply iterating through every element in array
  for (int i = 0; i < curr_pos; i++)
  {
    printf("%s %s %s \n", phoneBook[i].name, phoneBook[i].phoneNumber, phoneBook[i].birthDate);
  }
}

void delete (Contact **phoneBook, int *curr_pos)
{
  char *nameToDelete;
  printf("Name:");
  nameToDelete = getln();

  int flag = 0;

  for (int i = 0; i < *curr_pos; i++)
  {
    if (strcmp((*phoneBook)[i].name, nameToDelete) == 0)
    {
      // Rewrite everything from the current position till the end
      while (i != *curr_pos - 1)
      {
        (*phoneBook)[i] = (*phoneBook)[i + 1];
        i++;
      }
      // Free the memory allocated to struct fields to prevent memory leak
      free((*phoneBook)[*curr_pos].birthDate);
      free((*phoneBook)[*curr_pos].name);
      free((*phoneBook)[*curr_pos].phoneNumber);
      *phoneBook = realloc(*phoneBook, (*curr_pos - 1) * sizeof(Contact));
      // Decrement the size
      *curr_pos = *curr_pos - 1;
      // Change the flag
      flag = 1;
      break;
    }
  }

  if (!flag)
  {
    // If not found, displays this message
    printf("NO MEMBER\n");
  }
}

int getMonth(Contact phoneBook)
{
  // Function which gets an integer of a month of the given element of the array
  char a = phoneBook.birthDate[5];
  char b = phoneBook.birthDate[4];
  int res = 10 * (b - '0') + (a - '0');
  return res;
}

void findByBirth(Contact *phoneBook, int curr_pos)
{
  printf("Birth:");
  int monthToFind;
  scanf("%d", &monthToFind);
  for (int i = 0; i < curr_pos; i++)
  {
    // Iterating through all elements in the array and displaying only matching entries
    int month = getMonth(phoneBook[i]);
    if (month == monthToFind)
    {
      printf("%s %s %s \n", phoneBook[i].name, phoneBook[i].phoneNumber, phoneBook[i].birthDate);
    }
  }
}

void regFromFile(Contact **phoneBook, int *curr_pos, int size)
{
  FILE *ptr;
  if ((ptr = fopen("contacts.txt", "r")) == NULL)
  {
    printf("Error! opening file");

    // Program exits if the file pointer returns NULL.
    exit(1);
  }

  char buf[303];
  char *str;
  // Reading file line by line
  while ((str = fgets(buf, sizeof(buf), ptr)) != NULL)
  {
    if (*curr_pos >= size)
    {
      printf("OVERFLOW\n");
      return;
    }

    if (*curr_pos != 0)
    {
      // Reallocating memory
      *phoneBook = realloc(*phoneBook, (*curr_pos + 1) * sizeof(Contact));
    }
    // I'm using this weird syntax to get an access to basically a pointer to a pointer to a pointer (I love low level programming!!!!!!!)
    char name[101];
    char phone[101];
    char birth[101];
    sscanf(str, "%s %s %s", name, phone, birth);
    (*phoneBook)[*curr_pos].name = getlnf(name);
    (*phoneBook)[*curr_pos].phoneNumber = getlnf(phone);
    (*phoneBook)[*curr_pos].birthDate = getlnf(birth);

    // Incrementing the current position
    *curr_pos = *curr_pos + 1;
    // Sorting after adding to array
    sort(*phoneBook, *curr_pos);

    // This project took way much time than I expected (i hate pointers)
  }
  fclose(ptr);
}

int main()
{
  int max_num;
  printf("Max_num:");
  scanf("%d", &max_num);
  // Allocating minimum amount of memory
  Contact *phoneBook = (Contact *)malloc(sizeof(Contact));
  int curr_pos = 0;

  int menu = 0;
  while (menu != 6)
  {
    printf("*****Menu*****\n");
    printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
    printf("Enter_the_menu_number:");
    scanf("%d", &menu);

    switch (menu)
    {
    case 1:
      // Passing and address to pointer to reallocate it later
      registration(&phoneBook, &curr_pos, max_num);
      break;

    case 2:
      showAll(phoneBook, curr_pos);
      break;

    case 3:
      // Same thing as with the registration function
      delete (&phoneBook, &curr_pos);
      break;

    case 4:
      findByBirth(phoneBook, curr_pos);
      break;

    case 5:
      regFromFile(&phoneBook, &curr_pos, max_num);
      break;

    default:
      break;
    }
  }
  // Freeing phoneBook
  free(phoneBook);
}