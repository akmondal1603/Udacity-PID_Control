#include "PID.h"
#include <cmath>
#include <vector>
#include <stdlib.h>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  PID::Kp=Kp_;
  PID::Kd=Kd_;
  PID::Ki=Ki_;
  
  p_error=0.0;
  d_error=0.0;
  i_error=0.0;
  
  prev_cte=9999.9;
  
 

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  //PID::Init;
  p_error=cte;
  d_error=prev_cte-cte;
  prev_cte=cte;
  i_error+=cte;
  
 
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  double error_total = Kp*p_error + Kd*d_error + Ki*i_error;
  return error_total;  // TODO: Add your total error calc here!
}

std::vector<double> PID::twiddle(double cte)
{
  //std::vector<double> p = {0.0005, 0, 2.5};
  std::vector<double> p = {0.0, 0.0, 0.0};
  std::vector<double> dp = {1.,1.,1.};
  double best_err=TotalError();
  double tol=0.2;
  double sum = dp[0]+dp[1]+dp[2];
  while(sum>tol)
  {
    for (int i=0; i<p.size(); i++)
    {
      p[i]+=dp[i];
      
      Kp=p[0];
      Ki=p[1];
      Kd=p[2];
      double err=TotalError();
      if (abs(err)<best_err)
      {
        best_err=err;
        dp[i]*=1.1;
      }
      else
      {
        p[i]-=2*dp[i];
        Kp=p[0];
      	Ki=p[1];
      	Kd=p[2];
      	double err=TotalError();
        if (abs(err)<best_err)
        {
          best_err=abs(err);
          dp[i]*=1.1;
        }
        else
        {
          p[i]+=dp[i];
          dp[i]*=0.9;
        }
      }
    }
    return p;
  }
}


