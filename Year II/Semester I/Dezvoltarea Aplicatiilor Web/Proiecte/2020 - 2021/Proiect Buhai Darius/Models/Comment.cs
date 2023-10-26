using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations;

namespace ProiectDAW.Models
{
    public class Comment
    {
        [Key]
        public int CommentId { get; set; }
        [Required]
        public string Content { get; set; }
        public DateTime Date { get; set; }
        public int ProductId { get; set; }
        public int Rating { get; set; }
        public virtual Product Product { get; set; }
        public string UserId { get; internal set; }
    }
}