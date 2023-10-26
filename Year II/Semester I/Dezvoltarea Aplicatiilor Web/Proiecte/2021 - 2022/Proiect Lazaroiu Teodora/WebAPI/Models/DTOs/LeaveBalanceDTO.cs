using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class LeaveBalanceDTO
    {
        public int Id { get; set; }
        public int EmployeeId { get; set; }
        public int DaysTotal { get; set; } = 20;
        public int DaysRemaining { get; set; } = 20;
        public int DaysTaken { get; set; } = 0;

        public LeaveBalanceDTO(LeaveBalance leaveBalance)
        {
            this.Id = leaveBalance.LeaveBalanceId;
            this.EmployeeId = leaveBalance.EmployeeId;
            this.DaysTotal = leaveBalance.DaysTotal;
            this.DaysRemaining = leaveBalance.DaysRemaining;
            this.DaysTaken = leaveBalance.DaysTaken;
        }

        public LeaveBalanceDTO()
        {

        }
    }
}
