#include "PID.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
using std::string;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  p_error=0.0;
  d_error=0.0;
  i_error=0.0;
  
  prev_cte = 0.0;

  best_err = 0.0;
  current_err = 0.0;

  twiddle_call = 0;
}

void PID::UpdateError(double cte) {
  //accum_cte += cte;
  // Update PID errors based on CTE.
  p_error = cte;
  i_error += cte;
  d_error = cte-prev_cte;
  prev_cte = cte;
}

double PID::TotalError() {
  // Calculate and return the total error
  return -(Kp * p_error + Kd * d_error + Ki * i_error);
}

void PID::twiddle(double tol, double cte) 
{
  twiddle_call += 1;
  current_err += (cte * cte);
  current_err /= twiddle_call;
  best_err = (cte * cte);
  std::vector<double> p = {0.0, 0.0, 0.0};
  std::vector<double> dp = {1.0,1.0,1.0};
  double sum = dp[0]+dp[1]+dp[2];
  int it = 0;
  while (sum > tol) 
  {
    for (int i=0; i<3; i++) 
    {
      p[i] += dp[i];
      Kp=p[0];
      Ki=p[1];
      Kd=p[2];

      if (current_err < best_err) 
      { // There was some improvement

        best_err = current_err;
        dp[i] *= 1.1;
      }
      else 
      { // No improvement
     
        p[i] -= 2 * dp[i];
        Kp=p[0];
        Ki=p[1];
        Kd=p[2];
        
        if (current_err < best_err) 
        { // There was an improvement
          //std::cout << "loop 2a" << std::endl;
          best_err = current_err;
          dp[i] *= 1.1;
        }
        else 
        { 
          p[i] += dp[0];
          dp[i] *= 0.9;
        }
      }
    }
    it += 1;
  }
}

