#include "TuringMachineTape.h"
#include <iostream>

struct CounterMachine {
    TuringMachineTape a_tape;
    TuringMachineTape counter_tape;
    TuringMachineUtility ut;
    int count = 'x';
    int marked = 0;

    CounterMachine() {
        a_tape = TuringMachineTape();
        counter_tape = TuringMachineTape();

        //setup begin | blank
        ut.insertBegin(&a_tape);

        //setup begin | blank
        ut.insertBegin(&counter_tape);
    }

    void start_state(){
        if(a_tape.read() == count){
            a_tape.right();
            forward_state();
        }
        if(a_tape.read() == BLANK_SYMBOL){
            fin_state();
        }
    }

    void fin_state(){
        if(a_tape.read() == marked){
            a_tape.write(count);
            a_tape.right();
            fin_state();
        }
        if(a_tape.read() == BLANK_SYMBOL){
            a_tape.write(count);
            ut.rewind(a_tape);
        }

    }

    void forward_state(){
       if(a_tape.read() == count){
           ut.findRight(&a_tape, BLANK_SYMBOL);
       }
       if(a_tape.read() == BLANK_SYMBOL){
           a_tape.left();
           q1_state();
       }
    }

    void q1_state() {
        if(a_tape.read() == marked){
            ut.shiftAndInsert(&counter_tape, marked);
            a_tape.left();
            q1_state();
        }
        if(a_tape.read() == count){
            a_tape.right();
            q2_state();
        }
        if(a_tape.read() == BEGIN_SYMBOL){
            a_tape.right();
            fin_state();
        }
    }

    void q2_state() {
        if(a_tape.read() == marked){
            ut.shiftAndInsert(&counter_tape, marked);
            a_tape.right();
            q2_state();
        }
        if(a_tape.read() == BLANK_SYMBOL){
            a_tape.left();
            q1_state();
        }
    }
};

int main() {
    TuringMachineTape input_tm = TuringMachineTape(&std::cin);

    input_tm.debug(&std::cout);

   return 0;
}


