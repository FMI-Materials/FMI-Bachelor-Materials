package Banking;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class SavingsAccountSingleton {

    private static SavingsAccountSingleton single_instance = null;

    final private AccountFactory accountFactory = new AccountFactory();
    private List<SavingsAccount> savingsAccounts = new ArrayList<SavingsAccount>();

    public static SavingsAccountSingleton getInstance()
    {
        if (single_instance == null)
            single_instance = new SavingsAccountSingleton();
        return single_instance;
    }

    public void setSavingsAccounts(List<SavingsAccount> savingsAccounts) {
        this.savingsAccounts = savingsAccounts;
    }

    public List<SavingsAccount> getSavingsAccounts() {
        return savingsAccounts;
    }

    private static List<String[]> getCSVColumns(String fileName){

        List<String[]> columns = new ArrayList<>();

        try(var in = new BufferedReader(new FileReader(fileName))) {

            String line;

            while((line = in.readLine()) != null ) {
                String[] fields = line.replaceAll(" ", "").split(",");
                columns.add(fields);
            }
        } catch (IOException e) {
            System.out.println("No saved savings accounts!");
        }

        return columns;
    }

    public void loadFromCSV() {
        try {
            var columns = SavingsAccountSingleton.getCSVColumns("data/savings_accounts.csv");
            for(var fields : columns){
                var newSavingsAccount = new SavingsAccount(
                        fields[0],
                        fields[1],
                        Double.parseDouble(fields[2]),
                        fields[3],
                        Integer.parseInt(fields[4]),
                        new SimpleDateFormat("yyyy-MM-dd").parse(fields[5]),
                        new SimpleDateFormat("yyyy-MM-dd").parse(fields[6]),
                        Integer.parseInt(fields[7])
                );
                savingsAccounts.add(newSavingsAccount);
            }
            AccountFactory.incrementUniqueId(columns.size());
        }catch (ParseException e){
            System.out.println("Cannot load savings accounts!");
        }

    }

    public void dumpToCSV(){
        try{
            var writer = new FileWriter("data/savings_accounts.csv");
            for(var account : this.savingsAccounts){
                writer.write(account.toCSV());
                writer.write("\n");
            }
            writer.close();
        }catch (IOException e){
            System.out.println(e.toString());
        }
    }
}
