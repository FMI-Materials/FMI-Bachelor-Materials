using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface ILeaveHistoryRepository : IGenericRepository<LeaveHistory>
    {
        int GetNumberOfDays(LeaveHistory leaveHistory);
    }
}
