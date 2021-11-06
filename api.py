import socket
from flask import Flask

app = Flask(__name__)

@app.route('/testKey', methods=['GET'])
def ola():
    return 'true'


app.run(socket.gethostbyname(socket.gethostname()), port=80)