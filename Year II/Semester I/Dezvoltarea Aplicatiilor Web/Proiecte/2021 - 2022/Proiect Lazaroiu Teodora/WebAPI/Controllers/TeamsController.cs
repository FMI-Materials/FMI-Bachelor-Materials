using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TeamsController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public TeamsController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/Teams
        [HttpGet]
        public async Task<ActionResult<IEnumerable<TeamDTO>>> GetTeams()
        {
            var teams = (await _unitOfWork.Teams.GetAll()).Select(a => new TeamDTO(a)).ToList();
            return teams;
        }

        // GET: api/Teams/id
        [HttpGet("{id}")]
        public async Task<ActionResult<TeamDTO>> GetTeamByName(int id)
        {
            var team = await _unitOfWork.Teams.GetById(id);

            if (team == null)
            {
                return NotFound("Team with this id doesn't exist");
            }

            return new TeamDTO(team);
        }

        // PUT: api/Teams/id
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutTeam(int id, TeamDTO team)
        {
            var teamInDb = await _unitOfWork.Teams.GetById(id);

            if (teamInDb == null)
            {
                return NotFound("Team with this id doesn't exist");
            }

            teamInDb.TeamName = team.TeamName;
            teamInDb.TeamLeadId = team.TeamLeadId;
            teamInDb.LocationId = team.LocationId;

            await _unitOfWork.Teams.Update(teamInDb);
            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/Teams
        [HttpPost]
        [Authorize(Roles = "admin")]
        public async Task<ActionResult<TeamDTO>> PostTeam(TeamDTO team)
        {
            var teamToAdd = new Team(team);

            await _unitOfWork.Teams.Create(teamToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/Teams/name
        [HttpDelete("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteTeam(int id)
        {
            var teamInDb = await _unitOfWork.Teams.GetById(id);

            if (teamInDb == null)
            {
                return NotFound("Team with this id doesn't exist");
            }

            await _unitOfWork.Teams.Delete(teamInDb);
            _unitOfWork.Save();

            return Ok();
        }
    }
}
