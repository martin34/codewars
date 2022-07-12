#!/usr/bin/python3
from flask import Flask, render_template, request
import sqlite3
from pathlib import Path

db_path = "/tmp/example.db"
con = sqlite3.connect(db_path)
cur = con.cursor()
if not Path(db_path).is_file():
    cur.execute(
        """CREATE TABLE greetings
                   (greetings text, name text)"""
    )
cur.execute("""INSERT INTO greetings VALUES ("foo", "bar")""")
con.commit()
con.close()

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def form():
    return render_template("form.html")


@app.route("/hello", methods=["GET", "POST"])
def hello():
    con = sqlite3.connect(db_path)
    cur = con.cursor()
    cur.execute("INSERT INTO greetings VALUES (?,?)", (request.form["say"], request.form["to"]))
    con.commit()
    con.close()
    return render_template("greeting.html", say=request.form["say"], to=request.form["to"])


@app.route("/show", methods=["GET", "POST"])
def show():
    con = sqlite3.connect(db_path)
    greetings = con.execute(f"""SELECT * FROM greetings""").fetchall()
    con.close()
    return render_template("greetings.html", greetings=greetings)


if __name__ == "__main__":
    app.run()
