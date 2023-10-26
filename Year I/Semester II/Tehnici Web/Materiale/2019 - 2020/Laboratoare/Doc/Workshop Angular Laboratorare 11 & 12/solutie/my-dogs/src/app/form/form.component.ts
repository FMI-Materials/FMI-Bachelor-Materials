import { Component, Inject } from '@angular/core';
import { MatDialogRef, MAT_DIALOG_DATA} from '@angular/material';
import { Dog } from '../dog';
import { DogsService } from '../dogs.service';

@Component({
  selector: 'app-form',
  templateUrl: './form.component.html',
  styleUrls: ['./form.component.css']
})
export class FormComponent {

  constructor(
    public dialogRef: MatDialogRef<FormComponent>,
    private dogsService: DogsService,
    @Inject(MAT_DIALOG_DATA) public data: Dog
  ) { }

  ngOnInit() {
  }

  closeModal(): void {
    this.dialogRef.close();
  }

  saveDog() {
    if (this.data.id) {
      this.dogsService.updateDog(this.data).subscribe(() => {
        this.dialogRef.close();
      })
    }
    else {
      this.dogsService.addDog(this.data).subscribe(() => {
        this.dialogRef.close();
      })
    }

  }

}
