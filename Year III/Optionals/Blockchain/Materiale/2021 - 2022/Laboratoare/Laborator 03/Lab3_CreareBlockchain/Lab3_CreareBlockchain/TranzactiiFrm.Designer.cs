namespace Lab3_CreareBlockchain
{
    partial class TranzactiiFrm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.txtTranzactiiDisponibile = new System.Windows.Forms.TextBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.btnIesire = new System.Windows.Forms.Button();
            this.btnGenereazaTranzactii = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tranzactii disponibile";
            // 
            // txtTranzactiiDisponibile
            // 
            this.txtTranzactiiDisponibile.Location = new System.Drawing.Point(30, 52);
            this.txtTranzactiiDisponibile.Multiline = true;
            this.txtTranzactiiDisponibile.Name = "txtTranzactiiDisponibile";
            this.txtTranzactiiDisponibile.Size = new System.Drawing.Size(413, 279);
            this.txtTranzactiiDisponibile.TabIndex = 1;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 392);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(842, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // btnIesire
            // 
            this.btnIesire.Location = new System.Drawing.Point(368, 337);
            this.btnIesire.Name = "btnIesire";
            this.btnIesire.Size = new System.Drawing.Size(75, 34);
            this.btnIesire.TabIndex = 3;
            this.btnIesire.Text = "Iesire";
            this.btnIesire.UseVisualStyleBackColor = true;
            this.btnIesire.Click += new System.EventHandler(this.btnIesire_Click);
            // 
            // btnGenereazaTranzactii
            // 
            this.btnGenereazaTranzactii.Location = new System.Drawing.Point(30, 337);
            this.btnGenereazaTranzactii.Name = "btnGenereazaTranzactii";
            this.btnGenereazaTranzactii.Size = new System.Drawing.Size(148, 34);
            this.btnGenereazaTranzactii.TabIndex = 4;
            this.btnGenereazaTranzactii.Text = "Genereaza tranzactii";
            this.btnGenereazaTranzactii.UseVisualStyleBackColor = true;
            this.btnGenereazaTranzactii.Click += new System.EventHandler(this.btnGenereazaTranzactii_Click);
            // 
            // TranzactiiFrm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(842, 414);
            this.Controls.Add(this.btnGenereazaTranzactii);
            this.Controls.Add(this.btnIesire);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.txtTranzactiiDisponibile);
            this.Controls.Add(this.label1);
            this.Name = "TranzactiiFrm";
            this.Text = "Vizulizare tranzactii";
            this.Load += new System.EventHandler(this.TranzactiiFrm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtTranzactiiDisponibile;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Button btnIesire;
        private System.Windows.Forms.Button btnGenereazaTranzactii;
    }
}