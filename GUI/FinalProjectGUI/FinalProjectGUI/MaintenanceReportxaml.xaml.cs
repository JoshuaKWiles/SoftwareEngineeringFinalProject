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
    /// Interaction logic for MaintenanceReportxaml.xaml
    /// </summary>
    public partial class MaintenanceReportxaml : Page
    {
        public MaintenanceReportxaml()
        {
            InitializeComponent();
        }

        private void MaintenanceOptions_Checked(object sender, RoutedEventArgs e)
        {
            if (equipmentRadio.IsChecked == true)
            {
                equipmentCombo.Visibility = Visibility.Visible;
                roomCombo.Visibility = Visibility.Hidden;
            }
            else if (roomRadio.IsChecked == true)
            {
                equipmentCombo.Visibility = Visibility.Hidden;
                roomCombo.Visibility = Visibility.Visible;
            }
            else if (facilitiesRadio.IsChecked == true)
            {
                equipmentCombo.Visibility = Visibility.Hidden;
                roomCombo.Visibility = Visibility.Hidden;
            }

            checkForEnableButtonParam();
        }

        private void userInputBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (userInputBox.Text == "Describe Grievance...")
            {
                userInputBox.Text = "";
                userInputBox.Foreground = Brushes.Black;
            }
        }

        private void userInputBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (userInputBox.Text == "")
            {
                userInputBox.Text = "Describe Grievance...";
                userInputBox.Foreground = Brushes.Gray;
            }
        }

        private void userInputBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            checkForEnableButtonParam();
        }

        void checkForEnableButtonParam()
        {
            if (userInputBox.Text != "Describe Grievance..." && userInputBox.Text != "" && userInputBox.Text.Length > 20)
            {
                if (equipmentRadio.IsChecked == true)
                {
                    if (equipmentCombo.SelectedIndex != 0)
                    {
                        submitReport.IsEnabled = true;
                    }
                    else
                    {
                        submitReport.IsEnabled = false;
                    }
                }
                else if (roomRadio.IsChecked == true)
                {
                    if (roomCombo.SelectedIndex != 0)
                    {
                        submitReport.IsEnabled = true;
                    }
                    else
                    {
                        submitReport.IsEnabled = false;
                    }
                }
                else if (facilitiesRadio.IsChecked == true)
                {
                    submitReport.IsEnabled = true;
                }
                else
                {
                    submitReport.IsEnabled = false;
                }
            }
            else
            {
                submitReport.IsEnabled = false;
            }
        }

        private void equipmentCombo_LostFocus(object sender, RoutedEventArgs e)
        {
            checkForEnableButtonParam();
        }

        private void equipmentCombo_GotFocus(object sender, RoutedEventArgs e)
        {
            checkForEnableButtonParam();
        }

        private void roomCombo_GotFocus(object sender, RoutedEventArgs e)
        {
            checkForEnableButtonParam();
        }

        private void roomCombo_LostFocus(object sender, RoutedEventArgs e)
        {
            checkForEnableButtonParam();
        }

        private void submitReport_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
