using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab3_CreareBlockchain
{
    public partial class TranzactiiFrm : Form
    {
        public TranzactiiFrm()
        {
            InitializeComponent();
            // pozitionam fereastra pe centrul ecranului
            this.CenterToScreen();

            // dezactivam modul de editare al controlelor
            txtTranzactiiDisponibile.ReadOnly = true;
        }

        private void TranzactiiFrm_Load(object sender, EventArgs e)
        {

        }

        private void btnIesire_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnGenereazaTranzactii_Click(object sender, EventArgs e)
        {
            var startTime = DateTime.Now;

            UB_FMI_Blockchain phillyCoin = new UB_FMI_Blockchain();
            phillyCoin.CreareTranzactii(new UB_FMI_Tranzactie("Henry", "MaHesh", 10));
            phillyCoin.ProcesareTranzactiiInAsteptare("Bill");

            phillyCoin.CreareTranzactii(new UB_FMI_Tranzactie("MaHesh", "Henry", 5));
            phillyCoin.CreareTranzactii(new UB_FMI_Tranzactie("MaHesh", "Henry", 5));
            phillyCoin.ProcesareTranzactiiInAsteptare("Bill");

            var endTime = DateTime.Now;

            txtTranzactiiDisponibile.AppendText($"Duration: {endTime - startTime}");

            txtTranzactiiDisponibile.AppendText("=========================");
            txtTranzactiiDisponibile.AppendText($"Henry' balance: {phillyCoin.ReturneazaBalantaSold("Henry")}");
            txtTranzactiiDisponibile.AppendText($"MaHesh' balance: {phillyCoin.ReturneazaBalantaSold("MaHesh")}");
            txtTranzactiiDisponibile.AppendText($"Bill' balance: {phillyCoin.ReturneazaBalantaSold("Bill")}");

            txtTranzactiiDisponibile.AppendText("=========================");
            txtTranzactiiDisponibile.AppendText($"phillyCoin");
            txtTranzactiiDisponibile.AppendText(JsonConvert.SerializeObject(phillyCoin, Formatting.Indented));            
        }
    }
}
