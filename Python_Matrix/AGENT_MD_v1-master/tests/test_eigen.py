import numpy as np
from matrixpy.eigen import eig, gerschgorin_disks, gerschgorin_bounds


def test_eig():
    A = np.array([[1.0, 2.0], [2.0, 4.0]])
    evals, evecs = eig(A)
    assert evals.shape == (2,)
    assert evecs.shape == (2, 2)


def test_gerschgorin_disks():
    A = np.array([[3.0, 1.0], [1.0, 2.0]])
    disks = gerschgorin_disks(A)
    assert len(disks) == 2
    assert disks[0][0] == 3.0  # center
    assert disks[0][1] == 1.0  # radius


def test_gerschgorin_bounds():
    A = np.array([[3.0, 1.0], [1.0, 2.0]])
    bounds = gerschgorin_bounds(A)
    assert len(bounds) == 4
