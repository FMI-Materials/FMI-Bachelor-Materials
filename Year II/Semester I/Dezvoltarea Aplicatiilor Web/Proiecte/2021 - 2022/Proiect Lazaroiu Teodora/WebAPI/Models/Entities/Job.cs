using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using WebAPI.Models.DTOs;

namespace WebAPI.Models.Entities
{
    [Table("Job")]
    public class Job
    {
        [Key]
        public int JobId { get; set; }
        public string JobTitle { get; set; } = string.Empty;
        public string JobDescription { get; set; } = string.Empty;
        public IEnumerable<JobHistory> JobHistories { get; set; } = new HashSet<JobHistory>();
        public Job()
        {

        }
        public Job(JobDTO job)
        {
            this.JobTitle = job.JobTitle;
            this.JobDescription = job.JobDescription;
        }
    }
}
