using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;         // pentru calcularea valorilor hash
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Lab3_CreareBlockchain
{
    internal class UB_FMI_Block
    {
        public int Index { get; set; }
        public DateTime DataTimp { get; set; }
        public string HashAnterior { get; set; }
        public string ValoareHash { get; set; }
        public string DateBloc { get; set; }
        public IList<UB_FMI_Tranzactie> Tranzactii { get; set; }
        public int Nonce { get; set; } = 0;


        //** constructor
        public UB_FMI_Block(DateTime valDataTimp, string hashAnterior, string dateDinBloc)
        {
            Index = 0;
            DataTimp = valDataTimp;
            HashAnterior = hashAnterior;
            DateBloc = dateDinBloc;
            ValoareHash = calculeazaHash();
        }

        public UB_FMI_Block(DateTime timeStamp, string hashAnterior, IList<UB_FMI_Tranzactie> tranzactii)
        {
            Index = 0;
            DataTimp = timeStamp;
            HashAnterior = hashAnterior;
            Tranzactii = tranzactii;
        }

        public string calculeazaHash()
        {
            // general un hash tip sha pe 256 biti
            SHA256 sha256 = SHA256.Create();

            // reprezentam in octeti data&timp impreuna cu hash-ul obtinut anterior si datele din bloc
            byte[] intrare = Encoding.ASCII.GetBytes($"{DataTimp}-{HashAnterior ?? ""}-{DateBloc}");
            byte[] iesire = sha256.ComputeHash(intrare);

            // returnam hash-ul
            return Convert.ToBase64String(iesire);
        }

        // functia este pentru contextul de tranzactii
        public string calculeazaHash_ContextTranzactii()
        {
            SHA256 sha256 = SHA256.Create();

            byte[] intrare = Encoding.ASCII.GetBytes($"{DataTimp}-{HashAnterior ?? ""}-{JsonConvert.SerializeObject(Tranzactii)}-{Nonce}");
            byte[] iesire = sha256.ComputeHash(intrare);

            return Convert.ToBase64String(iesire);
        }
        public void Minare(int gradDificultate)
        {
            var leadingZeros = new string('0', gradDificultate);
            while (this.ValoareHash == null || this.ValoareHash.Substring(0, gradDificultate) != leadingZeros)
            {
                this.Nonce++;
                this.ValoareHash = this.calculeazaHash_ContextTranzactii();
            }
        }
    }
}
