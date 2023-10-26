using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebAPI.Models.Entities
{
    [Table("User")]
    public class User
    {
        [Key]
        public int UserId { get; set; }
        public int EmployeeId { get; set; }
        public Employee? Employee { get; set; }
        public string EmailAddress { get; set; } = string.Empty;
        public string HashedPassword { get; set; } = string.Empty;
        public string PasswordSalt { get; set; } = string.Empty;
        public RoleType Role { get; set; } = RoleType.user;
        public User()
        {

        }
        public User(int employeeId, string emailAddress, string hashedPassword, string salt, RoleType role)
        {
            EmployeeId = employeeId;
            EmailAddress = emailAddress;
            HashedPassword = hashedPassword;
            PasswordSalt = salt;
            Role = role;
        }
    }
}
