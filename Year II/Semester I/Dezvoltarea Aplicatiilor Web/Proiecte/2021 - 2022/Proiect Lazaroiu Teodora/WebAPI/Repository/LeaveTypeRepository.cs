using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class LeaveTypeRepository : GenericRepository<LeaveType>, ILeaveTypeRepository
    {
        public LeaveTypeRepository(DataContext context) : base(context) { }
        public async Task<LeaveType?> GetLeaveTypeByName(string name)
        {
            if (string.IsNullOrEmpty(name))
            {
                return null;
            }

            return await _context.LeaveTypes
                .Where(a => a.LeaveName.ToLower() == name.ToLower())
                .FirstOrDefaultAsync();
        }
    }
}
