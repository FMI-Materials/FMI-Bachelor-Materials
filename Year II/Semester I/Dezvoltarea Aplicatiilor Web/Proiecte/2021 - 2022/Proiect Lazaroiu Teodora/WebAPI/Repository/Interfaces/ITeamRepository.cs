using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface ITeamRepository : IGenericRepository<Team>
    {
        Task<Team?> GetTeamByName (string name);
        Task<Employee?> GetTeamLead (Team team);
    }
}
