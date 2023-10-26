using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;
using WebAPI.Services;

namespace WebAPI.Repository
{
    public class UserRepository : GenericRepository<User>, IUserRepository
    {
        public UserRepository(DataContext context) : base(context) { }
        public async Task<User?> GetUserByEmail(string email)
        {
             return await _context.Users.Where(a => a.EmailAddress == email).FirstOrDefaultAsync();
        }
        public async Task<User?> GetUserByEmailAndHashedPassword(string email, string hash)
        {
            return await _context.Users.Where(a => a.EmailAddress == email &&
            a.HashedPassword == hash).FirstOrDefaultAsync();
        }
    }
}
