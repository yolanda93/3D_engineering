#ifndef DIALOG_OPTIONS
#define DIALOG_OPTIONS 1

#include "ui_options.h"

class Dialog_options : public QDialog, private Ui::Dialog_options
{
    Q_OBJECT
public:
    Dialog_options(QWidget *parent = 0)
    {
        setupUi(this);
    }
    
    double get_alpha() const { return alpha_spinbox->value(); }
    void set_alpha(const double alpha) { alpha_spinbox->setValue(alpha); }
};

#endif
