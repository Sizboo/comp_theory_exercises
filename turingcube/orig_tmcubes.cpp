#include "TuringMachineTape.h"
#include <iostream>

//ya ya. i know i should've capitalized. I just didn't feel like refactoring
//all refs. sorry.
const int count = 'x';
const int marked = 0;
const int INPUT = 'a';

//beast machine. these r kind of fun.
struct CounterMachine {
    TuringMachineTape a_tape;
    TuringMachineTape counter_tape;
    TuringMachineUtility ut;

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
        else if(a_tape.read() == BLANK_SYMBOL){
            fin_state();
        }
    }

    void fin_state(){
        if(a_tape.read() == marked){
            a_tape.write(count);
            a_tape.right();
            fin_state();
        }
        else if(a_tape.read() == BLANK_SYMBOL){
            ut.shiftAndInsert(&a_tape, count);
            ut.rewind(&a_tape);
        }
    }

    void forward_state(){
       if(a_tape.read() == count){
           ut.findRight(&a_tape, BLANK_SYMBOL);
           forward_state();
       }
       else if(a_tape.read() == BLANK_SYMBOL){
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
        else if(a_tape.read() == count){
            a_tape.write(marked);
            a_tape.right();
            q2_state();
        }
        else if(a_tape.read() == BEGIN_SYMBOL){
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
        else if(a_tape.read() == BLANK_SYMBOL){
            a_tape.left();
            q1_state();
        }
    }
};

int main() {
    TuringMachineTape input_tm = TuringMachineTape(&std::cin);
    TuringMachineUtility ut;
    CounterMachine cm = CounterMachine();

    ut.insertBegin(&input_tm);

    while(1){
        if(input_tm.read() == INPUT){
            if (cm.counter_tape.read() == marked){
                cm.counter_tape.right();
                input_tm.right();
            }
            else if(cm.counter_tape.read() == BLANK_SYMBOL){
                cm.counter_tape = TuringMachineTape();
                ut.insertBegin(&cm.counter_tape);
                ut.rewind(&input_tm);
                cm.start_state();
                ut.rewind(&cm.counter_tape);
                continue;
            }
        }
        else if(input_tm.read() == BLANK_SYMBOL){
            if(cm.counter_tape.read() == marked){
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


