using System;
using System.Runtime.InteropServices;

namespace CoCarClientCs
{
    // {5228FE37-5148-438A-92E1-9E93A7315FE1}
    //DEFINE_GUID(CLSID_CoCar,
    //	0x5228fe37, 0x5148, 0x438a, 0x92, 0xe1, 0x9e, 0x93, 0xa7, 0x31, 0x5f, 0xe1);
    [ComVisible(true), ComImport, Guid("5228FE37-5148-438A-92E1-9E93A7315FE1")]
    public class Car
    {
    }

    // {6A60CA50-F37D-4292-A873-A98FC9ABB6BC}
    //DEFINE_GUID(IID_ICreateCar,
    //	0x6a60ca50, 0xf37d, 0x4292, 0xa8, 0x73, 0xa9, 0x8f, 0xc9, 0xab, 0xb6, 0xbc);
    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("6A60CA50-F37D-4292-A873-A98FC9ABB6BC")]
    public interface ICreateCar
    {
        void SetPetName(string petName);
        void SetMaxSpeed(int maxSp);
    }

    // {4E51046E-FD3E-4285-83C1-B9AAD073A7B6}
    //DEFINE_GUID(IID_IStats,
    //	0x4e51046e, 0xfd3e, 0x4285, 0x83, 0xc1, 0xb9, 0xaa, 0xd0, 0x73, 0xa7, 0xb6);
    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("4E51046E-FD3E-4285-83C1-B9AAD073A7B6")]
    public interface IStats
    {
        void DisplayStats();
        void GetPetName(ref string petName);
    }

    // {0F4ABAB8-6A05-4197-A81A-DA9C4D5187E4}
    //DEFINE_GUID(IID_IEngine,
    //	0xf4abab8, 0x6a05, 0x4197, 0xa8, 0x1a, 0xda, 0x9c, 0x4d, 0x51, 0x87, 0xe4);
    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("0F4ABAB8-6A05-4197-A81A-DA9C4D5187E4")]
    public interface IEngine
    {
        void SpeedUp();
        void GetMaxSpeed(ref int curSpeed);
        void GetCurSpeed(ref int maxSpeed);
    }


    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Car myCar = new Car();
            ICreateCar iCrCar = (ICreateCar)myCar;
            iCrCar.SetPetName("KOCHA");

            var iStats = (IStats)myCar;
            string name = null;
            iStats.GetPetName(ref name);
            Console.WriteLine($"name is '{name}'.");
            Console.ReadKey();
        }
    }
}
