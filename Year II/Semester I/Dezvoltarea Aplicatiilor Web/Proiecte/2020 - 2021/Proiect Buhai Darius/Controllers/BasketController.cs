using ProiectDAW.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ProiectDAW.Controllers
{
    [Authorize]
    public class BasketController : Controller
    {
        private ProiectDAW.Models.ApplicationDbContext db = new ProiectDAW.Models.ApplicationDbContext();

        public ActionResult Index()
        {
            var products = new List<Product>();
            int totalPrice = 0;
            HttpCookie basketCookie = Request.Cookies["Basket"];

            if (basketCookie != null && !string.IsNullOrEmpty(basketCookie.Value))
            {
                string[] splitString = basketCookie.Value.Split(new[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                foreach (string item in splitString)
                {
                    int productId = int.Parse(item);
                    var product = db.Products.Find(productId);
                    ProductsController.CalculateProductFinalRating(product);
                    products.Add(product);
                    totalPrice += product.Price;
                }
            }
            ViewBag.Products = products;
            ViewBag.TotalPrice = totalPrice;
            return View();
        }

        public ActionResult New(int id)
        {
            HttpCookie basketCookie = new HttpCookie("Basket");
            if (Request.Cookies["Basket"] != null)
                basketCookie = Request.Cookies["Basket"];

            if(string.IsNullOrEmpty(basketCookie.Value))
                basketCookie.Value = id.ToString();
            else
                basketCookie.Value += ","+id.ToString();
            basketCookie.Expires = DateTime.Now.AddHours(24);

            Response.Cookies.Add(basketCookie);

            return Redirect("/Basket");
        }

        public ActionResult Empty()
        {
            if (Request.Cookies["Basket"] != null)
            {
                HttpCookie basketCookie = Request.Cookies["Basket"];
                basketCookie.Value = "";
                basketCookie.Expires = DateTime.Now;
                Response.Cookies.Add(basketCookie);
            }
            return Redirect("/Basket");
        }

    }
}
