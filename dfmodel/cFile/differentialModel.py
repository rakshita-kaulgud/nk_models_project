import sys
import subprocess
import os

import logging
import boto3
from botocore.exceptions import ClientError


def process():
    # if not os.path.exists('foo'):
    subprocess.call(["gcc", "foo.c", "-ofoo", "-lm"])


def dfModel(*args):
    print("arguments are:\n" + str(args[2]))
    process()
    subprocess.call(["./foo", str(args[2]), str(args[1]), "0.3"], stdin=sys.stdin)
    subprocess.run(["python", "moveTos3.py"])
    print("printing result")
    return 'index.html'
