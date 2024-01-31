package Banking;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Transaction {
    final private String fromIBAN, toIBAN;
    final private double amount;
    final private String description;
    final private Date creationDate;

    public Transaction(String fromIBAN, String toIBAN, double amount, String description) throws Exception {

        if(amount <= 0)
            throw new Exception("The given amount is too low!");

        this.fromIBAN = fromIBAN;
        this.toIBAN = toIBAN;
        this.amount = amount;
        this.description = description;
        this.creationDate = new Date();
    }

    public Transaction(String fromIBAN, String toIBAN, double amount, String description, Date creationDate) throws Exception {
        this.fromIBAN = fromIBAN;
        this.toIBAN = toIBAN;
        this.amount = amount;
        this.description = description;
        this.creationDate = creationDate;
    }

    public Transaction(ResultSet in) throws SQLException {
        this.fromIBAN = in.getString("fromIBAN");
        this.toIBAN = in.getString("toIBAN");
        this.amount = in.getDouble("amount");
        this.description = in.getString("description");
        this.creationDate = in.getDate("creationDate");
    }

    @Override
    public String toString() {
        return "Transaction{" +
                "from=" + fromIBAN +
                ", to=" + toIBAN +
                ", amount=" + amount +
                ", description='" + description + '\'' +
                ", creationDate=" + (new SimpleDateFormat("yyyy-MM-dd+HH:mm:ss")).format(creationDate) +
                '}';
    }

    public String toCSV() {
        return fromIBAN +
                "," + toIBAN +
                "," + amount +
                "," + description +
                "," + (new SimpleDateFormat("yyyy-MM-dd h:m:s")).format(creationDate);
    }

    public String getFromIBAN() {
        return fromIBAN;
    }

    public String getToIBAN() {
        return toIBAN;
    }

    public double getAmount() {
        return amount;
    }

    public String getDescription() {
        return description;
    }

    public Date getCreationDate() {
        return creationDate;
    }
}
