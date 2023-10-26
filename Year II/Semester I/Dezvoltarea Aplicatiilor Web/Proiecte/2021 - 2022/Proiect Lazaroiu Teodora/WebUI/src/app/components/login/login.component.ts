import { Component, OnInit, Input } from '@angular/core';
import { Router } from '@angular/router';
import { UsersService } from 'src/app/services/users.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  emailAddress: string = "";
  password: string = "";
  
  responseData: any;

  constructor(private service:UsersService, private route:Router) {
  }

  ngOnInit(): void {
  }

  ProceedLogin() {
    var user = {
      emailAddress: this.emailAddress,
      password: this.password
    }
    
    this.service.ProceedLogin(user).subscribe(res =>
        {
          if (res != null) {
            this.responseData = res;
            localStorage.setItem('token', this.responseData.tokenString);
            this.route.navigate(['']).then(() =>
            {
              window.location.reload();
            });
          }
        })
  }

  ReloadPage() {
    window.location.reload();
  }

}
