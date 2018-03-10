using C9ScanNative;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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
            var files = Directory.GetFiles("e:\\ebooks", "*.*", SearchOption.AllDirectories);

            var item = new TreeViewItem();
            item.Header = "Files Found";
            foreach (var file in files)
            {
                item.Items.Add(new TreeViewItem() { Header = file.ToString() });
            }
            foundMatches.Items.Add(item);

            //var ii = new C9ScanNative.Tzpx();
            var jj = new C9ScanHelpers.GetScanResults();
            C9ScanHelpers.GetScanResults.GetSomething();
            string result = C9ScanNative.NativeAccessHelpers.GetSomething();
            C9ScanNative.NativeAccessHelpers.VolumeNames();
            

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
