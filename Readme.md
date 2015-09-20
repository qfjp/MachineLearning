Machine Learning Snap Dataset
=============================

Install
-------
Download [Snap-2.4.zip](https://snap.stanford.edu/snap/download.html)
and unzip it within the projects top-level directory.

You should also have a dataset. By default, this uses the [Amazon
ground truth community
dataset](https://snap.stanford.edu/data/com-Amazon.html). Make sure
you download the 'Amazon communities', not the 'co-purchasing
network'. Then, move the file to your top-level directory and run
```
gunzip com-amazon.all.dedup.cmty.txt.gz
```

Run
---
First, compile Snap:
```
cd Snap-2.4
make
```

Then you can compile the main program by running `make` from the
top-level directory.
