using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class JobRepository : GenericRepository<Job>, IJobRepository
    {
        public JobRepository(DataContext context) : base(context) { }
        public async Task<Job?> GetJobByTitle(string title)
        {
            return await _context.Jobs.Where(a => a.JobTitle.ToLower() == title.ToLower()).FirstOrDefaultAsync();
        }
    }
}
