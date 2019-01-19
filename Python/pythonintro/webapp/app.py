from flask import Flask, render_template, request
import mymodule

app = Flask(__name__)

@app.route('/')
def home() -> 'html':
	return render_template('entry.html', page_title='Play with Functions')

@app.route('/findcommonletters', methods=['POST'])
def findcommonletters() -> 'html':
	results = mymodule.find_common_letters(request.form['sentence'], request.form['letters'])
	return render_template('results.html', results_title = 'Common Letters:', the_results = results)

@app.route('/countvowels', methods=['POST'])
def countvowels() -> 'html':
	results = mymodule.count_vowels(request.form['sentence'])
	return render_template('results.html', results_title = 'Vowel Count:', the_results = results)

app.run()