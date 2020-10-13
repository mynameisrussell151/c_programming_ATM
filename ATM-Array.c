#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#define MAX 1000

typedef struct list {
  int A[MAX];
  char name[MAX][30];
  int pinCode[7];
  int last;
  float balance[MAX];
}
LIST;

LIST L;

void retrieve();
void makenull();
void insert(int x, char acc_name1[30], float at, int b);
void del(int x);
void update(int x, int b);
void display(int x);
void withdraw(int x, int a);
void deposit(int x, int a);
void balance();
void fundTransfer(int x, int y, int amount);
int isfull();
int isempty();
int locate(int x);
int locate2(int x);
int locatePin(int x);
int menu(int x);
int pincode();
int insertcard();
void removecard();
char pin[7];
int cfileexists(const char * filename);
int rand(void);
int clean_stdin();

main() {
  //Use to save file on ATM Card (Flash Drive)
  char * filename = "h:/sat.db";
  int exist = cfileexists(filename);
  int i, p, data, data1, opt, opt1, Q1, Q2, U1 = 0, U2, r, h = 0, lower = 100000, upper = 999999;
  int cp = 1, tp;
  float a, at;
  char name[31];
  char c;
  time_t t;
  srand((unsigned) time( & t));
  data = (rand() % (upper - lower + 1)) + lower;

  r = rand() % 2;
  //Simulate if ATM is currently offline or not
  if (r == h) {
    printf("Sorry! This ATM is temporary out of service..\n");
    printf("Please Run Again\n");
    exit(0);
  } else {
    printf("Welcome to Bank Karote Bank! Press any key to continue..");
    getch();
    insertcard();
    printf("Card Successfully Inserted!\n");
    system("cls");
    printf("Press Any Key To Continue!\n");
    //Check whether user already have account
    if (!exist) {
      system("cls");
      at = 0;
      printf("Create Bank Account\n");
      printf("Account Number: %d\n", data);
      printf("Account Name: ");
      scanf("%s", & name);
      printf("PinCode: ");
      scanf("%d", & Q2);
      printf("Balance: %6.1f\n ", at);
      insert(data, name, at, Q2);
      printf("Processing....\n");
      Sleep(1500);
      printf("Account Successfully Created");
    } else {
      makenull();
      retrieve();
      save();
      save1();
    }
    U1 = pincode();

    while (1) {
      opt = menu(U1);
      switch (opt) {
      case 1:

        system("cls");
        printf("Deposit Mode\n");
        printf("Deposit Amount: ");
        while (((scanf("%d%c", & Q1, & c) != 2 || c != '\n') && clean_stdin())) {
          if (Q1 != 2 || c != 2 || c != '\n' && clean_stdin()) {
            printf("Incorrect Input. Please Try Again\n");
            getch();
            system("cls");
            printf("Deposit Amount: ");
            getch();
          } else {
            printf("Success!\n");
            getch();
          }
        }
        deposit(U1, Q1);
        break;
      case 2:
        system("cls");
        printf("Withdrawal Mode\n");

        printf("Withdrawal Amount: ");
        while (((scanf("%d%c", & Q1, & c) != 2 || c != '\n') && clean_stdin())) {
          if (Q1 != 2 || c != 2 || c != '\n' && clean_stdin()) {
            printf("Incorrect Input. Please Try Again\n");
            getch();
            system("cls");
            printf("Withdraw Amount: ");
            getch();
          } else {
            printf("Success\n");
            getch();
          }
        }
        withdraw(U1, Q1);
        break;
      case 3:
        display(U1);
        break;
      case 4:
        system("cls");
        printf("Change PinCode Mode\n");
        printf("New PinCode: ");
        scanf("%d", & Q2);
        update(U1, Q2);
        break;
      case 5:
        system("cls");
        printf("Fund Transfer:\n");
        do {
          printf("Enter Destination Account Number: ");
        } while (((scanf("%d%c", & data1, & c) != 2 || c != '\n') && clean_stdin()));
        do {
          printf("Enter Transfer Amount: ");
        } while (((scanf("%d%c", & Q1, & c) != 2 || c != '\n') && clean_stdin()));

        fundTransfer(U1, data1, Q1);
        break;
      case 6:
        save();
        save1();
        removecard();
        printf("Thank You For Banking With Us!\n");
        exit(0);
        //case 7: system("cls"); printf("Deactivate Mode\n");printf("ID: ");scanf("%d",&data);del(data);break;
      default:
        printf("\n 1 -8 lang.");
        getch();

      }
    }
  }
}
int cfileexists(const char * filename) {
  /* try to open file to read */
  FILE * file;
  if (file = fopen(filename, "r")) {
    fclose(file);
    return 1;
  }
  return 0;
}

