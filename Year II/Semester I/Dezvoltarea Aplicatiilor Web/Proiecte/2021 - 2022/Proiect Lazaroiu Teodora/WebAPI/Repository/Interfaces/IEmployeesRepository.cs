using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;

namespace WebAPI.Repository.Interfaces
{
    public interface IEmployeesRepository : IGenericRepository<Employee>
    {
        Task<Employee?> GetEmployeeByFullName(string firstName, string lastName);
    }
}
