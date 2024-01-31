package pachetA;

/*
        Ordine modificatori acces permisiv -> restrictiv

        public    = oricine de oriunde poate accesa orice fel de atribut/metoda dintr-o clasa publica
        protected = avem acces in acelasi pachet si chiar daca ne aflam in alt pachet,
                    avem acces la atribut/metoda prin mostenire
        default   = avem acces la atribut/metoda doar din acelasi pachet
        private   = avem acces doar in interioriul clasei

 */

public class TestPachetA {

    public static void main(String[] args) {

        Human human = new Human();
        human.name = "Ilie";
        human.address = "Bucuresti";
        human.age = 18;

    }
}
