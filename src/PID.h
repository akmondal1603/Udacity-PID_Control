#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);
    
    /**
    * Assign Kp, Ki and Kd according to twiddle iteration
    */
    //void UpdateParams(double K_, int i);

	/**
	* Update the PID error variables given cross track error.
	* @param cte The current cross track error
	*/
 void UpdateError(double cte);

	/**
	* Calculate the total PID error.
	* @output The total PID error
	*/
  double TotalError();

	/**
	* Calculate Kp, Kd and Ki values
	* given a tolerance parameter
	*/
  void twiddle(double tol, double cte);  

	/**
	* Calculate the sum of a given array
	* given its length and elements
	*/
	//double arr_sum(double dp[], int n);


 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  double prev_cte;
  //double error_total;
  double best_err;
  /**
  parameters introduces for twiddle
  */
  double dp[3];
  double p[3];
  //double best_error;
  double current_err;
  //int n;
  int twiddle_call;
};

#endif  // PID_H