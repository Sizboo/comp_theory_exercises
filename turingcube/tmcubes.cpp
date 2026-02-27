#include "TuringMachineTape.h"
#include <iostream>

const int COUNT = 'x';
const int MARKED = 0;
const int INPUT = 'a';
const TuringMachineUtility UT;

class CounterMachine {
public:
    TuringMachineTape a_tape;
    TuringMachineTape sqr_tape;
    TuringMachineTape counter_tape;

    CounterMachine() {
        a_tape = TuringMachineTape();
        sqr_tape = TuringMachineTape();
        //counter_tape = TuringMachineTape();

        UT.insertBegin(&a_tape);
        UT.insertBegin(&sqr_tape);
        //UT.insertBegin(&counter_tape);
    }

    void start_cube_machine(){
        s_start_st();
    }

    void find_next_cube(){
        s_restart();

        counter_tape = TuringMachineTape();
        UT.insertBegin(&counter_tape);
        
        UT.rewind(&a_tape);
        q3_st();
    }

private:
    void s_start_st(){
        if(a_tape.read() == COUNT){
            a_tape.write(MARKED);
            a_tape.left();
            q1_st();
        }
        else if(a_tape.read() == BLANK_SYMBOL){
            UT.shiftAndInsert(&a_tape, COUNT);
            a_tape.left();
        }
    }

    void s_restart(){
        if(a_tape.read() == COUNT){
            a_tape.write(MARKED);
            a_tape.left();
            q1_st();
        }
        else {
            std::cout << "catastrphic restart error" << std::endl;
        }
    }

    void q1_st(){
        if(a_tape.read() == BEGIN_SYMBOL){
            a_tape.right();
            q2_st();
        }
        else if(a_tape.read() == MARKED){
            UT.shiftAndInsert(&sqr_tape, MARKED);
            a_tape.left();
            q1_st();
        }
        else {
            std::cout << "catastrophic q1 error" << std::endl;
        }
    }

    void q2_st(){
        if(a_tape.read() == MARKED){
            UT.shiftAndInsert(&sqr_tape, MARKED);
            a_tape.right();
            q2_st();
        }
        else if(a_tape.read() == COUNT){
            a_tape.write(MARKED);
            a_tape.left();
            q1_st();
        }
        else if(a_tape.read() == BLANK_SYMBOL){
            UT.shiftAndInsert(&a_tape, COUNT);
            a_tape.left();
        }
        else{
            std::cout << "catostrophic q2 error" << std::endl;
        }
    }

    void q3_st() {
        if(a_tape.read() == COUNT){
            UT.rewind(&counter_tape);
        }
        else if(a_tape.read() == MARKED){
            UT.rewind(&sqr_tape);
            q4_st();
        }
    }
    
    void q4_st(){
        if(sqr_tape.read() == MARKED){
            counter_tape.write(MARKED);
            counter_tape.right();
            sqr_tape.right();
            q4_st();
        }
        else if(sqr_tape.read() == BLANK_SYMBOL){
            a_tape.right();
            q3_st();
        }
    }


};

int main() {
    TuringMachineTape input_tm = TuringMachineTape(&std::cin);
    CounterMachine cm = CounterMachine();

    UT.insertBegin(&input_tm);
    cm.start_cube_machine();

    while(1){
        if(input_tm.read() == INPUT){
            if (cm.counter_tape.read() == MARKED){
                cm.counter_tape.right();
                input_tm.right();
            }
            else if(cm.counter_tape.read() == BLANK_SYMBOL){
                UT.rewind(&input_tm);
                cm.find_next_cube();

                continue;
            }
        }
        else if(input_tm.read() == BLANK_SYMBOL){
            if(cm.counter_tape.read() == MARKED){
                input_tm.reject();
                break;
            }
            else if(cm.counter_tape.read() == BLANK_SYMBOL){
                input_tm.accept();
                break;
            }else {
                std:: cout << "Random error" << std::endl;
                break;
            }
        }
    }


   return 0;
}


