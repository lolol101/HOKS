#include "MessageWidget.h"
#include "ui_MessageWidget.h"

void MessageWidget::slot_clicked_open_button() {
    if (is_media) {
        emit MessageWidget::signal_clicked_open_button(*this);
    }
}
