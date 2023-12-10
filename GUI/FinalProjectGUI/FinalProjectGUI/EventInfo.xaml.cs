﻿using System;
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
    /// Interaction logic for EventInfo.xaml
    /// </summary>
    public partial class EventInfo : Page
    {
        public bool editing = false;
        public EventInfo(string userType, string viewOrEdit)
        {
            InitializeComponent();

            restoreDefaultVisibilities();

            if (userType == "employee")
            {
                deleteEvent.Visibility = Visibility.Visible;
                saveEvent.Visibility = Visibility.Visible;


            }
            else if (userType == "presenter" && viewOrEdit == "view")
            {
                checkIn.Visibility = Visibility.Visible;
            }
            else if (userType == "guest")
            {
                checkIn.Visibility = Visibility.Visible;
                x_EventPrice.Visibility = Visibility.Hidden;
                x_EventAdditionalInfo.Visibility = Visibility.Hidden;
            }
        }

        void restoreDefaultVisibilities()
        {
            deleteEvent.Visibility = Visibility.Hidden;
            checkIn.Visibility = Visibility.Hidden;
            saveEvent.Visibility = Visibility.Hidden;
            x_EventPrice.Visibility = Visibility.Hidden;
            x_EventAdditionalInfo.Visibility = Visibility.Hidden;
        }

        void allowOrDisableEditing(bool editingAllowed)
        {
            x_EventName.IsReadOnly = !editingAllowed;
            x_EventDate.IsReadOnly = !editingAllowed; // Risky but I'll allow it
            x_EventStatus.IsReadOnly = true; // Not editable by any, values are logically derived
            x_EventTime.IsReadOnly = true; // Should be editable, but too much room for error and not enough time to impliment properly

            //These are binary, no room for error
            whiteboardButton.IsEnabled = editingAllowed;
            projectorButton.IsEnabled = editingAllowed;
            speakerButton.IsEnabled = editingAllowed;
            microphoneButton.IsEnabled = editingAllowed;

            x_EventLocation.IsEnabled = true; // Also has potential to fuck things up
            x_EventAdditionalInfo.IsReadOnly = !editingAllowed;

        }

        bool changeColor(Rectangle rect)
        {
            if (rect.Fill == Brushes.White)
            {
                rect.Fill = Brushes.Black;
                return true;
            }
            else if (rect.Fill == Brushes.Black)
            {
                rect.Fill= Brushes.White;
                return false;
            }
            else
            {
                return false;
            }
        }

        private void whiteboardButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(WhiteboardBox);
        }

        private void projectorButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(ProjectorBox);
        }

        private void speakerButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(SpeakerBox);
        }

        private void microphoneButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(MicrophoneBox);
        }

    }
}