void makenull() {
  L.last = -1;
}

int locate(int x) {
  int i;
  for (i = 0; i <= L.last; i++)
    if (x == L.A[i])
      return (i);
  return (-1);
}

int locatePin(int x) {
  int i;
  for (i = 0; i <= L.last; i++)
    if (x == L.pinCode[i])
      return (i);
  return (-1);
}

int locate2(int x) {
  int i;
  for (i = 0; i <= L.last; i++)
    if (x < L.A[i])
      return (i);
  return (i);
}

void insert(int x, char acc_name1[30], float at, int b) {
  int i, duplicate, p1;
  p1 = locate2(x);
  duplicate = locate(x);
  if (isfull()) {
    printf("List is full.");
    getch();
  } else {

    if (duplicate >= 0) {
      printf("Account No. %d already exist.", x);
      getch();
    } else {
      for (i = L.last; i >= p1; i--) {

        strcpy(L.name[i + 1], L.name[i]);
        L.balance[i + 1] = L.balance[i];
        L.pinCode[i + 1] = L.pinCode[i];
      }

      L.A[p1] = x;
      strcpy(L.name[p1], acc_name1);
      L.balance[p1] = at;
      L.pinCode[p1] = b;
      L.last++;
      getch();
    }

  }
}

void update(int x, int b) {
  int p;
  p = locatePin(x);

  if (isempty()) {
    printf("List is empty.");
    getch();
  } else if (p < 0) {
    printf("Processing....\n");
    Sleep(2000);
    printf("Old PinCode Does Not Exist");
    getch();
  } else if (x == b) {
    printf("Processing....\n");
    Sleep(2000);
    printf("Your PinCode Cannot Not Be The Same.");
    getch();
  } else {
    printf("Processing....\n");
    Sleep(2000);
    printf("Change PinCode Successfully.\n");
    getch();
    L.pinCode[p] = x;
    L.pinCode[p] = b;
    save();
    save1();
    printf("Please Remove Your Card And Insert Again");
    Sleep(2000);
    exit(0);
  }

}

void withdraw(int x, int a) {
  int p;
  int tae = 1;
  p = locatePin(x);
  if (isempty()) {
    printf("List is empty.");
    getch();
  } else {
    if (L.balance[p] < tae) {
      printf("Processing....\n");
      Sleep(2000);
      printf("Insufficient Balance. Please Try Again");

      getch();
    } else if (a % 100 != 0) {
      printf("Processing....\n");
      Sleep(2000);
      printf("Only denominations of 100s are allowed");
      getch();
    } else if (L.balance[p] < a) {
      printf("Processing....\n");
      Sleep(2000);
      printf("Withdrawal Amount Is Greater Than Your Balance. Please Try Again");
      getch();
    } else {
      printf("Processing....\n");
      Sleep(2000);
      printf("Withdraw Successfully.");
      float tae = L.balance[p] - a;
      L.pinCode[p] = x;
      L.balance[p] = tae;
      getch();
    }

  }

}
//Deposit Function
void deposit(int x, int a) {
  int p;
  p = locatePin(x);
  if (isempty()) {
    printf("List is empty.");
    getch();
  } else {
    printf("Processing....\n");
    Sleep(2000);
    printf("Deposit Successfully.");
    float tae = L.balance[p] + a;
    L.pinCode[p] = x;
    L.balance[p] = tae;
    getch();

  }

}

//Fund Transfer Function
void fundTransfer(int x, int y, int amount) {
  int p, q, t;
  p = locatePin(x); //Locating Your Acc Number
  q = locate(y); //Locating Destination Acc Number
  t = y;

  if (isempty()) {
    printf("List is empty.");
    getch();
  } else if (q < 0) {
    printf("Processing....\n");
    Sleep(2000);
    printf("Destination Account Number Not Found.");
    getch();
  } else if (L.A[p] == t) {
    printf("Processing....\n");
    Sleep(2000);
    printf("You Cannot Transfer To Your Own Account.");
    getch();
  } else {

    if (L.balance[p] < amount) {
      printf("Processing....\n");
      Sleep(2000);
      printf("Insufficient Balance! Please Try Again.");
      getch();
    } else {
      printf("Processing....\n");
      Sleep(2000);
      printf("Fund Transfer Complete!");

      //Account Owner
      float tae = L.balance[p] - amount;
      L.pinCode[p] = x;
      L.balance[p] = tae;
      //Account Destination
      L.A[q] = y;
      L.balance[q] += amount;
      getch();

    }

  }

}

