package Banking;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.security.AccessControlContext;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class AccountSingleton {

    private static AccountSingleton single_instance = null;

    private List<Account> accounts = new ArrayList<Account>();

    public static AccountSingleton getInstance()
    {
        if (single_instance == null)
            single_instance = new AccountSingleton();
        return single_instance;
    }

    public void setAccounts(List<Account> accounts) {
        this.accounts = accounts;
    }

    public List<Account> getAccounts() {
        return accounts;
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
            System.out.println("No saved accounts!");
        }

        return columns;
    }

    public void loadFromCSV() {
        var columns = AccountSingleton.getCSVColumns("data/accounts.csv");
        for(var fields : columns){
            var newAccount = new Account(
                    fields[0],
                    fields[1],
                    Double.parseDouble(fields[2]),
                    fields[3],
                    Integer.parseInt(fields[4])
            );
            accounts.add(newAccount);
        }
        AccountFactory.incrementUniqueId(columns.size());
    }

    public void dumpToCSV(){
        try{
            var writer = new FileWriter("data/accounts.csv");
            for(var account : this.accounts){
                writer.write(account.toCSV());
                writer.write("\n");
            }
            writer.close();
        }catch (IOException e){
            System.out.println(e.toString());
        }
    }
}
