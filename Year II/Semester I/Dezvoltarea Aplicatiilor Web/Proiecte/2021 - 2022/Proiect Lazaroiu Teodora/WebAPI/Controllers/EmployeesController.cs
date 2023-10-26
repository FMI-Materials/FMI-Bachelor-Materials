using Microsoft.AspNetCore.Mvc;
using WebAPI.Models.Entities;
using WebAPI.Models.DTOs;
using WebAPI.Repository.Interfaces;
using Microsoft.AspNetCore.Authorization;

namespace WebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class EmployeesController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public EmployeesController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/Employees
        [HttpGet]
        public async Task<ActionResult<IEnumerable<EmployeeDTO>>> GetEmployees()
        {
            var employees = (await _unitOfWork.Employees
                .GetAll()).Select(a => new EmployeeDTO(a)).ToList();
            return employees;
        }

        // GET: api/Employees/id
        [HttpGet("{id}")]
        public async Task<ActionResult<EmployeeDTO>> GetEmployeeById(int id)
        {
            var employee = await _unitOfWork.Employees.GetById(id);

            if (employee == null)
            {
                return NotFound("Employee with this id doesn't exist");
            }

            return new EmployeeDTO(employee);
        }

        // PUT: api/Employees/5
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutEmployee(int id, EmployeeDTO employee)
        {
            var employeeInDb = await _unitOfWork.Employees.GetById(id);

            if (employeeInDb == null)
            {
                return BadRequest("Employee with this id doesn't exist");
            }

            employeeInDb.FirstName = employee.FirstName;
            employeeInDb.LastName = employee.LastName;
            employeeInDb.EmailAddress = employee.EmailAddress;
            employeeInDb.TeamId = employee.TeamId;
            employeeInDb.CurrentJobId = employee.CurrentJobId;
            employeeInDb.Salary = employee.Salary;

            await _unitOfWork.Employees.Update(employeeInDb);
            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/Employees
        [HttpPost]
        public async Task<ActionResult<EmployeeDTO>> PostEmployee(EmployeeDTO employee)
        {

            var employeeToAdd = new Employee(employee);

            await _unitOfWork.Employees.Create(employeeToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/Employees/id
        [HttpDelete("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteEmployee(int id)
        {
            var employeeInDb = await _unitOfWork.Employees.GetById(id);

            if (employeeInDb == null)
            {
                return NotFound("Employee with this id doesn't exist");
            }

            await _unitOfWork.Employees.Delete(employeeInDb);
            _unitOfWork.Save();

            return Ok();
        }
    }
}
