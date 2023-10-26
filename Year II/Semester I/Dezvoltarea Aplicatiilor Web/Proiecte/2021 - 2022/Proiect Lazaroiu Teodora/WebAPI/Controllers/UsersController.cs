using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WebAPI.Models;
using WebAPI.Models.DTOs;
using WebAPI.Models.Entities;
using WebAPI.Repository.Interfaces;
using WebAPI.Services;

namespace API.Controllers
{
	[Route("api/[controller]")]
	[ApiController]
	public class UsersController : ControllerBase
	{
		private readonly IUnitOfWork _unitOfWork;
		private readonly IAuthenticationService _service;

		public UsersController(IUnitOfWork unitOfWork, IAuthenticationService service)
		{
			_unitOfWork = unitOfWork;
			_service = service;
		}

		// GET: api/User/email
		[HttpGet("{email}")]
		public async Task<ActionResult<UserDTO>> GetUser(string email)
		{
			var user = await _unitOfWork.Users.GetUserByEmail(email);

			if (user == null)
			{
				return NotFound("User with this email doesn't exist");
			}

			return new UserDTO(user);
		}

		[HttpPost]
		[AllowAnonymous]
		[Route("Login")]
		public async Task<IActionResult> Authenticate(UserLoginDTO user)
		{
			Token? token;
			try
			{
				token = await _service.Authenticate(user);
			}
			catch (Exception e)
			{
				return BadRequest(e.Message);
			}

			if (token == null)
			{
				return Unauthorized();
			}

			return Ok(token);
		}

		[HttpPost]
		[AllowAnonymous]
		[Route("Register")]
		public async Task<IActionResult> PostUser(UserRegisterDTO user)
		{
			try
			{
				var newUser = await _service.Register(user);
				await _unitOfWork.Users.Create(newUser);
				_unitOfWork.Save();
			}
			catch (Exception e)
			{
				return BadRequest(e.Message);
			}

			return Ok();
		}

		// DELETE: api/Users/id
		[HttpDelete("{id}")]
		[Authorize(Roles = "admin")]
		public async Task<IActionResult> DeleteUser(int id)
		{
			var userInDb = await _unitOfWork.Users.GetById(id);

			if (userInDb == null)
			{
				return NotFound("User with this id doesn't exist");
			}

			await _unitOfWork.Users.Delete(userInDb);
			_unitOfWork.Save();

			return Ok();
		}
	}
}



