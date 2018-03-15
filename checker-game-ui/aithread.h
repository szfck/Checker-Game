//#ifndef AITHREAD_H
//#define AITHREAD_H
//#include <QObject>
//#include<QDebug>
//#include<QThread>

//class Worker:public QObject
//{
//    Q_OBJECT
//public:
//    Worker(QObject* parent = nullptr){}
//public slots:
//        //doWork定义了线程要执行的操作
//    void doWork(int parameter) {
//        qDebug()<<"receive the execute signal---------------------------------";
//        qDebug()<<"     current thread ID:"<<QThread::currentThreadId();
//       //循环一百万次
////       for(int i = 0;i!=100;++i)
////       {
////            ++parameter;
////       }
//       //发送结束信号
//       qDebug()<<"      finish the work and sent the resultReady signal\n";
//       emit resultReady(parameter);
//    }

////线程完成工作时发送的信号
//signals:
//    void resultReady(const int result);
//};


//class Controller : public QObject
//{
//    Q_OBJECT
//    QThread workerThread;
//public:
//    Controller(QObject *parent= nullptr) {
//        Worker *worker = new Worker;
//        //调用moveToThread将该任务交给workThread
//        worker->moveToThread(&workerThread);
//        //operate信号发射后启动线程工作
//        connect(this, SIGNAL(operate(const int)), worker, SLOT(doWork(int)));
//        //该线程结束时销毁
//        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
//        //线程结束后发送信号，对结果进行处理
//        connect(worker, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)));
//        //启动线程
//        workerThread.start();
//        //发射信号，开始执行
//        qDebug()<<"emit the signal to execute!---------------------------------";
//        qDebug()<<"     current thread ID:"<<QThread::currentThreadId()<<'\n';
//        emit operate(0);
//    }


//    ~Controller() {
//        workerThread.quit();
//        workerThread.wait();
//    }

//public slots:
//    //处理线程执行的结果
//    void handleResults(const int rslt) {
//        qDebug()<<"receive the resultReady signal---------------------------------";
//        qDebug()<<"     current thread ID:"<<QThread::currentThreadId()<<'\n';
//        qDebug()<<"     the last result is:"<<rslt;
//    }

//signals:
//    //发送信号触发线程
//    void operate(const int);

//};
//#endif // AITHREAD_H
