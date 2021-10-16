#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
    int year,month,date;
}Date;

typedef struct
{
    int pid,age,did;
    char name[40],address[50],gender;
    float weight,height;
    Date admit_date;
}Patient;

Patient P_Input()
{
    Patient p;
    printf("Enter patient details:\n");
    printf("Enter Patient Id:");
    scanf("%d",&p.pid);
    printf("Enter name:");
    scanf("%s",&p.name);
    printf("Enter age:");
    scanf(" %d",&p.age);
    printf("Enter gender(m/f):");
    scanf(" %c",&p.gender);
    printf("Enter weight(kg):");
    scanf(" %f",&p.weight);
    printf("Enter height(cm):");
    scanf(" %f",&p.height);
    printf("Enter date of admission(D,M,Y):\n");
    printf("Enter date:");
    scanf("%d",&p.admit_date.date);
    printf("Enter month:");
    scanf("%d",&p.admit_date.month);
    printf("Enter year:");
    scanf("%d",&p.admit_date.year);
    return p;
}

void P_Output(Patient p)
{
    printf("\nPatient Id: %d\nName: %s\nAge: %d\n",p.pid,p.name,p.age);
    printf("Gender: %c\nWeight(kg): %f\nHeight(cm): %f\n",p.gender,p.weight,p.height);
    printf("Date of Admission: %d-%d-%d\n",p.admit_date.date,p.admit_date.month,p.admit_date.year);
}

FILE *fp,*fp2;

void Add_Patient()
{
    system("cls");
    printf("NEW PATIENT ADDITION\n");
    Patient p = P_Input();
    fp = fopen("patients.bin","ab");
    if(!fp)
    {
        printf("Unable to enter data!!\n");
        return;
    } 
    fwrite(&p,sizeof(Patient),1,fp);
    printf("Record entered succesfully!!\n");
    fclose(fp);
    getchar();
}

void Search_Patient(int pid)
{
   system("cls");
   int f=0;
   Patient p; 
   fp = fopen("patients.bin","rb");
   if(!fp)
   {
       printf("\n\n\t\tFile does not exist!!");
       getchar();
       return;
   }
   while(fread(&p,sizeof(Patient),1,fp))
   {
       if(p.pid==pid)
       {
           printf("Record found!!\n");
           P_Output(p);
           f = 1;
           break;
       }
   }
   if(!f)
    printf("\n\n\t\tRecord not found!!\n");
   fclose(fp);
   getchar();
}

void Edit_Patient(int pid)
{

    system("cls");
    int f=0;
    Patient p; 
    fp = fopen("patients.bin","rb+");
    if(!fp)
    {
        printf("\n\n\t\tFile does not exist!!\n");
        getchar();
        return;
    }
    while(fread(&p,sizeof(Patient),1,fp))
    {
        if(p.pid==pid)
        {
           printf("\t\tRecord found!!\n\n");
           P_Output(p);
           f = 1;
           printf("\n\t\tEnter new details of the patient:\n");
           p = P_Input();
           fseek(fp,-1*sizeof(Patient),SEEK_CUR);
           fwrite(&p,sizeof(Patient),1,fp);
           break;
        }
    }
    if(!f)
        printf("\n\n\t\tRecord not found!!\n");
    else
        printf("\nRecord edited succesfully!!\n");
    fclose(fp);
    getchar();
}

void Delete_Patient(int pid)
{
    Patient p;
    int f = 0;
    fp = fopen("patients.bin","rb");
    if(!fp)
    {
        printf("\n\n\t\tFile does not exist!!");
        getchar();
        return;
    }
    fp2 = fopen("temp.bin","wb");
    while(fread(&p,sizeof(Patient),1,fp))
    {
        if(p.pid!=pid)
            fwrite(&p,sizeof(Patient),1,fp2);
        else 
            f = 1;
    }
    if(f)
        printf("\t\tDeletion succesful!!\n");
    else
        printf("\t\tRecord not found!!\n");
    fclose(fp);
    fclose(fp2);
    remove("patients.bin");
    rename("temp.bin","patients.bin");
    getchar();
}

void P_OutputAll()
{
    system("cls");
    Patient p;
    fp = fopen("patients.bin","rb");
    if(!fp)
    {
       printf("\n\n\t\tFile does not exist!!");
       getchar();
       return; 
    }
    while(fread(&p,sizeof(Patient),1,fp))
    {
        P_Output(p);
    }
    fclose(fp);
    getchar();
}

void P_Reset()
{
    system("cls");
    char c;
    printf("\n\n\t\tARE YOU SURE YOU WANT TO DELETE ALL RECORDS?(Y/N):");
    scanf(" %c",&c);
    if(c=='y' || c=='Y')
    {
        remove("patients.bin");
        printf("\n\n\t\tFACTORY RESET SUCCESSFUL!");
    }
    getchar();
}

void P_Menu()
{
    system("cls");
    int ch,x;
    printf("\n\t\t\t\t\t\tPATIENT MANAGEMENT MENU\n");
    printf("\n\n\t\t1.Add Patient Record\n\n\t\t2.Search Patient Record\n\n\t\t3.Edit Patient Record\n\n\t\t4.Delete Patient Record\n\n\t\t5.Display all Patients\n\n\t\t6.Factory Reset\n\n\t\t7.Exit\n\n\t\t\n\n\t\tEnter choice:");
    scanf("%d",&ch);
    switch (ch)
    {
        case 1:
            Add_Patient();
            break;
        case 2:
            printf("\n\t\tEnter Patient ID to search:");
            scanf("%d",&x);
            Search_Patient(x);
            break;
        case 3:
            printf("\n\t\tEnter Patient ID to edit:");
            scanf("%d",&x);
            Edit_Patient(x);
            break;
        case 4:
            printf("\n\t\tEnter Patient ID to delete:");
            scanf("%d",&x);
            Delete_Patient(x);
            break;
        case 5:
            P_OutputAll();
            break;
        case 6:
            P_Reset();
            break;
        case 7:
            return;
            break;
        default:
            printf("\t\tInvalid choice!!\n");
            getchar();
            break;
    }
    getchar();
    P_Menu();
}

void login()
{
    system("cls");
    printf("\n\t\t\t\t\t\tPATIENT MANAGEMENT MENU\n");
    printf("\n\t\t\tEnter Password:");
    char str[100];
    char str2[6] = "123456";
    int i = 0;
    static int cnt = 5;
    do{
        str[i++] = getch();
        if(str[i-1]==13)
            break;
        printf("*");
    }while(1);
    i--;
    int f = 1;
    if(i==6)
    {
        for(i=0;i<6;++i)
        {
            if(str[i]!=str2[i])
            {
                f = 0;
                break;
            }
        }
        if(f)
        P_Menu();
    }
    if(i!=6 || f==0)
    {
        cnt--;
        if(cnt==0)
            return;
        printf("\n\n\t\t\tIncorrect Password!!");
        printf("\n\n\t\t\tYou have %d more attempt(s) remaining!!",cnt);
        getchar();
        login();
    }
}

int main()
{
    login();
}