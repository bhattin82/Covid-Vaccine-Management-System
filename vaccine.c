// C preprocessing directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


// Define constants (macros)
#define MAX_PHONE_LENGTH 9999999999
#define MAX_ID_LENGTH 9999999999


// Creating a linked list structure
typedef struct linked_list{
    int age;
    char name[50];
    char gender[50];
    char vaccine[50];
    long phone_number;
    long id_number;
    struct linked_list *next;
} Node;


// Function Declarations 
bool access_system();
void time_delay(int);
Node *read_listfile(char *);
bool selection(Node *,char *,char *);
void display_currentdata(Node *);
void insertnode_data(Node *,char *);
int append_node_to_file(Node *, char *);
bool search_node_data(Node*);
Node *bubblesort_priority_person(Node *);
int list_nodes(Node *);
Node *none_vaccine_list(Node *,int);
void print_write_priority_file(Node *,char *);
int update_info(Node *);
Node *delete_head(Node *);
void delete_after(Node *,char *);
bool check_length(long,long);
void free_memory(Node *);


/*
The main function calls the access_system function.
If the access_system function returns 0, then the read_listfile function is called.
The program calls the selection function that prints the user options.
However, if the access system returns 1, the user has to wait for some time before the access_system function is called again.
*/


int main(int argc,char ** argv){

    Node *individual=NULL;
    int result;
    int seconds=1;
    result=access_system();

    while (result!=0){   
      time_delay(seconds);
      result=access_system();
    }

    individual=read_listfile(argv[1]);
    bool output=selection(individual,argv[1],argv[2]);

    if (output==0) {
      printf("Success!\n");
    }
    
    return 0;
}


/* This function has a pre-defined username and password.  
If the correct credentials are entered, then the user is granted access (EXIT_SUCCESS).
If not, then the user is given three attempts for a successful login.
If all three attempts are unsuccessful, the program returns EXIT_FAILURE to the main function
*/


bool access_system(){

char correct_username[]="bhattin82";
char correct_password[]="*********";
char entered_username[50];
char entered_password[50];
int attempt=0;

while (attempt!=3){
   printf("Enter your username:");
   scanf("%s",entered_username);
   printf("Enter your password:");
   scanf("%s",entered_password);

   if (((strcmp(entered_username,correct_username))==0) && ((strcmp(entered_password,correct_password))==0)){
        printf("\n               Welcome to the Covid Vaccine Management System!                  \n");
      attempt=3;
      return EXIT_SUCCESS;
    
   } 

  else {
      printf("Credentials are incorrect!\n");
      attempt++;

      if (attempt==2) {
         printf("\nThis is your last attempt!\n");
      }
      
}
}
return EXIT_FAILURE;
}

// This function uses a for loop to create a time delay for 5 seconds after 3 unsuccessful login attempts. 
void time_delay(int secs){
  printf("\nPlease wait for a few seconds\n");
  for (int delay=0; delay<5;delay++){
    sleep(secs);
    printf("%d seconds\n",delay+1);
  }
}


/*
This function opens the file in read mode.
If the file is empty, we return NULL.
A while loop is used to iterate until the end of file (feof).
The data is read from the file (fscanf) using the file pointer.
Memory is allocated (malloc) for each Node.
The data (name, gender, age, phone number, id number, vaccine) is stored in the linked list for each node.
Next, we create the linked list by linking all the nodes (e.g. A->B->C->D->E->NULL)
The file is closed. 
The head node is returned.
*/


Node *read_listfile(char *filename){
 
   Node *head_node=NULL;
   Node *current_node=NULL;
   Node information;
   Node *person=NULL;
   FILE *file_pointer=NULL;
 
   file_pointer=fopen(filename,"r");
   if (file_pointer==NULL) {
       return head_node;
   }
   while (feof(file_pointer)!=1){   
     if (fscanf(file_pointer,"%s %s %d %ld %ld %s",information.name,information.gender,&information.age,&information.phone_number,&information.id_number,information.vaccine)!=EOF){
        person=(struct linked_list*)malloc(sizeof(Node)); 
        person->next=NULL;
        strcpy(person->name,information.name);
        strcpy(person->gender,information.gender);
        person->age=information.age;
        person->phone_number=information.phone_number;
        person->id_number=information.id_number;
        strcpy(person->vaccine,information.vaccine);
     if (head_node==NULL){
         head_node=person;
         current_node=head_node;
     }
     else if (head_node!=NULL) {
        current_node->next=person;
        current_node=current_node->next;
     }
}
}
fclose(file_pointer);
return head_node;
}


/*
This function requires the user to enter an option.
The following operations can be performed:
1.Current Database 2.Add Record 3.Delete Record 4.Update Record 5.Search Record 6.Priority Individuals (Not vaccinated) 7.Log Out
Then, the relevant functions are called. 
If there is some error, this function will display that too.
This function recursively calls itself until the user logs out.
*/


