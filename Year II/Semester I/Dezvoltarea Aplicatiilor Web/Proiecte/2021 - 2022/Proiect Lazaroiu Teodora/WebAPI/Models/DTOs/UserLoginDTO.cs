using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class UserLoginDTO
    {
        public string EmailAddress { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty;

        public UserLoginDTO()
        {

        }
    }
}
