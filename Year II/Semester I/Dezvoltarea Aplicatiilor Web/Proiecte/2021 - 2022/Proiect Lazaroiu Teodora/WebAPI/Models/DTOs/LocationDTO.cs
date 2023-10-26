using WebAPI.Models.Entities;

namespace WebAPI.Models.DTOs
{
    public class LocationDTO
    {
        public int Id { get; set; }
        public string City { get; set; } = string.Empty;
        public string PostalCode { get; set; } = string.Empty;
        public string Street { get; set; } = string.Empty;
        public int Number { get; set; }
        public string Country { get; set; } = string.Empty;

        public LocationDTO(Location location)
        {
            this.Id = location.Id;
            this.City = location.City;
            this.PostalCode = location.PostalCode;
            this.Street = location.Street;
            this.Number = location.Number;
            this.Country = location.Country;
        }

        public LocationDTO()
        {

        }
    }
}
