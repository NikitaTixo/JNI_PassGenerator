package nativeLib;

public class NativeLib {

    static {
        System.loadLibrary("nativeLib");
    }

    public static native void generatePass(String[] symbols, int length, String password);

}
