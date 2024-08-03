CC=gcc 

all:
	$(CC) -D_PHOTON80_ -D_TABLE_  photon.c photondriver.c -o photon80 sha2.c timer.c -O3
	$(CC) -D_PHOTON128_ -D_TABLE_  photon.c photondriver.c -o photon128 sha2.c timer.c -O3
	$(CC) -D_PHOTON160_ -D_TABLE_  photon.c photondriver.c -o photon160 sha2.c timer.c -O3
	$(CC) -D_PHOTON224_ -D_TABLE_  photon.c photondriver.c -o photon224 sha2.c timer.c -O3
	$(CC) -D_PHOTON256_ -D_TABLE_  photon.c photondriver.c -o photon256 sha2.c timer.c -O3

ref:
	$(CC) -D_PHOTON80_  photon.c photondriver.c -o photon80 sha2.c timer.c -O3
	$(CC) -D_PHOTON128_  photon.c photondriver.c -o photon128 sha2.c timer.c -O3
	$(CC) -D_PHOTON160_  photon.c photondriver.c -o photon160 sha2.c timer.c -O3
	$(CC) -D_PHOTON224_  photon.c photondriver.c -o photon224 sha2.c timer.c -O3
	$(CC) -D_PHOTON256_  photon.c photondriver.c -o photon256 sha2.c timer.c -O3

speed:
	./photon80 -s
	./photon128 -s
	./photon160 -s
	./photon224 -s
	./photon256 -s

clean:
	rm photon80 photon128 photon160 photon224 photon256
