namespace WebAPI.Repository.Interfaces
{
    public interface IUnitOfWork : IDisposable
    {
        IEmployeesRepository Employees { get; }
        ITeamRepository Teams { get; }
        ILocationRepository Locations { get; }
        ILeaveTypeRepository LeaveTypes { get; }
        IJobRepository Jobs { get; }
        IJobHistoryRepository JobHistories { get; }
        ILeaveHistoryRepository LeaveHistories { get; }
        ILeaveBalanceRepository LeaveBalances { get; }
        IUserRepository Users { get; }
        int Save();
    }
}
