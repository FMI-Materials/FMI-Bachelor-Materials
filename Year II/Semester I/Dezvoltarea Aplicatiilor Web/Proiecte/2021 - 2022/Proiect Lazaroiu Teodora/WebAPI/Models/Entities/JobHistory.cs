using WebAPI.Models.DTOs;

namespace WebAPI.Models.Entities
{
    public class JobHistory
    {
        public int EmployeeId { get; set; }
        public Employee? Employee { get; set; }
        public int JobId { get; set; }
        public Job? Job { get; set; }

        public JobHistory()
        {

        }

        public JobHistory(JobHistoryDTO jobHistory)
        {
            this.EmployeeId = jobHistory.EmployeeId;
            this.JobId = jobHistory.JobId;
        }
    }
}
