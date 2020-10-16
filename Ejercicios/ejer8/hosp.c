//
//  main.c
//  HospitalAvanzada
//
//  Created by MacBook Pro on 19/08/20.
//  Copyright © 2020 Naji M A Saadat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *FirstName;
    char *LastName;
    int Age;
    unsigned long ContactNum;
    int CurrentState;
    int PatienBed;
} patient;

typedef struct
{
    int occupied;
    int patientNumber;
} bed;

void Menu()
{
    printf("\n \t ** Control Hospitalized Pacients In the Hospital  **\n");
    printf("\n You Have The Next Options \n");
    printf("Choose The Process to Execute: \n");
    printf("1) Hospitalize a new patient \n");
    printf("2) Discharge Hospitalized Pacient \n");
    printf("3) List of Hospitalized Patients \n");
    printf("4) Beds \n");
    printf("5) Increase 5 beds\n");
    printf("6) Exit\n");
}
int CheckAvailableBed(bed * beds, int totalNumberOfBeds)
{
    bed *finalBed = beds + totalNumberOfBeds;
    bed *IteBed;
    int position = 0;
    
    for (IteBed = beds; IteBed < finalBed; ++IteBed)
    {
        if (IteBed->occupied == 0)
        {
            return position;
        }
        position++;
    }
    return -1;
}


