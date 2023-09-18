from pie import get_max_volume

def test_get_max_volume():
    assert round(get_max_volume(3, 3, [4, 3, 3]), 4) == 25.1327
    #assert round(get_max_volume(1, 24, [5]), 4) == 3.1416
    assert round(get_max_volume(10, 5, [1, 4, 2, 3, 4, 5, 6, 5, 4, 2]), 4) == 50.2655
