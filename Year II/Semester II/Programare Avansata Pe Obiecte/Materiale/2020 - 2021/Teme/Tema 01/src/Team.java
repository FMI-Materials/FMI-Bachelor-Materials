import java.util.Comparator;

public class Team implements Comparator<Team> {
    private int score = 0, incomingGoals = 0, outgoingGoals = 0;
    private final String name;

    Team(String name, int score){
        this.name = name;
        this.score = score;
    }

    Team(String name){
        this.name = name;
    }

    Team(){
        this.name = "";
    }

    public int getIncomingGoals() {
        return incomingGoals;
    }

    public int getOutgoingGoals() {
        return outgoingGoals;
    }

    public int getScore() {
        return score;
    }

    public String getName() {
        return name;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public void addToScore(int points){
        this.score += points;
    }

    public void addToIncomingGoals(int goals){
        this.incomingGoals += goals;
    }

    public void addToOutgoingGoals(int goals){
        this.outgoingGoals += goals;
    }

    @Override
    public int compare(Team o1, Team o2) {
        return o2.score - o1.score;
    }
}