int main(int argc, char **argv)
{
    patient * PatientInfo = (patient *) malloc(sizeof(patient));
    int totalNumberOfBeds = 5;
    bed *beds = (bed *)malloc(sizeof(bed) * totalNumberOfBeds);
    bed * AvailableBed;
    bed *finalBed;
    bed *IteBed;
    int bedNumber;
    int AvailableBedPos;
    int patientNumber;
    int bedToDischarge;
    int TotalNumPatients = 0;
    
    patient *CurrentPatient = PatientInfo;
    patient *patientIterator;
    
    AvailableBedPos = CheckAvailableBed(beds, totalNumberOfBeds);
    AvailableBed = beds + AvailableBedPos;
    AvailableBed->occupied = 0;
    AvailableBed->patientNumber = TotalNumPatients -1;
    
    
    int option;
    do
    {
        Menu();
        printf("\n Option: ");
        scanf("%d", &option);
        
        switch (option)
        {
            case 1:
                printf("*** New Patient ***\n");
                printf("\n");
                //hospitalizing patient
                TotalNumPatients++;
                PatientInfo = (patient *)realloc(PatientInfo, sizeof(patient) * (TotalNumPatients));
                CurrentPatient = PatientInfo + TotalNumPatients -1;
                CurrentPatient->FirstName = (char *) malloc(sizeof(char) * 35);
                CurrentPatient->LastName = (char *) malloc(sizeof(char) * 35);
                
                printf("Patient's name  : ");
                scanf(" %[^\n]", CurrentPatient->FirstName);
                
                printf("lastname is : ");
                scanf(" %[^\n]", CurrentPatient->LastName);
                
                printf(" Age is : ");
                scanf(" %d", &CurrentPatient->Age);
                
                printf(" # Number  is : ");
                scanf(" %lu", &CurrentPatient->ContactNum);
                
                CurrentPatient->CurrentState = 1;
                AvailableBedPos = CheckAvailableBed(beds, totalNumberOfBeds);
                if (AvailableBedPos != -1)
                {
                    AvailableBed = beds + AvailableBedPos;
                    AvailableBed->occupied = 1;
                    AvailableBed->patientNumber = TotalNumPatients - 1;
                    printf("\t ****You have a new Patient With Bed Number assigned  : %d ******\n", AvailableBedPos + 1 );
                } else
                {
                    printf("No Availabe beds. Adding 5 more Beds.\n");
                    totalNumberOfBeds += 5;
                    beds = (bed *)realloc(beds, sizeof(bed) * (totalNumberOfBeds));
                    printf("5 Available Beds been added, Input the information of the Patient Again \n");
                }
                CurrentPatient->PatienBed = AvailableBedPos;
                printf("\n");
                printf("\n");
                break;
            case 2:
                printf("** Discharge Patient **\n");
                printf("\n");
                finalBed = beds + totalNumberOfBeds;
                bedNumber = 1;
                printf("*Total Number of Beds in The Hospital is : %d\n", totalNumberOfBeds);
                for (IteBed = beds; IteBed < finalBed; IteBed++)
                {
                    CurrentPatient = PatientInfo + IteBed->patientNumber;
                    if (IteBed->occupied == 1)
                    {
                        printf("Bed %d\t Occupied by patient: %s %s\n", bedNumber, CurrentPatient->FirstName, CurrentPatient->LastName);
                    }
                    else
                    {
                        printf("Bed %d\t Available\n", bedNumber);
                    }
                    bedNumber++;
                }
                printf("\n");
                printf("Enter the patient`s bed number to procced with the discharge: \n");
                scanf("%d", &bedToDischarge);
                if (bedToDischarge != 0)
                {
                    finalBed = beds + bedToDischarge - 1;
                    if (finalBed->occupied != 1 )
                    {if ( bedToDischarge <= totalNumberOfBeds){
                        printf("\n");
                        printf("** Bed is already Available  **\n");
                    }else
                        
                        printf("\n No Bed With that Bed Number, Please Check your list and try again\n");
                    }
                    else
                    {
                        //Free from list of patient
                        CurrentPatient = PatientInfo + finalBed->patientNumber;
                        CurrentPatient->CurrentState = 0;
                        //Freeing bed
                        finalBed->occupied = 0;
                        finalBed->patientNumber = 0;
                        printf("\n");
                        printf("**  Patient discharged Completed  and Bed %d is now Available **\n", bedToDischarge);
                    }
                }
                printf("\n");
                break;
            case 3:
                printf("** Patients List **\n");
                printf("\n");
                CurrentPatient = PatientInfo + TotalNumPatients;
                patientNumber = 1;
                for (patientIterator = PatientInfo; patientIterator < CurrentPatient; ++patientIterator)
                {
                    if (patientIterator->CurrentState == 1)
                    {
                        printf("Patient #%d\n \n", patientNumber);
                        printf("Name: %s %s\nAge: %d\n# Number: %lu\n" , patientIterator->FirstName, patientIterator->LastName, patientIterator->Age, patientIterator->ContactNum);
                        if (patientIterator->PatienBed == -1)
                        {
                            printf("Bed not assigned\n");
                        }
                        else
                        {
                            printf("Bed assigned : %d\n", patientIterator->PatienBed + 1);
                        }
                        printf("\n");
                    }
                    ++patientNumber;
                }
                printf(" ................................... \n \n ");
                break;
            case 4:
                printf("*** Beds List ***\n");
                printf("\n");
                finalBed = beds + totalNumberOfBeds;
                bedNumber = 1;
                printf("*Total Number of Beds in The Hospital is : %d\n", totalNumberOfBeds);
                int FreeBeds=0;
                int OccupiedBeds=0;
                for (IteBed = beds; IteBed < finalBed; IteBed++)
                {
                    CurrentPatient = PatientInfo + IteBed->patientNumber;
                    if (IteBed->occupied == 1)
                    {
                        printf("Bed %d   ", bedNumber);
                        printf(" Occupied by : %s %s \n" , CurrentPatient->FirstName, CurrentPatient->LastName);
                        OccupiedBeds++;
                    }
                    else
                    {
                        printf("Bed %d  Available\n", bedNumber);
                        FreeBeds++;
                    }
                    bedNumber++;
                }
                printf("\n");
                printf("******************************************\n");
                printf("****** Number of Available beds: %d  ******\n", FreeBeds);
                printf("****** Number of Occupied beds: %d  *******\n", OccupiedBeds);
                printf("******************************************\n");
                printf("\n");
                printf("\n");
                break;
                
            case 5:
                totalNumberOfBeds += 5;
                //reallocating memory to Total of beds
                beds = (bed *)realloc(beds, sizeof(bed) * (totalNumberOfBeds));
                printf("\n \n");
                printf("** 5 more Available Beds added **\n");
                printf("\n");
                printf("\n");
                break;
                
            case 6:
                option = 6;
                printf("\n GoodBye \n");
                printf("\n");
                break;
                
            default:
                printf("** Not a Valid Option, Please enter a valid option from the Menu  ***\n");
                printf("\n");
                break;
        }
    } while (option != 6);
    // Freeing list Of Patients
    patient *lastPatient = PatientInfo + TotalNumPatients;
    for (patientIterator = PatientInfo; patientIterator < lastPatient; ++patientIterator)
    {
        free(patientIterator->FirstName);
        free(patientIterator->LastName);
    }
    free(PatientInfo);
    free(beds);
    return 0;
}

