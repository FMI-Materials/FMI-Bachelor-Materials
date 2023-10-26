using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class JobHistoryDTO
    {
        public int JobId { get; set; }
        public int EmployeeId { get; set; }

        public JobHistoryDTO(JobHistory jobHistory)
        {
            this.JobId = jobHistory.JobId;
            this.EmployeeId = jobHistory.EmployeeId;
        }

        public JobHistoryDTO()
        {

        }
    }
}
