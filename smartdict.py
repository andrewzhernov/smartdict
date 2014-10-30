# all the imports
from __future__ import with_statement
from contextlib import closing
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, \
     abort, render_template, flash
     
from indexer import indexer
from searcher import searcher
import os
 
# configuration
DATABASE = ''
DEBUG = False
SECRET_KEY = 'development key'
USERNAME = 'admin'
PASSWORD = 'default'
if os.path.exists('data/sentences') == True:
    SENTENCES = open('data/sentences').readlines()
else:
    sys.exit(0)

# create our little application :)
app = Flask(__name__)
app.config.from_object(__name__)

@app.cli.command('init')
def init_command():
    print ' * Pre-calculation. *'
    indexer.run()
    print ' * Done. *'

@app.route('/', methods=['GET', 'POST'])
def search():    
    sentences = []
    
    if request.method == 'POST':
        if not session.get('logged_in'):
            abort(401)
        word = str(request.form['word'])
        indexes = searcher.find(word)
        if len(indexes) == 0:
            flash("Word was not found")
        for index in indexes:
            sentences.append(SENTENCES[index])
        
    return render_template('search.html', sentences=sentences)
    
@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != app.config['USERNAME']:
            error = 'Invalid username'
        elif request.form['password'] != app.config['PASSWORD']:
            error = 'Invalid password'
        else:
            session['logged_in'] = True
            flash('You were logged in')
            return redirect(url_for('search'))
    return render_template('login.html', error=error)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You were logged out')
    return redirect(url_for('search'))
    
