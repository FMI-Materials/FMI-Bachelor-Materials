using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace BuhaiDarius34.Models
{
    public class Meeting
    {
        [Key]
        public int Id { get; set; }
        [Required(ErrorMessage ="Titlul conferintei este obligatoriu")]
        [StringLength(100, ErrorMessage = "Titlul conferintei nu poate avea mai mult de 100 de caractere")]
        public string TitluMeet { get; set; }
        [Required(ErrorMessage ="Continutul conferintei este obligatoriu")]
        [StringLength(150, ErrorMessage = "Descrierea nu poate avea mai mult de 150 caractere")]
        [DataType(DataType.MultilineText)]
        public string Content { get; set; }
        [Required(ErrorMessage = "Data este obligatorie")]
        public DateTime DataMeet { get; set; }
        [Required(ErrorMessage ="Subiectul este obligatoriu")]
        public int SubjectId { get; set; }
        public virtual Subject Subject { get; set; }
        public IEnumerable<SelectListItem> Subjects { get; internal set; }
    }
}