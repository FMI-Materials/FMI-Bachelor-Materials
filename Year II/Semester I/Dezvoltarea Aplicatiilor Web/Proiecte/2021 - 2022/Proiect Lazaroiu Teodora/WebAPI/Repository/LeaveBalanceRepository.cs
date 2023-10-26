using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Repository
{
    public class LeaveBalanceRepository : GenericRepository<LeaveBalance>, ILeaveBalanceRepository
    {
        public LeaveBalanceRepository(DataContext context) : base(context) { }
        public LeaveBalance ReduceBalance(LeaveBalance balance, int numberOfDays)
        {
            balance.DaysRemaining -= numberOfDays;
            balance.DaysTaken += numberOfDays;

            return balance;
        }

        public LeaveBalance IncreaseBalance(LeaveBalance balance, int numberOfDays)
        {
            balance.DaysRemaining += numberOfDays;
            balance.DaysTaken -= numberOfDays;

            return balance;
        }

        public LeaveBalance ResetBalance(LeaveBalance balance)
        {
            balance.DaysTotal = 20;
            balance.DaysRemaining = 20;
            balance.DaysTaken = 0;

            return balance;
        }
    }
}
