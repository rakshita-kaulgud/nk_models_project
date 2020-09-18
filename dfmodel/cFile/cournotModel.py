import sys
import subprocess

def process():
    # if not os.path.exists('foo'):
    #subprocess.call(["gcc", "cournot.c", "-ocournot", "-lm"]) # lm to compile include math library. Or the math operations fails
    # also include -mcmodel=medium as argument to subprocess call if needed ,"-mcmodel=medium"]
    subprocess.call(["gcc", "cournot.c", "-ocournot", "-lm","-mcmodel=medium"])

def cournotModel(*args):
    print("arguments are:\n" + str(args[0]))
    process()
    subprocess.call(["./cournot", str(args[0]), "0.4", "0.3"], stdin=sys.stdin)
    args = ["./cournot", str(args[0]), "0.4", "0.3"]
    #child_proccess = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    #child_proccess.stdin.write(b"I love beans \n I like cars")
    #child_process_output = child_proccess.communicate()[0]
    #print('STDOUT:{}'.format(child_process_output))
    '''
    child_proccess = subprocess.Popen(args, stdout=subprocess.PIPE)
    while True:
        output = child_proccess.stdout.readline()
        if output == '' and child_proccess.poll() is not None:
            break
        if output:
            print(output.strip())'''
    #rc = child_proccess.poll()

    subprocess.run(["python3", "moveToS3.py"])
    print("printing result")
    return 'cournot_form.html'
