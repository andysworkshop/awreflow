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
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
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
      ((System.ComponentModel.ISupportInitialize)(this.chart)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editP)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editI)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editD)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editRoomTemperature)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaximum)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaxPerSecond)).BeginInit();
      this.SuspendLayout();
      // 
      // chart
      // 
      this.chart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      chartArea2.AxisX.MajorGrid.LineColor = System.Drawing.Color.Gainsboro;
      chartArea2.AxisY.MajorGrid.LineColor = System.Drawing.Color.Gainsboro;
      chartArea2.BorderColor = System.Drawing.Color.Silver;
      chartArea2.Name = "ChartArea1";
      this.chart.ChartAreas.Add(chartArea2);
      this.chart.Location = new System.Drawing.Point(23, 118);
      this.chart.Name = "chart";
      series3.ChartArea = "ChartArea1";
      series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
      series3.LabelForeColor = System.Drawing.Color.DimGray;
      series3.Name = "Series1";
      series4.ChartArea = "ChartArea1";
      series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
      series4.Name = "Series2";
      this.chart.Series.Add(series3);
      this.chart.Series.Add(series4);
      this.chart.Size = new System.Drawing.Size(1029, 538);
      this.chart.TabIndex = 0;
      this.chart.Text = "chart1";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(20, 26);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(17, 13);
      this.label1.TabIndex = 1;
      this.label1.Text = "P:";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(20, 52);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(13, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "I:";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(20, 78);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(18, 13);
      this.label3.TabIndex = 3;
      this.label3.Text = "D:";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(127, 26);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(97, 13);
      this.label4.TabIndex = 5;
      this.label4.Text = "Room temperature:";
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(127, 52);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(82, 13);
      this.label5.TabIndex = 6;
      this.label5.Text = "Oven maximum:";
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(127, 78);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(80, 13);
      this.label6.TabIndex = 7;
      this.label6.Text = "Oven max/sec:";
      // 
      // buttonRun
      // 
      this.buttonRun.Location = new System.Drawing.Point(344, 20);
      this.buttonRun.Name = "buttonRun";
      this.buttonRun.Size = new System.Drawing.Size(75, 23);
      this.buttonRun.TabIndex = 9;
      this.buttonRun.Text = "Run";
      this.buttonRun.UseVisualStyleBackColor = true;
      this.buttonRun.Click += new System.EventHandler(this.buttonRun_Click);
      // 
      // editP
      // 
      this.editP.Location = new System.Drawing.Point(44, 23);
      this.editP.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editP.Name = "editP";
      this.editP.Size = new System.Drawing.Size(61, 20);
      this.editP.TabIndex = 10;
      this.editP.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.editP.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editI
      // 
      this.editI.Location = new System.Drawing.Point(44, 49);
      this.editI.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editI.Name = "editI";
      this.editI.Size = new System.Drawing.Size(61, 20);
      this.editI.TabIndex = 11;
      this.editI.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.editI.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editD
      // 
      this.editD.Location = new System.Drawing.Point(44, 75);
      this.editD.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editD.Name = "editD";
      this.editD.Size = new System.Drawing.Size(61, 20);
      this.editD.TabIndex = 12;
      this.editD.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.editD.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editRoomTemperature
      // 
      this.editRoomTemperature.Location = new System.Drawing.Point(230, 23);
      this.editRoomTemperature.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
      this.editRoomTemperature.Name = "editRoomTemperature";
      this.editRoomTemperature.Size = new System.Drawing.Size(61, 20);
      this.editRoomTemperature.TabIndex = 12;
      this.editRoomTemperature.Value = new decimal(new int[] {
            25,
            0,
            0,
            0});
      this.editRoomTemperature.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editOvenMaximum
      // 
      this.editOvenMaximum.Location = new System.Drawing.Point(230, 49);
      this.editOvenMaximum.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editOvenMaximum.Name = "editOvenMaximum";
      this.editOvenMaximum.Size = new System.Drawing.Size(61, 20);
      this.editOvenMaximum.TabIndex = 12;
      this.editOvenMaximum.Value = new decimal(new int[] {
            250,
            0,
            0,
            0});
      this.editOvenMaximum.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // editOvenMaxPerSecond
      // 
      this.editOvenMaxPerSecond.Location = new System.Drawing.Point(230, 75);
      this.editOvenMaxPerSecond.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
      this.editOvenMaxPerSecond.Name = "editOvenMaxPerSecond";
      this.editOvenMaxPerSecond.Size = new System.Drawing.Size(61, 20);
      this.editOvenMaxPerSecond.TabIndex = 12;
      this.editOvenMaxPerSecond.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
      this.editOvenMaxPerSecond.ValueChanged += new System.EventHandler(this.buttonRun_Click);
      // 
      // MainForm
      // 
      this.AcceptButton = this.buttonRun;
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1076, 680);
      this.Controls.Add(this.editOvenMaxPerSecond);
      this.Controls.Add(this.editOvenMaximum);
      this.Controls.Add(this.editRoomTemperature);
      this.Controls.Add(this.editD);
      this.Controls.Add(this.editI);
      this.Controls.Add(this.editP);
      this.Controls.Add(this.buttonRun);
      this.Controls.Add(this.label6);
      this.Controls.Add(this.label5);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.chart);
      this.Name = "MainForm";
      this.Text = "PID Simulation";
      ((System.ComponentModel.ISupportInitialize)(this.chart)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editP)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editI)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editD)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editRoomTemperature)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaximum)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.editOvenMaxPerSecond)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.DataVisualization.Charting.Chart chart;
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
  }
}

