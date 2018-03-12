using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C9ScanHelpers
{
    class InfoFileContents
    {
        public long fileSize { get; set; }

        public string sha256 { get; set; }

        public string sha512 { get; set; }

        public string sha1 { get; set; }

        public byte[] head { get; set; }

        public byte[] tail { get; set; }

        public string variant { get; set; }

        // File type
        public string type { get; set; }

        public bool isValid { get; set; }

        public DateTime update { get; set; }

        public string comments { get; set; }
    }
}
