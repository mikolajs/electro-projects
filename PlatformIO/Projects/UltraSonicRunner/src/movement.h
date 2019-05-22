#ifndef MOVEMENT_H
#define MOVEMENT_H

class Motors
{
private:
 int A_1, A_2, B_1, B_2;
public:
    Motors(int a1, int a2, int b1, int b2);
    void forward();
    void backward();
    void left();
    void right();
    void stop();
};

#endif