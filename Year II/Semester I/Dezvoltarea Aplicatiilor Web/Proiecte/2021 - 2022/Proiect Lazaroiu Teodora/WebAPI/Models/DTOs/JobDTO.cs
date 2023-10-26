using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class JobDTO
    {
        public int JobId { get; set; }
        public string JobTitle { get; set; } = string.Empty;
        public string JobDescription { get; set; } = string.Empty;
        public JobDTO(Job job)
        {
            this.JobId = job.JobId;
            this.JobTitle = job.JobTitle;
            this.JobDescription = job.JobDescription;
        }

        public JobDTO()
        {

        }
    }
}
