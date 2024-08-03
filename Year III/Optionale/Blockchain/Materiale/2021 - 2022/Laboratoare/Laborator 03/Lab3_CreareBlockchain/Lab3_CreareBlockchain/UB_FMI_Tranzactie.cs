using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab3_CreareBlockchain
{
    internal class UB_FMI_Tranzactie
    {
        public string AdresaExpeditor { get; set; }
        public string AdresaDestinatar { get; set; }
        public int Valoare { get; set; }

        public UB_FMI_Tranzactie(string adresaExpeditor, string adresaDestinatar, int val)
        {
            AdresaExpeditor = adresaExpeditor;
            AdresaDestinatar = adresaDestinatar;
            Valoare = val;
        }
    }
}
