/**
 * definitions.cpp
 *
 * This file contains various declarations and definitions for
 * motors, sensors, controls, constants, and settings, so that
 * things that might need to be changed are all in one place.
 */
#include "23lib/Pneumatic.hpp"
#include "main.h" // gives access to definition.hpp and other dependencies

namespace def
{
/* ----------------------------------------------------------- */
/*                           Devices                           */
/* ----------------------------------------------------------- */

/* -------------------------- Motors ------------------------- */
Motor mtr_dt_left_front(19);
Motor mtr_dt_right_front(-18);
Motor mtr_dt_right_back(-1);
Motor mtr_dt_left_back(4);
/* ----------------------------------------------------------- */
Motor mtr_it_left(-6);
Motor mtr_it_right(-7);
/* ----------------------------------------------------------- */
Motor mtr_fw(3);

Motor mtr_move(-17);

/* ------------------------- Sensors ------------------------- */
ADIEncoder track_encoder_forward('G', 'H', false);
ADIEncoder track_encoder_side('E', 'F', true);
pros::Imu imu_top(2);
pros::Imu imu_bottom(5);

Pneumatic air('A', false);

/* ----------------------------------------------------------- */
/*                           Controls                          */
/* ----------------------------------------------------------- */
Controller controller = Controller(ControllerId::master);
Controller controller2 = Controller(ControllerId::partner);

} // namespace def