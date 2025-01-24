using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Newtonsoft.Json;

namespace Lab3_CreareBlockchain
{
    public partial class Start : Form
    {
        // ne declaram un obiect de tip blockchain cu moneda utilizata (simulator)
        UB_FMI_Blockchain monedaMIM = new UB_FMI_Blockchain();


        public Start()
        {
            InitializeComponent();

            // aliniem fereastra pe centrul ecranului
            this.CenterToScreen();

            // dezactivam modul de editare al urmatoarelor textbox-uri
            txtRezultat.ReadOnly = true;
            txtNrTotalBlocuri.ReadOnly = true;
            txtBloc_Data.ReadOnly = true;
            txtBloc_Ora.ReadOnly = true;
            txtBloc_Index.ReadOnly = true;
            txtBloc_Expeditor.ReadOnly = true; 
            txtBloc_Destinatar.ReadOnly = true;
            txtBloc_Suma.ReadOnly = true;
            txtBloc_HashAnterior.ReadOnly = true;
        }

        private void btnIesire_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           
        }

        private void ExtrageDateDinBloc(string dateBloc)
        {
            string[] dateDinBloc = dateBloc.Split(',');
            string expeditor = string.Empty;
            string destinatar = string.Empty; 
            string suma = string.Empty;
            
            expeditor = dateDinBloc[0].Remove(0,11);
            destinatar = dateDinBloc[1].Remove(0,11);
            suma = dateDinBloc[2].Remove(0, 5);            

            txtBloc_Expeditor.Text = expeditor;   
            txtBloc_Destinatar.Text = destinatar;
            txtBloc_Suma.Text = suma.Remove(suma.LastIndexOf('}'));
        }

        private void btnGenereazaBlockchain_Click(object sender, EventArgs e)
        {
            // generam blocuri mod aleator
            monedaMIM.AdaugaBlocLaLant(new UB_FMI_Block(DateTime.Now, null, "{expeditor:Marius,destinatar:Cristi,suma:31}"));
            monedaMIM.AdaugaBlocLaLant(new UB_FMI_Block(DateTime.Now, null, "{expeditor:Cristi,destinatar:Marius,suma:23}"));
            monedaMIM.AdaugaBlocLaLant(new UB_FMI_Block(DateTime.Now, null, "{expeditor:Laurentiu,destinatar:Ionut,suma:3}"));
            monedaMIM.AdaugaBlocLaLant(new UB_FMI_Block(DateTime.Now, null, "{expeditor:Popescu,destinatar:Valentin,suma:65}"));
            monedaMIM.AdaugaBlocLaLant(new UB_FMI_Block(DateTime.Now, null, "{expeditor:Ionescu,destinatar:Cristescu,suma:54}"));
            monedaMIM.AdaugaBlocLaLant(new UB_FMI_Block(DateTime.Now, null, "{expeditor:Cristescu,destinatar:Cristi,suma:34}"));

            // afisam numarul total de blocuri
            txtNrTotalBlocuri.Text = monedaMIM.Lant.Count().ToString();

            
            txtRezultat.AppendText(JsonConvert.SerializeObject(monedaMIM, Formatting.Indented) + System.Environment.NewLine);

            txtRezultat.AppendText(System.Environment.NewLine);
            txtRezultat.AppendText("------------------------------------------" + System.Environment.NewLine);

            txtRezultat.AppendText($"Is Chain Valid: " + monedaMIM.IsValid() + System.Environment.NewLine);

            txtRezultat.AppendText($"Update amount to 1000" + System.Environment.NewLine);
            monedaMIM.Lant[1].DateBloc = "{expeditor:Marinescu,destinatar:Dumitrescu,suma:1000}";           

            txtRezultat.AppendText($"Is Chain Valid: " + monedaMIM.IsValid() + System.Environment.NewLine);

            txtRezultat.AppendText($"Update hash" + System.Environment.NewLine);
            //monedaMIM.Chain[1].ValoareHash = monedaMIM.Chain[1].calculeazaHash();
            
            txtRezultat.AppendText($"Is Chain Valid: " + monedaMIM.IsValid() + System.Environment.NewLine);

            txtRezultat.AppendText($"Update the entire chain" + System.Environment.NewLine);
            //monedaMIM.Chain[2].HashAnterior = monedaMIM.Chain[1].ValoareHash;
            //monedaMIM.Chain[2].ValoareHash = monedaMIM.Chain[2].calculeazaHash();
            //monedaMIM.Chain[3].HashAnterior = monedaMIM.Chain[2].ValoareHash;
            //monedaMIM.Chain[3].ValoareHash = monedaMIM.Chain[3].calculeazaHash();

            txtRezultat.AppendText($"Is Chain Valid: " + monedaMIM.IsValid() + System.Environment.NewLine);

            // parcurgem toate blocurile create si le adaugam in combobox-ul cboBlocuriDupaHash
            for (int i = 0; i < monedaMIM.Lant.Count(); i++)
            {
                cboBlocuriDupaHash.Items.Add(monedaMIM.Lant[i].ValoareHash);
            }
        }

        private void cboBlocuriDupaHash_SelectedIndexChanged(object sender, EventArgs e)
        {
            string hashSelectat = cboBlocuriDupaHash.Text.ToString();
            DateTime data_timp;            

            for (int i = 0; i < monedaMIM.Lant.Count(); i++)
            {
                if (monedaMIM.Lant[i].ValoareHash == hashSelectat)
                {
                    ExtrageDateDinBloc(monedaMIM.Lant[i].DateBloc.ToString());
                    txtBloc_Index.Text = monedaMIM.Lant[i].Index.ToString();
                    data_timp = Convert.ToDateTime(monedaMIM.Lant[i].DataTimp);
                    txtBloc_Data.Text = data_timp.ToShortDateString().ToString();
                    txtBloc_Ora.Text = data_timp.TimeOfDay.ToString();
                    txtBloc_HashAnterior.Text = monedaMIM.Lant[i].HashAnterior.ToString();
                }
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DespreApp da = new DespreApp();
            da.Show();
        }

        private void iesireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void tranzactiiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TranzactiiFrm tf = new TranzactiiFrm();
            tf.Show();
        }
    }
}
