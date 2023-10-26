using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class UserDTO
    {
        public int EmployeeId { get; set; }
        public string EmailAddress { get; set; } = string.Empty;
        public RoleType Role { get; set; }

        public UserDTO()
        {

        }

        public UserDTO(User user)
        {
            this.EmployeeId = user.EmployeeId;
            this.EmailAddress = user.EmailAddress;
            this.Role = user.Role;
        }
    }
}
