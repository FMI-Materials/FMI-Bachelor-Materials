import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { UsersService } from 'src/app/services/users.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  employeeData: any;

  employeeId: number = 5;
  email: string = "";
  role: number = 0;

  constructor(private service:UsersService) {
  }

  ngOnInit(): void {
    this.service.GetEmployee(this.employeeId).subscribe(res =>
      {
        this.employeeData = res;
      });
  }

}
