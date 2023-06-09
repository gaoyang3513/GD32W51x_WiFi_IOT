"""
Tests for RSA keys
"""

import io
import os
import sys
import tempfile
import unittest

from cryptography.exceptions import InvalidSignature
from cryptography.hazmat.primitives.asymmetric.padding import PSS, MGF1
from cryptography.hazmat.primitives.hashes import SHA256

# Setup sys path so 'imgtool' is in it.
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../..')))

from imgtool.keys import load, RSA2048, RSAUsageError

class KeyGeneration(unittest.TestCase):

    def setUp(self):
        self.test_dir = tempfile.TemporaryDirectory()

    def tname(self, base):
        return os.path.join(self.test_dir.name, base)

    def tearDown(self):
        self.test_dir.cleanup()

    def test_keygen(self):
        name1 = self.tname("keygen.pem")
        k = RSA2048.generate()
        k.export_private(name1, b'secret')

        # Try loading the key without a password.
        self.assertIsNone(load(name1))

        k2 = load(name1, b'secret')

        pubname = self.tname('keygen-pub.pem')
        k2.export_public(pubname)
        pk2 = load(pubname)

        # We should be able to export the public key from the loaded
        # public key, but not the private key.
        pk2.export_public(self.tname('keygen-pub2.pem'))
        self.assertRaises(RSAUsageError, pk2.export_private, self.tname('keygen-priv2.pem'))

    def test_emit(self):
        """Basic sanity check on the code emitters."""
        k = RSA2048.generate()

        ccode = io.StringIO()
        k.emit_c(ccode)
        self.assertIn("rsa_pub_key", ccode.getvalue())
        self.assertIn("rsa_pub_key_len", ccode.getvalue())

        rustcode = io.StringIO()
        k.emit_rust(rustcode)
        self.assertIn("RSA_PUB_KEY", rustcode.getvalue())

    def test_emit_pub(self):
        """Basic sanity check on the code emitters, from public key."""
        pubname = self.tname("public.pem")
        k = RSA2048.generate()
        k.export_public(pubname)

        k2 = load(pubname)

        ccode = io.StringIO()
        k2.emit_c(ccode)
        self.assertIn("rsa_pub_key", ccode.getvalue())
        self.assertIn("rsa_pub_key_len", ccode.getvalue())

        rustcode = io.StringIO()
        k2.emit_rust(rustcode)
        self.assertIn("RSA_PUB_KEY", rustcode.getvalue())

    def test_sig(self):
        k = RSA2048.generate()
        buf = b'This is the message'
        sig = k.sign(buf)

        # The code doesn't have any verification, so verify this
        # manually.
        k.key.public_key().verify(
                signature=sig,
                data=buf,
                padding=PSS(mgf=MGF1(SHA256()), salt_length=32),
                algorithm=SHA256())

        # Modify the message to make sure the signature fails.
        self.assertRaises(InvalidSignature,
                k.key.public_key().verify,
                signature=sig,
                data=b'This is thE message',
                padding=PSS(mgf=MGF1(SHA256()), salt_length=32),
                algorithm=SHA256())

if __name__ == '__main__':
    unittest.main()
