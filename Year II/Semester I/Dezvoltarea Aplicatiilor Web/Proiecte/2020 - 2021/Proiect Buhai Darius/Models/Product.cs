using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;
using System.ComponentModel.DataAnnotations.Schema;

namespace ProiectDAW.Models
{
    public class Product
    {
        [Key]
        public int ProductId { get; set; }
        public string UserId { get; set; }
        public virtual ApplicationUser User { get; set; }
        [Required(ErrorMessage = "Titlul este obligatoriu")]
        [StringLength(100, ErrorMessage = "Titlul nu poate avea mai mult de 100 de caractere")]
        public string Title { get; set; }
        [Required(ErrorMessage = "Descrierea produsului este obligatorie")]
        [DataType(DataType.MultilineText)]
        public string Description { get; set; }
        public string Image { get; set; }
        [Required(ErrorMessage = "Pretul produsului este obligatoriu")]
        public int Price { get; set; }
        [Required]
        public int FinalRating { get; set; }
        [Required(ErrorMessage = "Categoria este obligatorie")]
        public int CategoryId { get; set; }
        public virtual Category Category { get; set; }
        public IEnumerable<SelectListItem> AllCategories { get; internal set; }
        public int Status { get; set; }
        public virtual ICollection<Comment> Comments { get; set; }
        public bool Approved { get; set; }
        [NotMapped]
        public HttpPostedFileBase ImageFile { get; set; }
    }
}