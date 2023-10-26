import { TestBed } from '@angular/core/testing';

import { DogsService } from './dogs.service';

describe('DogsService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: DogsService = TestBed.get(DogsService);
    expect(service).toBeTruthy();
  });
});
