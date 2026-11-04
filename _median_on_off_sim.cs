// �÷���
//   1. �ѡ����ź󡹵�ӫ��������� InputY���� Cycle1 ��ʼ�����±� 0,1,2...��
//   2. �� csc ���룬���� Visual Studio �ﵱ����̨��Ŀ��
//   3. ����̨���ӡ����(Median OFF) / ��(Median ON) ���׽��
//
// ˵����
//   - ����Ӧ���˲�ǰ�������� FLU_CROSSTALK���������Ѿ� Median �������
//   - ��ֵ�˲������棺���ܴӡ�������������ơ��ء�������
//   - �㷨���� PCRCtrlLib: Kdspt_Median + ǰ���� 0.1 ����

using System;
using System.Globalization;
using System.Linq;
using System.Text;

class MedianOnOffSim
{
    // ========== �����������֣����ź󣬰�ѭ��˳��==========
    static readonly double[] InputY = new double[]
    {
        // �����������滻���������
        // 5909.407, 5880.114, 5853.121, ...
    };
    // ========================================================

    const int MedianWnd = 5;   // nWnd
    const int MedianTimes = 1; // Times

    static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;

        if (InputY == null || InputY.Length < 2)
        {
            Console.WriteLine("������ InputY ���������� 2 ���㣨���ź�ӫ�⣩��");
            return;
        }

        double[] off = ProcessMedianOff(InputY);
        double[] on = ProcessMedianOn(InputY, MedianWnd, MedianTimes);

        Console.WriteLine("�������: {0}", InputY.Length);
        Console.WriteLine("����: nWnd={0}, Times={1}", MedianWnd, MedianTimes);
        Console.WriteLine();

        Console.WriteLine("======== �� Median�������========");
        PrintSeries(off);

        Console.WriteLine();
        Console.WriteLine("======== �� Median�����գ�========");
        PrintSeries(on);

        Console.WriteLine();
        Console.WriteLine("======== ���Ա� ========");
        Console.WriteLine("Cycle\tInput\tOFF(��)\tON(��)\tON-OFF");
        for (int i = 0; i < InputY.Length; i++)
        {
            Console.WriteLine("{0}\t{1}\t{2}\t{3}\t{4}",
                i + 1,
                F(InputY[i]),
                F(off[i]),
                F(on[i]),
                F(on[i] - off[i]));
        }
    }

    /// <summary>
    /// �أ����ź�ԭ�����������д�� FILTER_MEDIAN ǰ������ֵ������ǰ����������
    /// </summary>
    static double[] ProcessMedianOff(double[] crosstalk)
    {
        return (double[])crosstalk.Clone();
    }

    /// <summary>
    /// ������ֵ(nWnd)��Times �� ǰ�������3�� 0.1 ����
    /// </summary>
    static double[] ProcessMedianOn(double[] crosstalk, int nWnd, int times)
    {
        double[] cur = (double[])crosstalk.Clone();
        double[] next = new double[cur.Length];

        for (int t = 0; t < times; t++)
        {
            KdsptMedian(cur, next, nWnd);
            Array.Copy(next, cur, cur.Length);
        }

        // ǰ������������������ֵʱ��
        if (cur.Length > 3)
        {
            cur[0] = cur[2] + (cur[0] - cur[2]) * 0.1;
            cur[1] = cur[2] + (cur[1] - cur[2]) * 0.1;
        }

        return cur;
    }

    /// <summary>
    /// ���� CDataAlgorithm::Kdspt_Median
    /// </summary>
    static void KdsptMedian(double[] y, double[] yy, int cfnum)
    {
        int n = y.Length;

        if (cfnum < 3 || (cfnum % 2) != 1)
        {
            Array.Copy(y, yy, n);
            return;
        }

        int halfwindow = cfnum / 2;

        for (int i = 0; i < n; i++)
        {
            if (n < cfnum)
            {
                int k = (i < cfnum - 1) ? i : (cfnum - 1);
                double[] win = new double[k + 1];
                Array.Copy(y, i - k, win, 0, k + 1);
                Array.Sort(win);
                yy[i] = win[(k + 1) / 2];
            }
            else
            {
                int beginindex = (i >= halfwindow) ? (i - halfwindow) : 0;
                int endindex = (i + halfwindow <= n - 1) ? (i + halfwindow) : (n - 1);

                int nPre = i - beginindex;
                int nBehind = endindex - i;
                if (nPre > nBehind)
                    beginindex = i - nBehind;
                else
                    endindex = i + nPre;

                int nCount = endindex - beginindex + 1;
                double[] win = new double[nCount];
                Array.Copy(y, beginindex, win, 0, nCount);
                Array.Sort(win);
                yy[i] = win[nCount / 2];
            }
        }
    }

    static void PrintSeries(double[] y)
    {
        Console.WriteLine(string.Join(", ", y.Select(F)));
    }

    static string F(double v)
    {
        return v.ToString("0.###", CultureInfo.InvariantCulture);
    }
}
