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

    def test_get_personalized_greeting(self):
        self.assertEqual(L.get_personalized_greeting(), 'hello whoever you are')
        self.assertEqual(L.get_personalized_greeting('Arthur'), 'hello Arthur')
        with self.assertRaises(TypeError) as e:
            L.get_personalized_greeting(123)
        self.assertEqual(str(e.exception), 'argument 1 must be str, not int')
        with self.assertRaises(TypeError) as e:
            L.get_personalized_greeting('Arthur', 'Sam')
        self.assertEqual(str(e.exception), 'function takes at most 1 argument (2 given)')
        self.assertEqual(L.get_personalized_greeting.__doc__, 'Return a personalized greeting.')

    def test_greet_each(self):
        self.assertEqual(L.greet_each([]), [])
        self.assertEqual(L.greet_each(['Arthur']), ['hello Arthur'])
        self.assertEqual(L.greet_each(['Arthur', 'Sam']), ['hello Arthur', 'hello Sam'])
        with self.assertRaises(TypeError) as e:
            L.greet_each(123)
        self.assertEqual(str(e.exception), 'argument 1 must be list, not int')
        with self.assertRaises(TypeError) as e:
            L.greet_each('Arthur', 'Sam')
        self.assertEqual(str(e.exception), 'function takes exactly 1 argument (2 given)')
        with self.assertRaises(TypeError) as e:
            L.greet_each(['Arthur', 123])
        self.assertEqual(str(e.exception), 'sequence item 1: expected str instance, int found')

    def test_raise_error(self):
        with self.assertRaises(RuntimeError):
            L.raise_error()
        with self.assertRaises(RuntimeError):
            L.raise_error(123)
        with self.assertRaises(RuntimeError):
            L.raise_error('Arthur', 'Sam')


if __name__ == '__main__':
    unittest.main()
