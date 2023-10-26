import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AboutTimeOffComponent } from './about-time-off.component';

describe('AboutTimeOffComponent', () => {
  let component: AboutTimeOffComponent;
  let fixture: ComponentFixture<AboutTimeOffComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AboutTimeOffComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(AboutTimeOffComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
