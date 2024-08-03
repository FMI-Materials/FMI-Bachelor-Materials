import { Route } from '@angular/compiler/src/core';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { LoginDTO } from 'src/app/interfaces/login-dto';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss'],
})
export class LoginComponent implements OnInit {
  isDisabled: boolean = true;
  public user: LoginDTO = {
    email: 'test@test.com',
    password: '',
  };
  public error: boolean | string = false;
  constructor(private authService: AuthService, private router: Router) {}

  ngOnInit(): void {}

  isNotValid(): boolean {
    return !this.user.email || !this.user.password;
  }

  doLogin() {
    this.error = false;
    if (this.validateEmail(this.user.email)) {
      this.authService.login(this.user).subscribe((response: any) => {
        console.log(response);
        if (response && response.token) {
          localStorage.setItem('token', response.token);
          this.router.navigate(['/dashboard']);
        }
      });
    } else {
      this.error = 'Email is invalid';
    }
  }

  validateEmail(email: string) {
    const re =
      /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
  }
}
