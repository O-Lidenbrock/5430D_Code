#pragma once 
#include "okapi/api.hpp" 
#include "okapi/api/filter/emaFilter.hpp"
#include "Pneumatic.hpp"

using namespace okapi;

namespace def
{
/* ----------------------------------------------------------- */
/*                           Devices                           */
/* ----------------------------------------------------------- */

/* -------------------------- Motors ------------------------- */
extern Motor mtr_dt_left_front; // drive
extern Motor mtr_dt_right_front;
extern Motor mtr_dt_right_back;
extern Motor mtr_dt_left_back;

extern Motor mtr_it_left; // intake/roller  
extern Motor mtr_it_right;

extern Motor mtr_fw;; 

extern Motor mtr_move; 

/* ------------------------- Sensors ------------------------- */
extern ADIEncoder track_encoder_forward;
extern ADIEncoder track_encoder_side;
extern pros::Imu imu_top;
extern pros::Imu imu_bottom;

/* ------------------------- Pneumatics ------------------------- */
extern Pneumatic air; 
/* ----------------------------------------------------------- */
/*                           Controls                          */
/* ----------------------------------------------------------- */
extern Controller controller;
extern Controller controller2;

/* ----------------------------------------------------------- */
/*                          Constants                          */
/* ----------------------------------------------------------- */

/* --------------------- Tracking Wheels --------------------- */
const QLength TRACK_WHEEL_DIAMETER = 2.847_in;
const QLength TRACK_WHEEL_CIRCUMFERENCE = TRACK_WHEEL_DIAMETER * M_PI;
const QLength TRACK_FORWARD_OFFSET = 0.0_in;
const QLength TRACK_SIDE_OFFSET = 0.0_in;

/* ------------------------ Drivetrain ----------------------- */
const QLength DRIVE_WHEEL_DIAMETER = 4.041_in;
const double DRIVE_WHEEL_DIAMETER_IN = DRIVE_WHEEL_DIAMETER.convert(inch);
const QLength DRIVE_WHEEL_CIRCUMFERENCE = DRIVE_WHEEL_DIAMETER * M_PI;
const double DRIVE_WHEEL_CIRCUMFERENCE_IN = DRIVE_WHEEL_CIRCUMFERENCE.convert(inch);
const QLength DRIVE_OFFSET = 42_in;

const QAcceleration DRIVE_MAX_ACCEL = 1_G; // approxamate measured linear acceleration
const QSpeed DRIVE_MAX_SPEED = 2.7_mps; // a measured linear velocity

/* ------------------------- Settings ------------------------ */
const double SET_DT_MAX = 1; // default drivetrain max speed (1 is 100%)
const OdomState SET_ODOM_START = {0_ft, 0_ft, 0_deg}; // starting position of the robot on the field
} // namespace def