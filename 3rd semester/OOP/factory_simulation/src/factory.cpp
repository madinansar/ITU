#include "factory.hpp"

Factory::Factory(float capital)
        : m_capital(capital), m_is_bankrupt(false) {}

void Factory::passOneDay(){
    float daily_costs = 0;
    float daily_returns = 0;

//for worker:
    for(auto &worker : m_workers) {
        daily_costs = daily_costs + worker.getCostPerDay();
        daily_returns = daily_returns + worker.Worker::getReturnPerDay();

        if(worker.getExperience() >= 10){
            m_head_workers.push_back(HeadWorker(worker));
        }
    }

//for machine:
    for(auto &machine : m_machines) {
        daily_costs = daily_costs + machine.getCostPerDay();
        daily_returns = daily_returns + machine.Machine::getReturnPerDay();
    }

    m_capital = m_capital + daily_returns - daily_costs;

    if(m_capital <= 0){
        m_is_bankrupt = true;
    }

}

void Factory::addUnit(const Worker &rhs_worker){
    m_workers.push_back(rhs_worker);
}

void Factory::addUnit(const Machine &rhs_machine){
    m_machines.push_back(rhs_machine);
}

bool Factory::isBankrupt() const{
    return m_is_bankrupt;
}

float Factory::getCapital() const{
    return m_capital;
}

int Factory::getWorkerCount() const{
    return m_workers.size();
}

int Factory::getMachineCount() const{
    return m_machines.size();
}

int Factory::getHeadWorkerCount() const{
    return m_head_workers.size();
}

