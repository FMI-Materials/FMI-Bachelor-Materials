package Card;

public class CardFactory {
    private static int uniqueId = 0;

    public Card addCard(String IBAN, String name){
        return new Card(uniqueId++, IBAN, name);
    }
    public MasterCard createMasterCard(String IBAN, String name){
        return new MasterCard(uniqueId++, IBAN, name);
    }
    public Visa createVisaCard(String IBAN, String name){
        return new Visa(uniqueId++, IBAN, name);
    }
}
