# Autor:                         Mihailescu Marius Iulian
# E-mail:                        marius-iulian.mihailescu@unibuc.ro 
# Descriere:                     Exemplu de creare a unui blockchain folosind Python
# Data crearii:                  10.04.2021
# Data ultimei actualizari:      25.02.2022
# Scop:                          Didactic, Pentru Facultatea de Matematica si Informatica, Universitatea Bucuresti
 
import datetime                  # pentru timp 
import hashlib                   # calcularea hash-ului pentru a adauga blocurilor amprente digitale
import json                      # pentru stocarea datelor in blockchain
from flask import Flask, jsonify # utilizam si putin Flask pentru crearea aplicatiei web si jsonify pentru afisarea blockchain-ului
 
class UB_FMI_Blockchain:       
    # functia de mai jos creaza primul bloc si seteaza valoarea hash-ului la 0
    def __init__(self):
        self.chain = []
        self.creareBloc(proof=1, hashBlocAnterior='0') 
    
    # cu ajutorul functiei creareBloc vom crea urmatorul bloc 
    def creareBloc(self, proof, hashBlocAnterior):
        blocNou = {'index': len(self.chain) + 1,
                   'timestamp': str(datetime.datetime.now()),
                   'proof': proof,
                   'hashBlocAnterior': hashBlocAnterior}
                   
        # adaugam noul bloc la structura blockchain
        self.chain.append(blocNou)
        
        # returnam noul bloc creat
        return blocNou
       
    # functia afiseaza blocul anterior
    def afiseazaBlocAnterior(self):
        return self.chain[-1]
    
    # functia pentru calculul proof-of-work (PoW) si folosita pentru minarea blocului
    def PoW(self, proofAnterior):
        new_proof = 1
        check_proof = False
         
        while check_proof is False:
            hash_operation = hashlib.sha256(
                str(new_proof**2 - proofAnterior**2).encode()).hexdigest()
            if hash_operation[:5] == '00000':
                check_proof = True
            else:
                new_proof += 1
                 
        return new_proof
 
    # functia calculeaza hash-ul blocului
    def calculeazaHash(self, blocDinChain):
        encoded_block = json.dumps(blocDinChain, sort_keys=True).encode()
        return hashlib.sha256(encoded_block).hexdigest()
    
    # verifica validitatea chain-ului
    def verificaValidateLant(self, chain):
        blocAnterior = chain[0]
        block_index = 1
         
        while block_index < len(chain):
            blocDinChain = chain[block_index]
            if blocDinChain['hashBlocAnterior'] != self.calculeazaHash(blocAnterior):
                return False
               
            proofAnterior = blocAnterior['proof']
            proof = blocDinChain['proof']
            hash_operation = hashlib.sha256(
                str(proof**2 - proofAnterior**2).encode()).hexdigest()
             
            if hash_operation[:5] != '00000':
                return False
            blocAnterior = blocDinChain
            block_index += 1
         
        return True

# cream o aplicatie web folosind Flask
# Tutorial Flask - https://flask.palletsprojects.com/en/2.0.x/
aplicatieWebBlockchain = Flask(__name__)
 
# crearea unui obiect de clasa UB_FMI_Blockchain
ubFMIBlockchain = UB_FMI_Blockchain()
 
# minarea unui bloc nou

#stabilirea rutei pentru minarea blocului
@aplicatieWebBlockchain.route('/minare_bloc', methods=['GET'])
def mineazaBloc():
    blocAnterior = ubFMIBlockchain.afiseazaBlocAnterior()
    proofAnterior = blocAnterior['proof']
    proof = ubFMIBlockchain.PoW(proofAnterior)
    hashBlocAnterior = ubFMIBlockchain.calculeazaHash(blocAnterior)
    blocDinChain = ubFMIBlockchain.creareBloc(proof, hashBlocAnterior)
     
    mesajRaspuns = {'mesaj': 'Un bloc este minat',
                    'index': blocDinChain['index'],
                    'timestamp': blocDinChain['timestamp'],
                    'proof': blocDinChain['proof'],
                    'hashBlocAnterior': blocDinChain['hashBlocAnterior']}
     
    return jsonify(mesajRaspuns), 200
 
# afisarea blockchain-ului in format JSON
@aplicatieWebBlockchain.route('/obtine_lant', methods=['GET'])
def display_chain():
    mesajRaspuns = {'lant': ubFMIBlockchain.chain,
                    'lungime': len(ubFMIBlockchain.chain)}
    return jsonify(mesajRaspuns), 200
 
# verificarea validitatea blockchain-ului
@aplicatieWebBlockchain.route('/verificaValiditate', methods=['GET'])
def valid():
    valid = ubFMIBlockchain.verificaValidateLant(ubFMIBlockchain.chain)
     
    if valid:
        mesajRaspuns = {'mesaj': 'Blockchain-ul este valid.'}
    else:
        mesajRaspuns = {'mesaj': 'Blockchain-ul nu este valid.'}
    return jsonify(mesajRaspuns), 200
 
 
# rulam local serverul de Flask
# host = 127.0.0.1
# port = 5000
aplicatieWebBlockchain.run(host='127.0.0.1', port=5000)