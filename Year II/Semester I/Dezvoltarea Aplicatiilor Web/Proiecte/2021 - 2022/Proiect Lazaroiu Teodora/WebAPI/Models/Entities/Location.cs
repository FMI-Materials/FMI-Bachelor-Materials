using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using WebAPI.Models.DTOs;

namespace WebAPI.Models.Entities
{
    [Table("Location")]
    public class Location
    {
        [Key]
        public int Id { get; set; }
        public string City { get; set; } = string.Empty;
        public string PostalCode { get; set; } = string.Empty;
        public string Street { get; set; } = string.Empty;
        public int Number { get; set; } = 0;
        public string Country { get; set; } = string.Empty;
        public IEnumerable<Team> Teams { get; set; } = new HashSet<Team>();
        public Location()
        {

        }
        public Location(LocationDTO location)
        {
            this.City = location.City;
            this.PostalCode = location.PostalCode;
            this.Street = location.Street;
            this.Number = location.Number;
            this.Country = location.Country;
        }

    }
}
