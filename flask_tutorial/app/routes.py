from flask import render_template
from app import app


@app.route("/")
@app.route("/index")
def index():
    user = {"username": "Zheyu"}
    posts = [
        {"author": {"username": "Sarah"}, "body": "Beautiful day in Portland!"},
        {"author": {"username": "Ellen"}, "body": "The Avengers movie was so cool!"},
    ]
    return render_template("index.html", title="Home", user=user, posts=posts)
