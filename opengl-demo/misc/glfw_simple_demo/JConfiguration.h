#pragma once
class JConfiguration
{
public:
    JConfiguration();
    ~JConfiguration();
    JConfiguration(const JConfiguration& other);
    void operator=(const JConfiguration& other);

    int pointSize() const;
    void setPointSize(int size);

    int lineWidth() const;
    void setLineWidth(int width);

    // more line style?

    //TODO: color struct definition
    void setColor(int r, int g, int b);
};

