# Aplicatia My dogs cu React

## Cuprins

- [Pornirea server-ului de backend](#pornirea-server-ului-de-backend)
- [Crearea aplicatiei](#crearea-aplicatiei)
- [Adaugarea librariei Material-UI](#adaugarea-librariei-material-ui)
- [Eliminarea codului inutil](#eliminarea-codului-inutil)
- [Aducerea datelor de la server](#aducerea-datelor-de-la-server)
- [Afisarea listei de catei](#afisarea-listei-de-catei)
- [Stilizarea listei de catei](#stilizarea-listei-de-catei)
- [Stergerea unui element din lista de catei](#stergerea-unui-element-din-lista-de-catei)
- [Adaugarea si editarea unui element din lista de catei](#adaugarea-si-editarea-unui-element-din-lista-de-catei)

## Pornirea server-ului de backend

Instalati [JSON Server](https://github.com/typicode/json-server) folosind comanda de mai jos:

```bash
npm install -g json-server
```

Creati un fisier `db.json` avand continutul de mai jos:

```json
{
  "dogs": [
    { "id": 1, "name": "AFFENPINSCHER", "img": "https:\/\/dog.ceo\/api\/img\/affenpinscher\/n02110627_11584.jpg" },
    { "id": 2, "name": "AKITA", "img": "https:\/\/dog.ceo\/api\/img\/akita\/Akita_Inu_dog.jpg" },
    { "id": 3, "name": "CHIHUAHUA", "img": "https:\/\/dog.ceo\/api\/img\/chihuahua\/n02085620_8578.jpg" },
    { "id": 4, "name": "LHASA", "img": "https://dog.ceo//api//img//lhasa//n02098413_3033.jpg" },
    { "id": 5, "name": "MINIATURE SCHNAUZER", "img": "https://dog.ceo//api//img//schnauzer//n02097209_920.jpg" }
  ]
}
```

Porniti `JSON Server` folosind comanda de mai jos:

```bash
json-server --watch db.json -p 4000
```

Accesand link-ul [http://localhost:4000/dogs/1](http://localhost:4000/dogs/1), veti vedea:

```json
{ "id": 1, "title": "json-server", "author": "typicode" }
```

## Crearea aplicatiei

Creati aplicatia folosind generatorul de proiecte [Create react app](https://facebook.github.io/create-react-app/).

```sh
npx create-react-app my-dogs
cd my-dogs
npm start
```

Accesand link-ul [http://localhost:3000](http://localhost:3000), veti vedea noua noastra aplicatie React.

## Adaugarea librariei Material-UI

### NPM

Material-UI este disponibil ca [pachet npm](https://www.npmjs.com/package/@material-ui/core),
pentru a-l putea folosi acesta trebuie instalat:

```sh
npm install @material-ui/core
```

Observam ca toate dependentele sale s-au salvat in `package.json`.

### Roboto Font

Material-UI a fost conceput cu ajutorul font-ului Roboto de la Google. Sa-l adaugam si noi in `index.html`:

```html
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500">
```

### Iconitele SVG

Iconitele inbunatatesc experienta utilizatorului. Le instalam folosind:

```sh
npm install @material-ui/icons
```

## Eliminarea codului inutil

Sa inlaturam din componenta nou creata `App.js` tot ce nu ne trebuie:

```js
import React, { Component } from 'react';

class App extends Component {
  render() {
    return (
      <div>
      </div>
    );
  }
}

export default App;
```

## Aducerea datelor de la server

In componenta noastra avem nevoie de o variabila care sa stocheze lista de catei:

```js
  constructor(props){
    super(props);
    this.state = {
      dogs: [],
    }
  }
```

Aducem lista de catei cu ajutorul unui request de tip `GET`:

```js
  getDogs() {
    fetch('http://localhost:4000/dogs')
    .then((response) => response.json())
    .then((responseJson) => {

      this.setState({
        dogs: responseJson,
      })
    })
    .catch((error) =>{
      console.error(error);
    });
  }
```

Apelam functia creata anterior in momentul in care se initializeaza componenta:

```js
  componentDidMount() {
    this.getDogs()
  }
```

## Afisarea listei de catei

Folosim tabelul dat ca exemplu in [Material-UI](https://material-ui.com/demos/tables/) pentru a afisa lista de catei:

Importam componentele de care avem nevoie:

```js
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Paper from '@material-ui/core/Paper';
import Button from '@material-ui/core/Button';

import EditIcon from '@material-ui/icons/Edit';
import DeleteIcon from '@material-ui/icons/Delete';
```

Modificam functia `render` pentru a afisa lista:

```js
 render() {
    const { dogs } = this.state;
    return (
      <Paper>
      <Table>
        <TableHead>
          <TableRow>
            <TableCell>Nume</TableCell>
            <TableCell align="center">Imagine</TableCell>
            <TableCell align="right">Actiuni</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {dogs.map(dog => {
            return (
              <TableRow key={dog.id}>
                <TableCell component="th" scope="row">
                  {dog.name}
                </TableCell>
                <TableCell align="center">
                  <img src={dog.img} alt={dog.name} />
                </TableCell>
                <TableCell align="right">
                  <Button onClick={() => this.editDog(dog)}>
                    <EditIcon />
                     Editeaza
                  </Button>
                  <Button onClick={() => this.deleteDog(dog.id)}>
                    <DeleteIcon />
                     Sterge
                  </Button>
                </TableCell>
              </TableRow>
            );
          })}
        </TableBody>
      </Table>
    </Paper>
    );
  }
```

Pentru fiecare catel afisam numele, imaginea si butoanele de actiuni: *Editeaza* si *Sterge*.

## Stilizarea listei de catei

Pentru a imbunatati designul, folosim [CSS in JS](https://material-ui.com/css-in-js/basics/#higher-order-component-api) si ne cream un obiect care va contine noile stiluri:

```js
const styles = theme => ({
  root: {
    width: '100%',
    marginTop: theme.spacing.unit * 3,
    overflowX: 'auto',
  },
  table: {
    minWidth: 700,
  },
  addButton: {
    margin: '10px'
  },
  editButton: {
    marginRight: '20px'
  },
  img: {
    height: '150px'
  }
});
```

Transmitem obiectul creat anterior componentei `App`:

```js
import { withStyles } from '@material-ui/core/styles';
....
export default withStyles(styles)(App);
```

In functia `render` folosim stilurile:

```js
render() {
  const { classes } = this.props;
  ...
  return (
    ...
    <Table className={classes.table}>
    ...
      <img src={dog.img} alt={dog.name} className={classes.img} />
    ...
    <Button className={classes.editButton} onClick={() => this.editDog(dog)}>
    ...
  )
}
```

## Stergerea unui element din lista de catei

Stergem un element din lista de catei cu ajutorul unui request de tip `DELETE`:

```js
  deleteDog(id) {
    const self = this;

     fetch(`http://localhost:4000/dogs/${id}`, {
      method: 'DELETE',
      }).then(function () {
        self.getDogs();
    });
  }
```

## Adaugarea si editarea unui element din lista de catei

Adaugam in `state` noile proprietati de care avem nevoie:

```js
 this.state = {
      dogs: [],
      openModal: false,
      id: null,
      name: '',
      img: '',
    }
```

Inseram butonul de *Adaugare* deasupra tabelului:

```js
 <Button color="secondary" variant="contained" className={classes.addButton} onClick={this.addDog}>
    <AddIcon />
  Adauga
</Button>
...
```

Functia care va adauga un nou element va deschide o modala cu un formular nepopulat:

```js
  addDog = () => {
    this.setState({ openModal: true, id: null, name: '', img: '' });
  }
```

Functia care va edita un element va deschide o modala ce va contine detaliile despre catel:

```js
  editDog(dog) {
    this.setState({ openModal: true, id: dog.id, name: dog.name, img: dog.img });
  }
```

Importam toate componentele necesare modalei:

```js
import AddIcon from '@material-ui/icons/Add';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogTitle from '@material-ui/core/DialogTitle';
import TextField from '@material-ui/core/TextField';
```

Adaugam modala in functia `render` dupa tabel:

```js
 render() {
  const { dogs, openModal } = this.state;
  ...
  return (
    ...
    <Dialog
        open={openModal}
        onClose={this.closeModal}
        aria-labelledby="form-dialog-title"
      >
        <DialogTitle id="form-dialog-title">Subscribe</DialogTitle>
        <DialogContent>
          <TextField
            autoFocus
            margin="dense"
            id="name"
            label="Dog name"
            type="text"
            value={this.state.name}
            onChange={this.handleFieldChange('name')}
            fullWidth
          />
          <TextField
            margin="dense"
            id="img"
            label="Image Url"
            type="img"
            value={this.state.img}
            onChange={this.handleFieldChange('img')}
            fullWidth
          />
        </DialogContent>
        <DialogActions>
          <Button onClick={this.closeModal} color="primary">
            Anulare
          </Button>
          <Button onClick={this.saveDogs} color="primary">
            Salvare
          </Button>
        </DialogActions>
      </Dialog>
      ...
    )
 }  
```

Completam `state`-ul cu numele si imaginea din formular:

```js
  handleFieldChange = name => event => {
    this.setState({
      [name]: event.target.value,
    });
  };
```

Adaugam functia care inchide modala:

```js
 closeModal = () => {
    this.setState({ openModal: false });
  };
```

Salvam un element din lista de catei cu ajutorul request-urilor de tip `POST` si `PUT`:

```js
  saveDogs = () => {
    const { id, name, img } = this.state
    const url = id ===  null ? 'http://localhost:4000/dogs' : `http://localhost:4000/dogs/${id}`;
    const method = id === null ? 'POST' : 'PUT';
    const postObject = id === null ? { name, img } : { id, name, img }
    const self = this;

    fetch(url, {
      method: method,
      headers: {
          "Content-type": "application/json"
      },
      body: JSON.stringify(postObject)
    }).then(function () {
      self.getDogs();
      self.closeModal();
    });
  }
   closeModal = () => {
    this.setState({ openModal: false });
  };
```