bool selection(Node *person, char *filename, char *filename2){
  Node *list_node=NULL;
  char choice[50];
  int found=1;
  Node *new_node=NULL;
  char delete_name[50]="";
  int node_count=0;
  int head_remove_count=0;
  int other_remove_count=0;
  printf("\nPlease Choose from the following:");
  printf("\n1.Current Database 2.Add Record 3.Delete Record 4.Update Record 5.Search Record 6.Priority Individuals (Not vaccinated) 7.Log Out\n");
  printf("\nPlease enter your choice:");
  scanf("%s",choice);
  
  if ((strcmp(choice,"1")==0)){
    display_currentdata(person);
    selection(person,filename,filename2);
  }

  else if ((strcmp(choice,"2")==0)){
    insertnode_data(person,filename);
    print_write_priority_file(person,filename2);
    selection(person,filename,filename2);
  }

  else if ((strcmp(choice,"3")==0)){
   node_count=list_nodes(person);
   printf("Please enter the name to delete the record:");
   scanf("%s",delete_name);  
    if (strcmp(person->name,delete_name)==0){
       new_node=delete_head(person); 
       if (head_remove_count!=node_count){
         printf("\nRecord Deleted!\n");
       }
       else{
        printf("\nRecord NOT found!\n");
       }

       selection(new_node,filename,filename2);
    }  
    else {
       delete_after(person,delete_name); 
       other_remove_count=list_nodes(person);
     
       if (other_remove_count!=node_count){
         printf("\nRecord Deleted!\n");
       }
       else{
        printf("\nRecord NOT found!\n");
       }
       selection(person,filename,filename2); 
      }
  }

  else if ((strcmp(choice,"4")==0)){
   found=update_info(person);
   if (found==0) {
      printf("\nRecord Updated!\n");
      print_write_priority_file(person,filename2); 
   }
   else if (found==1) {
      printf("\nRECORD NOT FOUND!\n");
   }
   else {
     printf("\nUnable to update due to invalid phone number(should be 10 digits)!\n");
   }
   selection(person,filename,filename2);
   }
 
  else if ((strcmp(choice,"5")==0)){
    found=search_node_data(person);
     if (found==0) {
       printf("\nRecord found!\n");
     }
     else {
      printf("\nRECORD NOT FOUND!\n");
    }  
   selection(person,filename,filename2);
  }
  
  else if ((strcmp(choice,"6")==0)){
   list_node=bubblesort_priority_person(person);
   print_write_priority_file(list_node,filename2);
   free_memory(list_node);
   selection(person,filename,filename2);
  }
 
  else if ((strcmp(choice,"7")==0)){
  free_memory(person);
  printf("\nLogged Out!\n");
  return EXIT_SUCCESS;
  }
  else {
  printf("\nInvalid Option!\n"); 
  free_memory(person);
}
return EXIT_FAILURE;
}


/*
This function displays the current database.
It uses a while loop to traverse the linked list (terminates when reaches last node that has a null pointer).
It prints the information (name, gender, age, phone number, id number, vaccine) for each node in the current linked list.
The print statement uses width modifiers to arrange the data in an organized manner.
*/


void display_currentdata(Node *person){
 printf("\n| Name | Gender | Age | Phone Number | Id Number | Vaccine |\n"); 
 while (person!=NULL){
    printf("\n%7s %4s %7d %13ld %13ld %7s\n",person->name,person->gender,person->age,person->phone_number,person->id_number,person->vaccine);      
    person=person->next;
  }
free(person);
}


/*
This function inserts a new node in the linked list, and it requires user interaction.
It asks the user for a name, gender, age, phone number, id_number and vaccine. 
The check_length function is called that checks if the phone number and id number are in the specified range (10 digits each). 
Memory is allocated (malloc) for the new node in the linked list.
The data (name, gender, age, phone number, id number, vaccine) is stored in the new node. 
The new node is added to the linked list.
The append_node_to_file function is called.
*/


void insertnode_data(Node *person, char *filename){
  char Name[50];
  int Age;
  long Phone;
  long Id;
  int output;
  char Gender[50];
  char Vaccine[50];
  printf("Please enter name:");
  scanf("%s",Name); 
  printf("Please enter gender:");
  scanf("%s",Gender);
  printf("Please enter age:");
  scanf("%d",&Age);
  printf("Please enter phone:");
  scanf("%ld",&Phone);
  printf("Please enter id number:");
  scanf("%ld",&Id);
  printf("Please enter vaccine:");
  scanf("%s",Vaccine);
  output=check_length(Phone,Id);
  if (output==0) {
  Node *new_person=(struct linked_list*)malloc(sizeof(Node));
  new_person->next=NULL;
  strcpy(new_person->name,Name);
  strcpy(new_person->gender,Gender);
  new_person->age=Age;
  new_person->phone_number=Phone;
  new_person->id_number=Id; 
  strcpy(new_person->vaccine,Vaccine);
  while (person->next!=NULL){
    person=person->next;
  }
  person->next=new_person;
  int outcome=append_node_to_file(new_person,filename);
  if (outcome==0){
  printf("%s file append operation successfull!\n",filename); 
  }
  else{
   printf("%s file append operation unsuccessfull!\n",filename);
}
}
  else{
   printf("\nInvalid Phone or ID number! Both must be 10 digits!\n");
}
}

