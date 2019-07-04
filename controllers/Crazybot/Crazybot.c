/*
 * File:          Crazybot.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
/*#include <webots/distance_sensor.h>*/
#include <webots/position_sensor.h>
#include <webots/keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>




#define TIME_STEP 64
#define PI 3.1416

  double l_pos_1,l_pos_dif,r_pos_1,r_pos_dif;
  double l_pos_2 = 0;
  double r_pos_2 = 0;
  float left_angv, right_angv, left_linv, right_linv, left_rpm, right_rpm;
  double dis_sen;
  double radio=0.075;

int main(int argc, char **argv)
{

  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);


  WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
  WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
 /* WbDeviceTag ds = wb_robot_get_device("ds");*/
  WbDeviceTag right_pos = wb_robot_get_device("position_sensor_right");
  WbDeviceTag left_pos = wb_robot_get_device("position_sensor_left");
  
  wb_position_sensor_enable(right_pos, TIME_STEP);
  wb_position_sensor_enable(left_pos, TIME_STEP);
  
  



  while (wb_robot_step(TIME_STEP) != -1) {
  
  int key = wb_keyboard_get_key();
  
  wb_position_sensor_get_value(right_pos);
  wb_position_sensor_get_value(left_pos);
  
  l_pos_1 = wb_position_sensor_get_value(left_pos);
  l_pos_dif = l_pos_1 - l_pos_2;
  l_pos_2 = l_pos_1;
  left_angv = l_pos_dif/0.064;
  left_linv = left_angv*radio;
  left_rpm = left_angv*(60/(2*PI));
  
  r_pos_1 = wb_position_sensor_get_value(right_pos);
  r_pos_dif = r_pos_1 - r_pos_2;
  r_pos_2 = r_pos_1;
  right_angv = r_pos_dif/0.064;
  right_linv = right_angv*radio;
  right_rpm = right_angv*(60/(2*PI));
  
  
     if(key==WB_KEYBOARD_UP){
  
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, -40);
    wb_motor_set_position(wheel_right, INFINITY); 
    wb_motor_set_velocity(wheel_right, -40); 
    }
    
     if(key==WB_KEYBOARD_DOWN){
  
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, 1.333);
    wb_motor_set_position(wheel_right, INFINITY); 
    wb_motor_set_velocity(wheel_right, 1.333); 
    }
    
    if(key==WB_KEYBOARD_LEFT){
  
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, -35);
    wb_motor_set_position(wheel_right, INFINITY); 
    wb_motor_set_velocity(wheel_right, -45); 
    }
    
     if(key==WB_KEYBOARD_RIGHT){
  
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, -45);
    wb_motor_set_position(wheel_right, INFINITY); 
    wb_motor_set_velocity(wheel_right, -35); 
    }
  
  printf("Angular Velocity Left: %f \n", left_angv);
  printf("Linear Velocity Left: %f \n", left_linv);
  printf("RPM: %f \n", left_rpm);
  
  printf("Angular Velocity Right: %f \n", left_angv);
  printf("Linear Velocity Right: %f \n", left_linv);
  printf("RPM: %f \n", left_rpm);
  
  
  
  fflush(stdout);
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
