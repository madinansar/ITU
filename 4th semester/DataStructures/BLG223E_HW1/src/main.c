#include "schedule.h"
#include "exam.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
        // Create an initial schedule for testing
    Schedule* schedule = CreateSchedule();

        // Example: Add exams to the schedule
    AddExamToSchedule(schedule, "Monday", 8, 9, "BLG113E");
    AddExamToSchedule(schedule, "Monday", 8, 9, "BLG223E");
    AddExamToSchedule(schedule, "Sunday", 11, 13, "BLG102E");
    AddExamToSchedule(schedule, "Wednesday", 9, 10, "BLG223E");

    PrintSchedule(schedule);

    return 0;
}
