#include "headworker.hpp"

HeadWorker::HeadWorker(Worker &worker)
            : Worker(worker.getName(), worker.getCostPerDay(), worker.getReturnPerDay()){
                m_experience = worker.getExperience();
            }

float HeadWorker::getReturnPerDay(){
    float dayly_return = getReturnPerDay() + getExperience()*5;
    return dayly_return;
}
