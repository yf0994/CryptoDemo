package com.example.yinfeng.cryptodemo;

/**
 * Created by yinfeng on 14/10/24.
 */
public class Application extends android.app.Application {
    static
    {
        System.loadLibrary("testcrypto");
    };

}
