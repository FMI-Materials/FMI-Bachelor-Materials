package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"fmt"
)

func generateKeys() (*rsa.PrivateKey, *rsa.PublicKey, error) {
	// Generate a private key
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return nil, nil, err
	}
	return privateKey, &privateKey.PublicKey, nil
}

func encryptMessage(publicKey *rsa.PublicKey, message string) ([]byte, error) {
	// Encrypt the message using the public key and OAEP padding
	hash := sha256.New()
	ciphertext, err := rsa.EncryptOAEP(hash, rand.Reader, publicKey, []byte(message), nil)
	if err != nil {
		return nil, err
	}
	return ciphertext, nil
}

func decryptMessage(privateKey *rsa.PrivateKey, ciphertext []byte) (string, error) {
	// Decrypt the ciphertext using the private key and OAEP padding
	hash := sha256.New()
	plaintext, err := rsa.DecryptOAEP(hash, rand.Reader, privateKey, ciphertext, nil)
	if err != nil {
		return "", err
	}
	return string(plaintext), nil
}

func main() {
	// Generate RSA keys
	privateKey, publicKey, err := generateKeys()
	if err != nil {
		fmt.Printf("Error generating keys: %v\n", err)
		return
	}

	message := "Hello, RSA!"
	fmt.Printf("Original message: %s\n", message)

	// Encrypt the message
	ciphertext, err := encryptMessage(publicKey, message)
	if err != nil {
		fmt.Printf("Error encrypting message: %v\n", err)
		return
	}
	fmt.Printf("Encrypted message: %x\n", ciphertext)

	// Decrypt the message
	decryptedMessage, err := decryptMessage(privateKey, ciphertext)
	if err != nil {
		fmt.Printf("Error decrypting message: %v\n", err)
		return
	}
	fmt.Printf("Decrypted message: %s\n", decryptedMessage)
}
