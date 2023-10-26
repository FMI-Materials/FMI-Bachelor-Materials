using Microsoft.EntityFrameworkCore;
using WebAPI.Models.Entities;

namespace WebAPI.Data
{
    public class DataContext : DbContext
    {
        public DataContext() {  }

        public DataContext(DbContextOptions<DataContext> options) : base(options) { }
        public DbSet<Employee> Employees { get; set; } = null!;
        public DbSet<Job> Jobs { get; set; } = null!;
        public DbSet<JobHistory> JobHistories { get; set; } = null!;
        public DbSet<LeaveBalance> LeaveBalances { get; set; } = null!;
        public DbSet<LeaveHistory> LeaveHistories { get; set; } = null!;
        public DbSet<LeaveType> LeaveTypes { get; set; } = null!;
        public DbSet<Location> Locations { get; set; } = null!;
        public DbSet<Team> Teams { get; set; } = null!;
        public DbSet<User> Users { get; set; } = null!;

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // One to One Relationships

            modelBuilder.Entity<Employee>()
                .HasOne(a => a.User)
                .WithOne(b => b.Employee)
                .HasForeignKey<User>("EmployeeId");

            modelBuilder.Entity<Employee>()
                .HasOne(a => a.LeaveBalance)
                .WithOne(b => b.Employee)
                .HasForeignKey<LeaveBalance>("EmployeeId");


            // One to Many Relationships

            modelBuilder.Entity<Employee>()
                .HasOne(a => a.Team)
                .WithMany(b => b.Employees)
                .HasForeignKey(c => c.TeamId)
                .OnDelete(DeleteBehavior.SetNull);

            modelBuilder.Entity<Location>()
                .HasMany(a => a.Teams)
                .WithOne(b => b.Location)
                .HasForeignKey(c => c.LocationId)
                .OnDelete(DeleteBehavior.SetNull);

            modelBuilder.Entity<Employee>()
                .HasMany(a => a.LeaveHistories)
                .WithOne(b => b.Employee)
                .HasForeignKey(c => c.EmployeeId)
                .OnDelete(DeleteBehavior.NoAction);

            modelBuilder.Entity<LeaveType>()
                .HasMany(a => a.LeaveHistories)
                .WithOne(b => b.LeaveType)
                .HasForeignKey(c => c.LeaveTypeId)
                .OnDelete(DeleteBehavior.NoAction);

            // Many to Many Relationship

            modelBuilder.Entity<JobHistory>()
                .HasKey(a => new { a.EmployeeId, a.JobId });

            modelBuilder.Entity<JobHistory>()
                .HasOne(a => a.Employee)
                .WithMany(b => b.JobHistories)
                .HasForeignKey(c => c.EmployeeId);

            modelBuilder.Entity<JobHistory>()
                .HasOne(a => a.Job)
                .WithMany(c => c.JobHistories)
                .HasForeignKey(c => c.JobId);
        }

    }
}
