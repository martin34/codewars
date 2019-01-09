//
// Created by martin on 09.01.19.
//

#ifndef CODEWARS_GUESSER_H
#define CODEWARS_GUESSER_H

#include <stdexcept>

class Guesser
{
public:
    Guesser(int number, int lives)
            : number(number), lives(lives)
    { }
    bool guess(int n)
    {
        if(lives<=0)
        {
            throw std::runtime_error("Dead");
        }
        bool correct = n == number;
        if(!correct)
        {
            --lives;
        }
        return correct;
    }
private:
    int number, lives;
};

#endif //CODEWARS_GUESSER_H
