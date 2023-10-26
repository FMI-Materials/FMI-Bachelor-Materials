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
    public class LeaveTypesController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public LeaveTypesController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/LeaveTypes
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LeaveTypeDTO>>> GetLeaveTypes()
        {
            var leaveTypes = (await _unitOfWork.LeaveTypes
                .GetAll()).Select(a => new LeaveTypeDTO(a)).ToList();
            return leaveTypes;
        }

        // GET: api/LeaveTypes/id
        [HttpGet("{id}")]
        public async Task<ActionResult<LeaveTypeDTO>> GetLeaveType(int id)
        {
            var leaveType = await _unitOfWork.LeaveTypes.GetById(id);

            if (leaveType == null)
            {
                return NotFound("Leave Type with this id doesn't exist");
            }

            return new LeaveTypeDTO(leaveType);
        }

        // PUT: api/LeaveTypes/id
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutLeaveType(int id, LeaveTypeDTO leaveType)
        {
            var leaveTypeInDb = await _unitOfWork.LeaveTypes.GetById(id);

            if (leaveTypeInDb == null)
            {
                return NotFound("Leave Type with this id doesn't exist");
            }

            leaveTypeInDb.LeaveName = leaveType.LeaveName;
            leaveTypeInDb.NumberOfDays = leaveType.NumberOfDays;
            leaveTypeInDb.Description = leaveType.Description;

            await _unitOfWork.LeaveTypes.Update(leaveTypeInDb);
            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/LeaveTypes
        [HttpPost]
        [Authorize(Roles = "admin")]
        public async Task<ActionResult<LeaveTypeDTO>> PostLeaveType(LeaveTypeDTO leaveType)
        {
            var leaveTypeToAdd = new LeaveType(leaveType);

            await _unitOfWork.LeaveTypes.Create(leaveTypeToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/LeaveTypes/id
        [HttpDelete("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteLeaveType(int id)
        {
            var leaveTypeInDb = await _unitOfWork.LeaveTypes.GetById(id);

            if (leaveTypeInDb == null)
            {
                return NotFound("Leave Type with this id doesn't exist");
            }

            await _unitOfWork.LeaveTypes.Delete(leaveTypeInDb);
            _unitOfWork.Save();

            return Ok();
        }
    }
}
