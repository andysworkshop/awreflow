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
    
    public class Segment {
      public uint Seconds;
      public double Temperature;

      public Segment(uint seconds,double temp) {
        this.Seconds=seconds;
        this.Temperature=temp;
      }
    }

    public MainForm() {
      InitializeComponent();
    }

    private void buttonRun_Click(object sender, EventArgs e) {

      Segment[] segments=new Segment[] {
        new Segment(100, 110),
        new Segment(180, 125),
        new Segment(230, 225),
        new Segment(250, 225),
        new Segment(420, 75)
      };

      try {
        Pid pid=new Pid(double.Parse(editP.Text),double.Parse(editI.Text),double.Parse(editD.Text));
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

        chart.Series[0].Points.Clear();
        chart.Series[1].Points.Clear();

        // cycle over each segment
  
        for(segment=0;segment<5;segment++) {
  
          Segment seg=segments[segment];
  
          // cycle the seconds
    
          if(segment==0)
            step_temperature=(seg.Temperature-double.Parse(editRoomTemperature.Text)+1)/seg.Seconds;
          else
            step_temperature=(seg.Temperature-segments[segment-1].Temperature+1)/(seg.Seconds-segments[segment-1].Seconds+1);

          for(;current_seconds<seg.Seconds;current_seconds++) {

            chart.Series[0].Points.AddXY(current_seconds,target_temperature);
            chart.Series[1].Points.AddXY(current_seconds,current_temperature);

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
  }
}
