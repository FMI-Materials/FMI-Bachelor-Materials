using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebAPI.Models.Entities
{
    [Table("LeaveHistory")]
    public class LeaveHistory
    {
        [Key]
        public int Id { get; set; }
        public DateTime StartDate { get; set; }
        public DateTime EndDate { get; set; }
        public int? LeaveTypeId { get; set; }
        public LeaveType? LeaveType { get; set; }
        public int EmployeeId { get; set; }
        public Employee? Employee { get; set; }
        public string Status { get; set; } = string.Empty;
    }
}
