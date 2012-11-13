/* initialize the set of rrot nodes*/
rootnodes = the empty ascending priority queue;

/*construct a node for each symbol*/
for(i=0;i<n; i++){
    p = maketree(frequency[i]);
    position[i] = p; /* a pointer to the leaf containing the ith symbol*/
    pqinsert(rootnodes,p);
}
while(rootnodes contains more than one item){
    p1 = pqmindelete(rootnodes);
    p2 = pqmindelete(rootnodes);
    /*combine p1 and p2 as branches of a single tree*/
    p = maketree(info(p1) + info(p2));
    setleft(p, p1);
    setright(p, p2);
    pqinsert(rootnodes, p);
}
/*the tree is now constructed; use it to find codes*/
root = pqmindelete(rootnodes);
for(i=0; i<n; i++){
    p = position[i];
    code[i] = the null bit string;
    
    while(p != root){
        /* travel up the tree */
        if(isleft(p))
            code[i] = 0 followed by code[i];
        else
            code[i] = 1 followed by code[i];
        p = father(p);
    }
}
