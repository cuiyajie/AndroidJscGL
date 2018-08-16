package fex.momo.com.androidjscgl;

import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity {

    String js;

    private class MyRender implements GLSurfaceView.Renderer {

        @Override
        public void onDrawFrame(GL10 gl10) {
            runScript(js);
        }

        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
            bootstrap();
        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int i, int i1) {
			nativeSurfaceChanged(i, i1);
        }
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        GLSurfaceView glSurfaceView = findViewById(R.id.glSurfaceView);
        glSurfaceView.setEGLContextClientVersion(2);

        glSurfaceView.setRenderer(new MyRender());
        js = FileUtils.getFromAssets(this, "gl-sample.js");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        destory();
    }

    /**
     * A native method that is implemented by the 'main' native library,
     * which is packaged with this application.
     */

    public native void bootstrap();

    public native void destory();

    public native void runScript(String jscode);

    public native void nativeSurfaceChanged(int w, int h);

    // Used to load the 'native-lib' library on application startup.
    static {
        try {
            System.loadLibrary("jsc");
            System.loadLibrary("native-lib");
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }
}
