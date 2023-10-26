using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class LeaveTypeDTO
    {
        public int Id { get; set; }
        public string LeaveName { get; set; } = string.Empty;
        public int NumberOfDays { get; set; }
        public string Description { get; set; } = string.Empty;

        public LeaveTypeDTO(LeaveType leaveType)
        {
            this.Id = leaveType.Id;
            this.LeaveName = leaveType.LeaveName;
            this.NumberOfDays = leaveType.NumberOfDays;
            this.Description = leaveType.Description;
        }

        public LeaveTypeDTO()
        {

        }
    }
}
