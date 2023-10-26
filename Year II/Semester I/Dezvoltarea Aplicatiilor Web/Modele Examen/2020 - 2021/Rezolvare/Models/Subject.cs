using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;

namespace BuhaiDarius34.Models
{
    public class Subject
    {
        [Key]
        public int Id { get; set; }
        [Required(ErrorMessage = "Numele subiectului este obligatoriu")]
        public string NumeSub { get; set; }
        public virtual ICollection<Meeting> Meetings { get; set; }
    }
}