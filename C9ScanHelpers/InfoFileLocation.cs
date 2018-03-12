using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C9ScanHelpers
{
    public class InfoFileLocation
    {
        public string fileName { get; set; }

        public byte[] volumeSerial { get; set; }

       public byte[] fileId { get; set; }

        public DateTime created { get; set; }

        public DateTime modifed { get; set; }

        public int attributes { get; set; }

        // reparse tag and mount information?
    }
}
