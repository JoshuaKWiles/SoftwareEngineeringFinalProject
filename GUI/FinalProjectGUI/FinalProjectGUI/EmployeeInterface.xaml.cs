using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace FinalProjectGUI
{
    /// <summary>
    /// Interaction logic for EmployeeInterface.xaml
    /// </summary>
    public partial class EmployeeInterface : Page
    {
        private List<List<string>> allEvents = new List<List<string>>();
        private string userType = "employee";
        public EmployeeInterface(List<List<string>> eventData)
        {
            InitializeComponent();

            prepCalendarWithInvalidDates();
            allEvents = eventData;

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

        private void prepCalendarWithInvalidDates()
        {
            DateTime d1 = new DateTime(2023, 01, 01);
            List<DateTime> dateStart = new List<DateTime>();

            while (d1.Year == 2023 || d1.Year == 2024)
            {
                if ((d1.DayOfWeek == DayOfWeek.Saturday) ||
                    (d1.DayOfWeek == DayOfWeek.Sunday))
                    dateStart.Add(d1);
                d1 = d1.AddDays(1);
            }

            foreach (DateTime dateTime in dateStart)
            {
                scheduleCalendar.BlackoutDates.Add(new CalendarDateRange(dateTime));
            }
        }
        private void ViewScheduleButton_Click(object sender, RoutedEventArgs e)
        {
            while (eventInterface.NavigationService.RemoveBackEntry() != null) ;
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

        private void scheduleCalendar_SelectedDatesChanged(object sender, SelectionChangedEventArgs e)
        {
            var calendar = sender as Calendar;
            if (calendar.SelectedDate.HasValue)
            {
                DateTime selectedDateEvents = calendar.SelectedDate.Value;
                while (eventInterface.NavigationService.RemoveBackEntry() != null);
                List<List<string>> eventsOfDate = new List<List<string>>();
                foreach (List<string> eventInst in allEvents)
                {
                    if (eventInst[1] == selectedDateEvents.ToString("MM-dd-yyyy"))
                        eventsOfDate.Add(eventInst);
                }
                eventInterface.Navigate(new AvailableSlotsAndExistingEvents(eventsOfDate, userType));
            }
        }
    }
}
