#ifndef SERIALIZEDDATACALCULATION_H
#define SERIALIZEDDATACALCULATION_H

#include <QVariant>

class SerializedDataCalculation
{

public:

//checkMessSize
    static int checkMessageSize(const QVariant s_data, const quint16 s_command, const bool &verboseMode);

    static qint64 chkMessageSize(const QVariant &s_data);

};

#endif // SERIALIZEDDATACALCULATION_H
