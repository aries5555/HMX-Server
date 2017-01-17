/**
 * \brief ʵ�ַ����������
 *
 * 
 */
#include "SrvEngine.h"


/**
 * \brief CTRL + C���źŵĴ�����,��������
 *
 * \param signum �źű��
 */
static void ctrlcHandler(int signum)
{
  Zebra::logger->info("ctrlcHandler");
  fprintf(stderr,"ctrlcHandler\n");
  //���û�г�ʼ��zServiceʵ��,��ʾ����
  zService *instance = zService::serviceInstance();
  instance->Terminate();
}

/**
 * \brief HUP�źŴ�����
 *
 * \param signum �źű��
 */
static void hupHandler(int signum)
{
  Zebra::logger->info("hupHandler");
  //���û�г�ʼ��zServiceʵ��,��ʾ����
  zService *instance = zService::serviceInstance();
  instance->reloadConfig();
}

zService *zService::serviceInst = NULL;

/**
 * \brief ��������ܵ�������
 */
void zService::main()
{
  Zebra::logger->debug("zService::main");
  //��ʼ������,��ȷ�Ϸ����������ɹ�
  if(signal(SIGTERM  , ctrlcHandler)==SIG_ERR)
  {
	fprintf(stderr,"�ź�����ʧ��\n");
  }

  //��ʼ�������
  srand(time(NULL));

  if (init()
  && validate())
  {
    //�������ص��߳�
    while(!isTerminate())
    {
      if (!run())
      {
        break;
      }
    }
  }

  //��������,�ͷ���Ӧ����Դ
  finaly();
}

