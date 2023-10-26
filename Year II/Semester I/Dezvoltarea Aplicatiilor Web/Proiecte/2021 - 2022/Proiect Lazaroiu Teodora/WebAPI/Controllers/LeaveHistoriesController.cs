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
    public class LeaveHistoriesController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public LeaveHistoriesController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/LeaveHistories
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LeaveHistoryDTO>>> GetLeaveHistories()
        {
            var leaveHistories = (await _unitOfWork.LeaveHistories
                .GetAll()).Select(a => new LeaveHistoryDTO(a)).ToList();
            return leaveHistories;
        }

        // GET: api/LeaveHistories/id
        [HttpGet("{id}")]
        public async Task<ActionResult<LeaveHistoryDTO>> GetLeaveHistory(int id)
        {
            var leaveHistory = await _unitOfWork.LeaveHistories.GetById(id);

            if (leaveHistory == null)
            {
                return NotFound("Leave History with this id doesn't exist");
            }

            return new LeaveHistoryDTO(leaveHistory);
        }

        // PUT: api/LeaveTypes/id
        // for HR to accept or decline the leave
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutLeaveHistory(int id, LeaveHistoryDTO leaveHistory)
        {
            var leaveHistoryInDb = await _unitOfWork.LeaveHistories.GetById(id);

            if (leaveHistoryInDb == null)
            {
                return NotFound("Leave History with this id doesn't exist");
            }

            leaveHistoryInDb.Status = leaveHistory.Status;
            await _unitOfWork.LeaveHistories.Update(leaveHistoryInDb);

            // updating employee's balance in status is ACCEPTED
            if (leaveHistory.Status.ToUpper() == "ACCEPTED")
            {
                int numberOfDays = _unitOfWork.LeaveHistories.GetNumberOfDays(leaveHistoryInDb);
                var balance = await _unitOfWork.LeaveBalances.GetById(leaveHistory.EmployeeId);

                if (balance == null)
                {
                    return BadRequest("Balance doesn't exist for this employee");
                }

                balance = _unitOfWork.LeaveBalances.ReduceBalance(balance, numberOfDays);
                await _unitOfWork.LeaveBalances.Update(balance);
            }

            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/LeaveHistories
        // for employees to request a leave
        [HttpPost]
        public async Task<ActionResult<LeaveHistoryDTO>> PostLeaveHistory(LeaveHistoryDTO leaveHistory)
        {
            var leaveHistoryToAdd = new LeaveHistory();
            leaveHistoryToAdd.StartDate = leaveHistory.StartDate;
            leaveHistoryToAdd.EndDate = leaveHistory.EndDate;
            leaveHistoryToAdd.LeaveTypeId = leaveHistory.LeaveTypeId;
            leaveHistoryToAdd.EmployeeId = leaveHistory.EmployeeId;
            leaveHistoryToAdd.Status = "PENDING";

            await _unitOfWork.LeaveHistories.Create(leaveHistoryToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/LeaveHistories/id
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteLeaveHistory(int id)
        {
            var leaveHistoryInDb = await _unitOfWork.LeaveHistories.GetById(id);

            if (leaveHistoryInDb == null)
            {
                return NotFound("Leave History with this id doesn't exist");
            }

            await _unitOfWork.LeaveHistories.Delete(leaveHistoryInDb);

            // updating employee's balance if it was already accepted
            if (leaveHistoryInDb.Status.ToUpper() == "ACCEPTED")
            {
                int numberOfDays = _unitOfWork.LeaveHistories.GetNumberOfDays(leaveHistoryInDb);
                var balance = await _unitOfWork.LeaveBalances.GetById(leaveHistoryInDb.EmployeeId);

                if (balance == null)
                {
                    return BadRequest("Balance doesn't exist for this employee");
                }

                balance = _unitOfWork.LeaveBalances.IncreaseBalance(balance, numberOfDays);
                await _unitOfWork.LeaveBalances.Update(balance);
            }

            _unitOfWork.Save();

            return Ok();
        }
    }
}
