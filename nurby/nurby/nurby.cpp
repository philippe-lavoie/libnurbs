 #include <qapplication.h>
#include "form1.h"

    int main( int argc, char *argv[] )
    {
        QApplication app( argc, argv );

        Form1 clippingForm;
        app.setMainWidget( &clippingForm );
        clippingForm.show();

        return app.exec();
    }

