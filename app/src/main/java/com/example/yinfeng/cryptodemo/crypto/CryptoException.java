package com.example.yinfeng.cryptodemo.crypto;

/**
 * Created by yinfeng on 14/10/19.
 */
public class CryptoException extends RuntimeException {
    public CryptoException()
    {

    }

    public CryptoException(String detailMessage)
    {
        super(detailMessage);
    }
}
