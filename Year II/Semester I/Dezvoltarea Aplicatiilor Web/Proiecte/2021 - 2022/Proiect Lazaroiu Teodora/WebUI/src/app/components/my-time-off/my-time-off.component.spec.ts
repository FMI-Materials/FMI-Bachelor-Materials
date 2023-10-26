import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MyTimeOffComponent } from './my-time-off.component';

describe('MyTimeOffComponent', () => {
  let component: MyTimeOffComponent;
  let fixture: ComponentFixture<MyTimeOffComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ MyTimeOffComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(MyTimeOffComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
