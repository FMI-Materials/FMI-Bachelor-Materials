using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class TeamRepository : GenericRepository<Team>, ITeamRepository
    {
        public TeamRepository(DataContext context) : base(context) { }
        public async Task<Team?> GetTeamByName(string name)
        {
            if (string.IsNullOrEmpty(name))
            {
                return null;
            }    
            return await _context.Teams.Where(a => a.TeamName.ToLower() == name.ToLower()).FirstOrDefaultAsync();
        }
        public async Task<Employee?> GetTeamLead(Team team)
        {
            var teamLead = await _context.Employees.Where(a => a.EmployeeId == team.TeamLeadId).FirstOrDefaultAsync();

            return teamLead;
        }
    }
}
