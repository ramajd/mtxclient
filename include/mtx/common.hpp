#pragma once

#include <nlohmann/json.hpp>

#include <map>
#include <string>
#include <vector>

using json = nlohmann::json;

//! Common types used by the crypto related endpoints.

namespace mtx {
namespace crypto {

using AlgorithmDevice = std::string;

struct UnsignedDeviceInfo
{
        //! The display name which the user set on the device.
        std::string device_display_name;
};

void
from_json(const json &obj, UnsignedDeviceInfo &res);

void
to_json(json &obj, const UnsignedDeviceInfo &res);

struct DeviceKeys
{
        //! The ID of the user the device belongs to.
        std::string user_id;
        //! The ID of the device these keys belong to.
        std::string device_id;
        //! The encryption algorithms supported by this device.
        std::vector<std::string> algorithms = {"m.olm.v1.curve25519-aes-sha2",
                                               "m.megolm.v1.aes-sha2"};
        //! Public identity keys.
        //! The names of the properties should be in the format <algorithm>:<device_id>.
        //! The keys themselves should be encoded as specified by the key algorithm.
        std::map<AlgorithmDevice, std::string> keys;
        //! Signatures for the device key object.
        //! A map from user ID, to a map from <algorithm>:<device_id> to the signature.
        std::map<std::string, std::map<AlgorithmDevice, std::string>> signatures;
        ///! Additional data added to the device key information
        //! by intermediate servers, and not covered by the signatures.
        UnsignedDeviceInfo unsigned_info;
};

void
from_json(const json &obj, DeviceKeys &res);

void
to_json(json &obj, const DeviceKeys &res);

struct JWK
{
        //! Required. Key type. Must be oct.
        std::string kty;
        //! Required. Key operations. Must at least contain encrypt and decrypt.
        std::vector<std::string> key_ops;
        //! Required. Algorithm. Must be A256CTR.
        std::string alg;
        //! Required. The key, encoded as urlsafe unpadded base64.
        std::string k;
        //! Required. Extractable. Must be true. This is a W3C extension.
        bool ext;
};

void
from_json(const json &obj, JWK &res);

void
to_json(json &obj, const JWK &res);

struct EncryptedFile
{
        //! Required. The URL to the file.
        std::string url;
        //! Required. A JSON Web Key object. (The encryption key)
        JWK key;
        //! Required. The Initialisation Vector used by AES-CTR, encoded as unpadded base64.
        std::string iv;
        //! Required. A map from an algorithm name to a hash of the ciphertext, encoded as unpadded
        //! base64. Clients should support the SHA-256 hash, which uses the key sha256.
        std::map<std::string, std::string> hashes;
        //! Required. Version of the encrypted attachments protocol. Must be v2.
        std::string v;
};

void
from_json(const json &obj, EncryptedFile &res);

void
to_json(json &obj, const EncryptedFile &res);

} // namespace crypto
} // namespace mtx
