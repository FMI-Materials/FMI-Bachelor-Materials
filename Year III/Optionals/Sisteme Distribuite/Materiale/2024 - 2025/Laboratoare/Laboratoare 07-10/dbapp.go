package main

import (
	"database/sql" // For database interaction
	"fmt"          // For formatted input/output operations
	"log"          // For error logging

	_ "modernc.org/sqlite" // Alternative SQLite driver
)

type Contact struct {
	ID    int
	Name  string
	Phone string
	Email string
}

func main() {
	// Open the SQLite database (or create it if it doesn't exist)
	db, err := sql.Open("sqlite", "contacts.db")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// Initialize the database
	initializeDatabase(db)

	// Main menu loop
	for {
		fmt.Println("\nContact Agenda")
		fmt.Println("1. Add Contact")
		fmt.Println("2. Delete Contact")
		fmt.Println("3. Update Contact")
		fmt.Println("4. Search Contact")
		fmt.Println("5. View All Contacts")
		fmt.Println("6. Exit")
		fmt.Print("Choose an option: ")

		var choice int
		fmt.Scan(&choice)

		switch choice {
		case 1:
			addContact(db)
		case 2:
			deleteContact(db)
		case 3:
			updateContact(db)
		case 4:
			searchContact(db)
		case 5:
			viewAllContacts(db)
		case 6:
			fmt.Println("Goodbye!")
			return
		default:
			fmt.Println("Invalid choice, please try again.")
		}
	}
}

// Initialize the database schema
func initializeDatabase(db *sql.DB) {
	query := `CREATE TABLE IF NOT EXISTS contacts (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		name TEXT NOT NULL,
		phone TEXT NOT NULL,
		email TEXT NOT NULL
	)`
	_, err := db.Exec(query)
	if err != nil {
		log.Fatal(err)
	}
}

// Add a new contact to the database
func addContact(db *sql.DB) {
	var name, phone, email string
	fmt.Print("Enter name: ")
	fmt.Scan(&name)
	fmt.Print("Enter phone: ")
	fmt.Scan(&phone)
	fmt.Print("Enter email: ")
	fmt.Scan(&email)

	query := `INSERT INTO contacts (name, phone, email) VALUES (?, ?, ?)`
	_, err := db.Exec(query, name, phone, email)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Contact added successfully!")
}

// Delete a contact by ID
func deleteContact(db *sql.DB) {
	var id int
	fmt.Print("Enter the ID of the contact to delete: ")
	fmt.Scan(&id)

	query := `DELETE FROM contacts WHERE id = ?`
	_, err := db.Exec(query, id)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Contact deleted successfully!")
}

// Update a contact by ID
func updateContact(db *sql.DB) {
	var id int
	fmt.Print("Enter the ID of the contact to update: ")
	fmt.Scan(&id)

	var name, phone, email string
	fmt.Print("Enter new name: ")
	fmt.Scan(&name)
	fmt.Print("Enter new phone: ")
	fmt.Scan(&phone)
	fmt.Print("Enter new email: ")
	fmt.Scan(&email)

	query := `UPDATE contacts SET name = ?, phone = ?, email = ? WHERE id = ?`
	_, err := db.Exec(query, name, phone, email, id)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Contact updated successfully!")
}

// Search for contacts by a keyword
func searchContact(db *sql.DB) {
	var keyword string
	fmt.Print("Enter name, phone, or email to search: ")
	fmt.Scan(&keyword)

	query := `SELECT id, name, phone, email FROM contacts WHERE name LIKE ? OR phone LIKE ? OR email LIKE ?`
	rows, err := db.Query(query, "%"+keyword+"%", "%"+keyword+"%", "%"+keyword+"%")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()

	fmt.Println("Results:")
	for rows.Next() {
		var contact Contact
		if err := rows.Scan(&contact.ID, &contact.Name, &contact.Phone, &contact.Email); err != nil {
			log.Fatal(err)
		}
		fmt.Printf("ID: %d, Name: %s, Phone: %s, Email: %s\n", contact.ID, contact.Name, contact.Phone, contact.Email)
	}
}

// View all contacts in the database
func viewAllContacts(db *sql.DB) {
	query := `SELECT id, name, phone, email FROM contacts`
	rows, err := db.Query(query)
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()

	fmt.Println("All Contacts:")
	for rows.Next() {
		var contact Contact
		if err := rows.Scan(&contact.ID, &contact.Name, &contact.Phone, &contact.Email); err != nil {
			log.Fatal(err)
		}
		fmt.Printf("ID: %d, Name: %s, Phone: %s, Email: %s\n", contact.ID, contact.Name, contact.Phone, contact.Email)
	}
}
