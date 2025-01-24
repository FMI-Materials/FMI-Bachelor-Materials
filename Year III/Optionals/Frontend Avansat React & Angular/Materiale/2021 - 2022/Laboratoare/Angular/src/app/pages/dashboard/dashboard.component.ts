import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss'],
})
export class DashboardComponent implements OnInit {
  public classNames: string = 'btn btn-primary';
  public isRed: boolean = false;
  public studenti: any[] = [];
  constructor(private authService: AuthService) {}

  ngOnInit(): void {
    this.getUsers();
  }

  getUsers() {
    this.authService.getAllUsers().subscribe((response: any) => {
      this.studenti = response.allUsers;
    });
  }

  toggleIsRed() {
    this.isRed = !this.isRed;
  }

  addStudent() {
    this.studenti.push({
      nume: 'George',
      ani: 50,
    });
  }

  stergeStudent(index: number) {
    this.studenti.splice(index, 1);
  }

  stergeStudentInFunctieDeNume(numeStudent: string) {
    this.studenti = this.studenti.filter((student) => {
      return student.nume !== numeStudent;
    });
  }
}
