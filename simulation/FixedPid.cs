using System;


namespace @double {

  public class FixedPid {

    protected int _kp;
    protected int _ki;
    protected int _kd;

    protected int _lastError;
    protected int _integral;

    public FixedPid(int kp,int ki,int kd) {
    
      _kp=kp;
      _ki=ki;
      _kd=kd;
      _lastError=0;
      _integral=0;
    }

    public byte update(int desiredTemperature,int currentTemperature) {

      int error,pwm,derivative;

      // current error term is the difference between desired and current temperature

      error=desiredTemperature-currentTemperature;

      // update the integral (historical error)

      _integral+=error;

      // the derivative term

      derivative=error-_lastError;

      // calculate the control variable

      pwm=(_kp*error)+(_ki*_integral)+(_kd*derivative);
      pwm=Math.Max(Math.Min(255,pwm),0);

      // save the last error

      _lastError=error;

      // return the control variable

      return Convert.ToByte(pwm);
    }
  }
}
