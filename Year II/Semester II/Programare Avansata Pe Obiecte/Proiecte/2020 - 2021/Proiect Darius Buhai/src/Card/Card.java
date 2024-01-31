package Card;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class Card{
    private final int cardId, CVV;
    private String number, name;
    private String IBAN;
    private final Date expirationDate;

    static private final Set<String> usedNumbers = new HashSet<>();

    public Card(int cardId, String IBAN, String name) {
        this.cardId = cardId;
        this.IBAN = IBAN;
        this.name = name;
        this.number = this.generateCardNumber();

        /* Generate Card Number */
        while(usedNumbers.contains(this.number))
            this.number = this.generateCardNumber();
        usedNumbers.add(this.number);

        /* Generate CVV */
        this.CVV = this.generateCardCVV();

        /* Generate expiration date */
        Calendar c = Calendar.getInstance();
        c.setTime(new Date());
        c.add(Calendar.YEAR, 3);
        this.expirationDate = c.getTime();
    }

    public void read(Scanner in){
        System.out.println("IBAN: ");
        this.IBAN = in.nextLine();
        System.out.println("Name: ");
        this.name = in.nextLine();
    }

    private String generateCardNumber(){
        byte[] array = new byte[16];
        new Random().nextBytes(array);
        return new String(array, StandardCharsets.UTF_8);
    }

    private int generateCardCVV(){
        var rand = new Random();
        return 100 + rand.nextInt(899);
    }

    public int getCardId() {
        return cardId;
    }

    public String getNumber() {
        return number;
    }

    public String getName() {
        return name;
    }

    public int getCVV() {
        return CVV;
    }

    public String getIBAN() {
        return IBAN;
    }

    public Date getExpirationDate() {
        return expirationDate;
    }
}
