/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C" {
#endif

const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n\
rqXRfboQnoZsG4q5WTP468SQvvG5\n\
-----END CERTIFICATE-----\n"};

const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWjCCAkKgAwIBAgIVAJ67Alg8UmEr7pQzVC2dD7mhHzK8MA0GCSqGSIb3DQEB\n\
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n\
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTAyMTMxNzM0\n\
MTJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n\
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDKad30YVUCT9HLzZwW\n\
fE3qwaGhidJt9CqFBcQ9ihbBc4Z+hoFIbTk9UwjpVkSN6g9c5fKCLwvxUBhQTUk7\n\
MlLMDf6zT66UdgoL/Ufimf37UgkMVKuT/Yjk7gP6U+QH8ya9xA59QbPLC9MemrJ1\n\
3Xp6zTv4wqJRN7hUJrQ+4L3GSwM75ioQl+qJ2i55MvgRpSexebj9sfU+xOimytye\n\
rJcvVreZiQ/GYXyRZVg0vMH9qHPZl2mCWYk6EbSp5kE/FBbjE2J+Ka7rOrF4Ov2E\n\
C61EemxM/EMO/AqymmwCkN0SN6PoqO9hjgJkB6EM3ZnzbAivB7/Duiw3cXhqaIum\n\
1gmBAgMBAAGjYDBeMB8GA1UdIwQYMBaAFB+TWvldXr+QBQpNgbkM8+oIY2RaMB0G\n\
A1UdDgQWBBSbF1i9K/u/xtF+g9wKn+yxkEDbZDAMBgNVHRMBAf8EAjAAMA4GA1Ud\n\
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAstUdMPoX3M77WcoeRSVp1U3/\n\
+DgQu+6iOZ11xfTPnxHXy3irN2JRm0Hvb+qwUNdP8zBSTP471shDjGAVTCDKLQiy\n\
cWmg2HD8pV3xJUmpR+vFCTWasVjac82a7hHJsA9YdhcbimuYPKh+bpYCnXa+Tp/e\n\
vXRy0QFq5x0T8/RuwcVeFgmLyYMfEVryGzuEPoxOmgjnWESyDdPW8s8uvAdcYn/2\n\
9w4B5l/DH3ILwk4lDngCZoQmFE+ZOH1Dyc5H4zGZvLyiGhiTIgsvJ66EViIqd1v/\n\
JlVmQDW1MghdNiO5m69Bm/5a9q88SI4MVl/ePoxmsAKj3kMeoquw5f9fSASuvg==\n\
-----END CERTIFICATE-----\n"};

const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAymnd9GFVAk/Ry82cFnxN6sGhoYnSbfQqhQXEPYoWwXOGfoaB\n\
SG05PVMI6VZEjeoPXOXygi8L8VAYUE1JOzJSzA3+s0+ulHYKC/1H4pn9+1IJDFSr\n\
k/2I5O4D+lPkB/MmvcQOfUGzywvTHpqydd16es07+MKiUTe4VCa0PuC9xksDO+Yq\n\
EJfqidoueTL4EaUnsXm4/bH1PsTopsrcnqyXL1a3mYkPxmF8kWVYNLzB/ahz2Zdp\n\
glmJOhG0qeZBPxQW4xNifimu6zqxeDr9hAutRHpsTPxDDvwKsppsApDdEjej6Kjv\n\
YY4CZAehDN2Z82wIrwe/w7osN3F4amiLptYJgQIDAQABAoIBAF276uH5lNFOP1w+\n\
qfKru7Vj18KjvUPX1zzkr7zDzsflBLpg9Uuh8OjaI/1SSsrhQh4GCmiI+uHT8n51\n\
W91C7565OGK3GqR7iSmGMBzarQgONEx2hUIyHYvOQR9Sa/3WdvFX8lHE9Eqp/ill\n\
ABGe79Igao5HK72qrPyjM8MOdjN1w6XKK57dxr0z1msm2F5ocaDeK226DOwTohCI\n\
XB4wrHa+eNpA2NEguD8YUAfzitgU2VsUznClkv5RgYXc7Xd1m3Uf88M1rLezQigR\n\
5JepyTDCOFK6OtsG1rYK4VNLFshSAkRKY4BdyeKXp/N7wqd5mWHKZbEj/z1rh1ct\n\
JAWqhnECgYEA+T77sUny+3G8WHvxynh3K/oJywXnUVBu8wFknXAEjBCx2LVLQf/0\n\
VGAiMnOU3XsVz6KwlQQbQXrMLYLRsE8uA3jEL/jDJtLEf9I6rCkhYIfpI6p1Nnq6\n\
Q35E//1qRARWcBs7t7Un1A352S4rvuJOm+hp19sw/wQ/XNP08HhXHu0CgYEAz+YB\n\
5rypfgdmy5A+hms+Oqp1B8WoOCDGC5wmnVTT1WAghpXyyfiWBbx2uCDdgRiNpw7G\n\
J/bOukxSI9ELv6O6bKL9j/ktrdCLGPsry7HUENeQrPsCFqpcGSL16lxznnuoPi8E\n\
M3DnOHsA/y/Ri65g9VaogT9UCj2w6oxEKA9BbmUCgYEA8TiumRfLrOSXdz+FdAIA\n\
vDQCtFWjWQQyTMclXGWkUPZ7WROkoVyZV+uuTQuloHDWXBzFL4NI6adx4f4A+NS4\n\
4K1Jmm/0VyeW+2o4VJR99BG1Zko7pJ1ElbuoBeR5qxhTm64Prq0JveZEz5cqyVP2\n\
5lcZ0MoXckfnFu0f2ndtQcUCgYATD9rSxi+gP5t8RLCG8KRXCrQKT2Q6KT8fZ2Te\n\
/h0iLlstG+iT/jf7NKmJ/nFw2ch7Lc6bcXTI/iB16j/yhVediGBJaCZ5DmsCkl0U\n\
oyx3ktxQD//EBkDFiUAVCf8L4/isIvF2qf55XkXcIA1NimKXfCedGiphegCTsOK6\n\
7ZMpRQKBgECwWDvlXPrnwf0Br1AsBQAc82L/TsH4x91w322pZD6ems/ZvtQAFEvo\n\
00X0F2hoJwKKVqTrsJvFIpAKNvcQXi6lZzbs74lIKQ0IQZPOcgvYuuilTQaFHMIE\n\
8BGsgu0ZSiE4i73Xe1QW85ir24+BlNLGrQZml5X9FzGP9hZYfjL8\n\
-----END RSA PRIVATE KEY-----\n"};


#ifdef __cplusplus
}
#endif
