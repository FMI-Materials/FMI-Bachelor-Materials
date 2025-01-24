import unittest
from splay_tree import SplayTree


class TestCase(unittest.TestCase):
    def setUp(self):
        self.keys = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        self.t = SplayTree()
        for key in self.keys:
            self.t.insert(key)

    # def testInsert(self):
    #     for key in self.keys:
    #         self.assertEquals(key, self.t.find(key))
    #
    def testRemove(self):
        for key in self.keys:
            self.t.remove(key)
            self.assertEqual(self.t.find(key), None)

    def testLargeInserts(self):
        t = SplayTree()
        nums = 40000
        gap = 307
        i = gap
        while i != 0:
            t.insert(i)
            i = (i + gap) % nums

    def testIsEmpty(self):
        self.assertFalse(self.t.isEmpty())
        t = SplayTree()
        self.assertTrue(t.isEmpty())

    def testMinMax(self):
        self.assertEqual(self.t.findMin(), 0)
        self.assertEqual(self.t.findMax(), 0)


if __name__ == "__main__":
    unittest.main()

# https://codereview.stackexchange.com/questions/209904/unit-testing-for-splay-tree-in-python