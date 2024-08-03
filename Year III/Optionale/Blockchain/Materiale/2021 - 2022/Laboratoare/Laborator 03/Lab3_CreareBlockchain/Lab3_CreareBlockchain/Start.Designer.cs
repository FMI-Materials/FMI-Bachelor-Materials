namespace Lab3_CreareBlockchain
{
    partial class Start
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.iesireToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.operatiiBlockchainToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tranzactiiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.despreToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.txtRezultat = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnGenereazaBlockchain = new System.Windows.Forms.Button();
            this.btnIesire = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txtNrTotalBlocuri = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cboBlocuriDupaHash = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtBloc_HashAnterior = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtBloc_Index = new System.Windows.Forms.TextBox();
            this.txtBloc_Ora = new System.Windows.Forms.TextBox();
            this.txtBloc_Data = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtBloc_Suma = new System.Windows.Forms.TextBox();
            this.txtBloc_Destinatar = new System.Windows.Forms.TextBox();
            this.txtBloc_Expeditor = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.operatiiBlockchainToolStripMenuItem,
            this.despreToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(928, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.iesireToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // iesireToolStripMenuItem
            // 
            this.iesireToolStripMenuItem.Name = "iesireToolStripMenuItem";
            this.iesireToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
            this.iesireToolStripMenuItem.Text = "Iesire";
            this.iesireToolStripMenuItem.Click += new System.EventHandler(this.iesireToolStripMenuItem_Click);
            // 
            // operatiiBlockchainToolStripMenuItem
            // 
            this.operatiiBlockchainToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tranzactiiToolStripMenuItem});
            this.operatiiBlockchainToolStripMenuItem.Name = "operatiiBlockchainToolStripMenuItem";
            this.operatiiBlockchainToolStripMenuItem.Size = new System.Drawing.Size(122, 20);
            this.operatiiBlockchainToolStripMenuItem.Text = "Operatii Blockchain";
            // 
            // tranzactiiToolStripMenuItem
            // 
            this.tranzactiiToolStripMenuItem.Name = "tranzactiiToolStripMenuItem";
            this.tranzactiiToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.tranzactiiToolStripMenuItem.Text = "Tranzactii";
            this.tranzactiiToolStripMenuItem.Click += new System.EventHandler(this.tranzactiiToolStripMenuItem_Click);
            // 
            // despreToolStripMenuItem
            // 
            this.despreToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.despreToolStripMenuItem.Name = "despreToolStripMenuItem";
            this.despreToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.despreToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 541);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(928, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // txtRezultat
            // 
            this.txtRezultat.Location = new System.Drawing.Point(12, 73);
            this.txtRezultat.Multiline = true;
            this.txtRezultat.Name = "txtRezultat";
            this.txtRezultat.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtRezultat.Size = new System.Drawing.Size(450, 410);
            this.txtRezultat.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Detalii Blockchain";
            // 
            // btnGenereazaBlockchain
            // 
            this.btnGenereazaBlockchain.Location = new System.Drawing.Point(12, 495);
            this.btnGenereazaBlockchain.Name = "btnGenereazaBlockchain";
            this.btnGenereazaBlockchain.Size = new System.Drawing.Size(167, 35);
            this.btnGenereazaBlockchain.TabIndex = 4;
            this.btnGenereazaBlockchain.Text = "Genereaza Blockchain";
            this.btnGenereazaBlockchain.UseVisualStyleBackColor = true;
            this.btnGenereazaBlockchain.Click += new System.EventHandler(this.btnGenereazaBlockchain_Click);
            // 
            // btnIesire
            // 
            this.btnIesire.Location = new System.Drawing.Point(801, 495);
            this.btnIesire.Name = "btnIesire";
            this.btnIesire.Size = new System.Drawing.Size(110, 35);
            this.btnIesire.TabIndex = 5;
            this.btnIesire.Text = "Iesire";
            this.btnIesire.UseVisualStyleBackColor = true;
            this.btnIesire.Click += new System.EventHandler(this.btnIesire_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(254, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Nr. total de blocuri";
            // 
            // txtNrTotalBlocuri
            // 
            this.txtNrTotalBlocuri.Location = new System.Drawing.Point(353, 45);
            this.txtNrTotalBlocuri.Name = "txtNrTotalBlocuri";
            this.txtNrTotalBlocuri.Size = new System.Drawing.Size(109, 20);
            this.txtNrTotalBlocuri.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(495, 48);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(195, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Selecteaza un bloc dupa valoarea hash";
            // 
            // cboBlocuriDupaHash
            // 
            this.cboBlocuriDupaHash.FormattingEnabled = true;
            this.cboBlocuriDupaHash.Location = new System.Drawing.Point(498, 73);
            this.cboBlocuriDupaHash.Name = "cboBlocuriDupaHash";
            this.cboBlocuriDupaHash.Size = new System.Drawing.Size(413, 21);
            this.cboBlocuriDupaHash.TabIndex = 9;
            this.cboBlocuriDupaHash.SelectedIndexChanged += new System.EventHandler(this.cboBlocuriDupaHash_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtBloc_HashAnterior);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.txtBloc_Index);
            this.groupBox1.Controls.Add(this.txtBloc_Ora);
            this.groupBox1.Controls.Add(this.txtBloc_Data);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Location = new System.Drawing.Point(498, 103);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(413, 380);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Detalii blocuri";
            // 
            // txtBloc_HashAnterior
            // 
            this.txtBloc_HashAnterior.Location = new System.Drawing.Point(25, 341);
            this.txtBloc_HashAnterior.Name = "txtBloc_HashAnterior";
            this.txtBloc_HashAnterior.Size = new System.Drawing.Size(361, 20);
            this.txtBloc_HashAnterior.TabIndex = 8;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(22, 325);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(84, 13);
            this.label7.TabIndex = 7;
            this.label7.Text = "Hash Anterior";
            // 
            // txtBloc_Index
            // 
            this.txtBloc_Index.Location = new System.Drawing.Point(83, 87);
            this.txtBloc_Index.Name = "txtBloc_Index";
            this.txtBloc_Index.Size = new System.Drawing.Size(303, 20);
            this.txtBloc_Index.TabIndex = 6;
            // 
            // txtBloc_Ora
            // 
            this.txtBloc_Ora.Location = new System.Drawing.Point(83, 55);
            this.txtBloc_Ora.Name = "txtBloc_Ora";
            this.txtBloc_Ora.Size = new System.Drawing.Size(303, 20);
            this.txtBloc_Ora.TabIndex = 5;
            // 
            // txtBloc_Data
            // 
            this.txtBloc_Data.Location = new System.Drawing.Point(83, 25);
            this.txtBloc_Data.Name = "txtBloc_Data";
            this.txtBloc_Data.Size = new System.Drawing.Size(303, 20);
            this.txtBloc_Data.TabIndex = 4;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtBloc_Suma);
            this.groupBox2.Controls.Add(this.txtBloc_Destinatar);
            this.groupBox2.Controls.Add(this.txtBloc_Expeditor);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(25, 155);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(361, 129);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Datele blocului";
            // 
            // txtBloc_Suma
            // 
            this.txtBloc_Suma.Location = new System.Drawing.Point(91, 87);
            this.txtBloc_Suma.Name = "txtBloc_Suma";
            this.txtBloc_Suma.Size = new System.Drawing.Size(257, 20);
            this.txtBloc_Suma.TabIndex = 9;
            // 
            // txtBloc_Destinatar
            // 
            this.txtBloc_Destinatar.Location = new System.Drawing.Point(91, 54);
            this.txtBloc_Destinatar.Name = "txtBloc_Destinatar";
            this.txtBloc_Destinatar.Size = new System.Drawing.Size(257, 20);
            this.txtBloc_Destinatar.TabIndex = 8;
            // 
            // txtBloc_Expeditor
            // 
            this.txtBloc_Expeditor.Location = new System.Drawing.Point(90, 23);
            this.txtBloc_Expeditor.Name = "txtBloc_Expeditor";
            this.txtBloc_Expeditor.Size = new System.Drawing.Size(257, 20);
            this.txtBloc_Expeditor.TabIndex = 7;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(6, 90);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(79, 13);
            this.label10.TabIndex = 2;
            this.label10.Text = "Suma (Valoare)";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(30, 26);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 13);
            this.label9.TabIndex = 1;
            this.label9.Text = "Expeditor";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(30, 59);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 13);
            this.label8.TabIndex = 0;
            this.label8.Text = "Destinatar";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(22, 90);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(38, 13);
            this.label6.TabIndex = 2;
            this.label6.Text = "Index";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(22, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(27, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Ora";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(22, 28);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(34, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Data";
            // 
            // Start
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(928, 563);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.cboBlocuriDupaHash);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtNrTotalBlocuri);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnIesire);
            this.Controls.Add(this.btnGenereazaBlockchain);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtRezultat);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Start";
            this.Text = "Blockchain - Laborator 3";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem despreToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.TextBox txtRezultat;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnGenereazaBlockchain;
        private System.Windows.Forms.Button btnIesire;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtNrTotalBlocuri;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cboBlocuriDupaHash;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtBloc_Index;
        private System.Windows.Forms.TextBox txtBloc_Ora;
        private System.Windows.Forms.TextBox txtBloc_Data;
        private System.Windows.Forms.TextBox txtBloc_Suma;
        private System.Windows.Forms.TextBox txtBloc_Destinatar;
        private System.Windows.Forms.TextBox txtBloc_Expeditor;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtBloc_HashAnterior;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem iesireToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem operatiiBlockchainToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tranzactiiToolStripMenuItem;
    }
}

