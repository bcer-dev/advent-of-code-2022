#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

enum class Instructions
{
    NoOp = 1,
    AddX = 2
};

class CPU
{
private:
    int cycles = 0;
    int X = 1;

public:
    CPU() = default;
    void tick();
    void addX(int v);
    inline int getCycles() const;
    inline int getX() const;
};

inline int CPU::getCycles() const
{
    return this->cycles;
}

inline int CPU::getX() const
{
    return this->X;
}

#endif