using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using WebAPI.Models.DTOs;

namespace WebAPI.Models.Entities
{
    [Table("LeaveBalance")]
    public class LeaveBalance
    {
        [Key]
        public int LeaveBalanceId { get; set; }
        public int EmployeeId { get; set; }
        public Employee? Employee { get; set; }
        public int DaysTotal { get; set; } = 20;
        public int DaysRemaining { get; set; } = 20;
        public int DaysTaken { get; set; } = 0;

        public LeaveBalance()
        {

        }

        public LeaveBalance(LeaveBalanceDTO leaveBalance)
        {
            this.EmployeeId = leaveBalance.EmployeeId;
            this.DaysTotal = leaveBalance.DaysTotal;
            this.DaysRemaining = leaveBalance.DaysRemaining;
            this.DaysTaken = leaveBalance.DaysTaken;
        }
    }
}
