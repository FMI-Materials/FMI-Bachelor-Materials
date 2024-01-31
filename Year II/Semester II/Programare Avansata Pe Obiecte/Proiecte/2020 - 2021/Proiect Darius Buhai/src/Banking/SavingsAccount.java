package Banking;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class SavingsAccount extends Account{
    private final Date startDate, endDate;
    private final int interest;

    public SavingsAccount(String name, int customerId, int uniqueId) {
        super(name, customerId, uniqueId);

        this.startDate = new Date();
        this.interest = 3;

        Calendar c = Calendar.getInstance();
        c.setTime(new Date());
        c.add(Calendar.YEAR, 1);
        this.endDate = c.getTime();
    }

    public SavingsAccount(String IBAN, String swift, double amount, String name, int customerId, Date startDate, Date endDate, int interest) {
        super(IBAN, swift, amount, name, customerId);

        this.startDate = startDate;
        this.endDate = endDate;
        this.interest = interest;
    }

    public SavingsAccount(ResultSet in) throws SQLException {
        super(in);
        this.startDate = in.getDate("startDate");
        this.endDate = in.getDate("endDate");
        this.interest = in.getInt("interest");
    }

    @Override
    public String toString() {
        return "SavingsAccount{" +
                "IBAN='" + IBAN + '\'' +
                ", swift='" + swift + '\'' +
                ", amount=" + amount +
                ", name='" + name + '\'' +
                ", customerId=" + customerId +
                ", cards=" + cards +
                ", startDate=" + (new SimpleDateFormat("yyyy-MM-dd")).format(startDate) +
                ", endDate=" + (new SimpleDateFormat("yyyy-MM-dd")).format(endDate) +
                ", interest=" + interest +
                '}';
    }

    public String toCSV() {
        return IBAN +
                "," + swift +
                "," + amount +
                "," + name +
                "," + customerId +
                "," + cards +
                "," + (new SimpleDateFormat("yyyy-MM-dd")).format(startDate) +
                "," + (new SimpleDateFormat("yyyy-MM-dd")).format(endDate) +
                "," + interest;
    }

    public Date getStartDate() {
        return startDate;
    }

    public Date getEndDate() {
        return endDate;
    }

    public int getInterest() {
        return interest;
    }
}
