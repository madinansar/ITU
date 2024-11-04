#include "schedule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char globCourseCode[50];    //global courseCode string: Remove function also "returns" courseCode, while its return type is int
int globAddFlag = 1; //1 for Add, 0 for Upd

// Create a new schedule with 7 days
struct Schedule* CreateSchedule() {

    Schedule* schedule = (Schedule*)malloc(sizeof(Schedule));
    schedule->head = NULL;


    const char* namesOfDays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    Day* prevDay = NULL;    //pointer to traverse

    for(int i =0; i<7; i++){
        Day* newDay = (Day*)malloc(sizeof(Day));
        strcpy(newDay->dayName, namesOfDays[i]);    //C style
        newDay->examList = NULL;    //initially empty

        if(schedule->head == NULL){ //no days added no sch yet
            schedule->head = newDay;    //monday in 1st iter
        }
        else{
            prevDay->nextDay = newDay;
        }
        prevDay = newDay;
        //printf("day no: %d\n", i);
    }   //end for
    prevDay->nextDay = schedule->head;  //making it circular
    printf("Schedule creation complete.\n");

    return schedule;
}

// // Clear all exams and days from the schedule and deallocate memory
// void DeleteSchedule(struct Schedule* schedule) {

// }

// Add an exam to a day in the schedule
int AddExamToSchedule(struct Schedule* schedule, const char* day, int startTime, int endTime, const char* courseCode) {
    Exam* newExam = CreateExam(startTime, endTime, courseCode);
    if(startTime < 8 || startTime > 17 || endTime < 9 || endTime>20 || endTime-startTime>3){
        printf("Invalid exam.\n");
        return 3;   
    }

//find targetDay
    Day* targetDay = schedule->head;    //start from monday
    for(int i =0; i<7; i++){
        if(strcmp(targetDay->dayName, day)==0){
            break;
        }
        targetDay = targetDay->nextDay;
    }

    int count =0; //to check < 7 days
    int firstTry = 1;   //true by default, becomes false in second+ try
    while(count<7){
        Exam* currentExam = targetDay->examList;    //for traversing
        Exam* prev = NULL;  //prev exam, for finish time

//do i need this?
        // if(currentExam == NULL){   //no any exam yet
        //     Exam* newExam = CreateExam(startTime, endTime, courseCode);
        //     targetDay->examList = newExam;  //now examlist for the opredelyonnyy day has an exam
        //     printf("%s exam added to %s at time %d to %d without conflict.\n", courseCode, day, startTime, endTime);

        //     return 0;
        // }

        while(currentExam != NULL){
            if(startTime < currentExam->startTime){
                break;  //newExam comes BEFORE currentExam
            }
            prev = currentExam;     //traverse traverse
            currentExam = currentExam->next; 
        }

        // Check for time conflict with both previous and current exams
        if ((prev == NULL || prev->endTime <= startTime) && (currentExam == NULL || endTime <= currentExam->startTime)) {
        Exam* newExam = CreateExam(startTime, endTime, courseCode); //put newExam actually

            if(prev == NULL){   //exam is at head
                newExam->next = currentExam;
                targetDay->examList = newExam;
            }
            else{   // put btwn prev and currentExam
                prev->next = newExam;
                newExam->next = currentExam;
            }

            if(firstTry == 1){
                printf("%s exam added to %s at time %d to %d without conflict.\n", courseCode, day, startTime, endTime);
                return 0;
            }
            else if(firstTry == 0){
                printf("%s exam added to %s at time %d to %d due to conflict.\n", courseCode, day, startTime, endTime);
                return 1;
            }

        
        }else if(globAddFlag == 1){  //if conflict occured and Addition is taking place, not Upd
            firstTry = 0;
            if(startTime > 17){ //time slots for this day ended, look for next day
                targetDay = targetDay->nextDay;
                //currentExam and prev doesnt need to be set cause the are at very beginning of while <7 loop
                startTime = 8;
                endTime = startTime + (endTime-startTime);  //maintain duration
                count++; 
            }
            else{   //continue for next slot within the SAME day
                startTime = currentExam->endTime;
                endTime = startTime + (endTime-startTime);
            }
        }

    }   //endwhile(count<7)

    if(count == 7){
        printf("Schedule full. Exam cannot be added.\n");
        return 2;
    }
    return 0;   //?? does it come to this point
}

