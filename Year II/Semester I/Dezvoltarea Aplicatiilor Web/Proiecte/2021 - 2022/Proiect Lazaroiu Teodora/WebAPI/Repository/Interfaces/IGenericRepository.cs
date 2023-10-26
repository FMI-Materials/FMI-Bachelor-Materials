namespace WebAPI.Repository.Interfaces
{
    public interface IGenericRepository<T>
    {
        Task<List<T>> GetAll();

        Task<T?> GetById(int id);

        Task Create(T entity);

        Task Update(T entity);

        Task Delete(T entity);
    }
}
