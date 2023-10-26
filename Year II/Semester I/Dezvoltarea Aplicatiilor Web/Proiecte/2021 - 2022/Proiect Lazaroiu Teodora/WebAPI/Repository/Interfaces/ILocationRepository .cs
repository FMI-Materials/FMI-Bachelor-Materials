using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface ILocationRepository : IGenericRepository<Location>
    {
        Task<Location?> GetLocationByCity (string city);
    }
}
