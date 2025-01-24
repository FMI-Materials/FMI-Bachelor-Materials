package main

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"crypto/x509"
	"encoding/base64"
	"encoding/csv"
	"encoding/pem"
	"flag"
	"fmt"
	"os"
	"strings"
)

func handleError(err error) {
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}
}

func encryptAES(key []byte, plaintext []byte) string {
    block, err := aes.NewCipher(key)
    handleError(err)

    ciphertext := make([]byte, aes.BlockSize+len(plaintext))
    iv := []byte("1234567890123456") 
    copy(ciphertext[:aes.BlockSize], iv)

    stream := cipher.NewCFBEncrypter(block, iv)
    stream.XORKeyStream(ciphertext[aes.BlockSize:], plaintext)

    return base64.StdEncoding.EncodeToString(ciphertext)
}


func encryptRSA(publicKey *rsa.PublicKey, plaintext []byte) []byte {
	hash := sha256.New()
	ciphertext, err := rsa.EncryptOAEP(hash, rand.Reader, publicKey, plaintext, nil)
	handleError(err)
	return ciphertext
}

func parseRSAPublicKey(publicKeyPEM string) *rsa.PublicKey {
	block, _ := pem.Decode([]byte(publicKeyPEM))
	pub, err := x509.ParsePKCS1PublicKey(block.Bytes)
	handleError(err)
	return pub
}

func main() {
	inputFile := flag.String("f", "table.csv", "CSV file to read")
	enc := flag.String("e", "None", "Encrypt the file, AES RSA or None")
	outputFile := flag.String("o", "output.csv", "Output file")
	flag.Parse()

	f, err := os.Open(*inputFile)
	handleError(err)
	defer f.Close()

	csvReader := csv.NewReader(f)
	data, err := csvReader.ReadAll()
	handleError(err)

	var encryptedData [][]byte

	switch *enc {
	case "AES":
		key := []byte("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
		for _, record := range data {
			recordString := strings.Join(record, ",")
			encryptedRecord := encryptAES(key, []byte(recordString))
			encryptedData = append(encryptedData, []byte(encryptedRecord))
		}
	case "RSA":
		rsaPublicKeyPEM := "-----BEGIN RSA PUBLIC KEY-----\nMIIBigKCAYEAskJK5TIgQCp+bj8WDgFv/vulPEe4qlSjZyGqp7833vtqK7WjWwqdnznRZAZzNJG1GbX+c7DwNVee1fu3fOSVN833az8t1cCf/Ouc+WFw2T/IGXqGpQHLIGV9B1LDm1Oye1vR1OX7AeZlswcSlyqjy7Q9O7iikx14cnZEreXoWeRCqo8HeeK5xHn9ewwlaOiEMBMKryi/7bRSXlb2C2nFDnnbZpVXtHjJhGwzxDaQmo7cmUgjNjK4xWtyCfBduUmhGYbR62jtXxgR0D4EvlIoGNgPvdFdIw1o1pd+tgwQWitJliYLHahMm2kMXxy0XziP5rw4vwPCDYnHMgmvpYpPXXqA1P9EgEajxwcNzSeVky93/SSa6ygzeWbQqKD8KBYpUNPU9e5LD28qLGdBpj9YAsCMolgHrbdPi0jbcIxcC5WygQSiHNP/4SmL5wtLgQE1OrTP/0Slh2koa2JlQWU38FIDA8SvazF6F9Rv3CcSHlD6g3Gdz2NdFdixjpdMJgP/AgMBAAE=\n-----END RSA PUBLIC KEY-----"
		publickey := parseRSAPublicKey(rsaPublicKeyPEM)
		for _, record := range data {
			recordString := strings.Join(record, ",")
			encryptedRecord := encryptRSA(publickey, []byte(recordString))
			encryptedBase64 := base64.StdEncoding.EncodeToString(encryptedRecord)
			encryptedData = append(encryptedData, []byte(encryptedBase64))
		}
	case "None":
		for _, record := range data {
			recordString := strings.Join(record, ",")
			encryptedData = append(encryptedData, []byte(recordString))
		}
	}

	err = os.WriteFile(*outputFile, bytes.Join(encryptedData, []byte("\n")), 0644)
	handleError(err)
}