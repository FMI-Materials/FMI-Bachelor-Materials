using Microsoft.AspNet.Identity;
using ProiectDAW.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ProiectDAW.Controllers
{
    public class ProductsController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();
        // GET: Products
        public ActionResult Index()
        {
            var search = Request.Params["search"];
            var sort = Request.Params["sort"];
            if (search == null)
                search = "";
            if (sort == null)
                sort = "";
            var products = db.Products.Include("Category").Include("User").Where(product => product.Title.Contains(search)).ToList();
            CalculateProductsFinalRatings(products);
            if (sort == "price-asc")
                products = products.OrderBy(product => product.Price).ToList();
            if (sort == "price-desc")
                products = products.OrderByDescending(product => product.Price).ToList();
            if (sort == "rating-asc")
                products = products.OrderBy(product => product.FinalRating).ToList();
            if (sort == "rating-desc")
                products = products.OrderByDescending(product => product.FinalRating).ToList();
            ViewBag.Products = products;
            if (TempData.ContainsKey("message"))
                ViewBag.Message = TempData["message"];
            ViewBag.UserId = User.Identity.GetUserId();
            ViewBag.Search = search;
            ViewBag.Sort = sort;
            return View();
        }
        private void CalculateProductsFinalRatings(List<Product> products)
        {
            foreach (Product prod in products)
                CalculateProductFinalRating(prod);
        }
        static public void CalculateProductFinalRating(Product product)
        {
            var NrComments = product.Comments.Count;
            foreach (Comment comm in product.Comments)
                product.FinalRating += comm.Rating;
            if (NrComments != 0)
                product.FinalRating = product.FinalRating / NrComments;
            else
                product.FinalRating = 0;
        }
        // Get: Product
        public ActionResult Show(int id)
        {
            var product = db.Products.Find(id);
            CalculateProductFinalRating(product);
            if (TempData.ContainsKey("message"))
                ViewBag.Message = TempData["message"];
            ViewBag.UserId = User.Identity.GetUserId();
            return View(product);
        }

        // Get: New
        [Authorize(Roles = "Editor,Admin")]
        public ActionResult New()
        {
            Product product = new Product();
            product.AllCategories = GetAllCategories();
            product.UserId = User.Identity.GetUserId();
            product.Approved = User.IsInRole("Admin");
            return View(product);
        }
        // Post: New
        [HttpPost]
        [Authorize(Roles = "Editor,Admin")]
        public ActionResult New(Product product)
        {
            product.AllCategories = GetAllCategories();
            product.UserId = User.Identity.GetUserId();
            product.Approved = User.IsInRole("Admin");

            try
            {
                if (ModelState.IsValid)
                {
                    UploadProductImage(product);

                    db.Products.Add(product);
                    db.SaveChanges();
                    TempData["message"] = "Produsul a fost adaugat!";
                    return RedirectToAction("Index");
                }
                return View(product);
            }
            catch (Exception e)
            {
                return View(product);
            }
        }
        [HttpDelete]
        [Authorize(Roles = "Editor,Admin")]
        public ActionResult Delete(int id)
        {
            try
            {
                Product product = db.Products.Find(id);
                if (product.UserId == User.Identity.GetUserId() || User.IsInRole("Admin"))
                {
                    db.Products.Remove(db.Products.Find(id));
                    db.SaveChanges();
                    TempData["message"] = "Produsul a fost sters!";
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Nu aveti dreptul sa stergeti un produs care nu va apartine!";
                    return RedirectToAction("Index");
                }
            }
            catch (Exception e)
            {
                return RedirectToAction("Index");
            }
        }
        // Get: Edit
        [Authorize(Roles = "Editor,Admin")]
        public ActionResult Edit(int id)
        {
            Product product = db.Products.Find(id);
            product.AllCategories = GetAllCategories();
            if (product.UserId == User.Identity.GetUserId() || User.IsInRole("Admin"))
                return View(product);
            TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui produs care nu va apartine!";
            return RedirectToAction("Index");
        }
        // Put: Edit
        [HttpPut]
        [Authorize(Roles = "Editor,Admin")]
        public ActionResult Edit(int id, Product requestProduct)
        {
            requestProduct.AllCategories = GetAllCategories();
            requestProduct.UserId = User.Identity.GetUserId();
            try
            {
                if (ModelState.IsValid)
                {
                    if(requestProduct.ImageFile != null)
                        UploadProductImage(requestProduct);

                    Product product = db.Products.Find(id);
                    if (product.Approved != requestProduct.Approved && !User.IsInRole("Admin"))
                        requestProduct.Approved = product.Approved;
                    if (product.UserId == User.Identity.GetUserId() || User.IsInRole("Admin"))
                    {
                        if (requestProduct.ImageFile != null)
                            product.Image = requestProduct.Image;
                        if (TryUpdateModel(product))
                        {
                            product = requestProduct;
                            db.SaveChanges();
                            TempData["message"] = "Produsul a fost modificat!";
                            return RedirectToAction("Index");
                        }
                    }
                    else
                    {
                        TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui produs care nu va apartine!";
                        return RedirectToAction("Index");
                    }

                }
                return View(requestProduct);

            }
            catch (Exception e)
            {
                return View(requestProduct);
            }
        }
        [Authorize(Roles = "Admin")]
        public ActionResult Approve()
        {
            var products = db.Products.Include("Category").Include("User");
            ViewBag.Products = products;
            if (TempData.ContainsKey("message"))
                ViewBag.Message = TempData["message"];
            return View();
        }
        [HttpPost]
        [Authorize(Roles = "Admin")]
        public ActionResult Approve(int id)
        {
            Product product = db.Products.Find(id);
            product.Approved = true;
            if (TryUpdateModel(product))
            {
                db.SaveChanges();
                TempData["message"] = "Produsul a fost aprobat!";
                return RedirectToAction("Index");
            }
            return View();
        }
        public IEnumerable<SelectListItem> GetAllCategories()
        {
            // generam o lista goala
            var selectList = new List<SelectListItem>();
            // extragem toate categoriile din baza de date
            var categories = from cat in db.Categories
                             select cat;
            // iteram prin categorii
            foreach (var category in categories)
            {
                // adaugam in lista elementele necesare pentru dropdown
                selectList.Add(new SelectListItem
                {
                    Value = category.CategoryId.ToString(),
                    Text = category.CategoryName.ToString()
                });
            }
            // returnam lista de categorii
            return selectList;
        }

        private void UploadProductImage(Product product)
        {
            string fileName = Path.GetFileNameWithoutExtension(product.ImageFile.FileName);
            string fileExtension = Path.GetExtension(product.ImageFile.FileName);
            fileName = fileName + DateTime.Now.ToString("yymmssfff") + fileExtension;
            product.Image = "~/Files/" + fileName;
            fileName = Path.Combine(Server.MapPath("~/Files/"), fileName);
            product.ImageFile.SaveAs(fileName);
        }
    }
}