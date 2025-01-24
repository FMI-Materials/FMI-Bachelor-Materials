using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab3_CreareBlockchain
{
    internal class UB_FMI_Blockchain
    {
        
        IList<UB_FMI_Tranzactie> TranzactiiInAsteptare = new List<UB_FMI_Tranzactie>();
        public IList<UB_FMI_Block> Lant { set; get; }
        public int Dificultate { set; get; } = 2;
        public int Recompensa = 1; //1 cryptocurrency

        public UB_FMI_Blockchain()
        {
            // initializam blockchain-ul creat
            InitializareLant();

            // adaugam blocul de start (blocul origine sau primul bloc)
            AdaugareBlocInitial();
        }


        public void InitializareLant()
        {
            Lant = new List<UB_FMI_Block>();
        }

        public UB_FMI_Block CreareBlocInitial()
        {
            return new UB_FMI_Block(DateTime.Now, null, "{}");
        }

        public void AdaugareBlocInitial()
        {
            Lant.Add(CreareBlocInitial());
        }

        public UB_FMI_Block ReturneazaUltimulBloc()
        {
            return Lant[Lant.Count - 1];
        }

        public void AdaugaBlocLaLant(UB_FMI_Block block)
        {
            UB_FMI_Block latestBlock = ReturneazaUltimulBloc();
            block.Index = latestBlock.Index + 1;
            block.HashAnterior = latestBlock.ValoareHash;
            block.ValoareHash = block.calculeazaHash();
            Lant.Add(block);
        }

        public bool IsValid()
        {
            for (int i = 1; i < Lant.Count; i++)
            {
                UB_FMI_Block currentBlock = Lant[i];
                UB_FMI_Block previousBlock = Lant[i - 1];

                if (currentBlock.ValoareHash != currentBlock.calculeazaHash())
                {
                    return false;
                }

                if (currentBlock.HashAnterior != previousBlock.ValoareHash)
                {
                    return false;
                }
            }
            return true;
        }
        public void CreareTranzactii(UB_FMI_Tranzactie tranzactie)
        {
            TranzactiiInAsteptare.Add(tranzactie);
        }

        public void ProcesareTranzactiiInAsteptare(string adresa_miner)
        {
            UB_FMI_Block block = new UB_FMI_Block(DateTime.Now, ObtineUltimulBloc().ValoareHash, TranzactiiInAsteptare);
            AdaugaBloc(block);

            TranzactiiInAsteptare = new List<UB_FMI_Tranzactie>();
            CreareTranzactii(new UB_FMI_Tranzactie(null, adresa_miner, Recompensa));
        }
        public void AdaugaBloc (UB_FMI_Block block)
        {
            UB_FMI_Block latestBlock = ObtineUltimulBloc();
            block.Index = latestBlock.Index + 1;
            block.HashAnterior = latestBlock.ValoareHash;
            block.Minare(this.Dificultate);
            Lant.Add(block);
        }

        public UB_FMI_Block ObtineUltimulBloc()
        {
            return Lant[Lant.Count - 1];
        }

        public int ReturneazaBalantaSold(string adresa)
        {
            int sold = 0;

            for (int i = 0; i < Lant.Count; i++)
            {
                for (int j = 0; j < Lant[i].Tranzactii.Count; j++)
                {
                    var tranzactiaMea = Lant[i].Tranzactii[j];

                    if (tranzactiaMea.AdresaExpeditor == adresa)
                    {
                        sold -= tranzactiaMea.Valoare;
                    }

                    if (tranzactiaMea.AdresaDestinatar == adresa)
                    {
                        sold += tranzactiaMea.Valoare;
                    }
                }
            }

            return sold;
        }
    }
}
