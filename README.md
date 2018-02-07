# HPGCC


wget https://www.cise.ufl.edu/research/sparse/MM/SNAP/cit-Patents.tar.gz
wget https://www.cise.ufl.edu/research/sparse/MM/SNAP/as-Skitter.tar.gz
wget https://www.cise.ufl.edu/research/sparse/MM/SNAP/amazon0312.tar.gz
wget https://www.cise.ufl.edu/research/sparse/MM/SNAP/ca-HepPh.tar.gz
wget https://www.cise.ufl.edu/research/sparse/MM/SNAP/roadNet-CA.tar.gz
wget https://www.cise.ufl.edu/research/sparse/MM/SNAP/soc-LiveJournal1.tar.gz
wget https://www.cise.ufl.edu/research/sparse/MM/GHS_indef/bmw3_2.tar.gz
mkdir output
tar -xzvf cit-Patents.tar.gz  --strip-components=1 
./pyhpgcc_text.py
