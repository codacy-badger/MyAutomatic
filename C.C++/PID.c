﻿#include<stdio.h>
#include<math.h>
 struct _pid
      {
       int pv; //过程量
       int sp; //设定值
       int integral; //积分值——偏差累计值
       float pgain;
       float igain;
       float dgain;
       int deadband; //一个死区
       int last_error;
      };
 struct _pid warm, *pid;
       int*process_point,set_point,dead_band;
       float p_gain,i_gain,d_gain,integral_val,new_integ; //pid_init DESCRIPTION this function initalizes the pointers in the _pid structure to the 'process variable'and the set point '*pv, *sp are integer pointers.'
 void pid_init(struct _pid*warm,int process_point,int set_point)
    {
 struct _pid*pid; pid=warm;
       pid->pv=process_point;
       pid->sp=set_point;
     }