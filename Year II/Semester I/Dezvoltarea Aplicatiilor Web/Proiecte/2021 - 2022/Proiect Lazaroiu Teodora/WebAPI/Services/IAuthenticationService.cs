using WebAPI.Models;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;

namespace WebAPI.Services
{
    public interface IAuthenticationService
    {
        Task<Token?> Authenticate(UserLoginDTO? user);
        Task<User> Register(UserRegisterDTO user);
        string GenerateSalt();
        string HashPassword(string password, string salt);
    }
}