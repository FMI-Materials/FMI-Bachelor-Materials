using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class LeaveHistoryRepository : GenericRepository<LeaveHistory>, ILeaveHistoryRepository
    {
        public LeaveHistoryRepository(DataContext context) : base(context) { }
        public int GetNumberOfDays(LeaveHistory leaveHistory)
        {
            return (int)((leaveHistory.EndDate - leaveHistory.StartDate).TotalDays);
        }
    }
}
