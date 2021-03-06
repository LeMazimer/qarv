#pragma once

#include "decoder.h"

namespace QArv
{

class BayerRG12 : public QObject, public QArvPixelFormat {
    Q_OBJECT
    Q_INTERFACES(QArvPixelFormat)
    Q_PLUGIN_METADATA(IID "si.ad-vega.qarv.BayerRG12")

public:
    ArvPixelFormat pixelFormat() { return ARV_PIXEL_FORMAT_BAYER_RG_12; }
    QArvDecoder* makeDecoder(QSize size) {
        return new BayerDecoder<ARV_PIXEL_FORMAT_BAYER_RG_12>(size);
    }
};

}
