using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace BuhaiDarius34.Models
{
    public class AppContext : DbContext
    {
        public AppContext() : base("DBConnectionString") { }
        public DbSet<Subject> Subjects { get; set; }
        public DbSet<Meeting> Meetings { get; set; }
    }
}