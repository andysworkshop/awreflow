using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace @double {
  
  public partial class MainForm : Form {
    
    int _formWidth;

    public class Segment<T> {
      public int Seconds;
      public T Temperature;

      public Segment(int seconds,T temp) {
        this.Seconds=seconds;
        this.Temperature=temp;
      }
    }

    public MainForm() {
      InitializeComponent();

      _formWidth=this.Width;
    }

    private void buttonRun_Click(object sender, EventArgs e) {

      runDouble();
      runFixed();
    }


    /// <summary>
    /// Run the double-precision PID
    /// </summary>

    private void runDouble() {

      Segment<double>[] segments=new Segment<double>[] {
        new Segment<double>(100, 110),
        new Segment<double>(180, 125),
        new Segment<double>(230, 225),
        new Segment<double>(250, 225),
        new Segment<double>(420, 75)
      };

      try {

        DoublePid pid=new DoublePid(Convert.ToDouble(editP.Value),Convert.ToDouble(editI.Value),Convert.ToDouble(editD.Value));
        int segment,current_seconds;
        double current_temperature,step_temperature,change,target_temperature,room_temperature,max_rate,oven_max;
        byte pwm;

        // reset
  
        room_temperature=double.Parse(editRoomTemperature.Text);
        max_rate=double.Parse(editOvenMaxPerSecond.Text);
        oven_max=double.Parse(editOvenMaximum.Text);

        current_seconds=0;
        current_temperature=room_temperature;
        target_temperature=double.Parse(editRoomTemperature.Text);

        floatingChart.Series[0].Points.Clear();
        floatingChart.Series[1].Points.Clear();

        // cycle over each segment
  
        for(segment=0;segment<segments.Length;segment++) {
  
          Segment<double> seg=segments[segment];

          // work out the step temperature per second

          if(segment==0)
            step_temperature=(seg.Temperature-room_temperature+1)/seg.Seconds;
          else
            step_temperature=(seg.Temperature-segments[segment-1].Temperature+1)/(seg.Seconds-segments[segment-1].Seconds+1);

          // cycle the seconds
    
          for(;current_seconds<seg.Seconds;current_seconds++) {

            floatingChart.Series[0].Points.AddXY(current_seconds,target_temperature);
            floatingChart.Series[1].Points.AddXY(current_seconds,current_temperature);

            pwm=pid.update(target_temperature,current_temperature);

            change=((pwm*max_rate)/255)-(((current_temperature-room_temperature)*max_rate)/oven_max);
            current_temperature+=change;
            target_temperature+=step_temperature;
          }
        }
      } catch(Exception ex) {
        MessageBox.Show(ex.ToString(),"Fail!",MessageBoxButtons.OK,MessageBoxIcon.Error);
      }
    }


    /// <summary>
    /// Run the fixed point pid
    /// </summary>

    private void runFixed() {

      int scaler=(int)Math.Pow(10.0,(double)fixedPointPlaces.Value);

      Segment<int>[] segments=new Segment<int>[] {
        new Segment<int>(100, 110*scaler),
        new Segment<int>(180, 125*scaler),
        new Segment<int>(230, 225*scaler),
        new Segment<int>(250, 225*scaler),
        new Segment<int>(420, 75*scaler)
      };

      try {

        FixedPid pid=new FixedPid(
          Convert.ToInt32(editP.Value)*scaler,
          Convert.ToInt32(editI.Value)*scaler,
          Convert.ToInt32(editD.Value)*scaler
        );
        
        int segment,current_seconds;
        int current_temperature,step_temperature,change,target_temperature,room_temperature,max_rate,oven_max;
        byte pwm;

        // reset
  
        room_temperature=int.Parse(editRoomTemperature.Text)*scaler;
        max_rate=int.Parse(editOvenMaxPerSecond.Text)*scaler;
        oven_max=int.Parse(editOvenMaximum.Text)*scaler;

        current_seconds=0;
        current_temperature=room_temperature;
        target_temperature=int.Parse(editRoomTemperature.Text)*scaler;

        fixedChart.Series[0].Points.Clear();
        fixedChart.Series[1].Points.Clear();

        // cycle over each segment
  
        for(segment=0;segment<segments.Length;segment++) {
  
          Segment<int> seg=segments[segment];
  
          // work out the step temperature per second
    
          if(segment==0)
            step_temperature=(seg.Temperature-room_temperature+(1*scaler))/seg.Seconds;
          else
            step_temperature=(seg.Temperature-segments[segment-1].Temperature+(1*scaler))/(seg.Seconds-segments[segment-1].Seconds+1);

          // cycle the seconds

          for(;current_seconds<seg.Seconds;current_seconds++) {

            fixedChart.Series[0].Points.AddXY(current_seconds,Convert.ToDouble(target_temperature)/scaler);
            fixedChart.Series[1].Points.AddXY(current_seconds,Convert.ToDouble(current_temperature)/scaler);

            pwm=pid.update(target_temperature,current_temperature);

            change=((pwm*max_rate)/255)-((current_temperature*max_rate)/oven_max);
            current_temperature+=change;
            target_temperature+=step_temperature;
          }
        }
      } catch(Exception ex) {
        MessageBox.Show(ex.ToString(),"Fail!",MessageBoxButtons.OK,MessageBoxIcon.Error);
      }
    }


    /// <summary>
    /// form resized
    /// </summary>

    private void MainForm_Resize(object sender, EventArgs e) {

      this.fixedChart.Width=(this.Width/2)-30;
      this.floatingChart.Width=(this.Width/2)-30;
      this.fixedChart.Left=this.Width/2;
      lblFixed.Left=this.fixedChart.Left;

      _formWidth=this.Width;
    }
  }
}
