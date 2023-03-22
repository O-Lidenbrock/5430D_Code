#include "v5_vcs.h"

using namespace vex;

brain Brain = brain();
motor mtr_dt_left_front(PORT19, ratio18_1, false);
motor mtr_dt_right_front(PORT18, ratio18_1, true); //fix ratios @stephen
motor mtr_dt_right_back(PORT1, ratio18_1, true);
motor mtr_dt_left_back(PORT4, ratio18_1, false);
motor mtr_it_left(PORT6, ratio18_1, false);
motor mtr_it_right(PORT7, ratio18_1, true);
motor mtr_fw(PORT3, ratio18_1, false);
motor mtr_move(PORT17, ratio18_1, true);
inertial inertiaA(PORT5, left);


pneumatics piston(Brain.ThreeWirePort.A);

controller control1 = controller(primary);
controller control2 = controller(partner);



