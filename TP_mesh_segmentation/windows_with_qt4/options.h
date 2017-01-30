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

	double get_angle_max() const { return alpha_spinbox_2->value(); }
	void set_angle_max(const double angle_max) { alpha_spinbox_2->setValue(angle_max); }

	double get_area_min() const { return alpha_spinbox_3->value(); }
	void set_area_min(const double area_min) { alpha_spinbox_3->setValue(area_min); }
	
};

#endif
