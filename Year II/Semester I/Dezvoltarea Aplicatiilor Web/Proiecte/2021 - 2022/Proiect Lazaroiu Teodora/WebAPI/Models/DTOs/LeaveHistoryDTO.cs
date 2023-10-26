using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class LeaveHistoryDTO
    {
        public int Id { get; set; }
        public DateTime StartDate { get; set; }
        public DateTime EndDate { get; set; }
        public int? LeaveTypeId { get; set; }
        public int EmployeeId { get; set; }
        public string Status { get; set; } = string.Empty;

        public LeaveHistoryDTO(LeaveHistory leaveHistory)
        {
            this.Id = leaveHistory.Id;
            this.StartDate = leaveHistory.StartDate;
            this.EndDate = leaveHistory.EndDate;
            this.LeaveTypeId = leaveHistory.LeaveTypeId;
            this.EmployeeId = leaveHistory.EmployeeId;
            this.Status = leaveHistory.Status;
        }

        public LeaveHistoryDTO()
        {

        }
    }
}
