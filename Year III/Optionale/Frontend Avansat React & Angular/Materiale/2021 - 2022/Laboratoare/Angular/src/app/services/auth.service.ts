import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { environment } from 'src/environments/environment';
import { LoginDTO } from '../interfaces/login-dto';

@Injectable({
  providedIn: 'root',
})
export class AuthService {
  private baseUrl = environment.baseUrl;
  private publicHttpHeaders = {
    headers: new HttpHeaders({ 'content-type': 'application/json' }),
  };

  private privateHttpHeaders = {
    headers: new HttpHeaders({
      'content-type': 'application/json',
      Authorization: 'Bearer ' + localStorage.getItem('token'),
    }),
  };
  constructor(private http: HttpClient) {}

  register(data: any) {
    return this.http.post(
      this.baseUrl + '/api/auth/register',
      data,
      this.publicHttpHeaders
    );
  }
  login(data: LoginDTO) {
    return this.http.post(
      this.baseUrl + '/api/auth/login',
      data,
      this.publicHttpHeaders
    );
  }

  getAllUsers() {
    return this.http.get(this.baseUrl + '/api/users', this.privateHttpHeaders);
  }
}
