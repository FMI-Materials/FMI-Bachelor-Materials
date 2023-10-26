using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using WebAPI.Models.DTOs;

namespace WebAPI.Models.Entities
{
    [Table("Team")]
    public class Team
    {
        [Key]
        public int Id { get; set; }
        public string TeamName { get; set; } = string.Empty;
        public int TeamLeadId { get; set; }
        public int? LocationId { get; set; }
        public Location? Location { get; set; }
        public IEnumerable<Employee> Employees { get; set; } = new HashSet<Employee>();
        public Team()
        {

        }
        public Team(TeamDTO team)
        {
            this.TeamName = team.TeamName;
            this.TeamLeadId = team.TeamLeadId;
            this.LocationId = team.LocationId;
        }
    }
}
