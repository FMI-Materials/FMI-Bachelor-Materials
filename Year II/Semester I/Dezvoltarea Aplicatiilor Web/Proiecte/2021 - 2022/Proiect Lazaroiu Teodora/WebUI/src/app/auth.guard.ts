import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot, UrlTree } from '@angular/router';
import { Observable } from 'rxjs';
import { UsersService } from './services/users.service';

@Injectable({
  providedIn: 'root'
})
export class AuthGuard implements CanActivate {
  
  constructor(private service:UsersService, private route:Router) {

  }
  canActivate() {
    if (this.service.IsLoggedIn())
    {
      return true;
    }
    else
    {
      this.route.navigate(['/login']);
      return false;
    }
  }
  
}
