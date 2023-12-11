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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
        }

        private void guestInterface_Click(object sender, RoutedEventArgs e)
        {
            main_frame.Visibility = Visibility.Visible;
            while (main_frame.NavigationService.RemoveBackEntry() != null) ;
            main_frame.Navigate(new GuestInterface());
        }

        private void presenterInterface_Click(object sender, RoutedEventArgs e)
        {
            main_frame.Visibility = Visibility.Visible;
            while (main_frame.NavigationService.RemoveBackEntry() != null) ;
            main_frame.Navigate(new PresenterInterface());
        }

        private void employeeInterface_Click(object sender, RoutedEventArgs e)
        {
            main_frame.Visibility = Visibility.Visible;
            while (main_frame.NavigationService.RemoveBackEntry() != null) ;
            main_frame.Navigate(new EmployeeInterface());
        }
    }
}
