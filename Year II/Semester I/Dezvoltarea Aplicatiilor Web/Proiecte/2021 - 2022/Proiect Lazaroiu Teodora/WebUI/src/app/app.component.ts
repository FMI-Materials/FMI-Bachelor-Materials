import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { UsersService } from './services/users.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'HR Application';
  isLoggedInVar: boolean = this.service.isLoggedInVar;

  constructor(private service:UsersService, private route:Router) {
  }

  LogOut() {
    this.service.LogOut();
  }
}
