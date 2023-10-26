using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface ILeaveTypeRepository : IGenericRepository<LeaveType>
    {
        Task<LeaveType?> GetLeaveTypeByName (string name);
    }
}
