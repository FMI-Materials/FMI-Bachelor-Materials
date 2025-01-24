import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';

@Component({
  selector: 'app-student',
  templateUrl: './student.component.html',
  styleUrls: ['./student.component.scss']
})
export class StudentComponent implements OnInit {
  @Input() nume:string='';
  @Input() ani:number=0;
  @Input() index:number=0;

  @Output() stergeNume = new EventEmitter();

  constructor() { }

  ngOnInit(): void {
  }

  sterge(numeStudent:string){
    this.stergeNume.emit(numeStudent)
  }

}
