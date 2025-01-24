package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"io"
)

// encrypt encrypts plaintext using AES-GCM with the given key
// key: the encryption key (must match the AES key length requirements: 16, 24, or 32 bytes)
// plaintext: the string to be encrypted
func encrypt(key []byte, plaintext string) (string, string, error) {
	// Create a new AES cipher block based on the provided key
	block, err := aes.NewCipher(key)
	if err != nil {
		return "", "", err
	}

	// Create a Galois/Counter Mode (GCM) cipher based on the AES block
	aesGCM, err := cipher.NewGCM(block)
	if err != nil {
		return "", "", err
	}

	// Generate a random nonce (number used once) with the required size for GCM
	nonce := make([]byte, aesGCM.NonceSize())
	if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
		return "", "", err
	}

	// Encrypt the plaintext and seal it with the nonce and additional data
	ciphertext := aesGCM.Seal(nil, nonce, []byte(plaintext), nil)

	// Return the nonce and ciphertext as hex-encoded strings
	return hex.EncodeToString(nonce), hex.EncodeToString(ciphertext), nil
}

// decrypt decrypts ciphertext using AES-GCM with the given key
// key: the decryption key (must match the encryption key)
// nonceHex: the hex-encoded nonce used during encryption
// ciphertextHex: the hex-encoded encrypted data
func decrypt(key []byte, nonceHex, ciphertextHex string) (string, error) {
	// Create a new AES cipher block based on the provided key
	block, err := aes.NewCipher(key)
	if err != nil {
		return "", err
	}

	// Create a Galois/Counter Mode (GCM) cipher based on the AES block
	aesGCM, err := cipher.NewGCM(block)
	if err != nil {
		return "", err
	}

	// Decode the hex-encoded nonce
	nonce, err := hex.DecodeString(nonceHex)
	if err != nil {
		return "", err
	}

	// Decode the hex-encoded ciphertext
	ciphertext, err := hex.DecodeString(ciphertextHex)
	if err != nil {
		return "", err
	}

	// Decrypt the ciphertext using the nonce and additional data
	plaintext, err := aesGCM.Open(nil, nonce, ciphertext, nil)
	if err != nil {
		return "", err
	}

	// Return the decrypted plaintext as a string
	return string(plaintext), nil
}

func main() {
	// Define a 32-byte encryption key for AES-256
	key := []byte("thisis32byteslongpassphrase123!") // Adjusted to exactly 32 bytes

	// Define the plaintext to be encrypted
	plaintext := "Hello, AES-GCM!"
	fmt.Printf("Original plaintext: %s\n", plaintext)

	// Encrypt the plaintext
	nonce, ciphertext, err := encrypt(key, plaintext)
	if err != nil {
		fmt.Printf("Error encrypting: %v\n", err)
		return
	}

	// Print the generated nonce and ciphertext
	fmt.Printf("Nonce: %s\n", nonce)
	fmt.Printf("Ciphertext: %s\n", ciphertext)

	// Decrypt the ciphertext
	decryptedText, err := decrypt(key, nonce, ciphertext)
	if err != nil {
		fmt.Printf("Error decrypting: %v\n", err)
		return
	}

	// Print the decrypted plaintext
	fmt.Printf("Decrypted text: %s\n", decryptedText)
}


