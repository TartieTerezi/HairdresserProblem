#include "Stool.h"

Stool::Stool()
{
    m_id = NUMBER_STOOLS;
    NUMBER_STOOLS++;
}

Stool::~Stool()
{
}

void Stool::Taking()
{
    std::cout << "Un client prend le tabouret " << m_id << std::endl;
}

bool Stool::Take()
{
    return m_isTake.try_lock();
}

void Stool::Drop()
{
    m_isTake.unlock();
    std::cout << "Le client quitte le tabouret " << m_id << std::endl;
}