// Function to print all exams in the schedule
void PrintSchedule(const Schedule* schedule) {
    if (schedule == NULL || schedule->head == NULL) {
        printf("No schedule to display.\n");
        return;
    }

    const Day* currentDay = schedule->head;
    int isFirstDay = 1;

    do {
        printf("Day: %s\n", currentDay->dayName);

        Exam* currentExam = currentDay->examList;
        if (currentExam == NULL) {
            printf("  No exams scheduled.\n");
        } else {
            while (currentExam != NULL) {
                printf("  Exam: %s | Start: %d | End: %d\n", currentExam->courseCode, currentExam->startTime, currentExam->endTime);
                currentExam = currentExam->next;
            }
        }

        currentDay = currentDay->nextDay;
        isFirstDay = 0;

    } while (currentDay != schedule->head || isFirstDay);

    printf("Schedule printing complete.\n");
}

// // Remove an exam from a specific day in the schedule
// int RemoveExamFromSchedule(struct Schedule* schedule, const char* day, int startTime) {
//     Day* targetDay = schedule->head;
//     for(int i =0; i < 7; i++){
//         if(strcmp(targetDay->dayName, day)==0){
//             break;
//         }
//         targetDay = targetDay->nextDay;
//     }

// Exam* currentExam = targetDay->examList;
// Exam* prevExam = NULL;

// while(currentExam != NULL){
//     if(currentExam->startTime == startTime){
//         strcpy(globCourseCode, currentExam->courseCode);    //globalCourse code is set, used for Update function
//         if(prevExam == NULL){
//             targetDay->examList = currentExam->next;
//         }
//         else{
//             prevExam->next = currentExam->next;
//         }
//         free(currentExam);
//         printf("Exam removed successfully.\n");
//         return 0;
//     }
//     prevExam = currentExam;
//     currentExam = currentExam->next;
// }
//     printf("Exam could not be found.\n");
//     return 1; // Exam not found
// }

// // Update an exam in the schedule
// int UpdateExam(struct Schedule* schedule, const char* oldDay, int oldStartTime, const char* newDay, int newStartTime, int newEndTime) {
//     globAddFlag = 0; //upd is happening, dont do resch in add func

//     if(newStartTime < 8 || newStartTime > 17 || newEndTime < 9 || newEndTime>=20 || newEndTime-newStartTime>3){
//         printf("Invalid exam.\n");
//         return 3;   
//     }

// //to get courseName:
//     Day* targetDay = schedule->head;
//     for(int i =0; i < 7; i++){
//         if(strcmp(targetDay->dayName, oldDay)==0){
//             break;
//         }
//         targetDay = targetDay->nextDay;
//     }

//     Exam* currentExam = targetDay->examList;
//     Exam* prevExam = NULL;
//     char courseCode[50];

//     while(currentExam != NULL){
//         if(currentExam->startTime == oldStartTime){
//             strcpy(courseCode, currentExam->courseCode);
//             break;
//         }
//         prevExam = currentExam;
//         currentExam = currentExam->next;
//     }

//     if(currentExam == NULL){ //if no value was assigned after traversing
//         printf("Exam could not be found.\n");
//         return 2;
//     }

//     int addResult = AddExamToSchedule(schedule, newDay, newStartTime, newEndTime, courseCode);
//     if(addResult == 0){
//         int removeResult = RemoveExamFromSchedule(schedule, oldDay, oldStartTime);  //should be defined here bc if addres==0
//         if(removeResult == 0){
//             printf("Update successful.\n");
//             return 0;
//         }
//         else{
//             printf("No such exam found.\n");        //exam is alreday added? should i delete it?
//             return 2; 
//         }
//     } else {
//         printf("Update unsuccessful.\n");
//         return 1;
//     }

// }

// // Clear all exams from a specific day and relocate them to other days
// int ClearDay(struct Schedule* schedule, const char* day) {

// }



// // Read schedule from file
// int ReadScheduleFromFile(struct Schedule* schedule, const char* filename) {

// }

// // Write schedule to file
// int WriteScheduleToFile(struct Schedule* schedule, const char* filename) {

// }
