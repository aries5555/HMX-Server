����ԭʼ˽�� 
openssl genrsa -out rsa_private_key.pem 1024

���ɹ�Կ
openssl rsa -in private_key.pem -pubout -out rsa_public_key.crt

��ԭʼ˽ԿתΪpkcs#8��ʽ
openssl pkcs8 -topk8 -inform PEM -in rsa_private_key.pem -outform PEM -nocrypt[ -out rsa_private_key.pem]

��pkcs#8��ʽתΪԭʼ��ʽ
openssl rsa -in rsa_private_key.pem -out rsa_private_key.pem