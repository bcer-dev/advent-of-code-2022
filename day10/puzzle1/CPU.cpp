#include "CPU.hpp"

void CPU::tick()
{
    this->cycles++;
}

void CPU::addX(int v)
{
    this->X += v;
}