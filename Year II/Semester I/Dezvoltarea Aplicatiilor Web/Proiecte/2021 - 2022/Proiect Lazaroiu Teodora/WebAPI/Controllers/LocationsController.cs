using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;

namespace WebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LocationsController : ControllerBase
    {
        private readonly IUnitOfWork _unitOfWork;

        public LocationsController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        // GET: api/Locations
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LocationDTO>>> GetLocations()
        {
            var locations = (await _unitOfWork.Locations
                .GetAll()).Select(a => new LocationDTO(a)).ToList();
            return locations;
        }

        // GET: api/Locations/id
        [HttpGet("{id}")]
        public async Task<ActionResult<LocationDTO>> GetLocation(int id)
        {
            var location = await _unitOfWork.Locations.GetById(id);

            if (location == null)
            {
                return NotFound("Location with this id doesn't exist");
            }

            return new LocationDTO(location);
        }

        // PUT: api/Locations/id
        [HttpPut("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> PutLocation(int id, LocationDTO location)
        {
            var locationInDb = await _unitOfWork.Locations.GetById(id);

            if (locationInDb == null)
            {
                return NotFound("Location with this id doesn't exist");
            }

            locationInDb.City = location.City;
            locationInDb.Country = location.Country;
            locationInDb.PostalCode = location.PostalCode;
            locationInDb.Street = location.Street;
            locationInDb.Number = location.Number;

            await _unitOfWork.Locations.Update(locationInDb);
            _unitOfWork.Save();

            return Ok();
        }

        // POST: api/Locations
        [HttpPost]
        [Authorize(Roles = "admin")]
        public async Task<ActionResult<LocationDTO>> PostLocation(LocationDTO location)
        {
            var locationToAdd = new Location(location);

            await _unitOfWork.Locations.Create(locationToAdd);
            _unitOfWork.Save();

            return Ok();
        }

        // DELETE: api/Locations/id
        [HttpDelete("{id}")]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteLocation(int id)
        {
            var locationInDb = await _unitOfWork.Locations.GetById(id);

            if (locationInDb == null)
            {
                return NotFound("Location with this id doesn't exist");
            }

            await _unitOfWork.Locations.Delete(locationInDb);
            _unitOfWork.Save();

            return Ok();
        }
    }
}
