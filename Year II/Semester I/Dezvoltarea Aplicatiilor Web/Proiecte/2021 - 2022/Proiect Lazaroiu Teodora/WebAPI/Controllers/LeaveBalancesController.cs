using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Controllers
{
    [Route("api/[controller]")]
    [Authorize]
    [ApiController]
    public class LeaveBalancesController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public LeaveBalancesController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/LeaveBalances
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LeaveBalanceDTO>>> GetLeaveBalances()
        {
            var leaveBalances = (await _unitOfWork.LeaveBalances.GetAll()).Select(a => new LeaveBalanceDTO(a)).ToList();
            return leaveBalances;
        }

        // GET: api/LeaveBalances/id
        [HttpGet("{id}")]
        public async Task<ActionResult<LeaveBalanceDTO>> GetLeaveBalance(int id)
        {
            var leaveBalance = await _unitOfWork.LeaveBalances.GetById(id);

            if (leaveBalance == null)
            {
                return NotFound("Leave Balance with this id doesn't exist");
            }

            return new LeaveBalanceDTO(leaveBalance);
        }

        // PUT: api/LeaveBalances/id
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutLeaveBalance(int id, LeaveBalanceDTO leaveBalance)
        {
            var leaveBalanceInDb = await _unitOfWork.LeaveBalances.GetById(id);

            if (leaveBalanceInDb == null)
            {
                return NotFound("Leave Balance with this id doesn't exist");
            }

            leaveBalanceInDb.DaysTotal = leaveBalance.DaysTotal;
            leaveBalanceInDb.DaysTaken = leaveBalance.DaysTaken;
            leaveBalanceInDb.DaysRemaining = leaveBalance.DaysRemaining;

            await _unitOfWork.LeaveBalances.Update(leaveBalanceInDb);
            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/LeaveBalances
        [HttpPost]
        [Authorize(Roles = "admin")]
        public async Task<ActionResult<LeaveBalanceDTO>> PostLeaveBalance(LeaveBalanceDTO leaveBalance)
        {

            var leaveBalanceToAdd = new LeaveBalance(leaveBalance);

            await _unitOfWork.LeaveBalances.Create(leaveBalanceToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/LeaveBalances/id
        [HttpDelete("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteLeaveBalance(int id)
        {
            var leaveBalanceInDb = await _unitOfWork.LeaveBalances.GetById(id);

            if (leaveBalanceInDb == null)
            {
                return NotFound("Leave Balance with this id doesn't exist");
            }

            await _unitOfWork.LeaveBalances.Delete(leaveBalanceInDb);
            _unitOfWork.Save();

            return Ok();
        }
    }
}
