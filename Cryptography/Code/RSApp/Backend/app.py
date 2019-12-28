import json

from rsa import RSA
from hashlib import sha256
from flask import Flask, flash, jsonify, redirect, render_template, request

templates, static = "../FrontEnd", "../FrontEnd/Distribution"
app = Flask(__name__, static_folder=static, template_folder=templates)

@app.route('/get_keys')
def get_keys():
    solver = RSA()
    private, public = str(solver.private_key), str(solver.public_key)
    return jsonify({'n': str(solver.n), 'privateKey': private, 'publicKey': public})


@app.route('/RSA', methods=["POST"])
def do_stuff():
    try:
        solver = RSA(empty_value=True)
        data: dict = request.json
        solver.n = int(data.get("n"))
        mode = data.get("mode")
        key = data.get("private") if "private" in data else data.get("public")

        if mode == "Encrypt":
            solver.public_key = int(key)
            result = solver.encrypt(data.get("text"))

            return jsonify({'message': [str(c) for c in result]})

        elif mode == "Decrypt" or mode == "Compare":
            text = json.loads(data.get("text"))
            text = [int(c) for c in text]

            solver.private_key = int(key)
            message = solver.decrypt(text)

            return jsonify({'message': message})

        elif mode == "Hash":
            text = data.get("text").encode('utf-8')
            hash_value = str(sha256(text).hexdigest())

            solver.public_key = int(key)
            result = solver.encrypt(hash_value)

            return jsonify({'message': [str(c) for c in result]})

        return ""

    except:
        return jsonify({'message': "", "error": True})


@app.route('/')
def index(): return render_template('index.html')


if __name__ == '__main__':
    app.run()
