import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs/internal/Observable';
import { Dog } from './dog';

@Injectable({
  providedIn: 'root'
})
export class DogsService {

  constructor(private http: HttpClient) {
  }

  getDogs() {
    return this.http.get('http://localhost:4000/dogs') as Observable<Dog[]>
  }

  addDog(postObject: Dog) {
    return this.http.post('http://localhost:4000/dogs', postObject) as Observable<Dog>
  }

  updateDog(postObject: Dog) {
    return this.http.put(`http://localhost:4000/dogs/${postObject.id}`, postObject) as Observable<Dog>
  }

  deleteDog(id: number) {
    return this.http.delete(`http://localhost:4000/dogs/${id}`) as Observable<{}>
  }
}
