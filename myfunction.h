#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <QDebug>
#include <QFile>
#include <bits/stdc++.h>

#define myDebug  qDebug

class myfunction
{
public:
  myfunction();
};
#define m_DELETE(p)  \
  {                  \
    if (p) delete (p); \
    (p) = nullptr;      \
  }

#endif // MYFUNCTION_H
