import libhelloworld as L
import unittest


class TestLibHelloWorld(unittest.TestCase):

    def test_module_name(self):
        self.assertEqual(L.__name__, 'libhelloworld-modulename')
        with self.assertRaises(AttributeError) as e:
            L.nonexistent_method()
        self.assertEqual(str(e.exception), "module 'libhelloworld-modulename' has no attribute 'nonexistent_method'")

    def test_get_hello(self):
        self.assertEqual(L.get_hello(), 'hello world')
        self.assertEqual(L.get_hello(123), 'hello world')
        self.assertEqual(L.get_hello('Arthur', 'Sam'), 'hello world')

    def test_raise_error(self):
        with self.assertRaises(RuntimeError):
            L.raise_error()
        with self.assertRaises(RuntimeError):
            L.raise_error(123)
        with self.assertRaises(RuntimeError):
            L.raise_error('Arthur', 'Sam')


if __name__ == '__main__':
    unittest.main()
