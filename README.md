# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Objective

1. Tune the hyperparameters of PID and implementing the PID on a car simulator.
2. To tune the hyperparameters, implementation of Twiddle alogorithm

## Methodology

The PiD control alogorithm works on the basis of Cross Track Error (CTE) provided by the simulator. It is the car's deviation from the centre line of the concerned lane. This CTE acts as the basis of PID controller. CTE directly gives the proportional error 'P'. But in this project it always overshoots, resulting oscillation and finally offtrack. Differential error 'D' is calculated via measuring the difference between the previous and current CTE. D acts as a damping factor and acts swiftly. To smoothen this transition integral error 'I' is added. I is the sum of all the differental errors over the time. It helps in gazing the damping rate and corrects the fall. All these error values are summed up and used for steering angle control. In relaity, throttle is also controlled.  

For the current project PID implementation, hyperparameters are optimized using twiddle algorithm. While tuning the hyperparameters, initially all the values were taken 0.
1. Initially a small Kp value of 0.1 was passed, but that work terreibly. So I reduce down the value (to 0.01) and tried to check where the vehicle atleast stayed in track or atleast for a good amount of time, although swerving movement was there. Then I slowly increased the value with incrementing the Kd value in parallel. I used Kp=0.04.
2. I refferd the nowledge section, and I started the value of Kd with 1 and I tried to use a lot of combinations with Kp. I used Kd=4.5. 
3. Ki doesn't have much effect in this partcular case, but increasing its value is causing swerving movement. I kept its value at 0.001.

## Twiddle Algorithm

Twiddle algorithm continously tunes the hyperparametrs by continously monitoring the CTE. Basically if the CTE value increases or decreases, twiddle algorithm also increase of decrease the hyperparameters to keep the smallest CTE.


