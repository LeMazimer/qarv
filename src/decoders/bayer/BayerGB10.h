#pragma once

#include "decoder.h"

namespace QArv
{

class BayerGB10 : public QObject, public QArvPixelFormat {
    Q_OBJECT
    Q_INTERFACES(QArvPixelFormat)
    Q_PLUGIN_METADATA(IID "si.ad-vega.qarv.BayerGB10")

public:
    ArvPixelFormat pixelFormat() { return ARV_PIXEL_FORMAT_BAYER_GB_10; }
    QArvDecoder* makeDecoder(QSize size) {
        return new BayerDecoder<ARV_PIXEL_FORMAT_BAYER_GB_10>(size);
    }
};

}
