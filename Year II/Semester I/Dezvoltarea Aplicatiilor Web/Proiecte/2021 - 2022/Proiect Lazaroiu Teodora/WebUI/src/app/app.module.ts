import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HomeComponent } from './components/home/home.component';
import { MyTimeOffComponent } from './components/my-time-off/my-time-off.component';
import { AboutTimeOffComponent } from './components/about-time-off/about-time-off.component';
import { TeamTimeOffComponent } from './components/team-time-off/team-time-off.component';
import { LoginComponent } from './components/login/login.component';

import { UsersService } from './services/users.service';

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    MyTimeOffComponent,
    AboutTimeOffComponent,
    TeamTimeOffComponent,
    LoginComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule
  ],
  providers: [UsersService],
  bootstrap: [AppComponent]
})
export class AppModule { }
