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
    public class JobHistoryController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public JobHistoryController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/JobHistories
        [HttpGet]
        public async Task<ActionResult<IEnumerable<JobHistoryDTO>>> GetJobHistories()
        {
            var jobHistories = (await _unitOfWork.JobHistories
                .GetAll()).Select(a => new JobHistoryDTO(a)).ToList();
            return jobHistories;
        }

        // GET: api/JobHistories/eid/jid
        [HttpGet("{eid}/{jid}")]
        public async Task<ActionResult<JobHistoryDTO>> GetJob(int eid, int jid)
        {
            var jobHistory = await _unitOfWork.JobHistories.GetByBothIds(eid, jid);

            if (jobHistory == null)
            {
                return NotFound("Job History with those ids doesn't exist");
            }

            return new JobHistoryDTO(jobHistory);
        }

        // PUT: api/JobHistories/id
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutJobHistory(int id, JobHistoryDTO job)
        {
            var jobHistoryInDb = await _unitOfWork.JobHistories.GetById(id);

            if (jobHistoryInDb == null)
            {
                return NotFound("Job with this id doesn't exist");
            }

            jobHistoryInDb.EmployeeId = job.EmployeeId;
            jobHistoryInDb.JobId = job.JobId;

            await _unitOfWork.JobHistories.Update(jobHistoryInDb);
            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/JobHistories
        [HttpPost]
        [Authorize(Roles = "admin")]
        public async Task<ActionResult<JobHistoryDTO>> PostJobHistory(JobHistoryDTO jobHistory)
        {
            var jobHistoryToAdd = new JobHistory(jobHistory);

            await _unitOfWork.JobHistories.Create(jobHistoryToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/JobHistories/eid/jid
        [HttpDelete("{eid}/{jid}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteJob(int eid, int jid)
        {
            var jobHistoryInDb = await _unitOfWork.JobHistories.GetByBothIds(eid, jid);

            if (jobHistoryInDb == null)
            {
                return NotFound("Job History with those ids doesn't exist");
            }

            await _unitOfWork.JobHistories.Delete(jobHistoryInDb);
            _unitOfWork.Save();

            return Ok();
        }
    }
}
