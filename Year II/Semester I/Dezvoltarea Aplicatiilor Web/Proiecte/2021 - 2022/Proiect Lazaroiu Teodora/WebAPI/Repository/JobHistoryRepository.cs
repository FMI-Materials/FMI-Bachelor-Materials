using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class JobHistoryRepository : GenericRepository<JobHistory>, IJobHistoryRepository
    {
        public JobHistoryRepository(DataContext context) : base(context) { }
        public async Task<JobHistory?> GetByBothIds(int EmployeeId, int JobId)
        {
            return await _context.JobHistories.Where(a => a.EmployeeId == EmployeeId
            && a.JobId == JobId).FirstOrDefaultAsync();
        }
    }
}
