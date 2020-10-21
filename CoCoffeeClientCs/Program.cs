using System;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace CoCoffeeClientCs
{
    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("00020400-0000-0000-C000-000000000046")]
    public interface IDispatch
    {
        int GetTypeInfoCount();

        [return: MarshalAs(UnmanagedType.Interface)]
        ITypeInfo GetTypeInfo([In, MarshalAs(UnmanagedType.U4)] int iTInfo, [In, MarshalAs(UnmanagedType.U4)] int lcid);

        void GetIDsOfNames([In] ref Guid riid, [In, MarshalAs(UnmanagedType.LPArray)] string[] rgszNames,
            [In, MarshalAs(UnmanagedType.U4)] int cNames, [In, MarshalAs(UnmanagedType.U4)] int lcid,
            [Out, MarshalAs(UnmanagedType.LPArray)]
            int[] rgDispId);
    }

    [ComVisible(true), ComImport, Guid("5228FE37-5148-438A-92E1-9E93A7315FE1")]
    public class Coffee
    {
    }

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("6A60CA50-F37D-4292-A873-A98FC9ABB6BC")]
    public interface ICreate
    {
        void SetName(string Name);
        void SetMaxVolume(int maxVol);
    }

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("4E51046E-FD3E-4285-83C1-B9AAD073A7B6")]
    public interface IStats
    {
        void DisplayStats();
        void GetName(ref string Name);
    }

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("0F4ABAB8-6A05-4197-A81A-DA9C4D5187E4")]
    public interface IFilling
    {
        void Use();
        void GetMaxVolume(ref int maxVolume);
        void GetCurVolume(ref int curVolume);
    }


    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            //Car myCar = new Car();
            //ICreateCar iCrCar = (ICreateCar)myCar;
            //iCrCar.SetPetName("KOCHA");

            //var iStats = (IStats)myCar;
            //string name = null;
            //iStats.GetPetName(ref name);
            //Console.WriteLine($"name is '{name}'.");
            //Console.ReadKey();
            var type_coffee = Type.GetTypeFromProgID("CoCoffeeComp.CoCoffee");
            var coffee = Activator.CreateInstance(type_coffee);
            var pDisp = (IDispatch)coffee;
            var count_type = pDisp.GetTypeInfoCount();
            Console.WriteLine($"Type info count: {count_type}");

            var iCrCoffee = (ICreate)coffee;
            iCrCoffee.SetName("BRUH");
            var iStats = (IStats)coffee;
            string name = "";
            iStats.GetName(ref name);
            Console.WriteLine($"Name: {name}");
        }
    }
}
