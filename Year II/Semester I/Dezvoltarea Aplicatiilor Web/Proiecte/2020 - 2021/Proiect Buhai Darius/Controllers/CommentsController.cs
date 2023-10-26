using System;
using ProiectDAW.Models;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Microsoft.AspNet.Identity;

namespace ProiectDAW.Controllers
{
    public class CommentsController : Controller
    {
        private ProiectDAW.Models.ApplicationDbContext db = new ProiectDAW.Models.ApplicationDbContext();

        // GET: Comments
        public ActionResult Index()
        {
            return View();
        }

        [HttpDelete]
        public ActionResult Delete(int id)
        {
            Comment comm = db.Comments.Find(id);
            if (comm.UserId == User.Identity.GetUserId() || User.IsInRole("Admin"))
            {
                db.Comments.Remove(comm);
                db.SaveChanges();
                TempData["message"] = "Comentariu sters!";
            }
            else
                TempData["message"] = "Nu aveti dreptul sa stergeti un comentariu care nu va apartine!";
            return Redirect("/Products/Show/" + comm.ProductId);
        }

        [HttpPost]
        public ActionResult New(Comment comm)
        {
            comm.Date = DateTime.Now;
            comm.UserId = User.Identity.GetUserId();
            try
            {
                db.Comments.Add(comm);
                db.SaveChanges();
                return Redirect("/Products/Show/" + comm.ProductId);
            }

            catch (Exception e)
            {
                return Redirect("/Products/Show/" + comm.ProductId);
            }

        }

        public ActionResult Edit(int id)
        {
            Comment comm = db.Comments.Find(id);
            comm.UserId = User.Identity.GetUserId();
            if (comm.UserId == User.Identity.GetUserId() || User.IsInRole("Admin"))
                return View(comm);
            TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui comentariu care nu va apartine!";
            return Redirect("/Products/Show/"+comm.ProductId);
        }

        [HttpPut]
        public ActionResult Edit(int id, Comment requestComment)
        {
            try
            {
                Comment comm = db.Comments.Find(id);
                if (comm.UserId == User.Identity.GetUserId() || User.IsInRole("Admin"))
                {
                    if (TryUpdateModel(comm))
                    {
                        comm.Content = requestComment.Content;
                        comm.Rating = requestComment.Rating;
                        comm.Date = DateTime.Now;
                        TempData["message"] = "Comentariu modificat.";
                        db.SaveChanges();
                        
                    }
                }
                else
                    TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui comentariu care nu va apartine!";
                return Redirect("/Products/Show/" + comm.ProductId);
            }
            catch (Exception e)
            {
                return View();
            }

        }


    }
}