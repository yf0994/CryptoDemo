package com.example.yinfeng.cryptodemo.crypto;

/**
 *
 * Created by yinfeng on 14/10/19.
 */
public class CryptoHelper {

    public static final int ENCRYPT = 0;
    public static final int DECRYPT = 1;


    /**
     *
     * @param buffer str the string to be encrypted or decrypted.
     * @param mode select crypto method.
     * @param flag encrypt or decrypt.
     * @return
     */
    public static byte[] crypto(byte [] buffer,int len,Crypto_method mode,int flag)
    {
        if(buffer == null || mode == null)
        {
            throw new NullPointerException();
        }

        if(flag != ENCRYPT && flag != DECRYPT)
        {
            throw new CryptoException();
        }


        switch (mode)
        {
            case AES:
                switch (flag)
                {
                    case ENCRYPT:
                        return aes_encrypt(buffer, len);
                    case DECRYPT:
                        return aes_decrypt(buffer, len);
                }
                break;
            case SM4:
                switch (flag)
                {
                    case ENCRYPT:
                        return sm4_encrypt(buffer,len);
                    case DECRYPT:
                        return sm4_decrypt(buffer,len);
                }
                break;
            default:
                break;
        }
        return buffer;

    }


    private static native byte[] aes_encrypt(byte[] str,int len);

    private static native byte[] aes_decrypt(byte[] str,int len);

    private static native byte[] sm4_encrypt(byte[] str,int len);

    private static native byte[] sm4_decrypt(byte[] str,int len);
}
