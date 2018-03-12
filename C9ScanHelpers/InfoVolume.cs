using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C9ScanHelpers
{
    class InfoVolume
    {
        public byte[] serialNumber { get; set; }

        public string path { get; set; }

        public string label { get; set; }

        public string fileSystem { get; set; }

        // Fixed drive, removable media, optical 
        public string type { get; set; }

        public long size { get; set; }


        public long free { get; set; }

        public string comments { get; set; }

        public DateTime updated { get; set; }
    }
}
