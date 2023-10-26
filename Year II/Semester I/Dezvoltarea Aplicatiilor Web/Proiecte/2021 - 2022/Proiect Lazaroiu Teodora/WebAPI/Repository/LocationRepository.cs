using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class LocationRepository : GenericRepository<Location>, ILocationRepository
    {
        public LocationRepository(DataContext context) : base(context) { }
        public async Task<Location?> GetLocationByCity(string city)
        {
            if (city == null)
            {
                return null;
            }

            return await _context.Locations
                .Where(a => a.City.ToLower() == city.ToLower())
                .FirstOrDefaultAsync();
        }
    }
}
