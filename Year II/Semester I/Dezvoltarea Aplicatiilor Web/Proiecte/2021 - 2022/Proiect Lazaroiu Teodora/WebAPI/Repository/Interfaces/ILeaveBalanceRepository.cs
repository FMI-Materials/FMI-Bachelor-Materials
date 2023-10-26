using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface ILeaveBalanceRepository : IGenericRepository<LeaveBalance>
    {
        LeaveBalance ReduceBalance(LeaveBalance balance, int numberOfDays);
        LeaveBalance IncreaseBalance(LeaveBalance balance, int numberOfDays);
        LeaveBalance ResetBalance(LeaveBalance balance);
    }
}
