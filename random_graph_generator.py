import cyaron
print("start")
_n = [0, 3, 10, 31, 100, 316, 1000, 3162, 10000, 31622]
_m = [
    0, 0.0001, 0.0003, 0.001, 0.003,
    0.01, 0.02, 0.04, 0.08,  
    0.1, 0.15, 0.2, 0.25, 0.3, 
    0.4, 0.5, 0.6, 0.7,   
    0.8, 0.9, 0.95, 0.99    
]
test_data = cyaron.IO(file_prefix="")
for i in range(1, 10):
    for j in range(1, 21):
        n = _n[i]
        m = min((int)(_n[i]*(_n[i]-1)*_m[j]/2), 750000)
        if m == 0:
            continue
        s = 1
        T = 10
        test_data.input_writeln(T)
        for k in range(1, T+1):
            test_data.input_writeln(n, m, s)
            graph = cyaron.Graph.graph(n, m, directed=True, weight_limit=(-1000, 1000), self_loop=False, repeated_edges=False)
            test_data.input_writeln(graph)
        print("finished:"+str(n)+","+str(m))
        if m == 750000:
            break