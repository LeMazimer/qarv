#pragma once

#include "decoder.h"

namespace QArv
{

class BayerBG10 : public QObject, public QArvPixelFormat {
    Q_OBJECT
    Q_INTERFACES(QArvPixelFormat)
    Q_PLUGIN_METADATA(IID "si.ad-vega.qarv.BayerBG10")

public:
    ArvPixelFormat pixelFormat() { return ARV_PIXEL_FORMAT_BAYER_BG_10; }
    QArvDecoder* makeDecoder(QSize size) {
        return new BayerDecoder<ARV_PIXEL_FORMAT_BAYER_BG_10>(size);
    }
};

}
