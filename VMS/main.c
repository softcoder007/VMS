#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int CountFiles(char path[250]){
    DIR *folder;
    int file_count = 0;
    struct dirent *dir;
    folder = opendir(path);
    if(folder)
    {
        while ((dir = readdir(folder)) != NULL)
        {
            /*printf("%s\n", dir->d_name);*/
            if (!strcmp(dir->d_name, "."))
                continue;
            if (!strcmp(dir->d_name, ".."))
                continue;
            file_count++;
        }
        closedir(folder);
    }
    return(file_count);
}
void Enter(int id){
    system("cls");
    FILE *fptr;
    char name[20];
    char number[20];
    char visiting_to[20];
    char purpose_of_visiting[100];
    char file_name[100];
    snprintf(file_name, sizeof file_name, "%s%d%s", "data/login/visitor_", id, ".txt");
    fptr = fopen(file_name, "w");
    if (fptr == NULL)
    {
      printf("File does not exists \n");
      return;
    }
    printf("\nEnter the name \n");
    scanf(" %[^\n]s", name);
    printf("\nEnter the Phone number \n");
    scanf(" %[^\n]s", number);
    printf("\nEnter the visiting to \n");
    scanf(" %[^\n]s", visiting_to);
    printf("\nEnter the purpose of visiting \n");
    scanf(" %[^\n]s", purpose_of_visiting);

    fprintf(fptr, "Id = %d\n", id);
    fprintf(fptr, "Name = %s\n", name);
    fprintf(fptr, "Phone number = %s\n", number);
    fprintf(fptr, "visiting to = %s\n", visiting_to);
    fprintf(fptr, "Purpose of visiting = %s\n", purpose_of_visiting);
    fclose(fptr);
    system("cls");
    printf("\n\t\t\t\t\t\t Successfully logged-in!!!");
    printf("\n\t\t\t\t\t\t Your visitor Id is : %d\n\n\n",id);
}
void Exit(){
    system("cls");
    int logId=0;
    printf("\n\t Please enter your id.\n");
    scanf("%d", &logId);
    if(logId !=0){
        char file_name[100];
        char file_new_name[100];
        snprintf(file_name, sizeof file_name, "%s%d%s", "data/login/visitor_", logId, ".txt");
        snprintf(file_new_name, sizeof file_new_name, "%s%d%s", "data/logout/visitor_", logId, "_log_out.txt");
        if (rename(file_name, file_new_name) == 0)
        {
            system("cls");
            printf("\n\t\t\t\t\t\t log-out successful!");
            printf("\n\t\t\t\t\t\t Thank you visiting us!\n\n\n");
        }
        else
        {
            system("cls");
            printf("\n\t\t\t\t\t\t Visitor not found!!!\n\n\n");
        }
    }
    else{
      printf("\n\t Please enter a valid id.\n");
    }

}
void Admin(){
   system("cls");
   const char password[15] = "admin123";
   char pass[20];
   printf("\n\t Please enter your password:");
   scanf(" %[^\n]s", pass);
   if(strcmp(pass, password) == 0){
        system("cls");
        AdminOptions();
   }
   else{
       system("cls");
       int opt;
       printf("\n\t\t\t\t\t\t wrong password!\n\n\n");
       printf("\n\t Do you want to try again?\n\n");
       printf("\n\t1. Yes");
       printf("\n\t2. no\n");
       scanf("%d", &opt);

       if(opt==1){
            Admin();
        }
        else if(opt==2){
            system("cls");
        }
        else{
             printf("\n\t please chose a valid option\n\n\n");
        }
    }
}
void AdminOptions(){
       int options=0;
       printf("\n\t\t\t\t\t\t Hi admin!\n\n\n");
       printf("\n\t1. logged-in visitor(%d)",CountFiles("data/login"));
       printf("\n\t2. logged-out visitor(%d)",CountFiles("data/logout"));
       printf("\n\t3. Admin log-out");
       printf("\n\n\n");
       scanf("%d", &options);
       if(options==1){
            ShowVisitor("data/login/");
       }
       else if(options==2){
            ShowVisitor("data/logout/");
       }
       else if(options==3){
            system("cls");
       }
       else {
            system("cls");
            printf("\n\t\t\t\t\t\t Please enter a valid option no.!!!\n\n\n");
            AdminOptions();
       }
}
void ShowVisitor(char dfolder[200]){
    system("cls");
    DIR *folder;
    struct dirent *dir;
    folder = opendir(dfolder);
    if(folder)
    {
        while ((dir = readdir(folder)) != NULL)
        {
            if (!strcmp(dir->d_name, "."))
                continue;
            if (!strcmp(dir->d_name, ".."))
                continue;
            char c[1000];
            FILE *fptr;
            char cd[100];
            snprintf(cd, sizeof cd, "%s%s", dfolder,dir->d_name);
            if ((fptr = fopen(cd, "r")) == NULL)
            {
                printf("Error! opening file");
                getch();
            }
            else{
               char str[1000];
               while (fgets(str, 1000, fptr) != NULL){
                printf("%s", str);
               }
               printf("\nPress Enter to Back\n");
            }
            fclose(fptr);
        }
        closedir(folder);
    }
    getch();

    system("cls");
    AdminOptions();
}
int GetLastId(){
    FILE *fptr;
    char ch;
    int num=0;
    if ((fptr = fopen("LastId.txt", "r")) == NULL)
            {
                printf("Error! opening file");
            }
            else{
               char str[1000];
               while (fgets(str, 1000, fptr) != NULL){
                num = atoi(&str);
                return num;
               }
            }
            fclose(fptr);
    printf(num);
    return num;
}
void SetLastId(int id){
    FILE *fptr = fopen("LastId.txt", "w");
    if (fptr == NULL)
    {
      printf("File does not exists \n");
      return;
    }
    fprintf(fptr, "%d",id);
    fclose(fptr);
}
void main()
{
    int id=1;
    int options=0;
    char file_name[100];
    id = GetLastId();
    while(id!=0){
        printf("\n\t Welcome To Warehouse \n\n\n");
        printf("\n\t 1. Check-in");
        printf("\n\t 2. Check-out");
        printf("\n\t 3. Admin panel\n");



        //printf("\n\t\t\t ***Please note that admin pass is 'admin123'***\n");

        printf("\n\n\t Please chose a option\n");
        scanf("%d", &options);
        if(options==1){
            Enter(id);
            id++;
            SetLastId(id);
        }
        else if(options==2){
            Exit();
         }
         else if (options==3){
            Admin();
         }
         else{
              system("cls");
              printf("\n\t\t\t\t\t\t Please enter a valid option no.!!!\n\n\n");
         }
    }
}
