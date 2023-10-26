using BuhaiDarius34.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace BuhaiDarius34.Controllers
{
    public class SubjectsController : Controller
    {
        private BuhaiDarius34.Models.AppContext db = new BuhaiDarius34.Models.AppContext();

        // GET: Subject
        public ActionResult Index()
        {
            if (TempData.ContainsKey("message"))
                ViewBag.message = TempData["message"].ToString();

            var Subjects = from subject in db.Subjects orderby subject.NumeSub select subject;
            ViewBag.Subjects = Subjects;
            return View();
        }

        public ActionResult Show(int id)
        {
            Subject subject = db.Subjects.Find(id);
            return View(subject);
        }

        public ActionResult New()
        {
            return View();
        }

        [HttpPost]
        public ActionResult New(Subject subject)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    db.Subjects.Add(subject);
                    db.SaveChanges();
                    TempData["message"] = "Subiectul a fost adaugat!";
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(subject);
                }
            }
            catch (Exception e)
            {
                return View(subject);
            }
        }

        public ActionResult Edit(int id)
        {
            Subject subject = db.Subjects.Find(id);
            return View(subject);
        }

        [HttpPut]
        public ActionResult Edit(int id, Subject requestSubject)
        {
            try
            {
                    Subject subject = db.Subjects.Find(id);

                    //throw new Exception();

                    if (TryUpdateModel(subject))
                    {
                        subject.NumeSub = requestSubject.NumeSub;
                        db.SaveChanges();
                        TempData["message"] = "Subiectul a fost modificat!";
                        return RedirectToAction("Index");
                    }

                return View(requestSubject);
            }
            catch (Exception e)
            {
                return View(requestSubject);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int id)
        {
            Subject subject = db.Subjects.Find(id);
            db.Subjects.Remove(subject);
            TempData["message"] = "Subiectul a fost sters!";
            db.SaveChanges();
            return RedirectToAction("Index");
        }
    }
}
