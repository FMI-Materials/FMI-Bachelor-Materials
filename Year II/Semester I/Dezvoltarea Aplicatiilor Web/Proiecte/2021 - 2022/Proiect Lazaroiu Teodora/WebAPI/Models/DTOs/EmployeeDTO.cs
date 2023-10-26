using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class EmployeeDTO
    {
        public int EmployeeId { get; set; }
        public string FirstName { get; set; } = string.Empty;
        public string LastName { get; set; } = string.Empty;
        public string EmailAddress { get; set; } = string.Empty;
        public int? TeamId { get; set; }
        public int CurrentJobId { get; set; }
        public int Salary { get; set; }

        public EmployeeDTO(Employee employee)
        {
            EmployeeId = employee.EmployeeId;
            FirstName = employee.FirstName;
            LastName = employee.LastName;
            EmailAddress = employee.EmailAddress;
            TeamId = employee.TeamId;
            CurrentJobId = employee.CurrentJobId;
            Salary = employee.Salary;
        }

        public EmployeeDTO()
        {

        }
    }
}
