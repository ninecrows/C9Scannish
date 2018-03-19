using C9ScanNative;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace C9Scannish
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {    
        public MainWindow()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            var cinfo = C9ScanNative.NativeAccessHelpers.VolumeInformation("C:\\");

            var files = Directory.GetFiles("e:\\ebooks", "*.*", SearchOption.AllDirectories);
            {
                var item = new TreeViewItem();
                item.Header = "Files Found";
                foreach (var file in files)
                {
                    item.Items.Add(new TreeViewItem() { Header = file.ToString() });
                }
                foundMatches.Items.Add(item);
            }

            {
                foreach (var file in files)
                {
                    // Open the file so that we can look inside it...
                    using (BinaryReader reader = new BinaryReader(File.Open(file, FileMode.Open)))
                    {
                        var information = new System.IO.FileInfo(file);
                        var fileLength = information.Length;
                        var maximumLength = (1024L * 16L);
                        long readSize = Math.Min(fileLength, maximumLength);

                        byte[] data = reader.ReadBytes((int)readSize);
                        var stream = reader.BaseStream;
                        {
                            int wherem = Array.IndexOf(data, (byte)13);
                            int wheren = Array.IndexOf(data, (byte)10);
                            int where = Math.Min(wherem, wheren);
                            if (where > 0)
                            {
                                string s = System.Text.Encoding.UTF8.GetString(data, 0, where);
                                string sa = System.Text.Encoding.ASCII.GetString(data, 0, where);
                            }
                        }

                        {
                            long chunkSize = 64;
                            if (fileLength > chunkSize)
                            {
                                stream.Seek(-chunkSize, SeekOrigin.End);
                                byte[] endData = reader.ReadBytes((int)chunkSize);
                            }
                        }
                    }

                    using (FileStream stream = File.OpenRead(file))
                    {
                        var sha = new SHA256Managed();
                        byte[] checksum = sha.ComputeHash(stream);
                        var resultHash = BitConverter.ToString(checksum).Replace("-", String.Empty);
                    }

                    using (FileStream stream = File.OpenRead(file))
                    {
                        var sha = new SHA1Managed();
                        byte[] checksum = sha.ComputeHash(stream);
                        var resultHash = BitConverter.ToString(checksum).Replace("-", String.Empty);
                    }

                    using (FileStream stream = File.OpenRead(file))
                    {
                        var sha = new SHA512Managed();
                        byte[] checksum = sha.ComputeHash(stream);
                        var resultHash = BitConverter.ToString(checksum).Replace("-", String.Empty);
                    }
                }
            }

            //var ii = new C9ScanNative.Tzpx();
            var jj = new C9ScanHelpers.GetScanResults();
            C9ScanHelpers.GetScanResults.GetSomething();
            //string result = C9ScanNative.NativeAccessHelpers.GetSomething();

            {
                var item = new TreeViewItem();
                item.Header = "Volumes";
                var names = C9ScanNative.NativeAccessHelpers.VolumeNames();
                foreach (string volumeName in names)
                {
                    // Create a node for the actual volume
                    var volumeItem = new TreeViewItem();
                    volumeItem.Header = volumeName;
                    item.Items.Add(volumeItem);

                    // Now enumerate the mount points...
                    var mounts = C9ScanNative.NativeAccessHelpers.MountNames(volumeName);
                    foreach (var mount in mounts)
                    {
                        item.Items.Add(new TreeViewItem() { Header = mount });
                    }
                }
                foundMatches.Items.Add(item);
            }

            C9ScanNative.NativeAccessHelpers.DriveNames();

            //var jjj = new NativeAccessHelpers();
            //jjj.DoSomething();

            //var aa = new C9ScanNative.

            // var tt = new C9ScanNative.Class1();
            //tt.Foo();

            //var i = new NativeAccessHelpers();


            //C9ScanNative.NativeAccessHelpers 

            //String[] vols = 
        }

        private void FilePath_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
