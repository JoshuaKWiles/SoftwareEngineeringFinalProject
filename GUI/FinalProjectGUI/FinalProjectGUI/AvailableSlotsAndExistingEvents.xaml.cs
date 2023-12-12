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
    /// Interaction logic for AvailableSlotsAndExistingEvents.xaml
    /// </summary>
    public partial class AvailableSlotsAndExistingEvents : Page
    {
        List<List<string>> eventsForToday = new List<List<string>>();
        List<Border> allEntries = new List<Border>();
        string userType;
        public AvailableSlotsAndExistingEvents(List<List<string>> inputEvents, string inputUserType)
        {
            InitializeComponent();
            eventsForToday = inputEvents;
            allEntries.Add(originalBorder);
            userType = inputUserType;
        }



        private Border addNewItem(string eventName = "", int desiredRoom = 0, int desiredTime = 0)
        {
            Border board = new Border();
            allEvents.Children.Add(board);

            board.BorderThickness = new Thickness(2);
            board.BorderBrush = Brushes.Gray;
            board.Height = 114;
            board.Background = originalBorder.Background;
            
            StackPanel mainHolder = new StackPanel();
            board.Child = mainHolder;
            mainHolder.Height = 110;

            TextBox title = new TextBox();
            mainHolder.Children.Add(title);
            title.FontSize = 20;
            title.Padding = new Thickness(5, 0, 0, 0);
            title.BorderBrush = Brushes.Gray;
            title.BorderThickness = new Thickness(2);
            title.MaxLength = 35;
            title.IsReadOnly = true;

            StackPanel roomDropdown = new StackPanel();
            mainHolder.Children.Add(roomDropdown);
            roomDropdown.Orientation = Orientation.Horizontal;

            TextBlock roomLabel = new TextBlock();
            roomDropdown.Children.Add(roomLabel);
            roomLabel.FontSize = 14;
            roomLabel.FontWeight = FontWeights.Bold;

            ComboBox roomOptions = new ComboBox();
            roomDropdown.Children.Add(roomOptions);
            roomOptions.Width = 320;
            roomOptions.IsEnabled = false;
            roomOptions.IsReadOnly = true;

            string[] roomtitles = { "--Select a Room--", "Roosevelt", "Lincoln", "Washington" };

            for (int i = 0; i < roomtitles.Length; i++)
            {
                ComboBoxItem comboBoxItemGeneric = new ComboBoxItem();
                comboBoxItemGeneric.Content = roomtitles[i];
                if ((desiredRoom != -1 && i == 0) || desiredRoom == i)
                {
                    comboBoxItemGeneric.IsSelected = true;
                }
                roomOptions.Items.Add(comboBoxItemGeneric);
            }

            StackPanel timeDropdown = new StackPanel();
            mainHolder.Children.Add(timeDropdown);
            timeDropdown.Orientation = Orientation.Horizontal;

            TextBlock timeLabel = new TextBlock();
            timeDropdown.Children.Add(timeLabel);
            timeLabel.FontSize = 14;
            timeLabel.FontWeight = FontWeights.Bold;

            ComboBox timeOptions = new ComboBox();
            timeDropdown.Children.Add(timeOptions);
            timeOptions.Width = 320;
            timeOptions.IsEnabled = false;
            timeOptions.IsReadOnly = true;

            string[] timeSlots = { "--Select a Time--", "8:00 AM - 10:00 AM", "10:30 AM - 12:30 PM", "1:00 PM - 3:00 PM", "3:30 PM - 5:30 PM", "6:00 PM - 8:00 PM" };

            for (int i = 0; i < timeSlots.Length; i++)
            {
                ComboBoxItem comboBoxItemGeneric = new ComboBoxItem();
                comboBoxItemGeneric.Content = timeSlots[i];
                if ((desiredTime != -1 && i == 0) || desiredTime == i)
                {
                    comboBoxItemGeneric.IsSelected = true;
                }
                timeOptions.Items.Add(comboBoxItemGeneric);
            }

            StackPanel buttonArray = new StackPanel();
            buttonArray.Orientation = Orientation.Horizontal;
            buttonArray.Height = 30;
            mainHolder.Children.Add(buttonArray);

            Button checkin = new Button();
            checkin.Content = "Check In";
            checkin.Width = 80;
            checkin.Margin = new Thickness(10, 1, 10, 1);
            checkin.Tag = Convert.ToString(allEntries.Count());
            buttonArray.Children.Add(checkin);

            Button claimTimeslot = new Button();
            claimTimeslot.Content = "Claim Timeslot";
            claimTimeslot.Width = 120;
            claimTimeslot.Margin = new Thickness(10, 1, 10, 1);
            claimTimeslot.Tag = Convert.ToString(allEntries.Count());
            buttonArray.Children.Add(claimTimeslot);

            Button editEvent = new Button();
            editEvent.Content = "Edit Event";
            editEvent.Width = 120;
            editEvent.Margin = new Thickness(10, 1, 10, 1);
            editEvent.Tag = Convert.ToString(allEntries.Count());
            buttonArray.Children.Add(editEvent);

            if (userType == "guest")
            {
                claimTimeslot.Visibility = Visibility.Hidden;
                editEvent.Visibility = Visibility.Hidden;
            }
            else if (userType == "presenter")
            {
                editEvent.Visibility = Visibility.Hidden;
            }
            else if (userType == "employee")
            {
                checkin.Visibility = Visibility.Hidden;
            }    

            return board;
        }

    }
}
