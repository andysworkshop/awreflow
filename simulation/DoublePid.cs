using System;


namespace @double {

  public class DoublePid {

    protected double _kp;
    protected double _ki;
    protected double _kd;

    protected double _lastError;
    protected double _integral;

    public DoublePid(double kp,double ki,double kd) {
    
      _kp=kp;
      _ki=ki;
      _kd=kd;
      _lastError=0;
      _integral=0;
    }

    public byte update(double desiredTemperature,double currentTemperature) {

      double error,pwm,derivative;

      // current error term is the difference between desired and current temperature

      error=desiredTemperature-currentTemperature;

      // update the integral (historical error)

      _integral+=error;

      // the derivative term

      derivative=error-_lastError;

      // calculate the control variable

      pwm=(_kp*error)+(_ki*_integral)+(_kd*derivative);
      pwm=Math.Max(Math.Min(255.0,pwm),0.0);

      // save the last error

      _lastError=error;

      // return the control variable

      return Convert.ToByte(pwm);
    }
  }
}
