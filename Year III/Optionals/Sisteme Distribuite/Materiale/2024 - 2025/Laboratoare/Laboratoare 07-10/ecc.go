package main

import (
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"crypto/sha256"
	"fmt"
	"math/big"
)

// generateKeys generates a public and private key pair using the P256 curve
func generateKeys() (*ecdsa.PrivateKey, *ecdsa.PublicKey, error) {
	privateKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return nil, nil, err
	}
	return privateKey, &privateKey.PublicKey, nil
}

// encrypt signs a message hash using the sender's private key
func encrypt(privateKey *ecdsa.PrivateKey, message string) ([]byte, *big.Int, *big.Int, error) {
	// Hash the message
	hash := sha256.Sum256([]byte(message))

	// Sign the hash using the private key
	r, s, err := ecdsa.Sign(rand.Reader, privateKey, hash[:])
	if err != nil {
		return nil, nil, nil, err
	}
	return hash[:], r, s, nil
}

// decrypt verifies the signature using the sender's public key
func decrypt(publicKey *ecdsa.PublicKey, hash []byte, r, s *big.Int) (bool, error) {
	// Verify the signature
	valid := ecdsa.Verify(publicKey, hash, r, s)
	return valid, nil
}

func main() {
	// Generate key pairs for sender
	privateKey, publicKey, err := generateKeys()
	if err != nil {
		fmt.Printf("Error generating keys: %v\n", err)
		return
	}

	// Message to encrypt
	message := "Hello, ECC encryption!"
	fmt.Printf("Original message: %s\n", message)

	// Encrypt (sign) the message
	hash, r, s, err := encrypt(privateKey, message)
	if err != nil {
		fmt.Printf("Error encrypting message: %v\n", err)
		return
	}
	fmt.Printf("Encrypted hash: %x\n", hash)
	fmt.Printf("Signature R: %s\n", r.String())
	fmt.Printf("Signature S: %s\n", s.String())

	// Decrypt (verify) the message
	valid, err := decrypt(publicKey, hash, r, s)
	if err != nil {
		fmt.Printf("Error verifying message: %v\n", err)
		return
	}

	if valid {
		fmt.Println("Message verification successful!")
	} else {
		fmt.Println("Message verification failed!")
	}
}
