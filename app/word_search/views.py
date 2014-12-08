# coding: utf-8

import subprocess

from django.template.loader import get_template
from django.template import Context, Template
from django.http import HttpResponse

def main(request):
    t = get_template('index.html')
    html = t.render(Context({}))
    return HttpResponse(html)

def search(request):
    query = request.GET.get('query', 'search empty query')
    out = subprocess.check_output("/home/andrew/code/smartdict/build/main find '" + query + "'", shell=True)
    return HttpResponse(out)
