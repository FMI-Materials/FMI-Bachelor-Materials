import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TeamTimeOffComponent } from './team-time-off.component';

describe('TeamTimeOffComponent', () => {
  let component: TeamTimeOffComponent;
  let fixture: ComponentFixture<TeamTimeOffComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TeamTimeOffComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(TeamTimeOffComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
