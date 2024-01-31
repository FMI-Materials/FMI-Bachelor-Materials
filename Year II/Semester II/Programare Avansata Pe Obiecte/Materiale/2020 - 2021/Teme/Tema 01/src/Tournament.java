import java.util.*;

public class Tournament {
    List<Team> teams = new ArrayList<Team>();
    Map<String, Team> teamsMap = new HashMap<>();
    List<Match> matches = new ArrayList<>();
    Scanner in;

    Tournament(Scanner in){
        this.in = in;
        this.read();
    }

    @Override
    public String toString(){
        teams.sort(new Team());
        String result = "";
        for (var team: teams)
            result += team.getName() + " " + team.getScore() + " " + team.getOutgoingGoals() + " " + team.getIncomingGoals() + "\n";
        return result;
    }

    public void show(){
        System.out.println(this.toString());
    }

    private void read(){
        int noOfTeams = in.nextInt();
        int noOfGames = in.nextInt();
        for(int i=0;i<noOfGames;++i)
            readMatch();
    }

    private void readMatch(){
        Match match = new Match(in);
        for(int j=0;j<2;j++){
            String teamName = match.getTeamsName().get(j);
            if(teamsMap.containsKey(teamName))
                match.addTeam(teamsMap.get(teamName));
            else{
                Team team = new Team(teamName);
                this.teamsMap.put(teamName, team);
                this.teams.add(team);
                match.addTeam(team);
            }
        }
        match.updateTeams();
        matches.add(match);
    }
}
