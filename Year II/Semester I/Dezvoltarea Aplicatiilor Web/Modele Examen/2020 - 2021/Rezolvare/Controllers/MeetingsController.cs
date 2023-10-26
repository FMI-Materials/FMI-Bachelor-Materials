using BuhaiDarius34.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using AppContext = BuhaiDarius34.Models.AppContext;

namespace BuhaiDarius34.Controllers
{
    public class MeetingsController : Controller
    {
        private AppContext db = new BuhaiDarius34.Models.AppContext();

        // GET: Meetings
        public ActionResult Index()
        {
            var meetings = db.Meetings.Include("Subject");
            ViewBag.Meetings = meetings;
            if (TempData.ContainsKey("message"))
                ViewBag.Message = TempData["message"];
            return View();
        }

        public ActionResult Search()
        {
            var search = Request.Params["search"];
            if (TempData.ContainsKey("message"))
                ViewBag.Message = TempData["message"];
            ViewBag.Meetings = new List<Meeting>();
            if (search == null)
                search = "";

            var meetings = db.Meetings.Include("Subject").Where(meeting => meeting.Subject.NumeSub.Contains(search)).ToList();
            meetings = meetings.Where(meeting => meeting.DataMeet.Day == DateTime.Now.Day && meeting.DataMeet.Month == DateTime.Now.Month && meeting.DataMeet.Year == DateTime.Now.Year).ToList();
            meetings = meetings.OrderByDescending(meeting => meeting.Subject.NumeSub).ToList();
            ViewBag.Meetings = meetings;
            ViewBag.Search = search;

            return View();
        }

        public ActionResult Show(int id)
        {
            Meeting meeting = db.Meetings.Find(id);
            return View(meeting);

        }

        public ActionResult New()
        {
            Meeting meeting = new Meeting();

            meeting.Subjects = GetAllSubjects();
            meeting.DataMeet = DateTime.Now.AddMinutes(2);

            return View(meeting);
        }

        [HttpPost]
        public ActionResult New(Meeting meeting)
        {
            meeting.Subjects = GetAllSubjects();
            try
            {
                if (meeting.DataMeet < DateTime.Now)
                {
                    ViewBag.Message = "Data nu poate fi din trecut!";
                    return View(meeting);
                }
                if(ModelState.IsValid)
                {
                    db.Meetings.Add(meeting);
                    db.SaveChanges();
                    TempData["message"] = "Conferinta a fost adaugata!";
                    return RedirectToAction("Index");
                }
                return View(meeting);
            }
            catch (Exception e)
            {
                return View(meeting);
            }
        }

        public ActionResult Edit(int id)
        {
            Meeting meeting = db.Meetings.Find(id);
            meeting.Subjects = GetAllSubjects();
            return View(meeting);
        }

        [HttpPut]
        public ActionResult Edit(int id, Meeting requestMeeting)
        {
            requestMeeting.Subjects = GetAllSubjects();
            try
            {
                if (requestMeeting.DataMeet < DateTime.Now)
                {
                    ViewBag.Message = "Data nu poate fi din trecut!";
                    return View(requestMeeting);
                }
                Meeting meeting = db.Meetings.Find(id);

                if (ModelState.IsValid && TryUpdateModel(meeting))
                {
                    meeting.TitluMeet = requestMeeting.TitluMeet;
                    meeting.Content = requestMeeting.Content;
                    meeting.DataMeet = requestMeeting.DataMeet;
                    meeting.SubjectId = requestMeeting.SubjectId;
                    db.SaveChanges();
                    TempData["message"] = "Conferinta a fost modificata cu success!";
                    return RedirectToAction("Index");
                }

                return View(requestMeeting);

            }
            catch (Exception e)
            {
                return View(requestMeeting);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int id)
        {
            Meeting meeting = db.Meetings.Find(id);
            db.Meetings.Remove(meeting);
            db.SaveChanges();
            TempData["message"] = "Conferinta a fost stearsa!";
            return RedirectToAction("Index");
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllSubjects()
        {
            var selectList = new List<SelectListItem>();

            var subjects = from sub in db.Subjects select sub;

            foreach (var subject in subjects)
            {
                selectList.Add(new SelectListItem
                {
                    Value = subject.Id.ToString(),
                    Text = subject.NumeSub.ToString()
                });
            }
            return selectList;
        }
    }
}