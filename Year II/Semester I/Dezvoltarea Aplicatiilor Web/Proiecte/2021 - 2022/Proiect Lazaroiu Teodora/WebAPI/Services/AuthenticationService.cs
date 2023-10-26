using Microsoft.AspNetCore.Cryptography.KeyDerivation;
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Security.Cryptography;
using System.Text;
using WebAPI.Models;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Services
{
    public class AuthenticationService : IAuthenticationService
    {
        private readonly IUnitOfWork _unitOfWork;
        private readonly IConfiguration _configuration;
        public AuthenticationService(IUnitOfWork unitOfWork, IConfiguration configuration)
        {
            _unitOfWork = unitOfWork;
            _configuration = configuration;
        }
        public async Task<Token?> Authenticate(UserLoginDTO? user)
        {
            if (user == null || user.EmailAddress == null || user.Password == null
                || user.EmailAddress == "" || user.Password == "")
            {
                throw new Exception("Must enter a email and password");
            }

            var userInDb = await _unitOfWork.Users.GetUserByEmail(user.EmailAddress);
            if (userInDb == null)
            {
                throw new Exception("User doesn't exist");
            }

            string salt = userInDb.PasswordSalt;
            string hashedPassword;
            if (salt != null)
            {
                hashedPassword = HashPassword(user.Password, salt);
            }
            else return null;

            userInDb = await _unitOfWork.Users.GetUserByEmailAndHashedPassword(user.EmailAddress, hashedPassword);

            if (userInDb == null)
            {
                throw new Exception("Incorrect password");
            }

            var tokenHandler = new JwtSecurityTokenHandler();
            var tokenKey = Encoding.UTF8.GetBytes(_configuration["JWT:Key"]);
            var tokenDescriptor = new SecurityTokenDescriptor
            {
                Subject = new ClaimsIdentity(new Claim[]
                {
                    new Claim(ClaimTypes.Email, userInDb.EmailAddress),
                    new Claim(ClaimTypes.Role, userInDb.Role.ToString())
                }),
                Expires = DateTime.UtcNow.AddMinutes(20),
                SigningCredentials = new SigningCredentials(new SymmetricSecurityKey(tokenKey),
                SecurityAlgorithms.HmacSha256Signature),
                Issuer = _configuration["JWT:Issuer"],
                Audience = _configuration["JWT:Audience"]
            };
            var token = tokenHandler.CreateToken(tokenDescriptor);
            return new Token { TokenString = tokenHandler.WriteToken(token) };
        }

        public async Task<User> Register(UserRegisterDTO user)
        {
            if (user == null || user.EmailAddress == "" || user.Password == ""
                || user.EmailAddress == null || user.Password == null)
            {
                throw new Exception("Must enter an email and password");
            }

            if (user.Role.ToLower() != "admin" && user.Role.ToLower() != "user")
            {
                throw new Exception("Role must be admin or user");
            }

            var userInDb = await _unitOfWork.Users.GetUserByEmail(user.EmailAddress);

            if (userInDb != null)
            {
                throw new Exception("User with this email already exists");
            }

            int employee = user.EmployeeId;
            string email = user.EmailAddress;
            string salt = GenerateSalt();
            string hashedPassword = HashPassword(user.Password, salt);
            RoleType role = (RoleType)Enum.Parse(typeof(RoleType), user.Role.ToLower());

            User newUser = new(employee, email, hashedPassword, salt, role);
            return newUser;
        }

            public string HashPassword(string password, string salt)
        {
            byte[] saltByte = Convert.FromBase64String(salt);

            string hashed = Convert.ToBase64String(KeyDerivation.Pbkdf2(
                password: password,
                salt: saltByte,
                prf: KeyDerivationPrf.HMACSHA256,
                iterationCount: 100000,
                numBytesRequested: 32));

            return hashed;
        }
        public string GenerateSalt()
        {
            byte[] salt = new byte[16];
            using (var rng = RandomNumberGenerator.Create())
            {
                rng.GetBytes(salt);
            }

            return Convert.ToBase64String(salt);
        }



    }
}
