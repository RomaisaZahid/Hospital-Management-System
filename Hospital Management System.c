// Replace fopen_s with fopen
#define _CRT_SECURE_NO_WARNINGS // Use this to suppress warnings in Visual Studio
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h> 

struct Patient
{
    int id;
    char patientName[50];
    char patientAddress[100];
    char disease[50];
    char date[12];
} p;

struct Doctor
{
    int id;
    char Name[50];
    char Address[100];
    char specialize[50];
    char date[12];
} d;

void admitPatient();
void patientList();
void dischargePatient();
void addDoctor();
void doctorList();

FILE* fp;

int main()
{
    int ch;
    while (1)
    {
        system("cls");
        printf("<== Hospital Management System ==>");
        printf("\n 1.Admit Patient");
        printf("\n 2.Patient List");
        printf("\n 3.Discharge Patient");
        printf("\n 4.Add Doctor");
        printf("\n 5.Doctor List");
        printf("\n 0.Exit\n\n");
        printf(" Enter your Choice:");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            exit(0);
            break;
        case 1:
            admitPatient();
            break;
        case 2:
            patientList();
            break;
        case 3:
            dischargePatient();
            break;
        case 4:
            addDoctor();
            break;
        case 5:
            doctorList();
            break;
        default:
            printf("\n Invalid Input....");
        }
    }
    printf("\n Press any key to continue");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for a key press
    return 0;
}

void admitPatient()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(p.date, myDate);
    fp = fopen("patient.txt", "ab");
    printf("\n Enter patient ID:");
    scanf("%d", &p.id);
    printf("\n Enter Patient name:");
    while ((p.patientName[0] = _getche()) != '\r' && p.patientName[0] != '\n') {}
    p.patientName[1] = '\0';
    printf("\n Enter Patient Disease:");
    while ((p.disease[0] = _getche()) != '\r' && p.disease[0] != '\n') {}
    p.disease[1] = '\0';
    printf("\n Enter Patient Address:");
    while ((p.patientAddress[0] = _getche()) != '\r' && p.patientAddress[0] != '\n') {}
    p.patientAddress[1] = '\0';
    printf("\n -----------Patient Record Added Successfully------------");
    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void patientList()
{
    system("cls");
    printf("\n \n <==Patient Lists==>\n \n");
    printf("%-10s %-30s %-30s %-20s %s \n", "ID", "Patient Name", "Address", "Disease", "Date");
    fp = fopen("patient.txt", "rb");
    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        printf("%-10d %-30s %-30s %-20s %s \n", p.id, p.patientName, p.patientAddress, p.disease, p.date);
    }
    fclose(fp);
}

void dischargePatient()
{
    int id, f = 0;
    system("cls");
    printf("\n \n <==Discharge Patient==> \n \n");
    printf(" Enter Patient id to discharge:");
    scanf("%d", &id);
    FILE* ft;
    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");
    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (id == p.id)
        {
            f = 1;
        }
        else
        {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }
    if (f == 1)
    {
        printf("\n \n ------Patient Discharged Successfully---------");
    }
    else
    {
        printf("\n \n Record not found");
    }
    fclose(fp);
    fclose(ft);
    remove("patient.txt");
    rename("temp.txt", "patient.txt");
}

void doctorList()
{
    system("cls");
    printf("\n \n <==Doctors List==> \n \n");
    printf("%-10s %-30s %-30s %-20s %s \n", "ID", "Doctor Name", "Address", "Specialization", "Date");
    fp = fopen("doctor.txt", "rb");
    while (fread(&d, sizeof(d), 1, fp) == 1)
    {
        printf("%-10d %-30s %-30s %-20s %s \n", d.id, d.Name, d.Address, d.specialize, d.date);
    }
    fclose(fp);
}

void addDoctor()
{
    int f = 0;
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(d.date, myDate);
    fp = fopen("doctor.txt", "ab");
    printf("\n \n<==Add Doctor==> \n \n");
    printf("\n Enter Doctor ID:");
    scanf("%d", &d.id);
    printf("\n Enter Doctor name:");
    while ((d.Name[0] = _getche()) != '\r' && d.Name[0] != '\n') {}
    d.Name[1] = '\0';
    printf("\n Enter Doctor's Specialization:");
    while ((d.specialize[0] = _getche()) != '\r' && d.specialize[0] != '\n') {}
    d.specialize[1] = '\0';
    printf("\n Enter Doctor's Address:");
    while ((d.Address[0] = _getche()) != '\r' && d.Address[0] != '\n') {}
    d.Address[1] = '\0';
    printf("\n -----------Doctor Record Added Successfully------------");
    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}