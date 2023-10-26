using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class UserRegisterDTO
    {
        public int EmployeeId { get; set; }
        public string EmailAddress { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty;
        public string Role { get; set; }

        public UserRegisterDTO()
        {

        }
    }
}
