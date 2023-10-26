using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface IJobRepository : IGenericRepository<Job>
    {
        Task<Job?> GetJobByTitle(string title);
    }
}
