package Banking;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class TransactionSingleton {

    private static TransactionSingleton single_instance = null;

    final private AccountFactory accountFactory = new AccountFactory();
    private List<Transaction> transactions = new ArrayList<Transaction>();

    public static TransactionSingleton getInstance()
    {
        if (single_instance == null)
            single_instance = new TransactionSingleton();
        return single_instance;
    }

    public void setTransactions(List<Transaction> transactions) {
        this.transactions = transactions;
    }

    public List<Transaction> getTransactions() {
        return transactions;
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
            System.out.println("No saved transactions!");
        }

        return columns;
    }

    public void loadFromCSV() {
        try {
            var columns = TransactionSingleton.getCSVColumns("data/transactions.csv");
            for(var fields : columns){
                var newTransaction = new Transaction(
                        fields[0],
                        fields[1],
                        Double.parseDouble(fields[2]),
                        fields[3],
                        new SimpleDateFormat("yyyy-MM-dd+HH:mm:ss").parse(fields[4])
                );
                transactions.add(newTransaction);
            }
        }catch (ParseException e){
            System.out.println("Cannot load transactions! - parse exception");
        } catch (Exception e) {
            System.out.println("Cannot parse transaction - invalid format");
        }
    }

    public void dumpToCSV(){
        try{
            var writer = new FileWriter("data/transactions.csv");
            for(var transaction : this.transactions){
                writer.write(transaction.toCSV());
                writer.write("\n");
            }
            writer.close();
        }catch (IOException e){
            System.out.println(e.toString());
        }
    }
}
