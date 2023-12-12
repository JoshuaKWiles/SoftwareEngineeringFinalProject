using System;
using System.Collections.Generic;
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

namespace FinalProjectGUI
{
    /// <summary>
    /// Interaction logic for GuestInterface.xaml
    /// </summary>
    public partial class GuestInterface : Page
    {
        List<List<string>> allEvents = new List<List<string>>();
        public GuestInterface(List<List<string>> eventData)
        {
            InitializeComponent();

            allEvents = eventData;
        }

        private void reportDamages_Click(object sender, RoutedEventArgs e)
        {
            eventInterface.Navigate(new MaintenanceReportxaml());
        }
    }
}
