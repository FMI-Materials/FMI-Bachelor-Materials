using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface IJobHistoryRepository : IGenericRepository<JobHistory>
    {
        Task<JobHistory?> GetByBothIds(int EmployeeId, int JobId);
    }
}