//Dele
void del(int x) {
  int i, p;
  if (isempty()) {
    printf("List is empty.");
    getch();
  } else {
    p = locate(x);
    if (p < 0) {
      printf("Not found.");
      getch();
    } else {
      for (i = p; i < L.last; i++) {
        L.A[i] = L.A[i + 1];
      }
      L.last--;
    }
  }
}

void display(int x) {
  int i, p;
  p = locatePin(x);
  float a;
  system("cls");
  printf("Check Balance\n");
  printf("Account Number\tAccount Name\tBalance\n");

  printf(" %d\t\t %s\t\t %6.1f\n", L.A[p], L.name[p], L.balance[p]);

  getch();
}
int isfull() {
  return (L.last == MAX - 1);
}
int isempty() {
  return (L.last == -1);
}

int menu(int x) {
  int p;
  p = locatePin(x);
  char * m[] = {
    "Deposit",
    "Withdraw",
    "Balance Inquiry",
    "Change PinCode",
    "Fund Transfer",
    "Exit"
  };
  int i, op;
  system("cls");
  printf("Welcome To Bank Karote (Bank Name: %s)\n\n", L.name[p]);
  for (i = 0; i < 6; i++) {
    printf("%d.) %s\n", i + 1, m[i]);
  }
  printf("Select (1-6): ");
  scanf("%d", & op);
  return (op);
}

//Save Information to Main Database
void save() {
  FILE * fp;
  int i;
  fp = fopen("sat.db", "w+");
  for (i = 0; i <= L.last; i++)
    fprintf(fp, "%d %s %f %d\n", L.A[i], L.name[i], L.balance[i], L.pinCode[i]);
  fclose(fp);
}

//Save information to card (Flash Drive)
void save1() {
  FILE * fp1;
  int i;
  fp1 = fopen("h:\sat.db", "w+");
  for (i = 0; i <= L.last; i++)
    fprintf(fp1, "%d %s %f %d\n", L.A[i], L.name[i], L.balance[i], L.pinCode[i]);
  fclose(fp1);
}

//Retrieve Info on Main Database
void retrieve() {
  FILE * fp;
  float at;
  int i, d, e, a1;
  char nam[31];
  fp = fopen("sat.db", "r+");
  while (!feof(fp)) {
    fscanf(fp, "%d %s %f %d \n", & d, nam, & at, & e);
    insert(d, nam, at, e);
  }
  fclose(fp);
}

int pincode() {
  int q, s;
  int trye = 2, mali = -1;
  int tim;
  int a = 1;
  int b = 1;

  while (a == b) {
    system("cls");
    printf("Enter PinCode:   ");
    scanf("%d", & q);
    s = locatePin(q);

    if (s < 0) {
      printf("Checking....\n");
      Sleep(1000);
      printf("Pin Code Wrong. You Got %d chances left\n", trye);
      getch();
      trye--;

      if (trye == mali) {
        printf("Sorry! Too Many Attempts Tried For Today And Your Account Has Been Locked\n");
        printf("Please Go To Your Nearest Bank\n");
        exit(0);
      }
    } else if (isempty()) {
      printf("List is empty.");
      getch();
    } else {
      printf("Checking....\n");
      Sleep(1000);
      printf("Successful....Press Any Key To Continue\n");
      getch();
      L.pinCode[s] = q;
      a = 2;
    }
  }

  return q;

  /*FILE *fp;
  int i;
  fp=fopen("d:\pin.db", "r+");
  for (int i=0; i<6; i++){
      pin[i] = getch()+5;
      putch('*');
  }
  pin[i]='\0';
  printf("Pin Code = %s",pin);
  fprintf(fp,"%s",pin);
  fclose(fp);*/
}

int insertcard() {
  FILE * fp;
  int a;
  system("cls");
  printf("Please Insert Card\n");

  do {
    fp = fopen("h:/user.db", "w+");
    Beep(600, 500);
    printf("\a");

  } while (fp == NULL);

}

void removecard() {
  FILE * fp;
  system("cls");
  printf("Please remove Card\n");
  do {
    fp = fopen("h:/user.db", "w+");
    Beep(600, 500);
    printf("\a");

  } while (fp != NULL);

}

int clean_stdin() {
  while (getchar() != '\n');
  return 1;
}
