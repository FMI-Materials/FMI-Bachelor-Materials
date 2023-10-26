using WebAPI.Data;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace WebAPI.Repository
{
    public class EmployeesRepository : GenericRepository<Employee>, IEmployeesRepository
    {
        public EmployeesRepository(DataContext context) : base(context) { }

        public async Task<Employee?> GetEmployeeByFullName(string firstName, string lastName)
        {
            if (firstName == null || lastName == null)
            {
                return null;
            }

            return await _context.Employees.Where(a => (a.FirstName).ToLower().Equals(firstName.ToLower())
            && (a.LastName).ToLower().Equals(lastName.ToLower())).FirstOrDefaultAsync();
        }
    }
}
