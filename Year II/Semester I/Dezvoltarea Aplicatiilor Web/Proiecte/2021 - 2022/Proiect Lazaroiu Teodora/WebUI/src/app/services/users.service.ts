import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class UsersService{

  readonly apiurl = "https://localhost:7278/api";
  isLoggedInVar: boolean = this.IsLoggedIn();
  userData: any;

  constructor(private http:HttpClient) { }
  
  ProceedLogin(user:any) {
    this.userData = this.http.get(this.apiurl + `/Users/${user.emailAddress}`);
    return this.http.post(this.apiurl + '/Users/Login', user);
  }

  IsLoggedIn() {
    return localStorage.getItem('token') != null;
  }

  LogOut() {
    localStorage.removeItem('token');
    window.location.reload();
  }

  GetToken() {
    return localStorage.getItem('token') || '';
  }

  GetEmployee(id:number) {
    return this.http.get(this.apiurl + `/Employees/${id}`);
  }
}
