import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { HomeComponent } from './components/home/home.component';
import { MyTimeOffComponent } from './components/my-time-off/my-time-off.component';
import { AboutTimeOffComponent } from './components/about-time-off/about-time-off.component';
import { TeamTimeOffComponent } from './components/team-time-off/team-time-off.component';
import { LoginComponent } from './components/login/login.component';
import { AuthGuard } from './auth.guard';

const routes: Routes = [
  {path: "", component:HomeComponent, canActivate:[AuthGuard]},
  {path: "home", component:HomeComponent, canActivate:[AuthGuard]},
  {path: "my-time-off", component:MyTimeOffComponent, canActivate:[AuthGuard]},
  {path: "about-time-off", component:AboutTimeOffComponent, canActivate:[AuthGuard]},
  {path: "team-time-off", component:TeamTimeOffComponent, canActivate:[AuthGuard]},
  {path: "login", component:LoginComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