/*
This function appends the node data to the specified file.
The fprintf function is used since the file is a text file.
*/


int append_node_to_file(Node *new_person, char *file){
  FILE *file_pointer=fopen(file,"a");
  if (file_pointer==NULL){
    return 1;
  }
  fprintf(file_pointer,"%s %s %d %ld %ld %s\n",new_person->name,new_person->gender,new_person->age,new_person->phone_number,new_person->id_number,new_person->vaccine);
  fclose(file_pointer);
  return 0;
}


/*
This function searches through the database or the linked list, and it requires user interaction.
The user is asked if they want to search by name, gender or by vaccine.
For each type, the linked list is traversed.
If the data is found, then that specific node data is printed.
The function returns EXIT_SUCCESS if found and vice versa. 
For example, the user wants to know all the individuals who got the Pfizer vaccine.
This function would search for all nodes that have the Pfizer vaccine. 
*/


bool search_node_data(Node *person){
  char search_name[50]="";
  char search_gender[50]="";
  char search_vaccine[50]="";
  int value=0;
  int found_name=0;
  int found_gender=0;
  int found_vaccine=0;
  printf("\nHow do you want to search?\n");
  printf("\n1. By Name 2. By Gender 3. By Vaccine\n");
  printf("\nPlease enter your choice:");
  scanf("%d",&value);
  if (value==1) {
  printf("Please enter name:");
  scanf("%s",search_name);
  }
  else if (value==2) {
  printf("Please enter gender:");
  scanf("%s",search_gender);
  }
  else if (value==3) {
  printf("Please enter vaccine:");
  scanf("%s",search_vaccine);
  }
  if (person==NULL){
    return EXIT_FAILURE;
  }
   printf("\n| Name | Gender | Age | Phone Number | Id Number | Vaccine |\n");
  while (person!=NULL){
     if (strcmp(person->name,search_name)==0){
      printf("%7s %4s %7d %13ld %13ld %7s\n",person->name,person->gender,person->age,person->phone_number,person->id_number,person->vaccine);
      found_name++;
     }
     else if (strcmp(person->gender,search_gender)==0){
       printf("%7s %4s %7d %13ld %13ld %7s\n",person->name,person->gender,person->age,person->phone_number,person->id_number,person->vaccine);
       found_gender++;
     }
     else if (strcmp(person->vaccine,search_vaccine)==0){
      printf("%7s %4s %7d %13ld %13ld %7s\n",person->name,person->gender,person->age,person->phone_number,person->id_number,person->vaccine);
      found_vaccine++;
     }
     person=person->next;
}
  if ((found_name==0) && (found_gender==0) && (found_vaccine==0)){
   return EXIT_FAILURE;
  } 
  else {
   return EXIT_SUCCESS;
  }
}

// This function counts the number of nodes in the linked list.
int list_nodes(Node *head){
  int  count=0;  
  while (head!=NULL){
     count++;
    head=head->next;
 }
return count;
}


Node *none_vaccine_list(Node *head,int nc){
Node *copy_node=NULL;
Node *current_node=NULL;
Node *head_node=NULL;
for (int i=0;i<nc;i++){ 
if (strcmp(head->vaccine,"None")==0) {     
     copy_node=(struct linked_list*)malloc(sizeof(Node));   
     copy_node->next=NULL;
     strcpy(copy_node->name,head->name);
     strcpy(copy_node->gender,head->gender);
     copy_node->age=head->age;
     copy_node->phone_number=head->phone_number;
     copy_node->id_number=head->id_number;
     strcpy(copy_node->vaccine,head->vaccine);
     if (head_node==NULL){
         head_node=copy_node;
         current_node=head_node;
     }
     else{
        current_node->next=copy_node;
        current_node=current_node->next;
     }
}
head=head->next;
}
return head_node;
}


