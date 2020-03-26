import sys
import subprocess

def process():
    # if not os.path.exists('foo'):
    subprocess.call(["gcc", "cournot.c", "-ocournot", "-lm"])


def cournotModel(*args):
    print("arguments are:\n" + str(args[0]))
    process()
    subprocess.call(["./cournot", str(args[0]), "0.4", "0.3"], stdin=sys.stdin)
    subprocess.run(["python", "moveTos3.py"])
    print("printing result")
    return 'cournot_form.html'
