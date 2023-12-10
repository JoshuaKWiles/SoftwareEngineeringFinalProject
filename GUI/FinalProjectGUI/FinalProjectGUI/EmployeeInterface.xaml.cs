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
    /// Interaction logic for EmployeeInterface.xaml
    /// </summary>
    public partial class EmployeeInterface : Page
    {
        private List<Event> allEvents = new List<Event>();
        private string userType = "employee";
        public EmployeeInterface()
        {
            InitializeComponent();
        }

        private void RetrieveEventContainer()
        {
            //TODO
            //Define allEvents list
        }
        
        private void restoreDefaultButtonLabels()
        {
            //Load Event -> Close Event
            //View Schedule -> Close Schedule
        }

        private void ViewScheduleButton_Click(object sender, RoutedEventArgs e)
        {
            scheduleCalendar.Visibility = Visibility.Visible;
        }

        private void LoadEvent_Click(object sender, RoutedEventArgs e)
        {
            if (Convert.ToString(EventOpenClose.Content) == "Load Event")
            {
                eventInterface.Navigate(new EventInfo(userType, "edit"));
                EventOpenClose.Content = "Close Event";
            }
            else if(Convert.ToString(EventOpenClose.Content) == "Close Event")
            {
                eventInterface.Content = null;
                while (eventInterface.NavigationService.RemoveBackEntry() != null) ;
                EventOpenClose.Content = "Load Event";
            }
            
        }
    }
}
