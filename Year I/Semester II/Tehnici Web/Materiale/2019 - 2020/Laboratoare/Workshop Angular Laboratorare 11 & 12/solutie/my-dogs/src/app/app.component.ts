import { Component, OnInit } from '@angular/core';
import { MatDialog } from '@angular/material';
import { DogsService } from './dogs.service';
import { Dog } from './dog';
import { FormComponent } from './form/form.component';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  dogs: Dog[] = [];
  displayedColumns: string[] = ['name', 'img', 'actions']

  constructor(
    private dogsService: DogsService,
    public dialog: MatDialog
    ) { }
  
  ngOnInit() { 
    this.getDogs();
   }

   getDogs() {
    this.dogsService.getDogs().subscribe((response) => {
      this.dogs = response;
    })
   }

   editDog(dog: Dog) {
    const dialogRef = this.dialog.open(FormComponent, {
      width: '650px',
      data: { ...dog }
    });
    dialogRef.afterClosed().subscribe(result => {
      this.getDogs();
    });
   }

   addDog() {
    const dialogRef = this.dialog.open(FormComponent, {
      width: '650px',
      data: { name: '', img: ''}
    });
    dialogRef.afterClosed().subscribe(result => {
      this.getDogs();
    });
   }

   deleteDog(id: number) {
    this.dogsService.deleteDog(id).subscribe(() => {
      this.getDogs()
    });
  }
}
