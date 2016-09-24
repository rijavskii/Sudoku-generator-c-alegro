using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Windows;

namespace Sudoku_v_1._2
{
    class Program
    {
       
        static void Main(string[] args)
        {
            var form = new RenderForm("Tutorial 1: Basic Window");

        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public uint msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint time;
            public Point p;
        }

        [SuppressUnmanagedCodeSecurity]
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out Message msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);

        static bool AppStillIdle
        {
            get
            {
                Message msg;
                return !PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        public void MainLoop()
        {
            // hook the application's idle event
            Application.Idle += new EventHandler(OnApplicationIdle);
            Application.Run(form);
        }

        void OnApplicationIdle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                // Render a frame during idle time (no messages are waiting)
                RenderFrame();
            }
        }

        private void RenderFrame()
        {
            throw new NotImplementedException();
        }
    }
}