Node *bubblesort_priority_person(Node *person){
  int node_count=0;
  int node_c=0;
  node_count=list_nodes(person);
  Node *new_head=none_vaccine_list(person,node_count);
  node_c=list_nodes(new_head);
  printf("\nTotal people:%d \n",node_count);
  printf("%d individuals are vaccinated!\n",(node_count-node_c));
  printf("%d individuals are not vaccinated yet!\n",node_c);
  int temp1=0;
  Node *head=NULL;
  char temp2[50]="";
  long temp3=0;
  long temp4=0;
  char temp5[50]="";
  char temp6[50]="";
  for (int i=0;i<node_c;i++){
    head=new_head;
    for (int j=0; j<node_c-i-1;j++) {
    if (head->age<head->next->age){ 
       temp1=head->next->age;
       head->next->age=head->age;
       head->age=temp1;
       strcpy(temp2,head->next->name);
       strcpy(head->next->name,head->name);
       strcpy(head->name,temp2);       
       strcpy(temp5,head->next->gender);
       strcpy(head->next->gender,head->gender);
       strcpy(head->gender,temp5);
       temp3=head->next->phone_number;
       head->next->phone_number=head->phone_number;
       head->phone_number=temp3;
       temp4=head->next->id_number;
       head->next->id_number=head->id_number;
       head->id_number=temp4;
       strcpy(temp6,head->next->vaccine);
       strcpy(head->next->vaccine,head->vaccine);
       strcpy(head->vaccine,temp6);
    }
    head=head->next; 
    }
  }
return head; 
}


void print_write_priority_file(Node *head,char *file){
  FILE *file_ptr=fopen(file,"w");
  printf("\n| Name | Gender | Age | Phone Number | Id Number | Vaccine |\n");
  while (head!=NULL){
  printf("%7s %4s %7d %13ld %13ld %7s\n",head->name,head->gender,head->age,head->phone_number,head->id_number,head->vaccine);
  fprintf(file_ptr,"%s %s %d %ld %ld %s\n",head->name,head->gender,head->age,head->phone_number,head->id_number,head->vaccine);
  head=head->next;
  }
  fclose(file_ptr);
}


int update_info(Node *head){
  long updated_number;
  char person_name[50];
  char updated_vaccine[50];
  int val=0;
  int updated=0;
  printf("Please enter name:");
  scanf("%s",person_name);
  if (head==NULL) {
   return 1;
  }
  while (head!=NULL){
    if (strcmp(head->name,person_name)==0){
      printf("\nWhat do you want to update?\n");
      printf("\n1. Phone Number 2. Vaccination 3. Both\n");
      printf("\nPlease enter your choice:");  
      scanf("%d",&val);        
      if ((val==1) || (val==3)) {
      printf("Please enter the new phone number for that person:");
      scanf("%ld",&updated_number);
      if (updated_number<=MAX_PHONE_LENGTH){
      printf("\nPrevious Record\n");
      printf("%s %s %d %ld %ld %s\n",head->name,head->gender,head->age,head->phone_number,head->id_number,head->vaccine);
      head->phone_number=updated_number;
      printf("\nUpdated Record\n");
      printf("%s %s %d %ld %ld %s\n",head->name,head->gender,head->age,head->phone_number,head->id_number,head->vaccine);
      updated++; 
      }
      else {
       return 2;
      }
      }
      if ((val==2) || (val==3)) {
      printf("Please enter the new vaccine for that person:");
      scanf("%s",updated_vaccine);
      printf("\nPrevious Record\n");
      printf("%s %s %d %ld %ld %s\n",head->name,head->gender,head->age,head->phone_number,head->id_number,head->vaccine);
      strcpy(head->vaccine,updated_vaccine);
      printf("\nUpdated Record\n");
      printf("%s %s %d %ld %ld %s\n",head->name,head->gender,head->age,head->phone_number,head->id_number,head->vaccine);
      updated++; 
       }
      }
    head=head->next;
  }
   if (updated==0){
    return 1;
   }
   else {
    return 0;
   }
}


Node *delete_head(Node *head) {
  Node *list_node=NULL;
  list_node=head;
  head=head->next;
  free(list_node);
  return head;
}


void delete_after(Node *head,char *delete_name) {
   Node *previous=NULL;
   Node *list_node=NULL;
   while (head!=NULL) { 
     if (strcmp(head->name,delete_name)==0){
       list_node=head;
       previous->next=list_node->next;
       free(list_node);
       return;
     }
   previous=head;
   head=head->next;
   }
return;
}


// This function checks if the length of the phone number and id number is within the specified range (10 digits).
bool check_length(long pn,long idn){
if ((pn<=MAX_PHONE_LENGTH) && (idn<=MAX_ID_LENGTH)){
   return EXIT_SUCCESS;
}
else {
  return EXIT_FAILURE;
}
}


/* This function frees all the nodes of the linked list after the program terminates. 
Even though the linked list is freed, all the changes the user makes are stored in the file. 
*/


void free_memory(Node *head) {
Node *free_node=NULL; 
while (head!=NULL){
  free_node=head;
  head=head->next;
  free(free_node);
}
}
