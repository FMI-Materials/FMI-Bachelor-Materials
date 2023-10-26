using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class TeamDTO
    {
        public int Id { get; set; }
        public string TeamName { get; set; } = string.Empty;
        public int TeamLeadId { get; set; }
        public int? LocationId { get; set; }

        public TeamDTO(Team team)
        {
            Id = team.Id;
            TeamName = team.TeamName;
            TeamLeadId = team.TeamLeadId;
            LocationId = team.LocationId;
        }

        public TeamDTO()
        {

        }
    }
}
