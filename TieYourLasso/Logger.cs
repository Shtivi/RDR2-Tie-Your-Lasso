using RDR2;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TieYourLasso
{
    public static class Logger
    {
        private static string logfile { get; set; }

        public static void SetPath(string logfilePath)
        {
            logfile = logfilePath;
        }

        public static void Log(string message)
        {
            Log(logfile, message);
        }

        public static void Log(string path, string message)
        {
            File.AppendAllText(path, message + "\n");
        }
    }
}
