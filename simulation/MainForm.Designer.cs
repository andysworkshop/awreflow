namespace @double {
  partial class MainForm {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing) {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent() {
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.floatingChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.label5 = new System.Windows.Forms.Label();
      this.label6 = new System.Windows.Forms.Label();
      this.buttonRun = new System.Windows.Forms.Button();
      this.editP = new System.Windows.Forms.NumericUpDown();
      this.editI = new System.Windows.Forms.NumericUpDown();
      this.editD = new System.Windows.Forms.NumericUpDown();
      this.editRoomTemperature = new System.Windows.Forms.NumericUpDown();
      this.editOvenMaximum = new System.Windows.Forms.NumericUpDown();
      this.editOvenMaxPerSecond = new System.Windows.Forms.NumericUpDown();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.label7 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.floatingChart)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editP)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editI)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editD)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editRoomTemperature)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaximum)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaxPerSecond)).BeginInit();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // floatingChart
      // 
      this.floatingChart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.floatingChart.BackColor = System.Drawing.SystemColors.Control;
      this.floatingChart.BorderlineColor = System.Drawing.Color.Black;
      chartArea1.AxisX.MajorGrid.LineColor = System.Drawing.Color.Gainsboro;
      chartArea1.AxisY.MajorGrid.LineColor = System.Drawing.Color.Gainsboro;
      chartArea1.BackSecondaryColor = System.Drawing.Color.White;
      chartArea1.BorderColor = System.Drawing.Color.Silver;
      chartArea1.Name = "ChartArea1";
      this.floatingChart.ChartAreas.Add(chartArea1);
      this.floatingChart.Location = new System.Drawing.Point(12, 161);
      this.floatingChart.Name = "floatingChart";
      this.floatingChart.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Bright;
      series1.BorderWidth = 2;
      series1.ChartArea = "ChartArea1";
      series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
      series1.LabelForeColor = System.Drawing.Color.DimGray;
      series1.Name = "Series1";
      series2.BorderWidth = 2;
      series2.ChartArea = "ChartArea1";
      series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
      series2.Name = "Series2";
      this.floatingChart.Series.Add(series1);
      this.floatingChart.Series.Add(series2);
      this.floatingChart.Size = new System.Drawing.Size(1016, 613);
      this.floatingChart.TabIndex = 3;
      this.floatingChart.Text = "floatingChart";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(10, 22);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(17, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "P:";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(10, 48);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(13, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "I:";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(10, 74);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(18, 13);
      this.label3.TabIndex = 4;
      this.label3.Text = "D:";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(117, 22);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(97, 13);
      this.label4.TabIndex = 6;
      this.label4.Text = "Room temperature:";
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(117, 48);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(82, 13);
      this.label5.TabIndex = 8;
      this.label5.Text = "Oven maximum:";
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(117, 74);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(80, 13);
      this.label6.TabIndex = 10;
      this.label6.Text = "Oven max/sec:";
      // 
      // buttonRun
      // 
      this.buttonRun.Location = new System.Drawing.Point(324, 24);
      this.buttonRun.Name = "buttonRun";
      this.buttonRun.Size = new System.Drawing.Size(75, 23);
      this.buttonRun.TabIndex = 1;
      this.buttonRun.Text = "Run";
      this.buttonRun.UseVisualStyleBackColor = true;
      this.buttonRun.Click += new System.EventHandler(this.buttonRun_Click);
      // 
      // editP
      // 
      this.editP.Location = new System.Drawing.Point(34, 19);
      this.editP.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editP.Name = "editP";
      this.editP.Size = new System.Drawing.Size(61, 20);
      this.editP.TabIndex = 1;
      this.editP.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.editP.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editI
      // 
      this.editI.Location = new System.Drawing.Point(34, 45);
      this.editI.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editI.Name = "editI";
      this.editI.Size = new System.Drawing.Size(61, 20);
      this.editI.TabIndex = 3;
      this.editI.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.editI.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editD
      // 
      this.editD.Location = new System.Drawing.Point(34, 71);
      this.editD.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editD.Name = "editD";
      this.editD.Size = new System.Drawing.Size(61, 20);
      this.editD.TabIndex = 5;
      this.editD.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.editD.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editRoomTemperature
      // 
      this.editRoomTemperature.Location = new System.Drawing.Point(220, 19);
      this.editRoomTemperature.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
      this.editRoomTemperature.Name = "editRoomTemperature";
      this.editRoomTemperature.Size = new System.Drawing.Size(61, 20);
      this.editRoomTemperature.TabIndex = 7;
      this.editRoomTemperature.Value = new decimal(new int[] {
            25,
            0,
            0,
            0});
      this.editRoomTemperature.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editOvenMaximum
      // 
      this.editOvenMaximum.Location = new System.Drawing.Point(220, 45);
      this.editOvenMaximum.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editOvenMaximum.Name = "editOvenMaximum";
      this.editOvenMaximum.Size = new System.Drawing.Size(61, 20);
      this.editOvenMaximum.TabIndex = 9;
      this.editOvenMaximum.Value = new decimal(new int[] {
            250,
            0,
            0,
            0});
      this.editOvenMaximum.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editOvenMaxPerSecond
      // 
      this.editOvenMaxPerSecond.Location = new System.Drawing.Point(220, 71);
      this.editOvenMaxPerSecond.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editOvenMaxPerSecond.Name = "editOvenMaxPerSecond";
      this.editOvenMaxPerSecond.Size = new System.Drawing.Size(61, 20);
      this.editOvenMaxPerSecond.TabIndex = 11;
      this.editOvenMaxPerSecond.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
      this.editOvenMaxPerSecond.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.editP);
      this.groupBox1.Controls.Add(this.editOvenMaxPerSecond);
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Controls.Add(this.editOvenMaximum);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Controls.Add(this.editRoomTemperature);
      this.groupBox1.Controls.Add(this.label3);
      this.groupBox1.Controls.Add(this.editD);
      this.groupBox1.Controls.Add(this.label4);
      this.groupBox1.Controls.Add(this.editI);
      this.groupBox1.Controls.Add(this.label5);
      this.groupBox1.Controls.Add(this.label6);
      this.groupBox1.Location = new System.Drawing.Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(297, 105);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Settings";
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label7.Location = new System.Drawing.Point(12, 138);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(186, 20);
      this.label7.TabIndex = 2;
      this.label7.Text = "IEEE 64-bit floating point";
      // 
      // MainForm
      // 
      this.AcceptButton = this.buttonRun;
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1040, 785);
      this.Controls.Add(this.label7);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.buttonRun);
      this.Controls.Add(this.floatingChart);
      this.Name = "MainForm";
      this.Text = "PID Simulation";
      ((System.ComponentModel.ISupportInitialize)(this.floatingChart)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editP)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editI)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editD)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editRoomTemperature)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaximum)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaxPerSecond)).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.DataVisualization.Charting.Chart floatingChart;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.Button buttonRun;
    private System.Windows.Forms.NumericUpDown editP;
    private System.Windows.Forms.NumericUpDown editI;
    private System.Windows.Forms.NumericUpDown editD;
    private System.Windows.Forms.NumericUpDown editRoomTemperature;
    private System.Windows.Forms.NumericUpDown editOvenMaximum;
    private System.Windows.Forms.NumericUpDown editOvenMaxPerSecond;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.Label label7;
  }
}

