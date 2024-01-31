import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Match {
    private List<Team> teams = new ArrayList<Team>();
    private final List<String> teamsName = new ArrayList<String>();
    private final List<Integer> goals = new ArrayList<Integer>();

    Scanner in;

    Match(Scanner in){
        this.in = in;
        this.read();
    }

    private void read(){
        this.teamsName.add(in.next());
        this.goals.add(in.nextInt());
        in.next();
        this.goals.add(in.nextInt());
        this.teamsName.add(in.next());
    }

    private void updateScores(){
        if(goals.get(0).equals(goals.get(1))) {
            this.teams.get(0).addToScore(1);
            this.teams.get(1).addToScore(1);
        }
        else if(goals.get(0) > goals.get(1))
            this.teams.get(0).addToScore(3);
        else
            this.teams.get(1).addToScore(3);
    }

    private void updateGoals(){
        this.teams.get(0).addToIncomingGoals(this.goals.get(1));
        this.teams.get(0).addToOutgoingGoals(this.goals.get(0));
        this.teams.get(1).addToIncomingGoals(this.goals.get(0));
        this.teams.get(1).addToOutgoingGoals(this.goals.get(1));
    }

    public void updateTeams(){
        this.updateScores();
        this.updateGoals();
    }

    public void addTeam(Team team){
        this.teams.add(team);
    }

    public List<Team> getTeams() {
        return teams;
    }

    public List<String> getTeamsName() {
        return teamsName;
    }

    public List<Integer> getGoals() {
        return goals;
    }

    public void setTeams(List<Team> teams) {
        this.teams = teams;
    }
}
