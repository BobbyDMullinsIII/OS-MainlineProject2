#include <QObject>
#include <QVariant>

//Stolen from: https://stackoverflow.com/questions/7502600/how-to-use-signal-and-slot-without-deriving-from-qobject
class CopyableQObject : public QObject
{
protected:
    explicit CopyableQObject(QObject* parent = nullptr) : QObject(parent) {}
    CopyableQObject(const CopyableQObject& other) { initFrom(other); }
    CopyableQObject(CopyableQObject&& other) { initFrom(other); }
    CopyableQObject& operator=(const CopyableQObject& other)
    {
        return initFrom(other), * this;
    }
    CopyableQObject& operator=(CopyableQObject&& other)
    {
        return initFrom(other), * this;
    }
private:
    void initFrom(const CopyableQObject& other)
    {
        setParent(other.parent());
        setObjectName(other.objectName());
    }
    void initFrom(CopyableQObject& other)
    {
        initFrom(const_cast<const CopyableQObject&>(other));
        for (QObject* child : other.children())
            child->setParent(this);
        for (auto& name : other.dynamicPropertyNames())
            setProperty(name, other.property(name));
    }
};