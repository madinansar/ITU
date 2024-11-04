#include "worker.hpp"

Worker::Worker(std::string name, float cost_per_day, float base_return_per_day)
    : Unit(name, cost_per_day, base_return_per_day), m_experience(0) {}

float Worker::getReturnPerDay() {
    float daily_return = getReturnPerDay() + m_experience * 2 + m_num_head_workers * 3;
    m_experience++;

    if (m_experience >= 10) {
        increaseHeadWorkerCount(); // Promote the worker to a head worker
        m_experience = 0; // Reset the worker's experience to 0
    }
    
    return daily_return;
}

int Worker::getExperience() const {
    return m_experience;
}

void Worker::increaseHeadWorkerCount() {
    m_num_head_workers++;
}
